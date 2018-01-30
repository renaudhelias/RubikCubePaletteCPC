#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "jdvapi_basic.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"
#include "jdvapi_floppy.c"

// 13 sprites en largeur
// 4 sprites en hauteur
// des sprites de 48x50
#define TAILLE_X 13*6
//640/8
#define TAILLE_Y 200
#define TAILLE_X_SPRITE 6
#define TAILLE_Y_SPRITE 50

unsigned int *vram;

const unsigned char combat_palette[]=
{
		26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void transfertEtDecoupe()
{
	unsigned int x;unsigned int y;unsigned int i;unsigned int j;unsigned char * addressFrom;unsigned char * addressTo;char n;
	n=0;
	for (i=0;i<TAILLE_X/TAILLE_X_SPRITE;i++) {
		for (j=0;j<TAILLE_Y/TAILLE_Y_SPRITE;j++) {
			for (x=0;x<TAILLE_X_SPRITE;x++) {
				for (y=0;y<TAILLE_Y_SPRITE;y++) {
					addressFrom=0xC000+y*TAILLE_X*j*TAILLE_Y_SPRITE+x+i*TAILLE_X_SPRITE;
					addressTo=0x4000+n*TAILLE_X_SPRITE*TAILLE_Y_SPRITE + y*TAILLE_X+x;
					*addressTo=*addressFrom;
				}
			}
			n++;
		}
	}
}


void main(void)
{
	char layer=0;char x=10;char z=0;
mode(2);

	calqueC000();
	printf("chargement...");
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	calque4000();
	vram=precalc_vram();
	SetupDOS();
	mode(2); // à cause de la publicité ParaDOS ;)
	calque4000(); // à cause de la publicité ParaDOS ;)

	bank0123();
	LoadFile("J1A.scr", (char *)0xC000); // un scr exporté "linéaire"
	bank4_4000();
	transfertEtDecoupe();

// 3 seconde : un flash
calqueC000();
for (x=0;x<50*3;x++){
	vsync();
}
calque4000();

	bank0123();
	LoadFile("J1R.scr", (char *)0xC000);
	bank5_4000();
	transfertEtDecoupe();

// 3 seconde : un flash
calqueC000();
for (x=0;x<50*3;x++){
	vsync();
}
calque4000();
memcpy((char *)0x4000, (char *)0xC000, 0x3FFF);
calqueC000();
put_frame((unsigned char *)(vram[0]+0),6*13,200,0x4000);
for (x=0;x<50*3;x++){
	vsync();
}
for (x=0;x<50*3;x++){
	vsync();
}
for (x=0;x<50*3;x++){
	vsync();
}
for (x=0;x<50*3;x++){
	vsync();
}

	bank0123();
	LoadFile("J2A.scr", (char *)0xC000);
	bank6_4000();
	transfertEtDecoupe();

// 3 seconde : un flash
calqueC000();
for (x=0;x<50*3;x++){
	vsync();
}
calque4000();

	bank0123();
	LoadFile("J2R.scr", (char *)0xC000);
	bank7_4000();
	transfertEtDecoupe();

	// 3 seconde : un flash
calqueC000();
for (x=0;x<50*3;x++){
	vsync();
}
calque4000();

// et finalement.
calqueC000();
	bank0123();

	mode(2);
	//while(1){}
	// faire une boucle qui :
	while(1){
	// affiche 4000 pendant qu'on pose deux sprites de 4000 vers C000
	calque4000();
	vsync();
	bank4_4000();
	x=10;
	put_frame((unsigned char *)(vram[120]+x),6,50,0x4000+((6*50)*layer));
	bank5_4000();
	put_frame((unsigned char *)(vram[120]+x+6),6,50,0x4000+((6*50)*layer));
	bank6_4000();
	put_frame((unsigned char *)(vram[120]+x+6+6),6,50,0x4000+((6*50)*layer));
	bank7_4000();
	put_frame((unsigned char *)(vram[120]+x+6+6+6),6,50,0x4000+((6*50)*layer));
	z++;
	// 21 secondes avec 50*3
	if (z>3*3) {
		layer=(layer+1)%8;
		z=0;
	}
	// affiche C000 pendant qu'on recopie de C000 vers 4000 la "zone de combat"
	calqueC000();
	vsync();
	bank0123();
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	
	}
	
}