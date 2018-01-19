#include <stdio.h>
#include <stdlib.h>

#include "poisson.h"
#include "jdvapi_frame.h"

unsigned char *fish[12];

void mode(unsigned char m)
{
	__asm
		ld a,4(IX)
		CALL #0xBC0E
	__endasm;
}

void main(void)
{
	fish[0]=poisson1;
	fish[1]=poisson2;
	fish[2]=poisson_groupe;
	fish[3]=poisson_groupe+(6*16);
	fish[4]=poisson_groupe+((6*16)*2);
	
	
	mode(0);
	set_palette(poisson_palette);
	put_frame(vram(10,100),6,16,fish[3]);

	while(1){}
}