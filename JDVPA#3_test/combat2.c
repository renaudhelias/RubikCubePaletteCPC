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
#endif

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

void border_raster_begin2()
{
border_raster_begin();
/*  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set the BORDER to un peu de violet...
;red border
 ld BC,#0x7F10
 ld A,#0x5D
 out (C),C
 out (C),A
  __endasm;*/
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
		border_raster_begin();
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


void put_byte(char nX, char nY, unsigned char nByte) {
	unsigned char * pByteAddress = 0xC000 + vram[nY] + nX;
	*pByteAddress = nByte;
	pByteAddress = 0x4000 + vram[nY] + nX;
	*pByteAddress = nByte;
}

// on trace TAILLE_PAS*8 pixels à chaque lancement de progressbar()
char optim_bar=0;
#define TAILLE_PAS 4
char progressbar(char x, char y, unsigned int value, unsigned int max, char pas) {
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
	char c; // contre le coup
	char p; // porte le coup
	char b; // bank
	char ar; // allez_retour
} CALQUE;

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
	//CALQUE balayette2; // cyclique + avance
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
#define VERS_L_AVANT 16
#define VERS_L_ARRIERE 32
#define RAPIDEMENT 64
#define NON_CYCLIQUE 128

// J1A.adresse : bank4_4000();
const struct CALQUE_J1A J1A= {
	.marcher={0,8,0,0,BANK_4,MARCHE | MARCHER | RAPIDEMENT},
	.haut={9,0,0,0,BANK_4,0},
	.bas={10,0,0,0,BANK_4,0},
	//.tres_haut={11,0,0,0,BANK_4,0},
	.pied_haut={12,3,CONTRE_EN_2 | CONTRE_EN_3,PORTE_EN_4,BANK_4,ALLEZ_RETOUR},
	.pied_milieu={16,3,CONTRE_EN_2, PORTE_EN_3 | PORTE_EN_4,BANK_4,ALLEZ_RETOUR},
	//.genoux_milieu={20,1,CONTRE_EN_2,PORTE_EN_2,BANK_4,ALLEZ_RETOUR},
	//.pied_haut2={22,4,CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_4,PORTE_EN_3,BANK_4,0},
	.balayette={27,3,CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_4,PORTE_EN_3,BANK_4,MARCHE},
	.hypercut={31,4,0,PORTE_EN_2|PORTE_EN_3|PORTE_EN_4,BANK_4,NON_CYCLIQUE},
	.poing_milieu={36,1,0,PORTE_EN_2,BANK_4,ALLEZ_RETOUR},
	//.pied_milieu2={38,1,CONTRE_EN_1 ,PORTE_EN_2,BANK_4,ALLEZ_RETOUR},
	//.balayette2={40,2,CONTRE_EN_2,PORTE_EN_3,BANK_4,0},
	.pied_rotatif={43,8,CONTRE_EN_5 | CONTRE_EN_6, PORTE_EN_3 | PORTE_EN_5 | PORTE_EN_7 ,BANK_4,MARCHE}
};

struct CALQUE_J1R {
	CALQUE victory; // cyclique
	CALQUE fatality; // statique (stoppé au 3)
	//CALQUE hypercut2; // cyclique (sinon ridicule...)
	//CALQUE hadouken_personnage; // statique (stoppé au 4), la boule de feu affiché ensuite juste à droite du sprite, collée.
	//CALQUE hadouken_fire; // cyclique
	CALQUE ko; // cyclique
	CALQUE poing_double_jab; // cyclique, porté en 2/5 et 5/5
	CALQUE contre_haut; // allez-retour
	//CALQUE macarena_milieu; // cyclique, porté en 2/5 et 5/5
	CALQUE dragon; // statique, enchaine avec dragon_big
	//CALQUE dragon_big; // une seule image mais deux sprites ! => un dragon c un hadouken avec un seul calque secondaire (NON_CYCLIQUE, et sans MARCHE)
	//CALQUE contre_haut2; // allez-retour
};

// J1R.adresse : bank5_4000();
const struct CALQUE_J1R J1R= {
	.victory={0,5,0,0,BANK_5 | ENDING,0},
	.fatality={6,2,0,0,BANK_5 | ENDING | ENDING_KO,NON_CYCLIQUE},
	//.hypercut2={9,3,0,PORTE_EN_4,BANK_5,NON_CYCLIQUE},
	//.hadouken_personnage={13,3,0,0,BANK_5 | HADOUKEN,0},
	//.hadouken_fire={17,8,0,0,BANK_5,0},
	.ko={26,5,0,0,BANK_5 | ENDING_KO,0},
	.poing_double_jab={32,4,0,PORTE_EN_2 | PORTE_EN_5,BANK_5,0},
	.contre_haut={37,1,CONTRE_EN_1 | CONTRE_EN_2,0,BANK_5,ALLEZ_RETOUR},
	//.macarena_milieu={39,4,0,0,BANK_5,0},
	.dragon={44,2,0,0,BANK_5 /*| HADOUKEN*/,NON_CYCLIQUE},
	//.dragon_big={47,1,0,0,BANK_5,0},
	//.contre_haut2={49,1,CONTRE_EN_1 | CONTRE_EN_2,0,BANK_5,ALLEZ_RETOUR}
};

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
	.pied_haut={0,7,CONTRE_EN_1 | CONTRE_EN_2 | CONTRE_EN_3 | CONTRE_EN_4,PORTE_EN_4,BANK_6,0},
	//.pied_haut2={8,2,CONTRE_EN_2 | CONTRE_EN_3 | CONTRE_EN_4,PORTE_EN_1,BANK_6,ALLEZ_RETOUR},
	//.genoux_haut={11,1,CONTRE_EN_1 |CONTRE_EN_2,PORTE_EN_2,BANK_6,ALLEZ_RETOUR},
	.pied_retourne={13,6,CONTRE_EN_2 |CONTRE_EN_6,PORTE_EN_3 | PORTE_EN_4 | PORTE_EN_5,BANK_6,0},
	.balayette={20,3,CONTRE_EN_1|CONTRE_EN_2|CONTRE_EN_4,PORTE_EN_3,BANK_6,MARCHE},
	.marcher={24,9,0,0,BANK_6,MARCHE | MARCHER | RAPIDEMENT},
	.haut={34,0,0,0,BANK_6,0},
	.bas={35,0,0,0,BANK_6,0},
	.zombi={36,0,0,0,BANK_6,0},
	.victory={37,1,0,0,BANK_6 | ENDING,0},//ALLEZ_RETOUR},
	.poing_double_jab={39,7,0,PORTE_EN_2 | PORTE_EN_3 | PORTE_EN_5 | PORTE_EN_6,BANK_6,0},
	//.aie={48,0,0,0,BANK_6,0},
	.poing_gauche={49,2,0,PORTE_EN_2|PORTE_EN_3,BANK_6,ALLEZ_RETOUR}
};

struct CALQUE_J2R{
	CALQUE poing_droit; // allez-retour
	CALQUE ko; // cyclique
	CALQUE fatality; // statique (stoppé au 5)
	//CALQUE hadouken1_personnage; // statique (stoppé au 10), la boule de feu affiché ensuite juste à droite du sprite, collée.
	//CALQUE hadouken1_fire; // boule de neige
	//CALQUE hadouken2_personnage; // 1 2 3
	//CALQUE hadouken2_fire; // mega fire
	//CALQUE hadouken2_personnage_patch; // p3 p1 p2 1 2 3
	CALQUE hypercut; // cyclique porté en 3/5
	//CALQUE coup_bas; // allez-retour
	CALQUE flaque; //cyclique
};

// J2R.adresse : bank7_4000();
const struct CALQUE_J2R J2R= {
	.poing_droit={0,1,0,PORTE_EN_2,BANK_7,ALLEZ_RETOUR},
	.ko={2,4,0,0,BANK_7 | ENDING_KO,0},
	.fatality={7,4,0,0,BANK_7 | ENDING | ENDING_KO,NON_CYCLIQUE},
	//.hadouken1_personnage={12,9,0,0,BANK_7 | HADOUKEN,0},
	//.hadouken1_fire={22,0,0,0,BANK_7,0},
	//.hadouken2_personnage={23,2,0,0,BANK_7 | HADOUKEN,0},
	//.hadouken2_fire={26,8,0,0,BANK_7,0},
	//.hadouken2_personnage_patch={35,2,0,0,BANK_7,0},
	.hypercut={38,2,0,PORTE_EN_1|PORTE_EN_2,BANK_7,NON_CYCLIQUE},
	//.coup_bas={43,1,0,PORTE_EN_2,BANK_7,ALLEZ_RETOUR},
	.flaque={45,6,0,PORTE_EN_5|PORTE_EN_6|PORTE_EN_7,BANK_7 | FREEZE,0}
};

#define PERSO_LIU_KANG 0
#define PERSO_SUB_ZERO 1

typedef struct {
	char perso; // identifiant du jouer
	char direction;
	CALQUE * animation;
	char anim_restant; // decompte un CALQUE.l
	char allez_retour; // si ALLEZ ou RETOUR, decompte aussi un allez-retour de l'anim (ALLEZ, puis RETOUR, puis 0)
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

#define DEGATS 5
char degats_liu_kang;
char degats_sub_zero;
char contre_liu_kang;
char contre_sub_zero;
void check_mur(ANIMATION * liu_kang, ANIMATION * sub_zero) {
	char is_delautrebord=(liu_kang->x+4 > sub_zero->x);
	// pas grave de toute façon il KO... tant pis si on triche ici.
	if (((liu_kang->animation->b & ENDING_KO)!=0) || ((sub_zero->animation->b & ENDING_KO)!=0)
		|| ((sub_zero->animation->b & FREEZE)!=0)) {
		if (is_delautrebord) {
			// animation MARCHE sans MARCHER
			liu_kang->x=liu_kang->old_x;
			sub_zero->x=sub_zero->old_x;
		}
	} else {
	
	//is_liu_kang_attaque = ((liu_kang->allez_retour & MARCHER) == 0);
	//is_liu_kang_avance = (liu_kang->x > liu_kang->old_x);
	//is_sub_zero_attaque = ((sub_zero->allez_retour & MARCHER) == 0);
	//is_sub_zero_avance = (sub_zero->x < sub_zero->old_x);
	
		if (is_delautrebord) {
			// gameplay Barbarian :p - on ne pousse pas le gars sans le frapper.
			if (((liu_kang->allez_retour & MARCHER) == 0) && (liu_kang->x > liu_kang->old_x)
				&& !(((sub_zero->allez_retour & MARCHE) != 0) && ((sub_zero->allez_retour & MARCHER) == 0))) {
			// liu_kang attaque en avançant et sub_zero n'attaque pas
				// liu_kang pousse sub_zero
				if (sub_zero->x < 48 && sub_zero->old_x < 48) {
					sub_zero->x=sub_zero->old_x+1;
				} else {
					liu_kang->x=liu_kang->old_x;
				}
				return;
			} else if (((sub_zero->allez_retour & MARCHER) == 0) && (sub_zero->x < sub_zero->old_x)
				&& !(((liu_kang->allez_retour & MARCHE) != 0) && ((liu_kang->allez_retour & MARCHER) != 0))) {
			// sub_zero attaque en avançant et liu_kang n'attaque pas
				// sub_zero pousse liu_kang
				if (liu_kang->x > 3 && liu_kang->old_x > 3) {
					liu_kang->x=liu_kang->old_x-1;
				} else {
					sub_zero->x=sub_zero->old_x;
				}
				return;
			} else {
				// les deux poussent à la fois
				liu_kang->x=liu_kang->old_x;
				sub_zero->x=sub_zero->old_x;
			}
		}

		if (degats_liu_kang>degats_sub_zero) {
			if (liu_kang->x == liu_kang->old_x) {
				// sub_zero est ejecté
				if (sub_zero->x < 48 && sub_zero->old_x < 48) {
					sub_zero->x=sub_zero->old_x+1;
				}
				liu_kang->x=liu_kang->old_x;
			}
		} else if (degats_sub_zero>degats_liu_kang) {
			if (sub_zero->x == sub_zero->old_x) {
				// liu_kang est ejecté
				if (liu_kang->x > 3 && liu_kang->old_x > 3) {
					liu_kang->x=liu_kang->old_x-1;
				}
				sub_zero->x=sub_zero->old_x;
			}
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
	unsigned int vie; // 0-296
} SCORE;

SCORE liu_kang_score;//={100,196,100,30,75,194,100};
SCORE sub_zero_score;//={100,193,100,92,90,191,290};

char refresh = 0;
char refresh_pas = 0;

void paf(ANIMATION * liu_kang, ANIMATION * sub_zero) {
	char boum;
	//liu_kang->anim_restant 0 1  2  3  4   5
	//liu_kang->animation.p  1 2 [4] 8 [16] 32
	degats_liu_kang=0;
	degats_sub_zero=0;
	contre_liu_kang=0;
	contre_sub_zero=0;
	if (liu_kang->x+4+DEGATS > sub_zero->x) {
		boum=(liu_kang->x+4+DEGATS-sub_zero->x)*2-1;
		if (liu_kang->anim_restant<8) {
		if ((liu_kang->animation->p & math_2pow[liu_kang->anim_restant]) != 0) {
			// liu_kang PORTE un coup
			degats_liu_kang=boum;
			if (sub_zero_score.vie < boum) {
				sub_zero_score.vie = 0;//296;
			} else {
				sub_zero_score.vie = sub_zero_score.vie - boum;
			}
		}
		if ((liu_kang->animation->c & math_2pow[liu_kang->anim_restant]) != 0) {
			// liu_kang CONTRE un coup
			contre_liu_kang=1;
		}
		}
		if (sub_zero->anim_restant<8) {
		if ((sub_zero->animation->p & math_2pow[sub_zero->anim_restant]) != 0) {
			// sub_zero PORTE un coup
			degats_sub_zero=boum;
			if (liu_kang_score.vie < boum) {
				liu_kang_score.vie = 0;//296;
			} else {
				liu_kang_score.vie = liu_kang_score.vie - boum;
			}
		}
		if ((sub_zero->animation->c & math_2pow[sub_zero->anim_restant]) != 0) {
			// sub_zero CONTRE un coup
			contre_sub_zero=1;
		}
		}
	}
	
	if (contre_sub_zero && ((liu_kang->allez_retour & MARCHER) == 0) && ((liu_kang->animation->b & ENDING_KO) == 0)) {
		degats_liu_kang=0;
		// le coup de liu_kang est paré
		//liu_kang->allez_retour= (liu_kang->allez_retour & MARCHE) | (liu_kang->allez_retour & MARCHER) | NON_CYCLIQUE;
		liu_kang->allez_retour=NON_CYCLIQUE;
		liu_kang->anim_restant=liu_kang->animation->l;
	}
	if (contre_liu_kang && ((sub_zero->allez_retour & MARCHER) == 0) && ((sub_zero->animation->b & ENDING_KO) == 0)) {
		degats_sub_zero=0;
		// le coup de sub_zero est paré
		//sub_zero->allez_retour=(sub_zero->allez_retour & MARCHE) | (sub_zero->allez_retour & MARCHER) | NON_CYCLIQUE;
		sub_zero->allez_retour=NON_CYCLIQUE;
		sub_zero->anim_restant=sub_zero->animation->l;
	}
	
}
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

void action(ANIMATION * joueur, char direction_pressed) {
	char deplacement=0; char is_anim_fini;char is_arrete_marcher;char is_continue_marcher;

	

	if (direction_pressed==32) {
		// special animation : ENDING_KO | ENDING, déjà préchargé
		is_anim_fini=0;
		is_arrete_marcher=0;
		is_continue_marcher=0;
	} else {

	if (((joueur->allez_retour & NON_CYCLIQUE) != 0)
		&& mapping_direction_calque[joueur->perso][direction_pressed]->o == joueur->animation->o
		&& mapping_direction_calque[joueur->perso][direction_pressed]->b == joueur->animation->b) {
		// hypercut : un coup un seul !
		is_anim_fini=0;
	} else if ((joueur->allez_retour & ALLEZ_RETOUR) != 0) {
		is_anim_fini=0;
	} else if ((joueur->allez_retour & RETOUR) != 0) {
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
	
	// si le joueur marchait et ne marche plus
	is_arrete_marcher = ((joueur->allez_retour & MARCHER) != 0) && ((mapping_direction_calque[joueur->perso][direction_pressed]->ar & MARCHER) == 0);
	// sinon si le joueur marchait mais change de direction => à prendre compte
	is_continue_marcher = ((joueur->allez_retour & MARCHER) != 0) && ((mapping_direction_calque[joueur->perso][direction_pressed]->ar & MARCHER) != 0);
	
	is_continue_marcher = is_continue_marcher && ((joueur->allez_retour & (VERS_L_AVANT | VERS_L_ARRIERE)) != 0) && ((mapping_direction_calque[joueur->perso][direction_pressed]->ar & (VERS_L_AVANT | VERS_L_ARRIERE)) != 0);
}
	// si je MARCHE, alors je peux lancer une nouvelle action. Sinon si l'animation est épuisée, alors je peux aussi lancer une nouvelle action
	if (is_continue_marcher || is_arrete_marcher || is_anim_fini) {
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
		
		joueur->animation=mapping_direction_calque[joueur->perso][joueur->direction];
		joueur->allez_retour=mapping_direction_calque[joueur->perso][joueur->direction]->ar;
		if (joueur->perso == PERSO_LIU_KANG) {
			if (deplacement == DEPLACEMENT_AVANCE) {
				joueur->allez_retour=joueur->allez_retour | VERS_L_AVANT;
				 if (is_continue_marcher) {
					if (joueur->anim_restant==joueur->animation->l) {
						joueur->anim_restant=0; // cyclique
					} else {
						joueur->anim_restant=joueur->anim_restant+1;
					}
				} else {
					// pas de simple "RETOUR" ici.
					joueur->anim_restant=0;
				}
			} else if (deplacement == DEPLACEMENT_RECULE) {
				joueur->allez_retour=joueur->allez_retour | VERS_L_ARRIERE;
				if ((joueur->allez_retour & MARCHER) != 0) {
					joueur->allez_retour = joueur->allez_retour | RETOUR;
				}
				if (is_continue_marcher) {
					if (joueur->anim_restant==0) {
						joueur->anim_restant=joueur->animation->l; // cyclique
					} else {
						joueur->anim_restant=joueur->anim_restant-1;
					}
				} else {
					if ((joueur->allez_retour & RETOUR) != 0) {
						joueur->anim_restant=joueur->animation->l;
					} else {
						joueur->anim_restant=0;
					}
				}
			} else {
				// pas de simple "RETOUR" ici.
				joueur->anim_restant=0;
			}
		} else {
			if (deplacement == DEPLACEMENT_AVANCE) {
				joueur->allez_retour=joueur->allez_retour | VERS_L_AVANT;
				if (is_continue_marcher) {
					if (joueur->anim_restant==joueur->animation->l) {
						joueur->anim_restant=0; // cyclique
					} else {
						joueur->anim_restant=joueur->anim_restant+1;
					}
				} else {
					joueur->anim_restant=0;
				}
			} else if (deplacement == DEPLACEMENT_RECULE) {
				joueur->allez_retour=joueur->allez_retour | VERS_L_ARRIERE;
				if ((joueur->allez_retour & MARCHER) != 0) {
					joueur->allez_retour = joueur->allez_retour | RETOUR;
				}
				if (is_continue_marcher) {
					if (joueur->anim_restant==0) {
						joueur->anim_restant=joueur->animation->l; // cyclique
					} else {
						joueur->anim_restant=joueur->anim_restant-1;
					}
				} else {
					if ((joueur->allez_retour & RETOUR) != 0) {
						joueur->anim_restant=joueur->animation->l;
					} else {
						joueur->anim_restant=0;
					}
				}
			} else {
				// pas de simple "RETOUR" ici.
				joueur->anim_restant=0;
			}
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
					joueur->anim_restant = joueur->animation->l;
					joueur->allez_retour = ((joueur->allez_retour & (!ALLEZ_RETOUR)) | RETOUR);
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
			} else {
				//joueur->animation->p=0; // fin d'animation : donc plus de porté ! (cas hypercut)
				//FIXME croiser avec NON_CYCLIQUE ?
				if (direction_pressed == 32 && ((joueur->allez_retour & NON_CYCLIQUE) == 0) ) {
					// animation ENDING || ENDING_KO en boucle
					joueur->anim_restant = 0;
				}
			}
		}
	}
	
	// dans tout les cas, le personnage subit éventuellement un VERS_L_AVANT ou VERS_L_ARRIERE
	
	// une animation MARCHE est en cours
	if ((joueur->allez_retour & MARCHER) != 0) {
		// déplacement
		if ((joueur->direction & DIRECTION_DROITE) != 0) {
			// le joueur va a droite
			joueur->x = joueur->old_x + 1;
			if (joueur->x > 48) {
				joueur->x=48; //3;
			}
		}
		if ((joueur->direction & DIRECTION_GAUCHE) != 0) {
			// le joueur va a gauche
			joueur->x = joueur->old_x - 1;
			if (joueur->x < 3) {
				joueur->x=3; //48;
			}
		}
	} else if ((joueur->allez_retour & MARCHE) != 0) {
		if (joueur->perso==PERSO_LIU_KANG) {
			// le joueur va a droite
			joueur->x = joueur->old_x + 1;
			if (joueur->x > 48) {
				joueur->x=48; //3;
			}
		} else {
			// le joueur va a gauche
			joueur->x = joueur->old_x - 1;
			if (joueur->x < 3) {
				joueur->x=3; //48;
			}
		}
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

#define FREIN 1

// J1A.marcher avec l=2
const CALQUE J1A_repos ={0,2,0,0,BANK_4,MARCHE | MARCHER};
// J2A.marcher avec l=2
const CALQUE J2A_repos ={24,2,0,0,BANK_6,MARCHE | MARCHER};



char * bot1=0x6300;
char * bot2=0x6301;

char replay;
char is_bot;

void main(void)
{
	char i;char direction;char direction2;
	
	
	// ^^'
	replay=0;
	is_bot=3;
	
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
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_DROITE | DIRECTION_HAUT | DIRECTION_FIRE]=&J1A.pied_haut; // attaque haut
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_FIRE]=&J1R.poing_double_jab; //attaque centre
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_DROITE | DIRECTION_FIRE]=&J1A.pied_milieu; // attaque milieu
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_DROITE | DIRECTION_BAS | DIRECTION_FIRE]=&J1A.pied_rotatif; // attaque bas
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_BAS | DIRECTION_FIRE]=&J1A.balayette; // defense bas
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_HAUT | DIRECTION_FIRE]=&J1A.hypercut; // defense haut

	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_GAUCHE | DIRECTION_HAUT | DIRECTION_FIRE]=&J1R.contre_haut; // contre
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_GAUCHE | DIRECTION_FIRE]=&J1A.poing_milieu; // revers
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_GAUCHE | DIRECTION_BAS | DIRECTION_FIRE]=&J1R.dragon; // humiliation

	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_HAUT]=&J1A.haut; // haut
	mapping_direction_calque[PERSO_LIU_KANG][DIRECTION_BAS]=&J1A.bas; // bas

	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_GAUCHE | DIRECTION_HAUT | DIRECTION_FIRE]=&J2A.pied_haut; // attaque haut
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_FIRE]=&J2A.poing_double_jab; //attaque centre
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_GAUCHE | DIRECTION_FIRE]=&J2A.pied_retourne; //attaque milieu
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_GAUCHE | DIRECTION_BAS | DIRECTION_FIRE]=&J2R.flaque; // attaque bas
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_BAS | DIRECTION_FIRE]=&J2A.balayette; // defense bas
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_HAUT | DIRECTION_FIRE]=&J2R.hypercut; // defense haut

	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_DROITE | DIRECTION_HAUT | DIRECTION_FIRE]=&J2R.poing_droit; // contre
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_DROITE | DIRECTION_FIRE]=&J2A.poing_gauche; // revers
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_DROITE | DIRECTION_BAS | DIRECTION_FIRE]=&J2A.zombi; // humiliation

	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_HAUT]=&J2A.haut; // haut
	mapping_direction_calque[PERSO_SUB_ZERO][DIRECTION_BAS]=&J2A.bas; // bas

	// against "so said EVELYN the modified DOG" => volatile
	// volatile char layer=0;volatile char x=10;//char z=0;
	// char aaah=3;

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
	LoadFile("sks2000.bin", (char *)0x2000);
	LoadFile("sudo3000.bin", (char *)0x3000);
#endif
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
	
	
	
	while(1){
	calqueC000();
	bank0123();

//init liu_kang_score et sub_zero_score
	/*liu_kang_score.furie=100;
	liu_kang_score.aura=196;
	liu_kang_score.expert=100;
	liu_kang_score.tech_perd=30;
	liu_kang_score.tech_gagne=75;
	liu_kang_score.tech=194;*/
	liu_kang_score.vie=296*3;
/*	sub_zero_score.furie=100;
	sub_zero_score.aura=193;
	sub_zero_score.expert=100;
	sub_zero_score.tech_perd=92;
	sub_zero_score.tech_gagne=90;
	sub_zero_score.tech=191;*/
	sub_zero_score.vie=296*3;
	degats_liu_kang=0;
	degats_sub_zero=0;
	contre_liu_kang=0;
	contre_sub_zero=0;
	
	//init liu_kang et sub_zero
	liu_kang.x=10;
	liu_kang.old_x=liu_kang.x;
	liu_kang.perso=PERSO_LIU_KANG;
	liu_kang.direction=0;
	liu_kang.anim_restant=0;
	liu_kang.allez_retour=J1A_repos.ar;

	liu_kang.animation=&J1A_repos;
	
	sub_zero.x=30;
	sub_zero.old_x=sub_zero.x;
	sub_zero.perso=PERSO_SUB_ZERO;
	sub_zero.direction=0;
	sub_zero.anim_restant=0;
	sub_zero.allez_retour=J2A_repos.ar;

	sub_zero.animation=&J2A_repos;
	
	// fond
	erase_frame((unsigned char *)(0xC000 + vram[120]+3),6*8+3,50);
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
#ifndef NO_SOUND
		// cpctelera-1.4.2/examples/medium/arkosAudio
		cpct_akp_musicInit(); //(void *)0x4000);
#endif
	}





	replay=0;
	is_vsync=0;
	
	// faire une boucle qui :
	while(!replay){
		
	// affiche C000 pendant qu'on recopie de C000 vers 4000 la "zone de combat"
	while (is_vsync!=1) {
		if (is_vsync>1) {
			// saturation !
			border_raster_begin2();
		}
	}
	is_vsync=0;
	calqueC000();
	bank0123();

	refresh_all_progressbar();

	// optimisation
	for (i=120;i<120+50;i++) {
		// utiliser du min/max sur x/old_x ?
		memcpy((char *)(0x4000 + vram[i] + 3), (char *)(0xC000 + vram[i] + 3), 6*8+3); // memcpy(destination,source,longueur)
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


	
	// touche w pour faire reculer liu_kang (querty)
	check_controller();
	direction=0;
	if (get_key(Key_Joy1Left)) {
		direction=direction | DIRECTION_GAUCHE;
	} else if (get_key(Key_Joy1Right)){
		direction=direction | DIRECTION_DROITE;
	}
	if (get_key(Key_Joy1Up)) {
		direction=direction | DIRECTION_HAUT;
	} else if (get_key(Key_Joy1Down)) {
		direction=direction | DIRECTION_BAS;
	}
	if (get_key(Key_Joy1Fire1) || get_key(Key_Joy1Fire2)) {
		direction=direction | DIRECTION_FIRE;
	}

	direction2=0;
	if (get_key(Key_R_Joy2Left)) {
		direction2=direction2 | DIRECTION_GAUCHE;
	} else if (get_key(Key_T_Joy2Right)) {
		direction2=direction2 | DIRECTION_DROITE;
	}
	if (get_key(Key_6_Joy2Up)) {
		direction2=direction2 | DIRECTION_HAUT;
	} else if (get_key(Key_5_Joy2Down)) {
		direction2=direction2 | DIRECTION_BAS;
	}
	if (get_key(Key_G_Joy2Fire1) || get_key(Key_F_Joy2Fire2)) {
		direction2=direction2 | DIRECTION_FIRE;
	}
	
	if ((is_bot & 1)!=0) {
		bot1=bot1-3;
		direction=*bot1 & 31;
	}

	if ((is_bot & 2)!=0) {
		bot2=bot2+5;
		direction2=*bot2 & 31;
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
	
	if (sub_zero.direction == 33) {
		// fatality
		direction2=32;
	} else if (sub_zero.direction == 32) {
		// ko in progress
		direction2=32;
		if (sub_zero_score.vie==0) {
			sub_zero.anim_restant=0;
			sub_zero.allez_retour=J2R.fatality.ar;
			sub_zero.animation=&J2R.fatality;
			sub_zero.direction=33;
			
			// victory
			if (sub_zero.x<20) {
				liu_kang.x=30;
			} else {
				liu_kang.x=10;
			}
			liu_kang.anim_restant=0;
			liu_kang.allez_retour=J1R.victory.ar;
			liu_kang.animation=&J1R.victory;
			liu_kang.direction=33;
			direction2=34;
			direction=34;
		}
	} else if (sub_zero_score.vie==0) {
		// ko
		sub_zero.anim_restant=0;
		sub_zero.allez_retour=J2R.ko.ar;

		sub_zero.animation=&J2R.ko;
		sub_zero.direction=32;
		direction2=34;
		sub_zero_score.vie=296/2; // 15% pour aller au fatality
	}
	
	if (liu_kang.direction == 33) {
		// fatality
		if (direction != 34) { // sans ghost...
			direction=32;
		}
	} else if (liu_kang.direction == 32) {
		// ko in progress
		direction=32;
		if (liu_kang_score.vie==0) {
			liu_kang.anim_restant=0;
			liu_kang.allez_retour=J1R.fatality.ar;
			liu_kang.animation=&J1R.fatality;
			liu_kang.direction=33;
			
			// victory
			if (liu_kang.x<20) {
				sub_zero.x=30;
			} else {
				sub_zero.x=10;
			}
			sub_zero.anim_restant=0;
			sub_zero.allez_retour=J2A.victory.ar;
			sub_zero.animation=&J2A.victory;
			sub_zero.direction=33;
			direction2=34;
			direction=34;
		}
	} else if (liu_kang_score.vie==0) {
		// ko
		liu_kang.anim_restant=0;
		liu_kang.allez_retour=J1R.ko.ar;

		liu_kang.animation=&J1R.ko;
		liu_kang.direction=32;
		direction=34;
		liu_kang_score.vie=296/2; // 15% pour aller au fatality
	}
		
	if (direction!=34) {
		action(&liu_kang,direction);
	}
	
	if (direction2!=34) {
		action(&sub_zero,direction2);
	}

	if (!(direction==34 || direction2==34)) {
		paf(&liu_kang,&sub_zero);
	}
	check_mur(&liu_kang,&sub_zero);

	// sang par ici ?
	erase_frame((unsigned char *)(0xC000 + vram[120]+liu_kang.old_x),6,50);
	
	erase_frame((unsigned char *)(0xC000 + vram[120]+sub_zero.old_x),6,50);

	switch_bank(&liu_kang);
	put_frame((unsigned char *)(0xC000 + vram[120]+liu_kang.x),6,50,0x4000+((6*50)*(liu_kang.animation->o+liu_kang.anim_restant)));

	switch_bank(&sub_zero);
	put_frame_transparent((unsigned char *)(0xC000 + vram[120]+sub_zero.x),6,50,0x4000+((6*50)*(sub_zero.animation->o+sub_zero.anim_restant)));

	}// while !replay
	}// while 1
}