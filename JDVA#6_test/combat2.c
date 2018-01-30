#include <stdio.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"
#include "jdvapi_floppy.h"

// 13 sprites en largeur
// 4 sprites en hauteur
// des sprites de 48x50
#define TAILLE_X 640/8
#define TAILLE_Y 400
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
	char layer=0;
	// charger les fichiers mais avec réorganisation (paramètre tailleX tailleY tailleXsprite tailleYsprite) en &4000 en ayant choisi la bonne zone mémoire
	SetupDOS();
	
	calqueC000();
	printf("chargement...");
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	calque4000();
	
	bank4_4000();
	LoadFile("J1A.sli", (char *)0xC000); // un scr exporté "linéaire"
	transfertEtDecoupe();
	bank5_4000();
	LoadFile("J1R.sli", (char *)0xC000);
	transfertEtDecoupe();
	bank6_4000();
	LoadFile("J2A.sli", (char *)0xC000);
	transfertEtDecoupe();
	bank7_4000();
	LoadFile("J2R.sli", (char *)0xC000);
	transfertEtDecoupe();

	vram=precalc_vram();
	
	// faire une boucle qui :
	while(1){
	// affiche 4000 pendant qu'on pose deux sprites de 4000 vers C000
	calque4000();
	vsync();
	bank4_4000();
	put_frame((unsigned char *)(vram[120]+x),6,50,0x4000+((6*50)*layer));
	bank5_4000();
	put_frame((unsigned char *)(vram[120]+x+6),6,50,0x4000+((6*50)*layer));
	bank6_4000();
	put_frame((unsigned char *)(vram[120]+x+6+6),6,50,0x4000+((6*50)*layer));
	bank7_4000();
	put_frame((unsigned char *)(vram[120]+x+6+6+6),6,50,0x4000+((6*50)*layer));
	layer=(layer+1)%8;
	// affiche C000 pendant qu'on recopie de C000 vers 4000 la "zone de combat"
	calqueC000();
	vsync();
	bank0123();
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	
	}
	
}