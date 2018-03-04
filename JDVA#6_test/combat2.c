#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "jdvapi_basic.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"
#include "jdvapi_floppy.h"

// 13 sprites en largeur
// 4 sprites en hauteur
// des sprites de 48x50
#define TAILLE_X 13*6
//640/8
#define TAILLE_Y 200
#define TAILLE_X_SPRITE 6
#define TAILLE_Y_SPRITE 50

unsigned int *vram;



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

const unsigned char combat2_palette[]=
{
		//0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

const unsigned char intro_palette[]=
{
		//0,1,4,11,5,3,16,25,15,12,26,14,23,2,6,0
		0,4,1,11,5,16,25,26,15,3,12,14,23,2,6,0
};


void main(void)
{
	// against "so said EVELYN the modified DOG" => volatile
	volatile char layer=0;volatile char x=10;//char z=0;

	//intro en &4000
	SetupDOS();
	calque4000();
	mode(0); // à cause de la publicité ParaDOS ;)
	border(0);
	set_palette(intro_palette);
	overscanH();
	//overscan();
	//scan();
	calque4C00();
	bank0123();
	LoadFile("intro-oh.scr", (char *)0x4000);
	//LoadFile("intro-oc.scr", (char *)0x4000);
	//LoadFile("intro.scr", (char *)0x4000);
	vram=precalc_vram();
	
	bank0123();
	LoadFile("J1A.scr", (char *)0xC000); // un scr exporté "linéaire"
	bank4_4000();
	transfertEtDecoupe();

	bank0123();
	LoadFile("J1R.scr", (char *)0xC000); // un scr exporté "linéaire"
	bank5_4000();
	transfertEtDecoupe();

	bank0123();
	LoadFile("J2A.scr", (char *)0xC000); // un scr exporté "linéaire"
	bank6_4000();
	transfertEtDecoupe();

	bank0123();
	LoadFile("J2R.scr", (char *)0xC000); // un scr exporté "linéaire"
	bank7_4000();
	transfertEtDecoupe();

// et finalement.
calqueC000();
	bank0123();
	mode(2);
	border(0);
	set_palette(combat2_palette);
	scan();
	bank0123();
	LoadFile("fond2.scr", (char *)0xC000);
	// fond
	erase_frame((unsigned char *)(vram[120]+3),6*8+3,50);

	// faire une boucle qui :
	while(1){
		
	// affiche C000 pendant qu'on recopie de C000 vers 4000 la "zone de combat"
	vsync();
	calqueC000();
	bank0123();
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)

		
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
	
	}
	
}