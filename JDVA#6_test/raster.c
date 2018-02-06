#include <stdio.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_sync.h"

const unsigned char palette_noire[]=
{
		0,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const unsigned char palette0[]=
{
		26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const unsigned char palette1[]=
{
		25,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const unsigned char palette2[]=
{
		24,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const unsigned char palette3[]=
{
		23,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const unsigned char palette4[]=
{
		22,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const unsigned char palette5[]=
{
		21,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


char roulette=0;
void callback_roulette()
{
	roulette=(roulette+1)%6;
	switch(roulette) {
		case 0 :
			set_firmcolor(FIRM_COLOR_0);
		return;
		case 1 :
			set_firmcolor(FIRM_COLOR_1);
		return;
		case 2 :
			set_firmcolor(FIRM_COLOR_2);
		return;
		case 3 :
			set_firmcolor(FIRM_COLOR_3);
		return;
		case 4 :
			set_firmcolor(FIRM_COLOR_4);
		return;
		case 5 :
			set_firmcolor(FIRM_COLOR_5);
		return;
	}
}

void main(void)
{
	char z;
	mode(0);
	firmware();
	set_palette(palette_noire);
	printf("Test 1");
	// 6 interrupts per VBL
	for (z=0;z<50*3;z++) {
		vsync();
		set_palette(palette0);
		set_palette(palette1);
//		set_palette(palette2);
//		set_palette(palette3);
//		set_palette(palette4);
//		set_palette(palette5);
	}
	
	set_palette(palette_noire);
	printf("Test 2");
	raster_halt();
	
	for (z=0;z<50*3;z++) {
		vsync();
		set_firmcolor(FIRM_COLOR_0);
		halt();
		set_firmcolor(FIRM_COLOR_1);
		halt();
		set_firmcolor(FIRM_COLOR_2);
		halt();
		set_firmcolor(FIRM_COLOR_3);
		halt();
		set_firmcolor(FIRM_COLOR_4);
		halt();
		set_firmcolor(FIRM_COLOR_5);
	}
	
	
	firmware();
	set_palette(palette_noire);
	printf("Test 3");
	handle_raster(callback_roulette);
	raster();

	while(1){}


}