#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jdvapi_basic1.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"
#include "jdvapi_floppy.h"

const unsigned char palette_chat[]=
{
		5,0,18,6,0,0,0,0,0,0,0,0,0,0,0,0
};

unsigned int *vram;

char get_vsync() {
//;2	 8T	ld r,n	ld	b,#0xf5 ;; PPI port B input
//;4	12T	in r (c)	in	a,(c) ;; [4] read PPI port B input
//;2	 8T	and n	and	a, #0x01
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

// color BASIC 0
#define FIRM_COLOR_0 84
// color BASIC 1
#define FIRM_COLOR_1 68
// color BASIC 2
#define FIRM_COLOR_2 85
// color BASIC 3
#define FIRM_COLOR_3 92
// color BASIC 4
#define FIRM_COLOR_4 88 
// color BASIC 5
#define FIRM_COLOR_5 93

//void set_firmcolor(unsigned char firmColor)
void set_firmcolor(char firmColor)
{
  __asm
    ld a, 4 (ix)
	
	//ld	hl, #2+0
	//add	hl, sp
	//ld	a, (hl)
	
    ld bc, #0x7f00
    out (c), c
    out (c), a
    ld bc, #0x7f10
    out (c), c
    out (c), a
  __endasm;
}


void locate(unsigned char x,unsigned char y)
{
	__asm
		ld A,4 (IX)
		call #0xBB6F
		ld A,5 (IX)
		call #0xBB72
	__endasm;
}

// Moustache : chat de Gaston Lagaffe

unsigned char nb_vsync1[4];
unsigned char nb_vsync0[4];
unsigned char nb_vsync0_boum[4];

// chat.png
void test_vsync() {
	char i;char j;
	__asm
		DI
	__endasm;
//	put_frame((unsigned char *)(0xC000 + vram[60]+0),40,100,0x4000);
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
//;5	16T		ld HL, (nn)		ld	hl,#_nb_vsync1
//;2	 8T		ld (HL), r		ld	(hl),c
//;3	12T		jr e			jr	00101$
//donc : 31-30NOPs	116us-112us
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
//;2	 8T	ld r,n			ld	c,#0x00
//;5	16T	ld HL, (nn)		ld	hl, #_nb_vsync1 + 0
//;4	16T	ld A, (nn)		ld	b,(hl)
//;1	 4T	ld r, r'		ld	a,c
//;1	 4T	sub r			sub	a, b
//;3-2	12T-8T	jr NR, e		jr	NC,00126$
//;1	 4T		inc r			inc	c
//;3	12T	jr e			jr	00156$
//donc : 20-19NOPs	76us-72us
	nb_vsync0[0]=nb_vsync0[0]-1-2;
	while (get_vsync()==1) {}
	vsync();
	for (j=0;j<nb_vsync1[0];j++) {
		// 40 NOPs FIXME set_hsyncMinus1() à chronométrer aussi par là.
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//20
			NOP
			NOP
			NOP
		__endasm;
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 40 NOPs
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//20
			NOP
			NOP
			NOP
		__endasm;
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
		// 40 NOPs
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//20
			NOP
			NOP
			NOP
		__endasm;
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 40 NOPs
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//20
			NOP
			NOP
			NOP
		__endasm;
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
		// 40 NOPs
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//20
			NOP
			NOP
			NOP
		__endasm;
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 40 NOPs
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//20
			NOP
			NOP
			NOP
		__endasm;
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
		// 40 NOPs
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
		__endasm;
	} // VSYNC1
	for (j=0;j<nb_vsync0[0];j++) {
		// 40 NOPs
		__asm
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//10
			NOP
			NOP
			NOP
			NOP
			NOP
			
			NOP
			NOP
			NOP
			NOP
			NOP
			//20
			NOP
			NOP
			NOP
		__endasm;
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
//	check_controller();
//	while (!get_key(Key_Space)) {check_controller();}
//	while (get_key(Key_Space )) {check_controller();}
	__asm
		EI
	__endasm;
}


char no_int=0;
unsigned int count_int[40];

void callback_roulette(unsigned char roulette)
{
	if (no_int<10) {
		no_int++;
	}
}

void callback_rouletteNOP(unsigned char roulette)
{
	__asm
		NOP
	__endasm;
	if (no_int<20) {
		no_int++;
	}
}

void callback_rouletteNOPNOP(unsigned char roulette)
{
	__asm
		NOP
		NOP
	__endasm;
	if (no_int<30) {
		no_int++;
	}
}

void callback_rouletteNOPNOPNOP(unsigned char roulette)
{
	__asm
		NOP
		NOP
		NOP
	__endasm;
	if (no_int<40) {
		no_int++;
		count_int[no_int]=0;
	}
}

// chat-venére-gaston.jpg
void test_int() {
	char i;
	put_frame_transparent((unsigned char *)(0xC000 + vram[0]+30),50,200,0x5000);
	//2) VSYNC+INT :
	//VSYNC : sert juste à synchro le démarrage du tout
	//INT : change curseur d'un tableau (un pointeur)
	//sinon : incrémenter la valeur du tableau ciblé
	//si INT nb>10, stopper.
	no_int=0;
	count_int[0]=0;
	while (get_vsync()==1) {}
	vsync();
	handle_raster(callback_roulette);
	raster();
	while (no_int<10) {
		count_int[no_int]++;
	}
	while (get_vsync()==1) {}
	vsync();
	no_int=10;
	handle_raster(callback_rouletteNOP);
	raster();
	while (no_int<20) {
		count_int[no_int]++;
	}
	while (get_vsync()==1) {}
	vsync();
	no_int=20;
	handle_raster(callback_rouletteNOPNOP);
	raster();
	while (no_int<30) {
		count_int[no_int]++;
	}
	while (get_vsync()==1) {}
	vsync();
	no_int=30;
	handle_raster(callback_rouletteNOPNOPNOP);
	raster();
	while (no_int<40) {
		count_int[no_int]++;
	}
	while (get_vsync()==1) {}
	vsync();
	printf("            \r\n");
	printf("            \r\n");
	for(i=0;i<10;i++) {
		printf("%h2u:%3u,%3u,%3u,%3u.\r\n",i,count_int[i],count_int[i+10],count_int[i+20],count_int[i+30]);
	}
	
//	check_controller();
//	while (!get_key(Key_Space)) {check_controller();}
//	while (get_key(Key_Space )) {check_controller();}
}

void set_firmcolor1()
{
  __asm
	ld A,#0x5D
    ld bc, #0x7f00
    out (c), c
    out (c), a
    ld bc, #0x7f10
    out (c), c
    out (c), a
  __endasm;
}

void set_firmcolor2()
{
  __asm
	ld A,#0x54
    ld bc, #0x7f00
    out (c), c
    out (c), a
    ld bc, #0x7f10
    out (c), c
    out (c), a
  __endasm;
}

void callback_roulette2(unsigned char roulette)
{
	//set_firmcolor(FIRM_COLOR_0);
	set_firmcolor2();
	__asm
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
	__endasm;
	//set_firmcolor(FIRM_COLOR_5);
	set_firmcolor1();
}

// chat_gaston-prudent.png
void test_palette() {
	bank0123();
	put_frame_transparent((unsigned char *)(0xC000 + vram[148]+20),40,48,0x7800);
	//3) raster palette
	while (get_vsync()==1) {}
	vsync();
	handle_raster(callback_roulette2);
	raster();
}

void main() {
	vram=precalc_vram();
	SetupDOS();
	mode(1);// à cause de la publicité ParaDOS ;)
	border(5);
	set_palette(palette_chat);
//	LoadFile("chat1.scr", (char *)0x4000);
	LoadFile("chat2.scr", (char *)0x5000);
	LoadFile("chat3.scr", (char *)0x7800);
	test_vsync();
	test_int();
	printf("\r\n\r\n\r\n V0.0c3");
	test_palette();
	while(1) {} // keyboard scan does perturbate raster palette, so no keyb by here :p
}