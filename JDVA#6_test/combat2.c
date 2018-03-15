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


void cpct_akp_musicInit()
{
	__asm
	;; backup Z80 state
  push af
  push bc
  push de
  push hl
  push ix
  push iy
  exx
  ex af, af'
  push af
  push bc
  push de
  push hl
  
	; sks2000.bin/exemple.asm
	ld de,#0x3000
	call #0x2000
	
	;; restore Z80 state
  pop hl
  pop de
  pop bc
  pop af
  ex af, af'
  exx
  pop iy
  pop ix
  pop hl
  pop de
  pop bc
  pop af
	__endasm;
}

void cpct_akp_musicPlay()
{
	__asm
	;; backup Z80 state
  push af
  push bc
  push de
  push hl
  push ix
  push iy
  exx
  ex af, af'
  push af
  push bc
  push de
  push hl
	
	; sks2000.bin/exemple.asm
	call #0x2003
	
	;; restore Z80 state
  pop hl
  pop de
  pop bc
  pop af
  ex af, af'
  exx
  pop iy
  pop ix
  pop hl
  pop de
  pop bc
  pop af
	__endasm;
}

/*
void border_raster_begin()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set a white raster in the BORDER to "see" how much
	; CPU time the player takes.
	ld bc,#0x7F10
	out (c),c
	ld c,#0x4B
	out (c),c
  __endasm;
}

void border_raster_begin2()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set the BORDER to un peu de violet...
	ld bc,#0x7F5D
	out (c),c
  __endasm;
}

void border_raster_end()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set the BORDER to black
	ld bc,#0x7F54
	out (c),c
  __endasm;
}
*/

unsigned int is_vsync;

void callback_roulette(unsigned char roulette)
{
	if (roulette==0) {
		//border_raster_begin();
		
		// Play the STarKos song
		cpct_akp_musicPlay();
		
		//border_raster_begin2();
		
		is_vsync=1;
	}
	return;
}


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

typedef struct {
	char o; // offset
	char l; // longueur
} CALQUE;

struct CALQUE_J1A {
	CALQUE marcher; // cyclique, avance, recule
	CALQUE haut;
	CALQUE bas;
	CALQUE tres_haut;
	CALQUE pied_haut; // allez-retour
	CALQUE pied_milieu; // allez-retour
	CALQUE genoux_milieu; // allez-retour
	CALQUE pied_haut2; // cyclique, porté en 3/5
	CALQUE balayette; // cyclique, porté en 3/4 + avance
	CALQUE hypercut; // cyclique (sinon ridicule...)
	CALQUE poing_milieu; // allez-retour
	CALQUE pied_milieu2; // allez-retour
	CALQUE balayette2; // cyclique + avance
	CALQUE pied_rotatif; // cyclique + avance !
} ;

// J1A.adresse : bank4_4000();
static const struct CALQUE_J1A J1A= {
	.marcher={0,9},
	.haut={9,1},
	.bas={10,1},
	.tres_haut={11,1},
	.pied_haut={12,4},
	.pied_milieu={16,4},
	.genoux_milieu={20,2},
	.pied_haut2={22,5},
	.balayette={27,4},
	.hypercut={31,5},
	.poing_milieu={36,2},
	.pied_milieu2={38,2},
	.balayette2={40,3},
	.pied_rotatif={43,9}
};

struct CALQUE_J1R {
	CALQUE victory; // cyclique
	CALQUE fatality; // statique (stoppé au 3)
	CALQUE hypercut2; // cyclique (sinon ridicule...)
	CALQUE hadouken_personnage; // statique (stoppé au 4), la boule de feu affiché ensuite juste à droite du sprite, collée.
	CALQUE hadouken_fire; // cyclique
	CALQUE ko; // cyclique
	CALQUE poing_double_jab; // cyclique, porté en 2/5 et 5/5
	CALQUE contre_haut; // allez-retour
	CALQUE macarena_milieu; // cyclique, porté en 2/5 et 5/5
	CALQUE dragon; // statique, enchaine avec dragon_big
	CALQUE dragon_big; // une seule image mais deux sprites !
	CALQUE contre_haut2; // allez-retour
};

// J1R.adresse : bank5_4000();
static const struct CALQUE_J1R J1R= {
	.victory={0,6},
	.fatality={6,3},
	.hypercut2={9,4},
	.hadouken_personnage={13,4},
	.hadouken_fire={17,9},
	.ko={26,6},
	.poing_double_jab={32,5},
	.contre_haut={37,2},
	.macarena_milieu={39,5},
	.dragon={44,3},
	.dragon_big={47,2},
	.contre_haut2={49,2}
};

struct CALQUE_J2A {
	CALQUE pied_haut; // cyclique, porté en 4/8
	CALQUE pied_haut2; // allez-retour inversé : porté en 1/3 ...
	CALQUE genoux_haut; // allez-retour
	CALQUE pied_retourne; // cyclique, porté en 4/7
	CALQUE balayette; // cyclique, porté en 3/4
	CALQUE marcher; // cyclique, avance, recule
	CALQUE haut;
	CALQUE bas;
	CALQUE zombi;
	CALQUE victory; // allez-retour ;)
	CALQUE poing_double_jab; // cyclique porté en 3/8 et 6/8
	CALQUE aie;
	CALQUE poing_gauche; // allez-retour
};

// J2A.adresse : bank6_4000();
static const struct CALQUE_J2A J2A= {
	.pied_haut={0,8},
	.pied_haut2={8,3},
	.genoux_haut={11,2},
	.pied_retourne={13,7},
	.balayette={20,4},
	.marcher={24,10},
	.haut={34,1},
	.bas={35,1},
	.zombi={36,1},
	.victory={27,2},
	.poing_double_jab={28,8},
	.aie={36,1},
	.poing_gauche={37,3}
};

struct CALQUE_J2R{
	CALQUE poing_droit; // allez-retour
	CALQUE ko; // cyclique
	CALQUE fatality; // statique (stoppé au 5)
	CALQUE hadouken1_personnage; // statique (stoppé au 10), la boule de feu affiché ensuite juste à droite du sprite, collée.
	CALQUE hadouken1_fire; // boule de neige
	CALQUE hadouken2_personnage; // 1 2 3
	CALQUE hadouken2_fire; // mega fire
	CALQUE hadouken2_personnage_patch; // p3 p1 p2 1 2 3
	CALQUE hypercut; // cyclique porté en 3/5
	CALQUE coup_bas; // allez-retour
	CALQUE flaque; //cyclique
};

// J2R.adresse : bank7_4000();
static const struct CALQUE_J2R J2R= {
	.poing_droit={0,2},
	.ko={2,5},
	.fatality={7,5},
	.hadouken1_personnage={12,10},
	.hadouken1_fire={22,1},
	.hadouken2_personnage={23,3},
	.hadouken2_fire={26,9},
	.hadouken2_personnage_patch={35,3},
	.hypercut={38,5},
	.coup_bas={43,2},
	.flaque={45,7}
};

void main(void)
{
	// against "so said EVELYN the modified DOG" => volatile
	volatile char layer=0;volatile char x=10;//char z=0;
	volatile char aaah=3;

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
	LoadFile("sks2000.bin", (char *)0x2000);
	LoadFile("sudo3000.bin", (char *)0x3000);
	vram=precalc_vram();
	
	bank0123();
	LoadFile("J1A.scr", (char *)0xC000); // un scr exporté "linéaire"
	bank4_4000();
	transfertEtDecoupe();

	bank0123();
	LoadFile("J1R.scr", (char *)0xC000); // un scr exporté "linéaire"
	bank5_4000();
	transfertEtDecoupe();

	//if (J2R.hadouken2_personnage_patch.l == aaah) { // volatiles... sucks ?
	if (J2R.hadouken2_personnage_patch.l == 3) {
		bank0123();
		LoadFile("J2A.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank6_4000();
		transfertEtDecoupe();
		
		bank0123();
		LoadFile("J2R.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank7_4000();
		transfertEtDecoupe();
	}

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

	vsync();
	handle_raster(callback_roulette);
	raster();
	
	// cpctelera-1.4.2/examples/medium/arkosAudio
	cpct_akp_musicInit(); //(void *)0x4000);

	// faire une boucle qui :
	while(1){
		
	// affiche C000 pendant qu'on recopie de C000 vers 4000 la "zone de combat"
	if (is_vsync==0) {}
	is_vsync=0;

	calqueC000();
	bank0123();
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	
	//border_raster_end();
		
	// affiche 4000 pendant qu'on pose deux sprites de 4000 vers C000
	if (is_vsync==0) {}
	is_vsync=0;

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
	
	//border_raster_end();
	}
	
}