char get_vsync() {
//;2	 8T		ld r,n		ld	b,#0xf5 ;; PPI port B input
//;4	12T		in r (c)	in	a,(c) ;; [4] read PPI port B input
//;2	 8T		and n		and	a, #0x01
//;1	 4T		ld r, r'	ld	l,a
//;3	12T		ret			ret
//donc 12NOPs	44us

	__asm
		ld b,#0xf5            ;; PPI port B input
		in a,(c)            ;; [4] read PPI port B input
		and	a, #0x01
		ld	l,a
	__endasm;
}

void set_hsyncOriginal() {
	__asm
		//r2=46	Horizontal Sync Position
		ld bc,#0xbc02
		out (c),c
		ld bc,#0xbd00+46
		out (c),c
	__endasm;
}
void set_hsyncMinus1() {
//;5	20T		call nn		call	_set_hsyncMinus1
//;3	12T		ld dd, nn	ld	bc,#0xbc02
//;4	12T		out (c), r	out	(c),c
//;3	12T		ld dd, nn	ld	bc,#0xbd00+45
//;4	12T		out (c), r	out	(c),c
//;3	12T		ret			ret
//donc : 22Nops	80us	=>	nb_vsync0[0]=nb_vsync0[0]-1-2;//2*76us<80us
	
	__asm
		//r7=45	Vertical Sync position
		ld bc,#0xbc02
		out (c),c
		ld bc,#0xbd00+45
		out (c),c
	__endasm;
}

unsigned char nb_vsync1[4];
unsigned char nb_vsync0[4];
unsigned char nb_vsync0_boum[4];

// chat.png
void test_vsync() {
	char i;char j;
	__asm
		DI
	__endasm;
	//1) VSYNC : mesurer (détecter le passage de 1 à 0 et de 0 à 1, compter  trouver un moyen d'offset un certain nombre de NOP au début.
	//genre 5 6, 5 6, 6 7, 6 7, 6 7
	//mettre les différents résultats dans un tableau, comme ça on affiche un rapport à la fin.
	//VSYNC détecter un changement d'offset, lorsqu'on maj VSYNC juste au dernier moment (just in time, juste avant la fin (ou sinon juste au début si c'est pas bon, en fait qu'est ce que ça change ? on détecte un changement de comportement à partir d'un certain moment (entre deux VSYNC en lecture...)
	nb_vsync1[0]=0;
	nb_vsync0[0]=0;
	nb_vsync0_boum[0]=0;
	nb_vsync1[1]=0;
	nb_vsync0[1]=0;
	nb_vsync0_boum[1]=0;
	nb_vsync1[2]=0;
	nb_vsync0[2]=0;
	nb_vsync0_boum[2]=0;
	nb_vsync1[3]=0;
	nb_vsync0[3]=0;
	nb_vsync0_boum[3]=0;
	while (get_vsync()==1) {}
	vsync();
//;moustache.c:94: while (get_vsync()==1) {
//;5	20T		call nn			call	_get_vsync
//;1	 4T		dec r			dec	l
//;3-2	12T-8T	jr NZ, e		jr	NZ,00104$
//;4	16T		ld A, (nn)		ld	a,(#_nb_vsync1 + 0)
//;6	20T		ld (IX+D), r	ld	-1 (ix), a
//;1	 4T		ld r, r'		ld	c, a
//;1	 4T		inc r			inc	c
//;3	12T		ld dd, nn		ld	hl,#_nb_vsync1
//;2	 8T		ld (HL), r		ld	(hl),c
//;3	12T		jr e			jr	00101$
//donc : 29-28NOPs	112us-108us
	while (get_vsync()==1) {
		nb_vsync1[0]++;
	}
	while (get_vsync()==0) {
		nb_vsync0[0]++;
	}
	while (get_vsync()==1) {}
	vsync();
	__asm
		NOP
	__endasm;
	while (get_vsync()==1) {
		nb_vsync1[1]++;
	}
	while (get_vsync()==0) {
		nb_vsync0[1]++;
	}
	while (get_vsync()==1) {}
	vsync();
	__asm
		NOP
		NOP
	__endasm;
	while (get_vsync()==1) {
		nb_vsync1[2]++;
	}
	while (get_vsync()==0) {
		nb_vsync0[2]++;
	}
	while (get_vsync()==1) {}
	vsync();
	__asm
		NOP
		NOP
		NOP
	__endasm;
	while (get_vsync()==1) {
		nb_vsync1[3]++;
	}
	while (get_vsync()==0) {
		nb_vsync0[3]++;
	}
	for(i=0;i<4;i++) {
		// %u for unsigned int, %hu for unsigned char
		printf("%hu VS1:%hu VS0:%hu.\r\n",i,nb_vsync1[i],nb_vsync0[i]);
	}
	// dérapage
//;moustache.c:140: for (j=0;j<nb_vsync1[0];j++) {} // VSYNC1
// http://www.cpc-power.com/cpcarchives/index.php?page=articles&num=65
//;2	 8T		ld r,n		ld	c,#0x00
//;3	12T		ld dd, nn	ld	hl, #_nb_vsync1 + 0
//;4	16T		ld A, (nn)	ld	b,(hl)
//;1	 4T		ld r, r'	ld	a,c
//;1	 4T		sub r		sub	a, b
//;3-2	12T-8T	jr NR, e	jr	NC,00126$
//;1	 4T		inc r		inc	c
//;3	12T		jr e		jr	00156$
//donc : 18-17NOPs	72us-68us
	nb_vsync0[0]=nb_vsync0[0]-1-2;
	while (get_vsync()==1) {}
	vsync();
	for (j=0;j<nb_vsync1[0];j++) {
		// 23 NOPs FIXME set_hsyncMinus1() à chronométrer aussi par là.
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 23 NOPs
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC0
	set_hsyncMinus1();
	while (get_vsync()==0) {
		nb_vsync0_boum[0]++;
	}
	set_hsyncOriginal();
	while (get_vsync()==1) {}
	vsync();
	__asm
		NOP
	__endasm;
	for (j=0;j<nb_vsync1[0];j++) {
		// 23 NOPs
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 23 NOPs
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC0
	set_hsyncMinus1();
	while (get_vsync()==0) {
		nb_vsync0_boum[1]++;
	}
	set_hsyncOriginal();
	while (get_vsync()==1) {}
	vsync();
	__asm
		NOP
		NOP
	__endasm;
	for (j=0;j<nb_vsync1[0];j++) {
		// 23 NOPs
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 23 NOPs
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC0
	set_hsyncMinus1();
	while (get_vsync()==0) {
		nb_vsync0_boum[2]++;
	}
	set_hsyncOriginal();
	while (get_vsync()==1) {}
	vsync();
	__asm
		NOP
		NOP
		NOP
	__endasm;
	for (j=0;j<nb_vsync1[0];j++) {
		// 23 NOPs
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 23 NOPs
		__asm__("NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\nNOP\nNOP\n NOP\nNOP\nNOP\n");
	} // VSYNC0
	set_hsyncMinus1();
	while (get_vsync()==0) {
		nb_vsync0_boum[3]++;
	}
	set_hsyncOriginal();
	while (get_vsync()==1) {}
	vsync();
	for(i=0;i<4;i++) {
		printf("BOUM%hu:%hu.\r\n",i,nb_vsync0_boum[i]);
	}
	__asm
		EI
	__endasm;
}
