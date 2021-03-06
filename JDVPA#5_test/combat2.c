#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define NO_SOUND

#include "jdvapi_basic1.h"
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

#ifndef NO_SOUND
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
  
	; sks8000.bin/exemple.asm
	ld de,#0x9000
	call #0x8000
	
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
	call #0x8003
	
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
#endif

/**
void border_raster_begin()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set a white raster in the BORDER to "see" how much
	; CPU time the player takes.
	
 ;red border
 ld BC,#0x7F10
 ld A,#0x4C
 out (C),C
 out (C),A
  __endasm;
}
**/

void border_raster_begin2()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set the BORDER to un peu de violet...
;red border
 ld BC,#0x7F10
 ld A,#0x5D
 out (C),C
 out (C),A
  __endasm;
}

void border_raster_end()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set the BORDER to black
 ld BC,#0x7F10
 ld A,#0x54
 out (C),C
 out (C),A
  __endasm;
}

const char math_2pow[8]={1,2,4,8,16,32,64,128};

unsigned char is_vsync;

void callback_roulette(unsigned char roulette)
{
	if (roulette==0) {
		// 5 0 1 : deux interruptions après la musique (afin d'atterrir en dehors de l'écran, en bas)
		is_vsync=is_vsync+1;
	} else if (roulette==5) {
		//border_raster_begin();
		border_raster_end();
#ifndef NO_SOUND		
		// Play the STarKos song
		cpct_akp_musicPlay();
#endif
		border_raster_end();
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

void put_byteC000(unsigned char nX, unsigned char nY, unsigned char nByte) {
	unsigned char * pByteAddress = 0xC000 + vram[nY] + nX;
	*pByteAddress = nByte;
}

void put_byte4000(unsigned char nX, unsigned char nY, unsigned char nByte) {
	unsigned char * pByteAddress = 0x4000 + vram[nY] + nX;
	*pByteAddress = nByte;
}

void put_byte(unsigned char nX, unsigned char nY, unsigned char nByte) {
	unsigned char * pByteAddress = 0xC000 + vram[nY] + nX;
	*pByteAddress = nByte;
	pByteAddress = 0x4000 + vram[nY] + nX;
	*pByteAddress = nByte;
}

// on trace TAILLE_PAS*8 pixels à chaque lancement de progressbar()
char optim_bar=0;
#define TAILLE_PAS 4
char progressbar(unsigned char x, unsigned char y, unsigned int value, unsigned int max, char pas) {
	unsigned int tmp;char i;char j;unsigned char b;char max2;char maxi;
	char mod8=(value+2) %8;
	char div8=(value+2) /8;
	tmp=max/8;
	max2=tmp; // max2 est un char, pas un int...
	
	// si max<
	if ((pas+1)*TAILLE_PAS > max2) {
		maxi=max2%TAILLE_PAS;
	} else {
		maxi=TAILLE_PAS;
	}
	for (i=pas*TAILLE_PAS;i<pas*TAILLE_PAS+maxi;i++){
		if (!optim_bar) {
			put_byte(x+i,y,0xFF);
			for (j=1;j<=8;j++){
				if (i==0) {
					put_byte(x+i,y+j,0x80);
				} else if (i==max/8 -1) {
					put_byte(x+i,y+j,0x01);
				} else {
					put_byte(x+i,y+j,0x00);
				}
			}
			put_byte(x+i,y+9,0xFF);
		}
		//
			if ((i/6)%2==0) {
				j=(i%6)+2;
			} else {
				j=(5-(i%6))+2;
			}
			if (i<div8) {
				b=0xFF;
			} else if (i>div8) {
				b=0x00;
			} else {
				switch(mod8) {
					case 0:
						b=0x00;
						break;
					case 1:
						b=0x80;
						break;
					case 2:
						b=0xC0;
						break;
					case 3:
						b=0xE0;
						break;
					case 4:
						b=0xF0;
						break;
					case 5:
						b=0xF8;
						break;
					case 6:
						b=0xFC;
						break;
					case 7:
						b=0xFE;
						break;
				}
			}
			if (i==0) {
				b=(b & 0xBF) | 0x80;
			}
			if (i==max/8 -1) {
				b=(b & 0xFD) | 0x01;
			}
			put_byte(x+i,y+j,b);
	}
	if ((pas+1)*TAILLE_PAS > max2) {
		return 0;
	} else {
		return pas + 1;
	}
}

//unsigned char * paramAddr;
unsigned char no_combat;
unsigned char arcade;
unsigned char fond_largeur; // vrai largeur
unsigned char fond_offset; // début de vrai fond
unsigned char fond_joueur; // largeur+offset-taillePerso

const unsigned char combat2_palette[3][16]=
{
		// salle dragon fond2
		//0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		{0,6,12,11,0,0,0,0,0,0,0,0,0,0,0,0},
		// foret : 0,6,4,24 fond1
		{0,6,4,24,0,0,0,0,0,0,0,0,0,0,0,0},
		// maitre : 0,6,26,13 fond3
		{0,6,26,13,0,0,0,0,0,0,0,0,0,0,0,0}
};




const unsigned char intro_palette[]=
{
		//0,1,4,11,5,3,16,25,15,12,26,14,23,2,6,0
		0,4,1,11,5,16,25,26,15,3,12,14,23,2,6,0
};

typedef struct {
	char c; // contre le coup
	char p; // porte le coup
} COUPS;


typedef struct {
	char o; // offset
	char l; // longueur
	COUPS c[3]; // contre le coup
	char b; // bank
	char ar; // allez_retour
} CALQUE;


#define PORTE_EN_1 1
#define PORTE_EN_2 2
#define PORTE_EN_3 4
#define PORTE_EN_4 8
#define PORTE_EN_5 16
#define PORTE_EN_6 32
#define PORTE_EN_7 64
#define PORTE_EN_8 128

#define CONTRE_EN_1 1
#define CONTRE_EN_2 2
#define CONTRE_EN_3 4
#define CONTRE_EN_4 8
#define CONTRE_EN_5 16
#define CONTRE_EN_6 32
#define CONTRE_EN_7 64
#define CONTRE_EN_8 128

// sur les deux derniers bit : BANK
#define BANK_4 0
#define BANK_5 1
#define BANK_6 2
#define BANK_7 3
#define HADOUKEN 4
#define ENDING_KO 8
#define ENDING 16
#define FREEZE 32

#define ALLEZ_RETOUR 1
#define RETOUR 2
#define MARCHE 4
#define MARCHER 8
#define ESQUIVE 16
//#define VERS_L_ARRIERE 32
#define RAPIDEMENT 64
#define NON_CYCLIQUE 128

//const char marqueur_sprite1[13]={'D','E','B','U','T',' ','S','P','R','I','T','E','1'};

struct CALQUE_J1A {
	CALQUE marcher; // cyclique, avance, recule
	CALQUE haut;
	CALQUE bas;
	//CALQUE tres_haut;
	CALQUE pied_haut; // allez-retour
	CALQUE pied_milieu; // allez-retour
	//CALQUE genoux_milieu; // allez-retour
	//CALQUE pied_haut2; // cyclique, porté en 3/5
	CALQUE balayette; // cyclique, porté en 3/4 + avance
	CALQUE hypercut; // cyclique (sinon ridicule...)
	CALQUE poing_milieu; // allez-retour
	//CALQUE pied_milieu2; // allez-retour
	CALQUE pied_bas; // allez-retour
	CALQUE pied_rotatif; // cyclique + avance !
};

// J1A.adresse : bank4_4000();
const struct CALQUE_J1A J1A= {
	.marcher={0,8,{{0,0},{0,0},{0,0}},BANK_4,MARCHE | MARCHER | RAPIDEMENT},
	.haut={9,0,{{0,0},{0,0},{0,0}},BANK_4,0},
	.bas={10,0,{{CONTRE_EN_1,0},{0,0},{0,0}},BANK_4,ESQUIVE},
	//.tres_haut={11,0,0,0,BANK_4,0},
	.pied_haut={12,3,{{CONTRE_EN_2 | CONTRE_EN_3,PORTE_EN_4},{CONTRE_EN_2 | CONTRE_EN_3,0},{0,0}},BANK_4,ALLEZ_RETOUR},
	.pied_milieu={16,3,{{0,0},{CONTRE_EN_2, PORTE_EN_3 | PORTE_EN_4},{0,0}},BANK_4,ALLEZ_RETOUR},
	//.genoux_milieu={20,1,CONTRE_EN_2,PORTE_EN_2,BANK_4,ALLEZ_RETOUR},
	//.pied_haut2={22,4,CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_4,PORTE_EN_3,BANK_4,0},
	.balayette={27,3,{{CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_3|CONTRE_EN_4,0},{CONTRE_EN_3,0},{CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_4,PORTE_EN_3}},BANK_4,MARCHE},
	.hypercut={31,4,{{0,PORTE_EN_2|PORTE_EN_3|PORTE_EN_4},{0,0},{0,0}},BANK_4,NON_CYCLIQUE},
	.poing_milieu={36,1,{{CONTRE_EN_1|CONTRE_EN_2,0},{0,PORTE_EN_2},{0,0}},BANK_4,ALLEZ_RETOUR},
	//.pied_milieu2={38,1,CONTRE_EN_1 ,PORTE_EN_2,BANK_4,ALLEZ_RETOUR},
	.pied_bas={40,2,{{CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_3,0},{CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_3,0},{CONTRE_EN_2,PORTE_EN_3}},BANK_4,ALLEZ_RETOUR,ESQUIVE},
	.pied_rotatif={43,7,{{CONTRE_EN_5 | CONTRE_EN_6, PORTE_EN_3 | PORTE_EN_5 | PORTE_EN_7},{CONTRE_EN_5 | CONTRE_EN_6,0},{CONTRE_EN_5 | CONTRE_EN_6,0}},BANK_4,MARCHE}
};

// J1A.marcher avec l=2
//const CALQUE J1A_repos ={0,2,0,0,BANK_4,0};//MARCHE | MARCHER };
const CALQUE J1A_repos ={0,2,{{0,0},{0,0},{0,0}},BANK_4,MARCHE | MARCHER };

struct CALQUE_J1R {
	CALQUE victory; // cyclique
	CALQUE fatality; // statique (stoppé au 3)
	CALQUE hypercut2; // cyclique (sinon ridicule...)
	CALQUE hadouken_personnage; // statique (stoppé au 4), la boule de feu affiché ensuite juste à droite du sprite, collée.
	//CALQUE hadouken_fire; // cyclique
	CALQUE ko; // cyclique
	CALQUE poing_double_jab; // cyclique, porté en 2/5 et 5/5
	CALQUE contre_haut; // allez-retour
	CALQUE macarena_milieu; // cyclique, porté en 2/5 et 5/5
	CALQUE dragon; // statique, enchaine avec dragon_big
	//CALQUE dragon_big; // une seule image mais deux sprites ! => un dragon c un hadouken avec un seul calque secondaire (NON_CYCLIQUE, et sans MARCHE)
	CALQUE contre_haut2; // allez-retour
};

// J1R.adresse : bank5_4000();
const struct CALQUE_J1R J1R= {
	.victory={0,5,{{0,0},{0,0},{0,0}},BANK_5 | ENDING,NON_CYCLIQUE},
	.fatality={6,2,{{0,0},{0,0},{0,0}},BANK_5 | ENDING | ENDING_KO,NON_CYCLIQUE},
	.hypercut2={9,3,{{0,PORTE_EN_4},{0,0},{0,0}},BANK_5,NON_CYCLIQUE},
	.hadouken_personnage={13,3,{{0,0},{0,PORTE_EN_1|PORTE_EN_2|PORTE_EN_3},{0,0}},BANK_5 | HADOUKEN | FREEZE,NON_CYCLIQUE},
	//.hadouken_fire={17,8,0,0,BANK_5,0},
	.ko={26,5,{{0,0},{0,0},{0,0}},BANK_5 | ENDING_KO,0},
	.poing_double_jab={32,4,{{0,PORTE_EN_2 | PORTE_EN_3 | PORTE_EN_5},{0,0},{0,0}},BANK_5,0},
	.contre_haut={37,1,{{CONTRE_EN_1 | CONTRE_EN_2,0},{CONTRE_EN_1 | CONTRE_EN_2,0},{0,0}},BANK_5,NON_CYCLIQUE},
	.macarena_milieu={39,4,{{0,0},{0,0},{0,0}},BANK_5,0},
	.dragon={44,2,{{0,0},{0,0},{0,0}},BANK_5 /*| HADOUKEN*/,NON_CYCLIQUE},
	//.dragon_big={47,1,0,0,BANK_5,0},
	.contre_haut2={49,1,{{CONTRE_EN_1 | CONTRE_EN_2,0},{CONTRE_EN_1 | CONTRE_EN_2,0},{CONTRE_EN_1 | CONTRE_EN_2,0}},BANK_5,ALLEZ_RETOUR}
};


//const char marqueur_sprite2[13]={'D','E','B','U','T',' ','S','P','R','I','T','E','2'};

struct CALQUE_J2A {
	CALQUE pied_haut; // cyclique, porté en 4/8
	//CALQUE pied_haut2; // allez-retour inversé : porté en 1/3 ...
	//CALQUE genoux_haut; // allez-retour
	CALQUE pied_retourne; // cyclique, porté en 4/7
	CALQUE balayette; // cyclique, porté en 3/4
	CALQUE marcher; // cyclique, avance, recule
	CALQUE haut;
	CALQUE bas;
	CALQUE zombi;
	CALQUE victory; // allez-retour ;)
	CALQUE poing_double_jab; // cyclique porté en 3/8 et 6/8
	//CALQUE aie;
	CALQUE poing_gauche; // allez-retour
};

// J2A.adresse : bank6_4000();
const struct CALQUE_J2A J2A= {
	.pied_haut={0,7,{{CONTRE_EN_1 | CONTRE_EN_2 | CONTRE_EN_3 | CONTRE_EN_4,PORTE_EN_4},{0,0},{0,0}},BANK_6,ALLEZ_RETOUR},
	//.pied_haut2={8,2,CONTRE_EN_2 | CONTRE_EN_3 | CONTRE_EN_4,PORTE_EN_1,BANK_6,ALLEZ_RETOUR},
	//.genoux_haut={11,1,CONTRE_EN_1 |CONTRE_EN_2,PORTE_EN_2,BANK_6,ALLEZ_RETOUR},
	.pied_retourne={13,6,{{CONTRE_EN_2 |CONTRE_EN_6,PORTE_EN_3 | PORTE_EN_4 | PORTE_EN_5},{CONTRE_EN_2 |CONTRE_EN_6,0},{0,0}},BANK_6,0},
	.balayette={20,3,{{CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_3|CONTRE_EN_4,0},{CONTRE_EN_1,CONTRE_EN_2,CONTRE_EN_3,0},{CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_4,PORTE_EN_3}},BANK_6,MARCHE},
	.marcher={24,9,{{0,0},{0,0},{0,0}},BANK_6,MARCHE | MARCHER | RAPIDEMENT},
	.haut={34,0,{{0,0},{0,0},{0,0}},BANK_6,0},
	.bas={35,0,{{CONTRE_EN_1,0},{0,0},{0,0}},BANK_6,ESQUIVE},
	.zombi={36,0,{{0,0},{0,0},{0,0}},BANK_6,0},
	.victory={37,1,{{0,0},{0,0},{0,0}},BANK_6 | ENDING,0},//ALLEZ_RETOUR},
	.poing_double_jab={39,7,{{0,PORTE_EN_2 | PORTE_EN_3 | PORTE_EN_5 | PORTE_EN_6| PORTE_EN_8},{0,0},{0,0}},BANK_6,0},
	//.aie={48,0,0,0,BANK_6,0},
	.poing_gauche={49,2,{{0,PORTE_EN_2|PORTE_EN_3},{0,0},{0,0}},BANK_6,ALLEZ_RETOUR}
};

// J2A.marcher avec l=2
//const CALQUE J2A_repos ={24,0,0,0,BANK_6,0};//MARCHE | MARCHER };
const CALQUE J2A_repos ={24,0,{{0,0},{0,0},{0,0}},BANK_6,MARCHE | MARCHER };

struct CALQUE_J2R{
	CALQUE poing_droit; // allez-retour
	CALQUE ko; // cyclique
	CALQUE fatality; // statique (stoppé au 5)
	CALQUE hadouken1_personnage; // statique (stoppé au 10), la boule de feu affiché ensuite juste à droite du sprite, collée.
	//CALQUE hadouken1_fire; // boule de neige
	//CALQUE hadouken2_personnage; // 1 2 3
	//CALQUE hadouken2_fire; // mega fire
	//CALQUE hadouken2_personnage_patch; // p3 p1 p2 1 2 3
	CALQUE hypercut; // cyclique porté en 3/5
	CALQUE poing_milieu; // allez-retour
	CALQUE flaque; //cyclique
	CALQUE toto1;
	CALQUE toto2;
	CALQUE toto3;
};

// J2R.adresse : bank7_4000();
const struct CALQUE_J2R J2R= {
	.poing_droit={0,1,{{0,PORTE_EN_2},{0,0},{0,0}},BANK_7,0},
	.ko={2,4,{{0,0},{0,0},{0,0}},BANK_7 | ENDING_KO,0},
	.fatality={7,4,{{0,0},{0,0},{0,0}},BANK_7 | ENDING | ENDING_KO,NON_CYCLIQUE},
	//.hadouken1_personnage={12,9,0,0,BANK_7 | HADOUKEN,0},
	.hadouken1_personnage={16,5,{{CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_3,PORTE_EN_3|PORTE_EN_4|PORTE_EN_5},{0,0},{0,0}},BANK_7 | HADOUKEN | FREEZE,NON_CYCLIQUE},
	//.hadouken1_fire={22,0,0,0,BANK_7,0},
	//.hadouken2_personnage={23,2,0,0,BANK_7 | HADOUKEN,0},
	//.hadouken2_fire={26,8,0,0,BANK_7,0},
	//.hadouken2_personnage_patch={35,2,0,0,BANK_7,0},
	.hypercut={38,2,{{0,PORTE_EN_1|PORTE_EN_2},{0,0},{0,0}},BANK_7,NON_CYCLIQUE},
	.poing_milieu={43,1,{{0,0},{0,0},{0,PORTE_EN_2}},BANK_7,ALLEZ_RETOUR},
	.flaque={45,6,{{0,0},{CONTRE_EN_2,0},{CONTRE_EN_2,PORTE_EN_5|PORTE_EN_6|PORTE_EN_7}},BANK_7 | FREEZE,0},
	.toto1={0,0,{{0,0},{0,0},{0,0}},BANK_7,0},
	.toto2={0,0,{{0,0},{0,0},{0,0}},BANK_7,0},
	.toto3={0,0,{{0,0},{0,0},{0,0}},BANK_7,0}
};

//const char marqueur_sprites_fin[15]={'F','I','N',' ','D','E','S',' ','S','P','R','I','T','E','S'};

#define PERSO_LIU_KANG 0
#define PERSO_SUB_ZERO 1

typedef struct {
	char perso; // identifiant du jouer
	char direction;
	char phase; // in game,ko,victory
	char polarite; // 0 : normal, 1 : sprite inversé
	CALQUE * animation;
	char anim_restant; // decompte un CALQUE.l
	char allez_retour; // si ALLEZ ou RETOUR, decompte aussi un allez-retour de l'anim (ALLEZ, puis RETOUR, puis 0)
	char x;char old_x;
} ANIMATION;

#define DIRECTION_AVANT 1
#define DIRECTION_ARRIERE 2
#define DIRECTION_HAUT 4
#define DIRECTION_BAS 8
#define DIRECTION_FIRE 16
#define DIRECTION_FIRE1 32
#define DIRECTION_FIRE2 64

#define PHASE_REPOS 0
#define PHASE_KO 1
#define PHASE_FATALITY 2
#define PHASE_VICTORY 3
#define PHASE_GEL_ATTAQUE 4
#define PHASE_GEL_DEFENCE 8
#define PHASE_GEL 4+8

ANIMATION liu_kang;
ANIMATION sub_zero;

#define DEPLACEMENT_DROITE 1
#define DEPLACEMENT_GAUCHE 2
#define DEPLACEMENT_AUCUNE 3

//const char marqueur_directions[20]={'D','E','B','U','T',' ','D','E','S',' ','D','I','R','E','C','T','I','O','N','S'};

// bon le dump je regarde la taille du fichier pondu, j'en déduis la taille de l'entête du dump à supprimer : FF
// SPRITE1 est à "0885", effectivement selon combat2.map j'ai 00000885  _J1A, bon il y a 16 sprites dans J1.MAP donc 13 octets par sprite.
//                           5618 ;combat2.c:1480: mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_FIRE]=&J1R.poing_double_jab; //attaque centre
//   1F84 21rE9r07      [10] 5619 	ld	hl,#(_J1R + 0x0027) <= 3*13
//   1F87 22r3Dr00      [16] 5620 	ld	((_mapping_direction_calque + 0x0020)), hl 16*2 car c'est 2 octets une adresse !
//                           5682 ;combat2.c:1512: mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_FIRE1]=&J1R.contre_haut;
//   1FFC 21rF6r07      [10] 5683 	ld	hl,#(_J1R + 0x0034)
//   1FFF 22r5Dr00      [16] 5684 	ld	((_mapping_direction_calque + 0x0040)), hl
// donc idiot : 00000885  _J1A, 000008FA  _J1R et 0000335A  _mapping_direction_calque donc si ok en 335A+0020=337A on a 08FA+0034-0885=00A9 => j'ai "0C00" :/
// la fin du tableau est certainement le début du tableau d'après : 00003167  _current_blood, des tailles "0100" en fait.

// 10101001 A9
//     1100 0C

unsigned char mapping_direction_calque[2][1+DIRECTION_AVANT+DIRECTION_ARRIERE+DIRECTION_HAUT+DIRECTION_BAS+DIRECTION_FIRE+DIRECTION_FIRE1+DIRECTION_FIRE2];
unsigned char mapping_phase_calque[2][4];
unsigned int normDIR[2];

//const char marqueur_directions_fin[18]={'F','I','N',' ','D','E','S',' ','D','I','R','E','C','T','I','O','N','S'};

#define BLOOD_SIZE 6
// 1 + 2 + 3 + 4 < 14
#define BLOOD_SIZE_INIT 2
//#define BLOOD_B_SPEED 0 - vitesse d'entrée des gouttes dans l'algo : déjà au maximum (en entrer plusieurs ?)
#define BLOOD_X_SPEED 8
#define BLOOD_Y_SPEED 4
// == BLOOD_SIZE_INIT ? - attente durant insertion des gouttes, afin d'appliquer la gravité
//#define BLOOD_G_WAIT_MAX 3
// coupe l'animation dans ce cas ?
//#define BLOOD_G_MAX 9
unsigned char current_blood[BLOOD_SIZE][2];
char blood_depth=0;
char blood_n=0;
unsigned char blood_x_slow=0;
unsigned char blood_y_slow=0;
char blood_x;
char blood_y; // tete ou ventre ou pied
char blood_d; // direction
char blood_g; // gravite

/**
 * Controler : propagation du sang (lancé à chaque frame)
 */
void blood() {
	char i;char sx;char sy;char g;
	if (blood_n==0) return;

	// ==> ou <== : on s'en fou, le tableau on le retournera à l'affichage !
	blood_x_slow++;
	if (blood_x_slow == BLOOD_X_SPEED) { // x
		blood_x_slow=0;
	}
	if (blood_x_slow==0) {
		for (i=0;i<blood_depth;i++)  {
			// se poussent en x
			if (current_blood[i][0]<BLOOD_SIZE) { // x
				current_blood[i][0]=current_blood[i][0]+1;
			}
		}
		return;
	}
	blood_y_slow++;
	if (blood_y_slow == BLOOD_Y_SPEED) { // y
		blood_y_slow=0;
	}
	if (blood_y_slow==0) {
		for (i=0;i<blood_depth;i++)  {
			if (current_blood[i][1]>0) { // y
				// descend à vitesse constante.
				current_blood[i][1]=current_blood[i][1]-1;
			}
		}
		return;
	}
#ifndef BLOOD_G_WAIT_MAX
	if (blood_depth==0) {
		blood_g=1;
#else
	if (blood_depth<BLOOD_G_WAIT_MAX) {
		// gouttes en suspention dans l'air.
		blood_g=0;
#endif
	} else {
		blood_g++;
	}
	// BLOOD_B_SPEED/blood_b_slow
	if (blood_depth<blood_n) {
		// insertion
		current_blood[blood_depth][0]=0;
		current_blood[blood_depth][1]=blood_y;
		blood_depth++;
		if (blood_depth<blood_n) {
			current_blood[blood_depth][0]=1;
			current_blood[blood_depth][1]=blood_y+1;
			blood_depth++;
		}
	}
	if (blood_g>0) {
		// gravité
		g=blood_depth-(blood_n%3); // glitch (formule capturée lors de tests en échecs, car c'est jolie)
		for (i=0;i<blood_depth;i++)  {
			if (current_blood[i][1]>blood_g + g) {
				// descend à vitesse non constante
				current_blood[i][1]=current_blood[i][1]-g-blood_g;
			} else {
				// touche le sol
				current_blood[i][1]=0;
			}
		}
//		if (blood_g>BLOOD_G_MAX) {
//			// on coupe l'animation sang (car c'est moche sinon : une goutte reste bizarrement suspendue...)
//			blood_n=0;
//			blood_depth=0;
//		}
	}
	// solve superpositions X
	sx=current_blood[0][0];sy=current_blood[0][1];
	for (i=1;i<blood_depth;i++)  {
		if (current_blood[i][1] != sy) {
			// nouvelle ligne, pas de problème de gouttes
			sx=current_blood[i][0];
			sy=current_blood[i][1];
		} else if (current_blood[i][0] <= sx) {
			// goutte génante, je la pousse, puis je la garde de côté
			sx=sx+1;
			current_blood[i][0]= sx;
		} else {
			// goutte pas génante, je la garde de côté
			sx=current_blood[i][0];
		}
	}
}

char pixelBloodTerrain;
/**
 * Renderer : Affiche le sang
 */
void bloodRender() {
	char i;char pixel;
	for (i=0;i<blood_depth;i++)  {
		if (blood_d==0) {
			if (blood_x+current_blood[i][0]>6*12+2+2) continue;
			if (blood_x+current_blood[i][0]>=fond_largeur+fond_offset) {
				pixel=pixelBloodTerrain;
			} else {
				pixel=0xF0;
			}
			put_byte(blood_x+current_blood[i][0],120+50-1-current_blood[i][1],pixel);
		} else {
			if (blood_x<current_blood[i][0]) continue;
			if (blood_x-current_blood[i][0]<fond_offset) {
				pixel=pixelBloodTerrain;
			} else {
				pixel=0xF0;
			}
			put_byte(blood_x-current_blood[i][0],120+50-1-current_blood[i][1],pixel);
		}
	}
}

/**
 * Renderer : Efface le sang
 */
void bloodDerender() {
	char i;
	for (i=0;i<blood_depth;i++)  {
		if (blood_d==0) {
			if (blood_x+current_blood[i][0]>6*12+2+2) continue;
			if (blood_x+current_blood[i][0]>=fond_largeur+fond_offset) continue;
			put_byteC000(blood_x+current_blood[i][0],120+50-1-current_blood[i][1],0x00);
		} else {
			if (blood_x<current_blood[i][0]) continue;
			if (blood_x-current_blood[i][0]<fond_offset) continue;
			put_byteC000(blood_x-current_blood[i][0],120+50-1-current_blood[i][1],0x00);
		}
	}
}

typedef struct {
/*	unsigned char furie; // 0-196
	unsigned char aura; // 0-196
	unsigned char expert; // 0-196
	unsigned char tech_perd; // 0-96
	unsigned char tech_gagne; // 0-96
	unsigned char tech; // 0-196*/
	unsigned int espert; // 0-300
	unsigned int vie; // 0-296
} SCORE;

SCORE liu_kang_score;//={100,196,100,30,75,194,100};
SCORE sub_zero_score;//={100,193,100,92,90,191,290};

#define DEGATS 4
#define BONUS_DEGATS 2
#define DELAUTREBORD 3
char degats_liu_kang;
char degats_sub_zero;
char boum_hadouken_sub_zero;
char boum_hadouken_liu_kang;
char degats_liu_kang_corps;
char degats_sub_zero_corps;
char contre_liu_kang[3];
char contre_sub_zero[3];
char porte_liu_kang[3];
char porte_sub_zero[3];
const char corps[3]=
{
	// tête
	32,
	// ventre
	22,
	// genoux
	12
};


/**
 * affiche l'espert (énergie pour le Hadouken)
 */
void espertRender(unsigned char offset_x,unsigned int nb_espert) {
	char i;char pixel;
	put_byte(offset_x,105-4,0xF0); // "cadre"
	for (i=0;i<3;i++) {
		if (nb_espert>=(1+i)*100) {
			pixel=0xF6;
		} else {
			pixel=0x90;
		}
		put_byte(offset_x,105-1-i,pixel);
	}
}
unsigned char nb_victory_liu_kang;
unsigned char nb_victory_sub_zero;
void victoryCounterRender(unsigned char offset_x,unsigned char nb_victory) {
	if (nb_victory == 0) return;
	put_byte(offset_x+(nb_victory-1)/5,104-(nb_victory-1)%5,0xFE); // "cadre"
}

// BLOOD_SIZE/4
#define HADOUKEN_SIZE 4
// 1 + 2 + 3 < 7
#define HADOUKEN_SIZE_INIT 2
#define HADOUKEN_X_SPEED 3
#define HADOUKEN_BOULE_OFFSET 2
#define HADOUKEN_BOULE_SPEED 2
#define HADOUKEN_Y_TETE 25
#define HADOUKEN_Y_VENTRE 35

unsigned char current_hadouken[HADOUKEN_SIZE][2];
char hadouken_depth=0;
char hadouken_n=0;
unsigned char hadouken_x_slow=0;
unsigned char hadouken_boule_slow=0;
char hadouken_x;
char hadouken_x2; // boule (relatif à x)
char hadouken_x2_old;
char hadouken_y;
ANIMATION * hadouken_victime; // impact (coupé lors du rendu) (relatif à x)
char hadouken_y_top;
#define HADOUKEN_Y_TOP_DIV4 1
char hadouken_d; // direction

char hadoukenContact() {
	char is_contact=0;
	char is_contact_bord=0;
	if (hadouken_d==0) {
		// si la boule touche la victime
		if (HADOUKEN_BOULE_SPEED+hadouken_x+hadouken_x2+HADOUKEN_Y_TOP_DIV4>fond_largeur+fond_offset) {
			is_contact_bord=1;
		}
		if (hadouken_x+hadouken_x2+HADOUKEN_Y_TOP_DIV4-2>hadouken_victime->x && hadouken_x+hadouken_x2_old+HADOUKEN_Y_TOP_DIV4-2 <= hadouken_victime->x) {
			is_contact=1;
		}
	} else {
		if (hadouken_x<fond_offset+hadouken_x2+HADOUKEN_Y_TOP_DIV4+HADOUKEN_BOULE_SPEED) {
			is_contact_bord=1;
		}
		if (hadouken_x-hadouken_x2-HADOUKEN_Y_TOP_DIV4-4<hadouken_victime->x && hadouken_x-hadouken_x2_old-HADOUKEN_Y_TOP_DIV4-4 >= hadouken_victime->x) {
			is_contact=1;
		}
	}
	if (!is_contact_bord && is_contact) {
		if (hadouken_victime->perso==PERSO_LIU_KANG) {
			if (contre_liu_kang[hadouken_y==HADOUKEN_Y_VENTRE]) {
				// liu_kang a esquivé
				if ((hadouken_victime->allez_retour & ESQUIVE) != 0) {
					is_contact=0;
				} else {
					// liu_kang a contré, il absorbe l'énergie du choque
					if (liu_kang_score.espert>300-boum_hadouken_sub_zero) {
						liu_kang_score.espert=300;
					} else {
						liu_kang_score.espert=liu_kang_score.espert+boum_hadouken_sub_zero;
					}
				}
			} else {
				if (liu_kang_score.vie < boum_hadouken_sub_zero) {
					liu_kang_score.vie = 0;//296;
				} else {
					liu_kang_score.vie = liu_kang_score.vie - boum_hadouken_sub_zero;
				}
			}
		} else {
			if (contre_sub_zero[hadouken_y==HADOUKEN_Y_VENTRE]) {
				// sub_zero a esquivé
				if ((hadouken_victime->allez_retour & ESQUIVE) != 0) {
					is_contact=0;
				} else {
					// sub_zero a contré, il absorbe l'énergie du choque
					if (sub_zero_score.espert>300-boum_hadouken_liu_kang) {
						sub_zero_score.espert=300;
					} else {
						sub_zero_score.espert=sub_zero_score.espert+boum_hadouken_liu_kang;
					}
				}
			} else {
				if (sub_zero_score.vie < boum_hadouken_liu_kang) {
					sub_zero_score.vie = 0;//296;
				} else {
					sub_zero_score.vie = sub_zero_score.vie - boum_hadouken_liu_kang;
				}
			}
		}
	}
	if (is_contact || is_contact_bord) {
		boum_hadouken_liu_kang=0;
		boum_hadouken_sub_zero=0;
		// fin d'animation
		hadouken_n=0;
		hadouken_depth=0;
	}
	return is_contact || is_contact_bord;
}

/**
 * Controler : propagation du hadouken (lancé à chaque frame)
 */
void hadouken() {
	char i;char sx;char sy;
	if (hadouken_n == 0) return;
	// ==> ou <== : on s'en fou, le tableau on le retournera à l'affichage !
	// la BOULE avance.
	hadouken_x2_old=hadouken_x2;
	hadouken_x2 = hadouken_x2+HADOUKEN_BOULE_SPEED;
	if (hadoukenContact()) return;
	for (i=0;i<hadouken_depth;i++)  {
		// se poussent en x
		if (current_hadouken[i][0]<hadouken_x2) { // x
			current_hadouken[i][0]=current_hadouken[i][0]+HADOUKEN_X_SPEED;
		}
	}
	// HADOUKEN_B_SPEED/hadouken_b_slow
	for (i=0;i<HADOUKEN_X_SPEED;i++) {
		if (hadouken_depth<hadouken_n) {
			// insertion (selon vitesse propagation pixels : HADOUKEN_X_SPEED
			current_hadouken[hadouken_depth][0]=i;
			current_hadouken[hadouken_depth][1]=0;
			hadouken_depth++;
		}
	}
	// solve superpositions X
	sx=current_hadouken[0][0];sy=current_hadouken[0][1];
	for (i=1;i<hadouken_depth;i++)  {
		if (current_hadouken[i][1] != sy) {
			// nouvelle ligne, pas de problème de gouttes
			sx=current_hadouken[i][0];
			sy=current_hadouken[i][1];
		} else if (current_hadouken[i][0] >= sx) {
			if (sx<hadouken_x2) {
				// goutte génante je la pousse, puis je la garde de côté
				sx=sx+1;
				current_hadouken[i][0]= sx;
			} else {
				// goutte génante au bord je la pousse au dessus, relativement à hadouken_y_top, puis je ne la garde de côté (car y change)
				current_hadouken[i][1]=current_hadouken[i][1]+1;
				if (current_hadouken[i][1]>hadouken_y_top) {
					hadouken_y_top = current_hadouken[i][1];
				}
				current_hadouken[i][0]= hadouken_x2 - (hadouken_y_top - current_hadouken[i][1]);
			}
		} else {
			// goutte pas génante, je la garde de côté
			sx=current_hadouken[i][0];
		}
	}
}

/**
 * Renderer : Affiche le hadouken
 */
void hadoukenRender() {
	char i; char pixel;
	for (i=0;i<hadouken_depth;i++)  {
		if (current_hadouken[i][1] == hadouken_y_top) {
			pixel=0xFF;
		} else if (current_hadouken[i][1]%2 == 0) {
			pixel=0xAA;
		} else {
			pixel=0x55;
		}
		if (hadouken_d==0) {
			//if (current_hadouken[i][0]>hadouken_victime->x-hadouken_x) continue;
			put_byteC000(hadouken_x+current_hadouken[i][0],120+hadouken_y-current_hadouken[i][1],pixel);
			if (current_hadouken[i][1] != 0) {
				// impair mirror
				put_byteC000(hadouken_x+current_hadouken[i][0],120+hadouken_y+current_hadouken[i][1],pixel);
			}
			if ((hadouken_x2 - current_hadouken[i][0]>HADOUKEN_Y_TOP_DIV4)) {// || (hadouken_x2+(hadouken_x2 - current_hadouken[i][0])>hadouken_victime->x-hadouken_x)) {
				continue;
			}
			// boule mirror
			put_byteC000(hadouken_x+hadouken_x2+(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y-current_hadouken[i][1],pixel);
			if (current_hadouken[i][1] != 0) {
				// boule impair mirror
				put_byteC000(hadouken_x+hadouken_x2+(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y+current_hadouken[i][1],pixel);
			}
		} else {
			//if (current_hadouken[i][0]>hadouken_x-hadouken_victime->x) continue;
			put_byteC000(hadouken_x-current_hadouken[i][0],120+hadouken_y-current_hadouken[i][1],pixel);
			if (current_hadouken[i][1] != 0) {
				// impair mirror
				put_byteC000(hadouken_x-current_hadouken[i][0],120+hadouken_y+current_hadouken[i][1],pixel);
			}
			if ((hadouken_x2 - current_hadouken[i][0]>HADOUKEN_Y_TOP_DIV4)) {// || (hadouken_x2+(hadouken_x2 - current_hadouken[i][0])>hadouken_x-hadouken_victime->x)) {
				continue;
			}
			// boule mirror
			put_byteC000(hadouken_x-hadouken_x2-(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y-current_hadouken[i][1],pixel);
			if (current_hadouken[i][1] != 0) {
				// boule impair mirror
				put_byteC000(hadouken_x-hadouken_x2-(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y+current_hadouken[i][1],pixel);
			}
		}
	}
}

/**
 * Renderer : Efface le hadouken
 */
void hadoukenDerender() {
	char i;
	for (i=0;i<hadouken_depth;i++)  {
		if (hadouken_d==0) {
			//if (current_hadouken[i][0]>hadouken_victime->x - hadouken_x) continue;
			put_byteC000(hadouken_x+current_hadouken[i][0],120+hadouken_y-current_hadouken[i][1],0x00);
			if (current_hadouken[i][1] != 0) {
				// impair mirror
				put_byteC000(hadouken_x+current_hadouken[i][0],120+hadouken_y+current_hadouken[i][1],0x00);
			}
			if ((hadouken_x2 - current_hadouken[i][0]>hadouken_y_top)) {// || (hadouken_x2+(hadouken_x2 - current_hadouken[i][0])>hadouken_victime->x - hadouken_x)) {
				continue;
			}
			// boule mirror
			put_byteC000(hadouken_x+hadouken_x2+(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y-current_hadouken[i][1],0x00);
			if (current_hadouken[i][1] != 0) {
				// boule impair mirror
				put_byteC000(hadouken_x+hadouken_x2+(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y+current_hadouken[i][1],0x00);
			}
		} else {
			//if (current_hadouken[i][0]>hadouken_x-hadouken_victime->x) continue;
			put_byteC000(hadouken_x-current_hadouken[i][0],120+hadouken_y-current_hadouken[i][1],0x00);
			if (current_hadouken[i][1] != 0) {
				// impair mirror
				put_byteC000(hadouken_x-current_hadouken[i][0],120+hadouken_y+current_hadouken[i][1],0x00);
			}
			if ((hadouken_x2 - current_hadouken[i][0]>hadouken_y_top)) {// || (hadouken_x2+(hadouken_x2 - current_hadouken[i][0])>hadouken_x-hadouken_victime->x)) {
				continue;
			}
			// boule mirror
			put_byteC000(hadouken_x-hadouken_x2-(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y-current_hadouken[i][1],0x00);
			if (current_hadouken[i][1] != 0) {
				// boule impair mirror
				put_byteC000(hadouken_x-hadouken_x2-(hadouken_x2 - current_hadouken[i][0]),120+hadouken_y+current_hadouken[i][1],0x00);
			}
		}
	}
}

/**
 * Controler : lancé à la place de blood() lors d'un nouveau dégat - ça déclanche une nouvelle animation
 * @param d : direction (plutôt aléatoire)
 * @param n : dégats (entre 1 et BLOOD_SIZE)
 * @param x,y : coordonnées du coup reçu
 */
void bloodDegats(char d, char n,char x, char y) {
	if (hadouken_n!=0) return;
	blood_d = d;
	blood_n = n;
	blood_x = x;
	blood_y = y;
	blood_depth=0;
	while (blood_depth<blood_n && blood_depth<BLOOD_SIZE_INIT) {
		blood();
	}
}

#define HADOUKEN_MIN 20

/**
 * Controler : lancé à la place de hadouken() lors d'un nouveau dégat - ça déclanche une nouvelle animation
 * @param n : dégats (entre 1 et HADOUKEN_SIZE)
 * @param x : coordonnée x de la personne ayant fait un hadouken
 * @param x2 : coordonnée x de l'autre joueur
 */
char hadoukenDegats(char n,ANIMATION * lanceur, ANIMATION * victime) {
	// on coupe l'animation sang
	blood_n=0;
	blood_depth=0;
	// il y a quand même une certaine distance minimum pour lancer un hadouken...
	if (victime->x >= lanceur->x && victime->x - lanceur->x < HADOUKEN_MIN) return 0;
	if (lanceur->x >= victime->x && lanceur->x - victime->x < HADOUKEN_MIN) return 0;

	hadouken_n = n;
	if (lanceur->polarite) {
		hadouken_x = lanceur->x+1;
	} else {
		hadouken_x = lanceur->x+5;
	}
	hadouken_x2 = HADOUKEN_BOULE_OFFSET;
	hadouken_x2_old = hadouken_x2;
	hadouken_victime=victime;
	hadouken_d = lanceur->polarite;
	hadouken_y_top = 0;
	hadouken_depth=0;
	while (hadouken_depth<hadouken_n && hadouken_depth<HADOUKEN_SIZE_INIT) {
		hadouken();
	}
	return 1;
}

void check_mur(ANIMATION * liu_kang, ANIMATION * sub_zero) {
	char is_delautrebord=(
	((liu_kang->x >= sub_zero->x) && (liu_kang->x - sub_zero->x < DELAUTREBORD))
	||
	((sub_zero->x > liu_kang->x) && (sub_zero->x - liu_kang->x < DELAUTREBORD))
	);
	// pas grave de toute façon il KO... tant pis si on triche ici.
	if (((liu_kang->animation->b & ENDING_KO)!=0) || ((sub_zero->animation->b & ENDING_KO)!=0)
		|| ((liu_kang->animation->b & FREEZE)!=0) || ((sub_zero->animation->b & FREEZE)!=0)) {
		if (is_delautrebord) {
			// animation MARCHE sans MARCHER
			if (liu_kang->polarite==0) {
				if (liu_kang->x>liu_kang->old_x) {
					liu_kang->x=liu_kang->old_x;
				}
				//sub_zero->polarite==1
				if (sub_zero->x<sub_zero->old_x) {
					sub_zero->x=sub_zero->old_x;
				}
			} else {
				if (liu_kang->x<liu_kang->old_x) {
					liu_kang->x=liu_kang->old_x;
				}
				if (sub_zero->x>sub_zero->old_x) {
					sub_zero->x=sub_zero->old_x;
				}
			}
		}
	} else {
	
	
// polarite
		// Laurent Gendrop : Sur tous les jeux de baston le perso fini son attaque avant de changer de sens, si l'autre esquive en passant de l'autre coté tu donne un coup dans le vide. C'est archi classique, ca me choque pas
		if ((liu_kang->x > sub_zero->x && liu_kang->polarite==0)
			|| (sub_zero->x > liu_kang->x && liu_kang->polarite==1)) {
			// inversion de la polarite
			liu_kang->polarite=!liu_kang->polarite;
			sub_zero->polarite=!sub_zero->polarite;
			// fin de l'animation déclenché par le joystick
			
			if ((liu_kang->direction & (DIRECTION_AVANT|DIRECTION_ARRIERE)) != 0) {
				liu_kang->direction=liu_kang->direction ^ (DIRECTION_AVANT|DIRECTION_ARRIERE);
				//liu_kang->direction=(liu_kang->direction & ~(DIRECTION_AVANT|DIRECTION_ARRIERE)) | (~(liu_kang->direction & (DIRECTION_AVANT|DIRECTION_ARRIERE)) & (DIRECTION_AVANT|DIRECTION_ARRIERE));
			}
			
			//if ((liu_kang->direction & DIRECTION_AVANT) != 0) {
			//	liu_kang->direction=((liu_kang->direction & (!DIRECTION_AVANT)) | DIRECTION_ARRIERE);
			//} else if ((liu_kang->direction & DIRECTION_ARRIERE) != 0) {
			//	liu_kang->direction=((liu_kang->direction & (!DIRECTION_ARRIERE)) | DIRECTION_AVANT);
			//}
			// change de sens donc si marchait en avançant désormais il recule.
			if ((liu_kang->allez_retour & MARCHER) != 0) {
				liu_kang->allez_retour = liu_kang->allez_retour ^ RETOUR;
				//if ((liu_kang->allez_retour & RETOUR) != 0) {
				//	liu_kang->allez_retour = (liu_kang->allez_retour & (!RETOUR));
				//} else {
				//	liu_kang->allez_retour = (liu_kang->allez_retour | RETOUR);
				//}
			} else {//if ((liu_kang->direction & (DIRECTION_AVANT | DIRECTION_ARRIERE)) != 0) {
				// les attaques qui avancent on arrête d'avancer sinon ça fait droite/gauche/droite/gauche non déterministe
				liu_kang->allez_retour = liu_kang->allez_retour ^ MARCHE;
			}
			if ((sub_zero->direction & (DIRECTION_AVANT|DIRECTION_ARRIERE)) != 0) {
				sub_zero->direction=sub_zero->direction ^ (DIRECTION_AVANT|DIRECTION_ARRIERE);
				//sub_zero->direction=(sub_zero->direction & ~(DIRECTION_AVANT|DIRECTION_ARRIERE)) | (~(sub_zero->direction & (DIRECTION_AVANT|DIRECTION_ARRIERE)) & (DIRECTION_AVANT|DIRECTION_ARRIERE));
			}

			//if ((sub_zero->direction & DIRECTION_AVANT) != 0) {
			//	sub_zero->direction=((sub_zero->direction & (!DIRECTION_AVANT)) | DIRECTION_ARRIERE);
			//} else if ((sub_zero->direction & DIRECTION_ARRIERE) != 0) {
			//	sub_zero->direction=((sub_zero->direction & (!DIRECTION_ARRIERE)) | DIRECTION_AVANT);
			//}
			if ((sub_zero->allez_retour & MARCHER) != 0) {
				sub_zero->allez_retour = sub_zero->allez_retour ^ RETOUR;
				//if ((sub_zero->allez_retour & RETOUR) != 0) {
				//	sub_zero->allez_retour = (sub_zero->allez_retour & (!RETOUR));
				//} else {
				//	sub_zero->allez_retour = (sub_zero->allez_retour | RETOUR);
				//}
			} else {//if ((sub_zero->direction & (DIRECTION_AVANT | DIRECTION_ARRIERE)) != 0) {
				// les attaques qui avancent on arrête d'avancer sinon ça fait droite/gauche/droite/gauche non déterministe
				sub_zero->allez_retour = sub_zero->allez_retour ^ MARCHE;
			}
			// remet une distance entre les deux adversaires
			if (liu_kang->x-3 < fond_offset) {
				sub_zero->x=sub_zero->x+4;
			} else if (sub_zero->x+3 > fond_joueur) {
				liu_kang->x=liu_kang->x-4;
			} else if (liu_kang->x > sub_zero->x) {
				liu_kang->x=liu_kang->x+2;
				sub_zero->x=sub_zero->x-2;
			} else {
				sub_zero->x=sub_zero->x+2;
				liu_kang->x=liu_kang->x-2;
			}
		} else if (degats_liu_kang>0 && degats_sub_zero==0) {
			if (liu_kang->x == liu_kang->old_x) {
				// sub_zero est ejecté
				if (liu_kang->polarite==0) {
					if (sub_zero->x < fond_joueur && sub_zero->old_x < fond_joueur) {
						sub_zero->x=sub_zero->old_x+1;
					}
				} else {
					if (sub_zero->x > fond_offset && sub_zero->old_x > fond_offset) {
						sub_zero->x=sub_zero->old_x-1;
					}
				}
				liu_kang->x=liu_kang->old_x;
			}
			// FIXME : le scoring n'est pas bon de toute manière donc le sang selon le score encore moins.
			bloodDegats((blood_depth+blood_g)%2,degats_liu_kang%BLOOD_SIZE,sub_zero->x+3,corps[degats_liu_kang_corps]); // tête
		} else if (degats_sub_zero>0 && degats_liu_kang==0) {
			if (sub_zero->x == sub_zero->old_x) {
				// liu_kang est ejecté
				if (liu_kang->polarite==0) {
					if (liu_kang->x > fond_offset && liu_kang->old_x > fond_offset) {
						liu_kang->x=liu_kang->old_x-1;
					}
				} else {
					if (liu_kang->x < fond_joueur && liu_kang->old_x < fond_joueur) {
						liu_kang->x=liu_kang->old_x+1;
					}
				}
				sub_zero->x=sub_zero->old_x;
			}
			bloodDegats((blood_depth+blood_g)%2,degats_sub_zero%BLOOD_SIZE,liu_kang->x+3,corps[degats_sub_zero_corps]); // tête
		} else {
			blood();
		} // sinon : dégats des deux côtés à la fois, déjà assez de calculs fait par ici auparavant (?!?)
	}
}

void paf(ANIMATION * liu_kang, ANIMATION * sub_zero) {
	char boum;char i;
	char is_delautrebord_plus_degats=(
	((liu_kang->x >= sub_zero->x) && (liu_kang->x - sub_zero->x < DELAUTREBORD + DEGATS))
	||
	((sub_zero->x > liu_kang->x) && (sub_zero->x - liu_kang->x < DELAUTREBORD + DEGATS))
	);
	//liu_kang->anim_restant 0 1  2  3  4   5
	//liu_kang->animation.p  1 2 [4] 8 [16] 32
	degats_liu_kang=0;
	degats_sub_zero=0;
	//contre_liu_kang=0;
	//contre_sub_zero=0;
	for (i=0;i<3;i++) {
		porte_liu_kang[i]=0;
		contre_liu_kang[i]=0;
		porte_sub_zero[i]=0;
		contre_sub_zero[i]=0;
		if (liu_kang->anim_restant<8) {
			if ((liu_kang->animation->c[i].p & math_2pow[liu_kang->anim_restant]) != 0) {
				// liu_kang PORTE un coup
				if ((liu_kang->phase & PHASE_GEL_ATTAQUE) != PHASE_GEL_ATTAQUE) {
					// il n'est pas gelé (contré auparavant)
					porte_liu_kang[i]=1;
				}
			}
			if ((liu_kang->animation->c[i].c & math_2pow[liu_kang->anim_restant]) != 0) {
				// liu_kang CONTRE un coup
				if ((liu_kang->phase & PHASE_GEL_DEFENCE) != PHASE_GEL_DEFENCE) {
					contre_liu_kang[i]=1;
				}
			}
		}
		if (sub_zero->anim_restant<8) {
			if ((sub_zero->animation->c[i].p & math_2pow[sub_zero->anim_restant]) != 0) {
				// sub_zero PORTE un coup
				if ((sub_zero->phase & PHASE_GEL_ATTAQUE) != PHASE_GEL_ATTAQUE) {
					// il n'est pas gelé (contré auparavant)
					porte_sub_zero[i]=1;
				}
			}
			if ((sub_zero->animation->c[i].c & math_2pow[sub_zero->anim_restant]) != 0) {
				// sub_zero CONTRE un coup
				if ((sub_zero->phase & PHASE_GEL_DEFENCE) != PHASE_GEL_DEFENCE) {
					contre_sub_zero[i]=1;
				}
			}
		}
	}
	if (is_delautrebord_plus_degats) {
		if (liu_kang->x > sub_zero->x) {
			// plus je tape près, plus je score.
			// 10,5 => 5-10+7=2
			// 7,5 => 5-7+7=5
			boum=(sub_zero->x+DELAUTREBORD+DEGATS+BONUS_DEGATS-liu_kang->x)*4-1;
			// 10,5 => 10-5+7=12
			// 7,5 => 7-5+7=9
			//boum=(liu_kang->x+DELAUTREBORD+DEGATS+BONUS_DEGATS-sub_zero->x)*2-1;
		} else if (sub_zero->x > liu_kang->x) {
			boum=(liu_kang->x+DELAUTREBORD+DEGATS+BONUS_DEGATS-sub_zero->x)*4-1;
		} else {
			boum=(DELAUTREBORD+DEGATS+BONUS_DEGATS)*2-1;
		}
		for (i=0;i<3;i++) {
			if (porte_liu_kang[i]) {
				if (contre_sub_zero[i]) {
					// le coup de liu_kang est paré
					if ((sub_zero->allez_retour & ESQUIVE) == 0) {
						// et ce n'était pas une simple esquive
						liu_kang->phase=liu_kang->phase | PHASE_GEL;
					}
				} else {
					// le coup de liu_kang est porté
					degats_liu_kang=boum;
					degats_liu_kang_corps=i;
					// l'espert grimpe car c'est à main nue.
					if (sub_zero_score.espert>300-boum) {
						sub_zero_score.espert=300;
					} else {
						sub_zero_score.espert=sub_zero_score.espert+boum;
					}
				}
			}
			if (porte_sub_zero[i]) {
				if(contre_liu_kang[i]) {
					// le coup de sub_zero est paré
					if ((liu_kang->allez_retour & ESQUIVE) == 0) {
						// et ce n'était pas une simple esquive
						sub_zero->phase=sub_zero->phase | PHASE_GEL;
					}
				} else {
					// le coup de sub_zero est porté
					degats_sub_zero=boum;
					degats_sub_zero_corps=i;
					// l'espert grimpe car c'est à main nue.
					if (liu_kang_score.espert>300-boum) {
						liu_kang_score.espert=300;
					} else {
						liu_kang_score.espert=liu_kang_score.espert+boum;
					}
				}
			}
		}
		hadouken();
	} else {
		// FIXME : un peu d'injustice par là...
		if ((liu_kang->animation->b & HADOUKEN) != 0 && hadouken_n == 0) {
			// liu_kang PORTE un coup HADOUKEN
			if ((liu_kang->animation->c[0].p & math_2pow[liu_kang->anim_restant]) != 0) {
				boum_hadouken_liu_kang=boum_hadouken_liu_kang+2*(BONUS_DEGATS*4-1);
				hadouken_y=HADOUKEN_Y_TETE;
			} else if ((liu_kang->animation->c[1].p & math_2pow[liu_kang->anim_restant]) != 0) {
				boum_hadouken_liu_kang=boum_hadouken_liu_kang+2*(BONUS_DEGATS*4-1);
				hadouken_y=HADOUKEN_Y_VENTRE;
			}
			if (liu_kang->anim_restant == liu_kang->animation->l && boum_hadouken_liu_kang>0) {
				if (liu_kang_score.espert>=100) {
					if (hadoukenDegats(HADOUKEN_SIZE-1, liu_kang, sub_zero)) {
						// consomme de l'espert
						liu_kang_score.espert=liu_kang_score.espert-100;
					} else {
						// ne pas bloquer sa prochaine action (surtout pour un bot)
						liu_kang->allez_retour = liu_kang->allez_retour | MARCHER;
					}
				} else {
					// plouf : aucun pouvoir espert.
					boum_hadouken_liu_kang=0;
					// ne pas bloquer sa prochaine action (surtout pour un bot)
					liu_kang->allez_retour = liu_kang->allez_retour | MARCHER;
				}
			}
		}
		if ((sub_zero->animation->b & HADOUKEN) != 0 && hadouken_n == 0) {
			// sub_zero PORTE un coup HADOUKEN
			if ((sub_zero->animation->c[0].p & math_2pow[sub_zero->anim_restant]) != 0) {
				boum_hadouken_sub_zero=boum_hadouken_sub_zero+2*(BONUS_DEGATS*4-1);
				hadouken_y=HADOUKEN_Y_TETE;
			} else if ((sub_zero->animation->c[1].p & math_2pow[sub_zero->anim_restant]) != 0) {
				boum_hadouken_sub_zero=boum_hadouken_sub_zero+2*(BONUS_DEGATS*4-1);
				hadouken_y=HADOUKEN_Y_VENTRE;
			}
			if (sub_zero->anim_restant == sub_zero->animation->l && boum_hadouken_sub_zero>0) {
				if (sub_zero_score.espert>=100) {
					if (hadoukenDegats(HADOUKEN_SIZE-1, sub_zero, liu_kang)) {
						// consomme de l'espert
						sub_zero_score.espert=sub_zero_score.espert-100;
					} else {
						// ne pas bloquer sa prochaine action (surtout pour un bot)
						sub_zero->allez_retour = sub_zero->allez_retour | MARCHER;
					}
				} else {
					// plouf : aucun pouvoir espert.
					boum_hadouken_sub_zero=0;
					// ne pas bloquer sa prochaine action (surtout pour un bot)
					sub_zero->allez_retour = sub_zero->allez_retour | MARCHER;
				}
			}
		}
		// HADOUKEN_SIZE_INIT-- :p
		hadouken();
	}
	
	if (sub_zero_score.vie < degats_liu_kang) {
		sub_zero_score.vie = 0;//296;
	} else {
		sub_zero_score.vie = sub_zero_score.vie - degats_liu_kang;
	}
	
	if (liu_kang_score.vie < degats_sub_zero) {
		liu_kang_score.vie = 0;//296;
	} else {
		liu_kang_score.vie = liu_kang_score.vie - degats_sub_zero;
	}
}

char refresh = 0;
char refresh_pas = 0;

void refresh_all_progressbar() {
	switch (refresh) {
		case 0:
			refresh_pas=progressbar(3,105,liu_kang_score.vie / 3,300-6,refresh_pas);
			break;
		case 1:
			refresh_pas=progressbar(41,105,sub_zero_score.vie / 3,300-6,refresh_pas);
			break;
		/*case 2:
			refresh_pas=progressbar(3,30,liu_kang_score.furie,200,refresh_pas);
			break;
		case 3:
			refresh_pas=progressbar(3,45,liu_kang_score.aura,200,refresh_pas);
			break;
		case 4:
			refresh_pas=progressbar(3,60,liu_kang_score.expert,200,refresh_pas);
			break;
		case 5:
			refresh_pas=progressbar(3,75,liu_kang_score.tech_perd,100,refresh_pas);
			break;
		case 6:
			refresh_pas=progressbar(13+3,75,liu_kang_score.tech_gagne,100,refresh_pas);
			break;
		case 7:
			refresh_pas=progressbar(3,90,liu_kang_score.tech,200,refresh_pas);
			break;
		case 8:
			refresh_pas=progressbar(52,30,sub_zero_score.furie,200,refresh_pas);
			break;
		case 9:
			refresh_pas=progressbar(52,45,sub_zero_score.aura,200,refresh_pas);
			break;
		case 10:
			refresh_pas=progressbar(52,60,sub_zero_score.expert,200,refresh_pas);
			break;
		case 11:
			refresh_pas=progressbar(52,75,sub_zero_score.tech_perd,100,refresh_pas);
			break;
		case 12:
			refresh_pas=progressbar(13+52,75,sub_zero_score.tech_gagne,100,refresh_pas);
			break;
		case 13:
			refresh_pas=progressbar(52,90,sub_zero_score.tech,200,refresh_pas);
			break;*/
		default :
			refresh_pas=0; refresh=0;//2;
			return;
	}
	if (refresh_pas == 0) {
		// ne raffraichir que la vie
		refresh = (refresh+1) % 2;
	}
}

#define PIEGE_AU_BORD 3

void action(ANIMATION * joueur, char direction_pressed) {
	char deplacement=0; char is_anim_fini;char is_arrete_marcher;char is_same_anim;
	CALQUE * mapping_direction_pressed;

	mapping_direction_pressed=(CALQUE *)(normDIR[joueur->perso]+mapping_direction_calque[joueur->perso][direction_pressed]);
	is_same_anim=(mapping_direction_pressed->o == joueur->animation->o && mapping_direction_pressed->b == joueur->animation->b);

	if ((joueur->allez_retour & RETOUR) != 0) {
		if (joueur->anim_restant == 0) {
			is_anim_fini=1;
		} else {
			is_anim_fini=0;
		}
	} else {
		if (joueur->anim_restant == joueur->animation->l) {
			is_anim_fini=1;
		} else {
			is_anim_fini=0;
		}
	}
	
	if ((joueur->phase & PHASE_GEL) != 0) {
		if (is_same_anim) {
			// coup paré donc gelé
			return;
		} else {
			// nouvelle action
			is_anim_fini=1;
		}
	} else if (joueur->phase != 0) {
		if ((joueur->allez_retour & NON_CYCLIQUE) == 0 && joueur->anim_restant == joueur->animation->l) {
			// animation ENDING || ENDING_KO en boucle
			joueur->anim_restant = 0;
			return;
		} else {
			// special animation : ENDING_KO | ENDING, déjà préchargé
			is_anim_fini=0;
		}
	} else if ((joueur->allez_retour & NON_CYCLIQUE) != 0 && is_same_anim) {
		// hypercut : un coup un seul !
		is_anim_fini=0;
		if (joueur->anim_restant == joueur->animation->l) {
			// on permet des points d'attaque sur le dernier sprite de l'anim.
			joueur->phase = PHASE_GEL_ATTAQUE;
			return;
		}
	} else if ((joueur->allez_retour & ALLEZ_RETOUR) != 0) {
		is_anim_fini=0;
	}

	// si le joueur marchait et ne marche plus
	is_arrete_marcher = (joueur->phase == 0) && ((joueur->allez_retour & MARCHER) != 0) && ((mapping_direction_pressed->ar & MARCHER) == 0);

	// si je MARCHE, alors je peux lancer une nouvelle action. Sinon si l'animation est épuisée, alors je peux aussi lancer une nouvelle action
	if (is_arrete_marcher || is_anim_fini) {
		// déclanchement d'une nouvelle animation
		joueur->direction=direction_pressed;
		joueur->phase=0;
		joueur->animation=mapping_direction_pressed;
		joueur->allez_retour=mapping_direction_pressed->ar;
		if ((joueur->direction & DIRECTION_AVANT) != 0) {
			//joueur->allez_retour=joueur->allez_retour | VERS_L_AVANT;
				// pas de simple "RETOUR" ici.
				joueur->anim_restant=0;
		} else if ((joueur->direction & DIRECTION_ARRIERE) != 0) {
			//joueur->allez_retour=joueur->allez_retour | VERS_L_ARRIERE;
			if ((joueur->allez_retour & MARCHER) != 0) {
				// si le joueur marche à reculons.
				joueur->allez_retour = joueur->allez_retour | RETOUR;
				joueur->anim_restant=joueur->animation->l;
			} else {
				joueur->anim_restant=0;
			}
		} else {
				// pas de simple "RETOUR" ici.
				joueur->anim_restant=0;
		}
	} else {
		// jouer l'animation
		// ALLEZ_RETOUR : coup qui se joue de 0 à l-1, et passe à RETOUR (exemple : )
		// RETOUR : coup qui se joue de l-1 à 0
		// ALLEZ_RETOUR : coup qui se joue de 0 à l-1
		
		if ((joueur->allez_retour & ALLEZ_RETOUR) != 0) {
			// animation de type ALLEZ_RETOUR : incremente, puis RETOUR
			if (joueur->anim_restant < joueur->animation->l) {
				joueur->anim_restant = joueur->anim_restant +1;
				if (((joueur->allez_retour & RAPIDEMENT) != 0) && joueur->anim_restant < joueur->animation->l) {
					// patch pour zapper un calque sur deux lors de l'animation marcher.
					joueur->anim_restant = joueur->anim_restant +1;
				}
				if (joueur->anim_restant == joueur->animation->l ) {
					//joueur->anim_restant = joueur->animation->l;
					//joueur->allez_retour = ((joueur->allez_retour & (~ALLEZ_RETOUR)) | RETOUR);
					joueur->allez_retour = joueur->allez_retour ^ (ALLEZ_RETOUR | RETOUR);
				}
			}
		} else if ((joueur->allez_retour & RETOUR) != 0) {
			// animation de type RETOUR : décrémente
			if (joueur->anim_restant > 0) {
				joueur->anim_restant = joueur->anim_restant -1;
				if (((joueur->allez_retour & RAPIDEMENT) != 0) && joueur->anim_restant > 0) {
					// patch pour zapper un calque sur deux lors de l'animation marcher.
					joueur->anim_restant = joueur->anim_restant -1;
				}
			}
		} else {
			// animation de type normale ! incrémente
			if (joueur->anim_restant < joueur->animation->l) {
				joueur->anim_restant = joueur->anim_restant +1;
				if (((joueur->allez_retour & RAPIDEMENT) != 0) && joueur->anim_restant < joueur->animation->l) {
					// patch pour zapper un calque sur deux lors de l'animation marcher.
					joueur->anim_restant = joueur->anim_restant +1;
				}
			}
		}
	}
	
	// dans tout les cas, le personnage subit éventuellement un VERS_L_AVANT ou VERS_L_ARRIERE
	
	if (((joueur->direction & DIRECTION_AVANT) != 0) && ((joueur->direction & DIRECTION_ARRIERE) != 0)) {
		// un idiot
		deplacement = DEPLACEMENT_AUCUNE;
	} else if ((joueur->direction & DIRECTION_AVANT) != 0) {
		if (joueur->polarite==0) {
			deplacement = DEPLACEMENT_DROITE;
		} else {
			deplacement = DEPLACEMENT_GAUCHE;
		}
	} else if ((joueur->direction & DIRECTION_ARRIERE) != 0) {
		if (joueur->polarite==1) {
			deplacement = DEPLACEMENT_DROITE;
		} else {
			deplacement = DEPLACEMENT_GAUCHE;
		}
	} else {
		deplacement = DEPLACEMENT_AUCUNE;
	}
	
	// une animation MARCHE est en cours
	if ((joueur->allez_retour & MARCHER) != 0) {
		// déplacement
		if (deplacement == DEPLACEMENT_DROITE) {
			// le joueur va a droite
			joueur->x = joueur->old_x + 1;
			
		} else if (deplacement == DEPLACEMENT_GAUCHE) {
			// le joueur va a gauche
			joueur->x = joueur->old_x - 1;
			
		}
	} else if ((joueur->allez_retour & MARCHE) != 0) {
		if (joueur->polarite==0) {
			// le joueur va a droite
			joueur->x = joueur->old_x + 1;
		} else {
			// le joueur va a gauche
			joueur->x = joueur->old_x - 1;
		}
	}
	
	if (joueur->polarite==0 && joueur->x > fond_joueur-PIEGE_AU_BORD) {
		joueur->x=fond_joueur-PIEGE_AU_BORD;
	} else if (joueur->x > fond_joueur) {
		joueur->x=fond_joueur;
	}
	if (joueur->polarite==1 && joueur->x < fond_offset+PIEGE_AU_BORD) {
		joueur->x=fond_offset+PIEGE_AU_BORD;
	} else if (joueur->x < fond_offset) {
		joueur->x=fond_offset;
	}
}

void switch_bank(ANIMATION * joueur) {
	// sur les deux derniers bit : BANK
	switch (joueur->animation->b & 3) {
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

void fix_bank() {
	char i;
	unsigned int j1;unsigned int j2;char b1;char b2;
	j1=(int)&J1A;
	j2=(int)&J2A;
	for (i=0;i<10+1+10;i++) {
		b1 = *(char*)(j1+8);
		b2 = *(char*)(j2+8);
		b1 = b1 & (~3);
		b2 = b2 & (~3);
		if (i<10+1) { // FIXME : pour le moment le premier tas (y compris repos) a 10+1 éléments...
			b1 = b1 | BANK_4;
			b2 = b2 | BANK_6;
		} else {
			b1 = b1 | BANK_5;
			b2 = b2 | BANK_7;
		}
		*(char*)(j1+8)=b1;
		*(char*)(j2+8)=b2;
		j1=j1+10;
		j2=j2+10;
	}
}


char * bot1=0x6300;
char * bot2=0x6301;

char replay;
char is_bot;

unsigned int a;unsigned int b;

void main(void)
{
	char i;char direction;char direction2;
	
	bank4_4000();
	// print peek(&5FFF)
	// poke &5FFF,1
	// print peek(&5FFF)
	//
	// out &7FC4,&C4
	// poke &5FFF,1
	bot1=*((int *)0x5FFA);
	bot2=*((int *)0x5FFC);
	arcade=*((char *)0x5FFE);
	no_combat=*((char *)0x5FFF);

	nb_victory_sub_zero=0;
	nb_victory_liu_kang=0;
	
	// ^^'
	replay=0;
	is_bot=4;
	//for (i=0;i<BLOOD_SIZE;i++) {
	//	current_blood[i][0]=i;
	//	current_blood[i][1]=i;
	//}
	
	// init mapping
	
	normDIR[PERSO_LIU_KANG]=(int)&J1A;
	normDIR[PERSO_SUB_ZERO]=(int)&J2A;
	
	/*for (i=0;i<=DIRECTION_AVANT+DIRECTION_ARRIERE+DIRECTION_HAUT+DIRECTION_BAS+DIRECTION_FIRE+DIRECTION_FIRE1+DIRECTION_FIRE2;i++) {
		if ((i & DIRECTION_AVANT) == 0 && (i & DIRECTION_ARRIERE) == 0) {
			mapping_direction_calque[PERSO_LIU_KANG][i]=(int)&J1A_repos-normDIR[PERSO_LIU_KANG];
			mapping_direction_calque[PERSO_SUB_ZERO][i]=(int)&J2A_repos-normDIR[PERSO_SUB_ZERO];
		} else {
			mapping_direction_calque[PERSO_LIU_KANG][i]=(int)&J1A.marcher-normDIR[PERSO_LIU_KANG];
			mapping_direction_calque[PERSO_SUB_ZERO][i]=(int)&J2A.marcher-normDIR[PERSO_SUB_ZERO];
		}
	}
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_HAUT | DIRECTION_FIRE]=(int)&J1A.pied_haut-normDIR[PERSO_LIU_KANG]; // attaque haut
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_FIRE]=(int)&J1R.poing_double_jab-normDIR[PERSO_LIU_KANG]; //attaque centre
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_FIRE]=(int)&J1A.pied_milieu-normDIR[PERSO_LIU_KANG]; // attaque milieu
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_BAS | DIRECTION_FIRE]=(int)&J1A.pied_rotatif-normDIR[PERSO_LIU_KANG]; // attaque bas
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_BAS | DIRECTION_FIRE]=(int)&J1A.balayette-normDIR[PERSO_LIU_KANG]; // defense bas
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_HAUT | DIRECTION_FIRE]=(int)&J1A.hypercut-normDIR[PERSO_LIU_KANG]; // defense haut

	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_HAUT | DIRECTION_FIRE]=(int)&J1R.contre_haut-normDIR[PERSO_LIU_KANG]; // contre
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_FIRE]=(int)&J1A.poing_milieu-normDIR[PERSO_LIU_KANG]; // revers
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_BAS | DIRECTION_FIRE]=(int)&J1R.dragon-normDIR[PERSO_LIU_KANG]; // humiliation

	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_HAUT]=(int)&J1A.haut-normDIR[PERSO_LIU_KANG]; // haut
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_BAS]=(int)&J1A.bas-normDIR[PERSO_LIU_KANG]; // bas
	// BOT +1
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_HAUT | DIRECTION_BAS]=(int)&J1R.hadouken_personnage-normDIR[PERSO_LIU_KANG];

	//ARCADE
	// => (+ /\ \/)
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_FIRE1]=(int)&J1A.pied_milieu-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_FIRE1 | DIRECTION_HAUT]=(int)&J1A.pied_milieu-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_FIRE1 | DIRECTION_BAS]=(int)&J1A.pied_milieu-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_FIRE2]=(int)&J1A.pied_haut-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_FIRE2 | DIRECTION_HAUT]=(int)&J1A.pied_haut-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_AVANT | DIRECTION_FIRE2 | DIRECTION_BAS]=(int)&J1A.pied_haut-normDIR[PERSO_LIU_KANG];
	// <= (+ /\ \/)
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_FIRE1]=(int)&J1A.poing_milieu-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_FIRE1 | DIRECTION_HAUT]=(int)&J1A.poing_milieu-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_FIRE1 | DIRECTION_BAS]=(int)&J1A.poing_milieu-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_FIRE2]=(int)&J1R.contre_haut-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_FIRE2 | DIRECTION_HAUT]=(int)&J1R.contre_haut-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_ARRIERE | DIRECTION_FIRE2 | DIRECTION_BAS]=(int)&J1R.contre_haut-normDIR[PERSO_LIU_KANG];
	// \/
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_BAS | DIRECTION_FIRE1]=(int)&J1A.balayette-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_BAS | DIRECTION_FIRE2]=(int)&J1A.pied_rotatif-normDIR[PERSO_LIU_KANG];
	// <>
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_FIRE1]=(int)&J1R.poing_double_jab-normDIR[PERSO_LIU_KANG];
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_FIRE2]=(int)&J1A.hypercut-normDIR[PERSO_LIU_KANG];
	// ARCADE +1
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_FIRE1 | DIRECTION_FIRE2]=(int)&J1R.hadouken_personnage-normDIR[PERSO_LIU_KANG];
	
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_HAUT | DIRECTION_FIRE]=(int)&J2R.hadouken1_personnage-normDIR[PERSO_SUB_ZERO]; // attaque haut
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_FIRE]=(int)&J2A.poing_double_jab-normDIR[PERSO_SUB_ZERO]; //attaque centre
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_FIRE]=(int)&J2A.pied_retourne-normDIR[PERSO_SUB_ZERO]; //attaque milieu
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_BAS | DIRECTION_FIRE]=(int)&J2R.flaque-normDIR[PERSO_SUB_ZERO]; // attaque bas
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_BAS | DIRECTION_FIRE]=(int)&J2A.balayette-normDIR[PERSO_SUB_ZERO]; // defense bas
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_HAUT | DIRECTION_FIRE]=(int)&J2R.hypercut-normDIR[PERSO_SUB_ZERO]; // defense haut

	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_HAUT | DIRECTION_FIRE]=(int)&J2R.poing_droit-normDIR[PERSO_SUB_ZERO]; // contre
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_FIRE]=(int)&J2A.poing_gauche-normDIR[PERSO_SUB_ZERO]; // revers
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_BAS | DIRECTION_FIRE]=(int)&J2A.zombi-normDIR[PERSO_SUB_ZERO]; // humiliation

	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_HAUT]=(int)&J2A.haut-normDIR[PERSO_SUB_ZERO]; // haut
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_BAS]=(int)&J2A.bas-normDIR[PERSO_SUB_ZERO]; // bas

	//ARCADE
	// => (+ /\ \/)
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_FIRE1]=(int)&J2A.balayette-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_FIRE1 | DIRECTION_HAUT]=(int)&J2A.balayette-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_FIRE1 | DIRECTION_BAS]=(int)&J2A.balayette-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_FIRE2]=(int)&J2A.pied_retourne-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_FIRE2 | DIRECTION_HAUT]=(int)&J2A.pied_retourne-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_AVANT | DIRECTION_FIRE2 | DIRECTION_BAS]=(int)&J2A.pied_retourne-normDIR[PERSO_SUB_ZERO];
	// <= (+ /\ \/)
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_FIRE1]=(int)&J2R.poing_droit-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_FIRE1 | DIRECTION_HAUT]=(int)&J2R.poing_droit-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_FIRE1 | DIRECTION_BAS]=(int)&J2R.poing_droit-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_FIRE2]=(int)&J2R.hypercut-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_FIRE2 | DIRECTION_HAUT]=(int)&J2R.hypercut-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_ARRIERE | DIRECTION_FIRE2 | DIRECTION_BAS]=(int)&J2R.hypercut-normDIR[PERSO_SUB_ZERO];
	// \/
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_BAS | DIRECTION_FIRE1]=(int)&J2R.flaque-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_BAS | DIRECTION_FIRE2]=(int)&J2R.hadouken1_personnage-normDIR[PERSO_SUB_ZERO];
	// <>
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_FIRE1]=(int)&J2A.poing_gauche-normDIR[PERSO_SUB_ZERO];
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_FIRE2]=(int)&J2A.poing_double_jab-normDIR[PERSO_SUB_ZERO];
	
	// PHASES
	mapping_phase_calque[PERSO_LIU_KANG][PHASE_REPOS]=(int)&J1A_repos-normDIR[PERSO_LIU_KANG];
	mapping_phase_calque[PERSO_LIU_KANG][PHASE_KO]=(int)&J1R.ko-normDIR[PERSO_LIU_KANG];
	mapping_phase_calque[PERSO_LIU_KANG][PHASE_FATALITY]=(int)&J1R.fatality-normDIR[PERSO_LIU_KANG];
	mapping_phase_calque[PERSO_LIU_KANG][PHASE_VICTORY]=(int)&J1R.victory-normDIR[PERSO_LIU_KANG];
	mapping_phase_calque[PERSO_SUB_ZERO][PHASE_REPOS]=(int)&J2A_repos-normDIR[PERSO_SUB_ZERO];
	mapping_phase_calque[PERSO_SUB_ZERO][PHASE_KO]=(int)&J2R.ko-normDIR[PERSO_SUB_ZERO];
	mapping_phase_calque[PERSO_SUB_ZERO][PHASE_FATALITY]=(int)&J2R.fatality-normDIR[PERSO_SUB_ZERO];
	mapping_phase_calque[PERSO_SUB_ZERO][PHASE_VICTORY]=(int)&J2A.victory-normDIR[PERSO_SUB_ZERO];
	*/
	// against "so said EVELYN the modified DOG" => volatile
	// volatile char layer=0;volatile char x=10;//char z=0;
	// char aaah=3;

	raster_halt();

	//intro en &4000
	SetupDOS();
	//calque4000();
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
#ifndef NO_SOUND
	LoadFile("sks8000.bin", (char *)0x8000);
	switch (no_combat) {
		case 0:
			LoadFile("mkbo9000.bin", (char *)0x9000);
			break;
		case 1:
			LoadFile("SUDOKU-1.BIN", (char *)0x9000);
			break;
		case 2:
			LoadFile("SUDOKU-2.BIN", (char *)0x9000);
			break;
	}
#endif
	vram=precalc_vram();
	
	if (no_combat==2) {
		// test : pour le 3ème type de combat, je fais liu_kang vs liu_kang (ça sature un peu)
		
		//bank0123();
		LoadFile("J1A.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank4_4000();
		transfertEtDecoupe();

		bank0123();
		LoadFile("J1R.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank5_4000();
		transfertEtDecoupe();

		//if (J2R.hadouken2_personnage_patch.l == aaah) { // volatiles... sucks ?
		bank0123();
		LoadFile("J1A.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank6_4000();
		transfertEtDecoupe();

		bank0123();
		LoadFile("J1R.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank7_4000();
		transfertEtDecoupe();

		bank0123();
		LoadFile("J1.map", (char *)normDIR[PERSO_LIU_KANG]); // des sprites
		LoadFile("J1.dir", (char *)mapping_direction_calque[PERSO_LIU_KANG]); // des directions
		LoadFile("J1.pha", (char *)mapping_phase_calque[PERSO_LIU_KANG]); // des phases
		LoadFile("J1.map", (char *)normDIR[PERSO_SUB_ZERO]); // des sprites
		LoadFile("J1.dir", (char *)mapping_direction_calque[PERSO_SUB_ZERO]); // des directions
		LoadFile("J1.pha", (char *)mapping_phase_calque[PERSO_SUB_ZERO]); // des phases
		fix_bank();
	} else if (no_combat==1) {
		// test : pour le 2ème type de combat, j'inverse les joueurs.
		
		//bank0123();
		LoadFile("J2A.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank4_4000();
		transfertEtDecoupe();

		bank0123();
		LoadFile("J2R.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank5_4000();
		transfertEtDecoupe();

		//if (J2R.hadouken2_personnage_patch.l == aaah) { // volatiles... sucks ?
		bank0123();
		LoadFile("J1A.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank6_4000();
		transfertEtDecoupe();

		bank0123();
		LoadFile("J1R.scr", (char *)0xC000); // un scr exporté "linéaire"
		bank7_4000();
		transfertEtDecoupe();

		bank0123();
		LoadFile("J2.map", (char *)normDIR[PERSO_LIU_KANG]); // des sprites
		LoadFile("J2.dir", (char *)mapping_direction_calque[PERSO_LIU_KANG]); // des directions
		LoadFile("J2.pha", (char *)mapping_phase_calque[PERSO_LIU_KANG]); // des phases
		LoadFile("J1.map", (char *)normDIR[PERSO_SUB_ZERO]); // des sprites
		LoadFile("J1.dir", (char *)mapping_direction_calque[PERSO_SUB_ZERO]); // des directions
		LoadFile("J1.pha", (char *)mapping_phase_calque[PERSO_SUB_ZERO]); // des phases
		fix_bank();
	} else {
		//bank0123();
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

		bank0123();
		LoadFile("J1.map", (char *)normDIR[PERSO_LIU_KANG]); // des sprites
		LoadFile("J1.dir", (char *)mapping_direction_calque[PERSO_LIU_KANG]); // des directions
		LoadFile("J1.pha", (char *)mapping_phase_calque[PERSO_LIU_KANG]); // des phases
		LoadFile("J2.map", (char *)normDIR[PERSO_SUB_ZERO]); // des sprites
		LoadFile("J2.dir", (char *)mapping_direction_calque[PERSO_SUB_ZERO]); // des directions
		LoadFile("J2.pha", (char *)mapping_phase_calque[PERSO_SUB_ZERO]); // des phases
		fix_bank();
	}

// et finalement.



calqueC000();
	bank0123();
	mode(1);
	border(0);
	set_palette(combat2_palette[no_combat]);
	scan();
	//bank0123();
	switch (no_combat) {
		case 0:
			LoadFile("fond2.scr", (char *)0xC000);
			//fond_largeur=6*8+3;
			fond_largeur=6*8+3;
			fond_offset=3;
			pixelBloodTerrain=0xF0; // le terrain est principalement rouge, donc rouge sur rouge ici hop
			break;
		case 1:
			LoadFile("fond1.scr", (char *)0xC000);
			//fond_largeur=6*12+2;
			fond_largeur=6*8+3;
			fond_offset=15;
			// patch un peu le dessin de fond afin les racines des arbres soient plus jolies :p
			//erase_frame((unsigned char *)(0xC000 + vram[120]+fond_offset-4),fond_largeur+8,50);
			pixelBloodTerrain=0x0F; // pas de mur de sang => je met la couleur des arbres ici.
			break;
		case 2:
			LoadFile("fond3.scr", (char *)0xC000);
			fond_largeur=6*6+3;
			fond_offset=20;
			pixelBloodTerrain=0xF0; // les bords de l'arène c'est un mur, le sang rouge se dépose dessus
			break;
	}
	
	fond_joueur=fond_largeur+fond_offset-6-1;
	
	while(1){
	blood_depth=0;blood_n=0;
	hadouken_depth=0;hadouken_n=0;
		
	calqueC000();
	//bank0123();

//init liu_kang_score et sub_zero_score
	/*liu_kang_score.furie=100;
	liu_kang_score.aura=196;
	liu_kang_score.expert=100;
	liu_kang_score.tech_perd=30;
	liu_kang_score.tech_gagne=75;
	liu_kang_score.tech=194;*/
	liu_kang_score.espert=300;
	liu_kang_score.vie=296*3;
/*	sub_zero_score.furie=100;
	sub_zero_score.aura=193;
	sub_zero_score.expert=100;
	sub_zero_score.tech_perd=92;
	sub_zero_score.tech_gagne=90;
	sub_zero_score.tech=191;*/
	sub_zero_score.espert=300;
	sub_zero_score.vie=296*3;
	degats_liu_kang=0;
	degats_sub_zero=0;
	boum_hadouken_liu_kang=0;
	boum_hadouken_sub_zero=0;
	
	//init liu_kang et sub_zero
	liu_kang.x=fond_offset+fond_largeur/4;
	liu_kang.old_x=liu_kang.x;
	liu_kang.perso=PERSO_LIU_KANG;
	liu_kang.direction=0;
	liu_kang.phase=0;
	liu_kang.anim_restant=0;
	liu_kang.animation=(CALQUE *)(normDIR[PERSO_LIU_KANG]+mapping_phase_calque[PERSO_LIU_KANG][PHASE_REPOS]);
	liu_kang.allez_retour=liu_kang.animation->ar;
	liu_kang.polarite=0;
	
	sub_zero.x=fond_offset+fond_largeur/2+fond_largeur/4;
	sub_zero.old_x=sub_zero.x;
	sub_zero.perso=PERSO_SUB_ZERO;
	sub_zero.direction=0;
	sub_zero.phase=0;
	sub_zero.anim_restant=0;
	sub_zero.animation=(CALQUE *)(normDIR[PERSO_SUB_ZERO]+mapping_phase_calque[PERSO_SUB_ZERO][PHASE_REPOS]);
	sub_zero.allez_retour=sub_zero.animation->ar;
	sub_zero.polarite=1;

	
	// fond
	erase_frame((unsigned char *)(0xC000 + vram[120]+fond_offset),fond_largeur,50);
	
	// score
	//locate(4,1);printf("THSF 2018");
	//locate(5,1);printf("00");
	//locate(6,1);printf("00");
	//locate(7,1);printf("99");
	
	optim_bar=0;
	for (i=0;i<20;i++) {
		refresh_all_progressbar();
	}
	optim_bar=1;

	// copie complète sur le calque 4000
	memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	if (replay==0) {
		// calibration
		vsync();
		handle_raster(callback_roulette);
		raster();
	}
#ifndef NO_SOUND
	if (is_bot!=3+4) {
		// re-calibration
		vsync();
		// cpctelera-1.4.2/examples/medium/arkosAudio
		cpct_akp_musicInit(); //(void *)0x4000);
		// re-calibration
		vsync();
	}
#endif
	if (is_bot==4) {
		// faut bien démarrer la musique au début du jeu quand même...
		is_bot=3+4;
	}

	// optim : invariants
	a=0x4000+fond_offset;
	b=0xC000+fond_offset;

	replay=0;
	is_vsync=0;
	
	// faire une boucle qui :
	while(!replay){
		
	// affiche C000 pendant qu'on recopie de C000 vers 4000 la "zone de combat"
	while (is_vsync!=2) {
		if (is_vsync>2) {
			// saturation !
			// combat2.map.border_raster_begin2=>017B, WinAPE debug breakpoint : *#017B
			border_raster_begin2();
		}
	}
	is_vsync=0;
	calqueC000();
	//bank0123();

	refresh_all_progressbar();
	espertRender(3,liu_kang_score.espert);
	espertRender(41,sub_zero_score.espert);
	
	//for (i=120;i<120+50;i++) {
	//	memcpy((char *)(0x4000 + vram[i]+liu_kang.x-1), (char *)(0xC000 + vram[i]+liu_kang.x-1), 6+2);
	//	memcpy((char *)(0x4000 + vram[i]+sub_zero.x-1), (char *)(0xC000 + vram[i]+sub_zero.x-1), 6+2);
	//}
	
	switch (no_combat) { // LOL bug 3ème param memcpy : degradation perf si variable.
		case 0:
			// optimisation
			for (i=120;i<120+50;i++) {
				// utiliser du min/max sur x/old_x ?
				memcpy((char *)(a + vram[i]), (char *)(b + vram[i]), 6*8+3); // memcpy(destination,source,longueur)
			}
			break;
		case 1:
			// optimisation
			for (i=120;i<120+50;i++) {
				// utiliser du min/max sur x/old_x ?
				memcpy((char *)(a + vram[i]), (char *)(b + vram[i]), 6*8+3); // memcpy(destination,source,longueur)
			}
			break;
		case 2:
			// optimisation
			for (i=120;i<120+50;i++) {
				// utiliser du min/max sur x/old_x ?
				memcpy((char *)(a + vram[i]), (char *)(b + vram[i]), 6*6+3); // memcpy(destination,source,longueur)
			}
			break;
	}
	
	
	// affiche 4000 pendant qu'on pose deux sprites de 4000 vers C000
	while (is_vsync!=2) {
		if (is_vsync>2) {
			// saturation !
			border_raster_begin2();
		}
	}
	is_vsync=0;
	calque4000();

	//bank0123();
	
	bloodDerender();
	hadoukenDerender();
	
	// touche w pour faire reculer liu_kang (querty)
	check_controller();
	if ((is_bot & 1)!=0) {
		bot1=bot1-3;
		direction=(*bot1 + direction) % 31;
	} else {
		direction=0;
		if (get_key(Key_Joy1Left)) {
			if (liu_kang.polarite==0) {
				direction=direction | DIRECTION_ARRIERE;
			} else {
				direction=direction | DIRECTION_AVANT;
			}
		} else if (get_key(Key_Joy1Right)){
			if (liu_kang.polarite==0) {
				direction=direction | DIRECTION_AVANT;
			} else {
				direction=direction | DIRECTION_ARRIERE;
			}
		}
		if (get_key(Key_Joy1Up)) {
			direction=direction | DIRECTION_HAUT;
		} else if (get_key(Key_Joy1Down)) {
			direction=direction | DIRECTION_BAS;
		}
		
		if (get_key(Key_Joy1Fire1)) {
			if (arcade) {
				direction=direction | DIRECTION_FIRE1;
			} else {
				direction=direction | DIRECTION_FIRE;
			}
		}
		if (get_key(Key_Joy1Fire2)) {
			if (arcade) {
				direction=direction | DIRECTION_FIRE2;
			} else {
				direction=direction | DIRECTION_FIRE;
			}
		}
	}

	if ((is_bot & 2)!=0) {
		bot2=bot2+5;
		direction2=(*bot2 + direction2) % 31;
	} else {
		direction2=0;
		if (get_key(Key_R_Joy2Left)) {
			if (sub_zero.polarite==0) {
				direction2=direction2 | DIRECTION_ARRIERE;
			} else {
				direction2=direction2 | DIRECTION_AVANT;
			}
		} else if (get_key(Key_T_Joy2Right)) {
			if (sub_zero.polarite==0) {
				direction2=direction2 | DIRECTION_AVANT;
			} else {
				direction2=direction2 | DIRECTION_ARRIERE;
			}
		}
		if (get_key(Key_6_Joy2Up)) {
			direction2=direction2 | DIRECTION_HAUT;
		} else if (get_key(Key_5_Joy2Down)) {
			direction2=direction2 | DIRECTION_BAS;
		}
		if (get_key(Key_G_Joy2Fire1)) {
			if (arcade) {
				direction2=direction2 | DIRECTION_FIRE1;
			} else {
				direction2=direction2 | DIRECTION_FIRE;
			}
		}
		if (get_key(Key_F_Joy2Fire2)) {
			if (arcade) {
				direction2=direction2 | DIRECTION_FIRE2;
			} else {
				direction2=direction2 | DIRECTION_FIRE;
			}
		}
	}
	
	if ((is_bot==3+4 && (sub_zero.phase==PHASE_VICTORY || liu_kang.phase == PHASE_VICTORY || (sub_zero.phase==PHASE_FATALITY && liu_kang.phase == PHASE_FATALITY)))) {
		// auto new game (cool pour demo/musique en continue => mais si on souhaite faire des pronostiques on appui alors sur Key_C :p)
		is_bot=3+4;
		replay=1;
	}
	if (get_key(Key_X)) {
		// auto new game
		is_bot=4;
		replay=1;
	}
	if (get_key(Key_C)) {
		// new game
		is_bot=3;
		replay=1;
	}
	if (get_key(Key_V)) {
		// new game
		is_bot=1;
		replay=1;
	}
	if (get_key(Key_B)) {
		// new game
		is_bot=2;
		replay=1;
	}
	if (get_key(Key_N)) {
		// new game
		is_bot=0;
		replay=1;
	}
	
	liu_kang.old_x=liu_kang.x;
	sub_zero.old_x=sub_zero.x;
	
	if (sub_zero.phase == PHASE_FATALITY || sub_zero.phase == PHASE_VICTORY) {
		// fatality
		direction2=0;
	} else if (sub_zero.phase == PHASE_KO) {
		// ko in progress
		if (sub_zero_score.vie==0) {
			sub_zero.anim_restant=0;
			// FIXME ne peux pas marcher quand on réinjecte J1.MAP et J1.DIR...
			sub_zero.animation=(CALQUE *)(normDIR[PERSO_SUB_ZERO]+mapping_phase_calque[PERSO_SUB_ZERO][PHASE_FATALITY]);
			sub_zero.allez_retour=sub_zero.animation->ar;
			sub_zero.phase=PHASE_FATALITY;

			// victory
			if (sub_zero.x<fond_offset+fond_largeur/2) {
				liu_kang.x=sub_zero.x+fond_largeur/4;
			} else {
				liu_kang.x=fond_offset+fond_largeur/4;
			}
			liu_kang.anim_restant=0;
			liu_kang.animation=(CALQUE *)(normDIR[PERSO_LIU_KANG]+mapping_phase_calque[PERSO_LIU_KANG][PHASE_VICTORY]);
			liu_kang.allez_retour=liu_kang.animation->ar;
			liu_kang.phase=PHASE_VICTORY;
			if (nb_victory_liu_kang<176 && nb_victory_sub_zero<176) {
				nb_victory_liu_kang++;
				victoryCounterRender(3+1,nb_victory_liu_kang);
			}
			direction=0;
		}
		direction2=0;
	} else if (sub_zero_score.vie==0) {
		// ko
		blood_depth=0;
		hadouken_depth=0;
		sub_zero.anim_restant=0;
		sub_zero.animation=(CALQUE *)(normDIR[PERSO_SUB_ZERO]+mapping_phase_calque[PERSO_SUB_ZERO][PHASE_KO]);
		sub_zero.allez_retour=sub_zero.animation->ar;
		sub_zero.phase=PHASE_KO;
		sub_zero_score.vie=296/2; // 15% pour aller au fatality
		direction2=0;
	}
	
	if (liu_kang.phase == PHASE_FATALITY || liu_kang.phase == PHASE_VICTORY) {
		// fatality
		direction=0;
	} else if (liu_kang.phase == PHASE_KO) {
		// ko in progress
		if (liu_kang_score.vie==0) {
			liu_kang.anim_restant=0;
			liu_kang.animation=(CALQUE *)(normDIR[PERSO_LIU_KANG]+mapping_phase_calque[PERSO_LIU_KANG][PHASE_FATALITY]);
			liu_kang.allez_retour=liu_kang.animation->ar;
			liu_kang.phase=PHASE_FATALITY;
			
			// victory
			if (liu_kang.x<fond_offset+fond_largeur/2) {
				sub_zero.x=liu_kang.x+fond_largeur/4;
			} else {
				sub_zero.x=fond_offset+fond_largeur/4;
			}
			sub_zero.anim_restant=0;
			sub_zero.animation=(CALQUE *)(normDIR[PERSO_SUB_ZERO]+mapping_phase_calque[PERSO_SUB_ZERO][PHASE_VICTORY]);
			sub_zero.allez_retour=sub_zero.animation->ar;
			sub_zero.phase=PHASE_VICTORY;
			if (nb_victory_liu_kang<176 && nb_victory_sub_zero<176) {
				nb_victory_sub_zero++;
				victoryCounterRender(41+1,nb_victory_sub_zero);
			}
			direction2=0;
		}
		direction=0;
	} else if (liu_kang_score.vie==0) {
		// ko
		blood_depth=0;
		hadouken_depth=0;
		liu_kang.anim_restant=0;
		liu_kang.animation=(CALQUE *)(normDIR[PERSO_LIU_KANG]+mapping_phase_calque[PERSO_LIU_KANG][PHASE_KO]);
		liu_kang.allez_retour=liu_kang.animation->ar;
		liu_kang.phase=PHASE_KO;
		liu_kang_score.vie=296/2; // 15% pour aller au fatality
		direction=0;
	}

	if (liu_kang.phase==PHASE_KO && sub_zero.phase==PHASE_KO) {
		liu_kang.phase=PHASE_FATALITY;
		liu_kang_score.vie=0;
		sub_zero.phase=PHASE_FATALITY;
		sub_zero_score.vie=0;
	}
	
	action(&liu_kang,direction);
	
	action(&sub_zero,direction2);

	if (!(sub_zero.phase==PHASE_VICTORY || liu_kang.phase == PHASE_VICTORY || (sub_zero.phase==PHASE_FATALITY && liu_kang.phase == PHASE_FATALITY))) {
		paf(&liu_kang,&sub_zero);
	}
	check_mur(&liu_kang,&sub_zero);

	// sang par ici ?
	erase_frame((unsigned char *)(0xC000 + vram[120]+liu_kang.old_x),6,50);
	
	erase_frame((unsigned char *)(0xC000 + vram[120]+sub_zero.old_x),6,50);
	
	if (liu_kang.polarite == 1) {
		switch_bank(&liu_kang);
		//put_frame((unsigned char *)(0xC000 + vram[120]+liu_kang.x),6,50,0x4000+((6*50)*(liu_kang.animation->o+liu_kang.anim_restant)));
		put_inversed_frame((unsigned char *)(0xC000 + vram[120]+liu_kang.x),6,50,0x4000+((6*50)*(liu_kang.animation->o+liu_kang.anim_restant)));

		switch_bank(&sub_zero);
		put_frame_transparent((unsigned char *)(0xC000 + vram[120]+sub_zero.x),6,50,0x4000+((6*50)*(sub_zero.animation->o+sub_zero.anim_restant)));
	} else {
		switch_bank(&sub_zero);
		//put_frame((unsigned char *)(0xC000 + vram[120]+sub_zero.x),6,50,0x4000+((6*50)*(sub_zero.animation->o+sub_zero.anim_restant)));
		put_inversed_frame((unsigned char *)(0xC000 + vram[120]+sub_zero.x),6,50,0x4000+((6*50)*(sub_zero.animation->o+sub_zero.anim_restant)));

		switch_bank(&liu_kang);
		put_frame_transparent((unsigned char *)(0xC000 + vram[120]+liu_kang.x),6,50,0x4000+((6*50)*(liu_kang.animation->o+liu_kang.anim_restant)));
	}
	
	// sang et hadouken !
	bank0123();
	bloodRender();
	hadoukenRender();
	
	//bank0123();
	
	}// while !replay
	}// while 1
}