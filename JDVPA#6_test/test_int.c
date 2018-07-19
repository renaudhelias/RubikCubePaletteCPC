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
