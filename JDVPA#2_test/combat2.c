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


unsigned int is_vsync;

void callback_roulette(unsigned char roulette)
{
	if (roulette==1) {
		// 5 0 1 : deux interruptions après la musique (afin d'atterrir en dehors de l'écran, en bas)
		is_vsync=1;
	} else if (roulette==5) {
		border_raster_begin();
		
		// Play the STarKos song
		cpct_akp_musicPlay();
		
		border_raster_begin2();
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
	char p; // porte le coup
	char b; // bank
	char ar; // allez_retour
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

#define PORTE_EN_1 1
#define PORTE_EN_2 2
#define PORTE_EN_3 4
#define PORTE_EN_4 8
#define PORTE_EN_5 16
#define PORTE_EN_6 32
#define PORTE_EN_7 64
#define PORTE_EN_8 128


#define BANK_4 4
#define BANK_5 5
#define BANK_6 6
#define BANK_7 7

#define ALLEZ 1
#define RETOUR 2
#define MARCHE 4
#define VERS_L_AVANT 8
#define VERS_L_ARRIERE 16

// J1A.adresse : bank4_4000();
const struct CALQUE_J1A J1A= {
	.marcher={0,9,0,BANK_4,MARCHE},
	.haut={9,1,0,BANK_4,0},
	.bas={10,1,0,BANK_4,0},
	.tres_haut={11,1,0,BANK_4,0},
	.pied_haut={12,4,PORTE_EN_4,BANK_4,0},
	.pied_milieu={16,4,PORTE_EN_4,BANK_4,0},
	.genoux_milieu={20,2,PORTE_EN_2,BANK_4,0},
	.pied_haut2={22,5,PORTE_EN_3,BANK_4,0},
	.balayette={27,4,PORTE_EN_3,BANK_4,0},
	.hypercut={31,5,PORTE_EN_5,BANK_4,0},
	.poing_milieu={36,2,PORTE_EN_2,BANK_4,0},
	.pied_milieu2={38,2,PORTE_EN_2,BANK_4,0},
	.balayette2={40,3,PORTE_EN_3,BANK_4,0},
	.pied_rotatif={43,9,PORTE_EN_4 | PORTE_EN_5 | PORTE_EN_6 | PORTE_EN_7 | PORTE_EN_8,BANK_4,MARCHE}
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
const struct CALQUE_J1R J1R= {
	.victory={0,6,0,BANK_5,0},
	.fatality={6,3,0,BANK_5,0},
	.hypercut2={9,4,PORTE_EN_4,BANK_5,0},
	.hadouken_personnage={13,4,0,BANK_5,0},
	.hadouken_fire={17,9,0,BANK_5,0},
	.ko={26,6,0,BANK_5,0},
	.poing_double_jab={32,5,PORTE_EN_2 | PORTE_EN_5,BANK_5,0},
	.contre_haut={37,2,PORTE_EN_2,BANK_5,0},
	.macarena_milieu={39,5,PORTE_EN_2 | PORTE_EN_5,BANK_5,0},
	.dragon={44,3,0,BANK_5,0},
	.dragon_big={47,2,0,BANK_5,0},
	.contre_haut2={49,2,PORTE_EN_2,BANK_5,0}
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
const struct CALQUE_J2A J2A= {
	.pied_haut={0,8,PORTE_EN_4,BANK_6,0},
	.pied_haut2={8,3,PORTE_EN_1,BANK_6,0},
	.genoux_haut={11,2,PORTE_EN_2,BANK_6,0},
	.pied_retourne={13,7,PORTE_EN_4,BANK_6,0},
	.balayette={20,4,PORTE_EN_3,BANK_6,0},
	.marcher={24,10,0,BANK_6,MARCHE},
	.haut={34,1,0,BANK_6,0},
	.bas={35,1,0,BANK_6,0},
	.zombi={36,1,0,BANK_6,0},
	.victory={27,2,0,BANK_6,0},
	.poing_double_jab={28,8,PORTE_EN_3 | PORTE_EN_6,BANK_6,0},
	.aie={36,1,0,BANK_6,0},
	.poing_gauche={37,3,PORTE_EN_3,BANK_6,0}
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
const struct CALQUE_J2R J2R= {
	.poing_droit={0,2,PORTE_EN_2,BANK_7,0},
	.ko={2,5,0,BANK_7,0},
	.fatality={7,5,0,BANK_7,0},
	.hadouken1_personnage={12,10,0,BANK_7,0},
	.hadouken1_fire={22,1,0,BANK_7,0},
	.hadouken2_personnage={23,3,0,BANK_7,0},
	.hadouken2_fire={26,9,0,BANK_7,0},
	.hadouken2_personnage_patch={35,3,0,BANK_7,0},
	.hypercut={38,5,PORTE_EN_3,BANK_7,0},
	.coup_bas={43,2,PORTE_EN_2,BANK_7,0},
	.flaque={45,7,0,BANK_7,0}
};

#define PERSO_LIU_KANG 0
#define PERSO_SUB_ZERO 1

typedef struct {
	char perso; // identifiant du jouer
	char direction;
	CALQUE animation;
	char anim_restant; // decompte un CALQUE.l
	char allez_retour; // si ALLEZ ou RETOUR, decompte aussi un allez-retour de l'anim (ALLEZ, puis RETOUR, puis 0)
	char bank; // la bank mémoire de l'animation en cours
	char x;char old_x;
} ANIMATION;

#define DIRECTION_DROITE 1
#define DIRECTION_GAUCHE 2
#define DIRECTION_HAUT 4
#define DIRECTION_BAS 8
#define DIRECTION_FIRE 16

ANIMATION liu_kang;
ANIMATION sub_zero;

#define DEPLACEMENT_AVANCE 1
#define DEPLACEMENT_RECULE 2
#define DEPLACEMENT_AUCUNE 3

CALQUE * mapping_direction_calque[2][1+DIRECTION_DROITE+DIRECTION_GAUCHE+DIRECTION_HAUT+DIRECTION_BAS+DIRECTION_FIRE];

void action(ANIMATION * joueur, char direction_pressed) {
	char deplacement=0;

	joueur->old_x=joueur->x;
	
	// FIXME : si je MARCHE, alors je peux lancer une nouvelle action.
	// en fait quand tu attend, tu MARCHE sur place entre deux états (d'un air menaçant)
	if (joueur->allez_retour == ALLEZ || (joueur->allez_retour!=RETOUR && joueur->anim_restant > 0)) {
		// une animation ALLEZ est en cours
		if ((joueur->allez_retour | VERS_L_AVANT) != 0 || (joueur->allez_retour | VERS_L_AVANT) != 0 ) {
			// déplacement
			if ((joueur->direction & DIRECTION_DROITE) != 0) {
				// le joueur va a droite
				joueur->x = joueur->x + 1;
				if (joueur->x > 48) {
					joueur->x=3;
				}
			}
			if ((joueur->direction & DIRECTION_GAUCHE) != 0) {
				// le joueur va a gauche
				joueur->x = joueur->x - 1;
				if (joueur->x < 3) {
					joueur->x=48;
				}
			}
		}
		if (joueur->anim_restant > 0) {
			joueur->anim_restant = joueur->anim_restant -1;
			// FIXME patch pour zapper un calque sur deux lors de l'animation marcher.
			if (joueur->anim_restant > 0) joueur->anim_restant = joueur->anim_restant -1;
			if (joueur->anim_restant == 0 && joueur->allez_retour==ALLEZ) {
				joueur->anim_restant = joueur->animation.l;
				joueur->allez_retour = RETOUR;
			}
		}
	} else if (joueur->allez_retour == RETOUR) {
		// une animation RETOUR est en cours
		if (joueur->anim_restant > 0) {
			joueur->anim_restant = joueur->anim_restant -1;
			// FIXME patch pour zapper un calque sur deux lors de l'animation marcher.
			if (joueur->anim_restant > 0) joueur->anim_restant = joueur->anim_restant -1;
			if (joueur->anim_restant == 0) {
				joueur->allez_retour = 0;
			}
		}
	} else {
		
		// déclanchement d'une nouvelle animation
		joueur->direction=direction_pressed;
		if (((joueur->direction & DIRECTION_DROITE) != 0) && ((joueur->direction & DIRECTION_GAUCHE) != 0)) {
			// un idiot
			deplacement = DEPLACEMENT_AUCUNE;
		} else if ((joueur->direction & DIRECTION_DROITE) != 0) {
			if (joueur->perso==PERSO_LIU_KANG) {
				deplacement = DEPLACEMENT_AVANCE;
			} else {
				deplacement = DEPLACEMENT_RECULE;
			}
		} else if ((joueur->direction & DIRECTION_GAUCHE) != 0) {
			if (joueur->perso==PERSO_SUB_ZERO) {
				deplacement = DEPLACEMENT_AVANCE;
			} else {
				deplacement = DEPLACEMENT_RECULE;
			}
		} else {
			deplacement = DEPLACEMENT_AUCUNE;
		}
		
		if (joueur->perso == PERSO_LIU_KANG) {
			if (deplacement == DEPLACEMENT_AVANCE) {
				//joueur->animation.o=J1A.marcher.o;
				//joueur->animation.l=J1A.marcher.l;
				//joueur->bank=BANK_4;
				//joueur->allez_retour=MARCHE;
				joueur->animation.o=mapping_direction_calque[joueur->perso][joueur->direction]->o;
				joueur->animation.l=mapping_direction_calque[joueur->perso][joueur->direction]->l;
				joueur->bank=mapping_direction_calque[joueur->perso][joueur->direction]->b;
				joueur->allez_retour=mapping_direction_calque[joueur->perso][joueur->direction]->ar | VERS_L_AVANT;
				joueur->anim_restant=joueur->animation.l;
			} else if (deplacement == DEPLACEMENT_RECULE) {
				//joueur->animation.o=J1A.marcher.o;
				//joueur->animation.l=J1A.marcher.l;
				//joueur->bank=BANK_4;
				//joueur->allez_retour=MARCHE;
				joueur->animation.o=mapping_direction_calque[joueur->perso][joueur->direction]->o;
				joueur->animation.l=mapping_direction_calque[joueur->perso][joueur->direction]->l;
				joueur->bank=mapping_direction_calque[joueur->perso][joueur->direction]->b;
				joueur->allez_retour=mapping_direction_calque[joueur->perso][joueur->direction]->ar | VERS_L_ARRIERE;
				joueur->anim_restant=joueur->animation.l;
			} else {
				//joueur->animation.o=J1A.marcher.o;
				//joueur->animation.l=J1A.marcher.l;
				//joueur->bank=BANK_4;
				//joueur->allez_retour=0;
				//joueur->anim_restant=2;
				joueur->animation.o=mapping_direction_calque[joueur->perso][joueur->direction]->o;
				joueur->animation.l=mapping_direction_calque[joueur->perso][joueur->direction]->l;
				joueur->bank=mapping_direction_calque[joueur->perso][joueur->direction]->b;
				joueur->allez_retour=mapping_direction_calque[joueur->perso][joueur->direction]->ar;
				joueur->anim_restant=joueur->animation.l; // sur place, mais pas totalement fixe : mode faché.
			}
		} else {
			if (deplacement == DEPLACEMENT_AVANCE) {
				joueur->animation.o=J2A.marcher.o;
				joueur->animation.l=J2A.marcher.l;
				joueur->bank=BANK_6;
				joueur->anim_restant=joueur->animation.l;
				joueur->allez_retour=MARCHE | VERS_L_AVANT;
			} else if (deplacement == DEPLACEMENT_RECULE) {
				//joueur->animation.o=J2A.marcher.o;
				//joueur->animation.l=J2A.marcher.l;
				//joueur->bank=BANK_6;
				//joueur->allez_retour=MARCHE_ARRIERE;
				joueur->animation.o=mapping_direction_calque[joueur->perso][joueur->direction]->o;
				joueur->animation.l=mapping_direction_calque[joueur->perso][joueur->direction]->l;
				joueur->bank=mapping_direction_calque[joueur->perso][joueur->direction]->b;
				joueur->allez_retour=mapping_direction_calque[joueur->perso][joueur->direction]->ar | VERS_L_ARRIERE;
				joueur->anim_restant=joueur->animation.l;
			} else {
				joueur->animation.o=J2A.marcher.o;
				joueur->animation.l=J2A.marcher.l;
				joueur->bank=BANK_6;
				joueur->anim_restant=2; // sur place, mais pas totalement fixe : mode faché.
				joueur->allez_retour=0;
			}
		}
	}
}

void switch_bank(ANIMATION * joueur) {
	switch (joueur->bank) {
		case BANK_4 :
			bank4_4000();
		return;
		case BANK_5 :
			bank5_4000();
		return;
		case BANK_6 :
			bank6_4000();
		return;
		case BANK_7 :
			bank7_4000();
		return;
	}
}

// J1A.marcher avec l=2
const CALQUE J1A_repos ={0,2,0,BANK_4,MARCHE};
// J2A.marcher avec l=2
const CALQUE J2A_repos ={24,2,0,BANK_6,MARCHE};

void main(void)
{
	char i;char direction;
	
	//init liu_kang et sub_zero
	liu_kang.x=10;
	liu_kang.old_x=liu_kang.x;
	liu_kang.perso=PERSO_LIU_KANG;
	liu_kang.anim_restant=0;
	liu_kang.allez_retour=0;
	
	sub_zero.x=30;
	sub_zero.old_x=sub_zero.x;
	sub_zero.perso=PERSO_SUB_ZERO;
	sub_zero.anim_restant=0;
	sub_zero.allez_retour=0;
	
	// init mapping
	for (i=0;i<=DIRECTION_DROITE+DIRECTION_GAUCHE+DIRECTION_HAUT+DIRECTION_BAS+DIRECTION_FIRE;i++) {
		if ((i & DIRECTION_DROITE) == 0 && (i & DIRECTION_GAUCHE) == 0) {
			mapping_direction_calque[PERSO_LIU_KANG][i]=&J1A_repos;
			mapping_direction_calque[PERSO_SUB_ZERO][i]=&J2A_repos;
		} else {
			mapping_direction_calque[PERSO_LIU_KANG][i]=&J1A.marcher;
			mapping_direction_calque[PERSO_SUB_ZERO][i]=&J2A.marcher;
		}
	}
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_DROITE | DIRECTION_FIRE]=&J1A.pied_milieu;
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_DROITE | DIRECTION_BAS | DIRECTION_FIRE]=&J1A.pied_rotatif;
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_DROITE | DIRECTION_HAUT | DIRECTION_FIRE]=&J1A.pied_haut2;
	
	// against "so said EVELYN the modified DOG" => volatile
	// volatile char layer=0;volatile char x=10;//char z=0;
	// char aaah=3;

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

	// calibration
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

	// pas très utile de le faire bloc par bloc mais permet de voir le raster et calculer le temps réel.
	memcpy((char *)0x4000, (char *)0xC000, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
	memcpy((char *)0x4800, (char *)0xC800, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
	memcpy((char *)0x5000, (char *)0xD000, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
	memcpy((char *)0x5800, (char *)0xD800, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
	memcpy((char *)0x6000, (char *)0xE000, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
	memcpy((char *)0x6800, (char *)0xE800, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
	memcpy((char *)0x7000, (char *)0xF000, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
	memcpy((char *)0x7800, (char *)0xF800, 0x0800); // memcpy(destination,source,longueur)
	border_raster_end();
	if (is_vsync==0) {}
	is_vsync=0;
		
	// affiche 4000 pendant qu'on pose deux sprites de 4000 vers C000
	if (is_vsync==0) {}
	is_vsync=0;
	calque4000();

	// touche o pour faire reculer liu_kang
	check_controller();
	direction=0;
	if ((get_key(Key_Joy1Left)) || (get_key(Key_O))) {
		direction=direction | DIRECTION_GAUCHE;
	} else if ((get_key(Key_Joy1Right)) || (get_key(Key_P))) {
		direction=direction | DIRECTION_DROITE;
	}
	if ((get_key(Key_Joy1Up)) || (get_key(Key_Q))) {
		direction=direction | DIRECTION_HAUT;
	} else if ((get_key(Key_Joy1Down)) || (get_key(Key_A))) {
		direction=direction | DIRECTION_BAS;
	}
	if (get_key(Key_Space) || get_key(Key_Joy1Fire1) || get_key(Key_Joy1Fire2)) {
		direction=direction | DIRECTION_FIRE;
	}
	
	action(&liu_kang,direction);
	
	action(&sub_zero,DIRECTION_DROITE | DIRECTION_FIRE);

	erase_frame((unsigned char *)(vram[120]+liu_kang.old_x),6,50);
	erase_frame((unsigned char *)(vram[120]+sub_zero.old_x),6,50);
	border_raster_end();

	if (is_vsync==0) {}
	is_vsync=0;
	
	switch_bank(&liu_kang);
	put_frame((unsigned char *)(vram[120]+liu_kang.x),6,50,0x4000+((6*50)*(liu_kang.animation.o+liu_kang.anim_restant)));
	switch_bank(&sub_zero);
	put_frame_transparent((unsigned char *)(vram[120]+sub_zero.x),6,50,0x4000+((6*50)*(sub_zero.animation.o+sub_zero.anim_restant)));

	border_raster_end();
	}
	
}