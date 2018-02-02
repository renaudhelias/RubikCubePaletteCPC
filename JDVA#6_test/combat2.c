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
	for (j=0;j<TAILLE_Y/TAILLE_Y_SPRITE;j++) {
		for (i=0;i<TAILLE_X/TAILLE_X_SPRITE;i++) {
			for (x=0;x<TAILLE_X_SPRITE;x++) {
				for (y=0;y<TAILLE_Y_SPRITE;y++) {
					addressFrom=0xC000+y*TAILLE_X +j*TAILLE_X*TAILLE_Y_SPRITE+x+i*TAILLE_X_SPRITE;
					addressTo=0x4000+n*TAILLE_X_SPRITE*TAILLE_Y_SPRITE + y*TAILLE_X_SPRITE+x;
					*addressTo=*addressFrom;
				}
			}
			n++;
		}
	}
}


void main(void)
{
	// against "so said EVELYN the modified DOG" => volatile
	volatile char layer=0;volatile char x=10;//char z=0;
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
calque4000();bank0123();
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
	LoadFile("J1R.scr", (char *)0xC000);
	bank5_4000();
	transfertEtDecoupe();

// 3 seconde : un flash
calqueC000();
for (x=0;x<50*3;x++){
	vsync();
}
calque4000();bank0123();
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
calque4000();bank0123();
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
	LoadFile("J2R.scr", (char *)0xC000);
	bank7_4000();
	transfertEtDecoupe();

	// 3 seconde : un flash
calqueC000();
for (x=0;x<50*3;x++){
	vsync();
}
calque4000();bank0123();
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

// et finalement.
calqueC000();
	bank0123();

	mode(2);
	
	bank0123();
	LoadFile("fond2.scr", (char *)0xC000);
//	x=10;
	// fond
	erase_frame((unsigned char *)(vram[120]+3),6*7+3,50);
//	//debut
//	erase_frame((unsigned char *)(vram[120]+5),6,50);
//	// avant droite 1
//	erase_frame((unsigned char *)(vram[120]+x+6+6+6+6),3,50);
//	// avant milieu 1
//	erase_frame((unsigned char *)(vram[120]+x+6+3+1),2,50);
//	//fin
//	erase_frame((unsigned char *)(vram[120]+x+6+6+6+6+6+3+6),6,50);

	//while(1){}
	// faire une boucle qui :
	while(1){
	// affiche 4000 pendant qu'on pose deux sprites de 4000 vers C000
	vsync();
	calque4000();
	bank4_4000();
	x=7;
	// gauche 1
	put_frame((unsigned char *)(vram[120]+x),6,50,0x4000+((6*50)*layer));
	// droite 1
	put_frame((unsigned char *)(vram[120]+x+6+6+6+6+3),6,50,0x4000+((6*50)*layer));
	bank6_4000();
	// gauche 2
	erase_frame((unsigned char *)(vram[120]+x+6),4,50);
	put_frame_transparent((unsigned char *)(vram[120]+x+3+1),6,50,0x4000+((6*50)*layer));
	// droite 2
	put_frame((unsigned char *)(vram[120]+x+6+6+6+6+6+3),6,50,0x4000+((6*50)*layer));
	bank5_4000();
	// milieu 1
	put_frame((unsigned char *)(vram[120]+x+6+6),6,50,0x4000+((6*50)*layer));
	bank7_4000();
	// milieu 2
	put_frame((unsigned char *)(vram[120]+x+6+6+6),6,50,0x4000+((6*50)*layer));
	//z++;
	// 21 secondes avec 50*3
	//if (z>3) {
		layer=(layer+1)%(13*4);
		//z=0;
	//}
	// affiche C000 pendant qu'on recopie de C000 vers 4000 la "zone de combat"
	vsync();
	calqueC000();
	bank0123();
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	
	}
	
}