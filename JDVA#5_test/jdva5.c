#include <stdio.h>
#include <stdlib.h>
// set_palette, put_frame
#include "jdvapi_frame.h"

#define	vram(nX,nY) (unsigned char *)(0xC000 + ((nY / 8u) * 80u) + ((nY % 8u) * 2048u) + nX)

extern const unsigned char palette[];
extern const unsigned char poisson1[];
extern const unsigned char poisson2[];
extern const unsigned char poisson_groupe[];


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
	set_palette(palette);
	put_frame(vram(10,100),6,16,fish[3]);

	while(1){}
}