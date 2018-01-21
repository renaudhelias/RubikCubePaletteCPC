#include <stdio.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"

#include "bluegirl.h"
#include "jdvapi_frame.h"

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
#define	CASE_VIDE 18
#define	CURSEUR_BAS_SELECT 7*7
#define EN_HAUT 1
#define EN_BAS 2
#define EN_HAUT_ET_EN_BAS 3
#define SELECT_OFF 0
#define SELECT_ON 1
#define ESPACEMENT 4

/*
 * offset_x
 * offset_y
 * noTile no de l'image à tracer en offset_x,offset_y
 * tailleTile taille de l'image : 15 21 ou 35
 */
void piece(char offset_x,char offset_y,char noTile,char tailleTile) {
char x;
char y;
switch(noTile) {
	case 0 :
		// case blanche
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				put_pixel1(offset_x+x,offset_y+y,2);
			}
		}
	return;
	case 1 :
		// case bleu
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				put_pixel1(offset_x+x,offset_y+y,3);
			}
		}
	return;
	case 2 :
		// triangle 1
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x+y<tailleTile-1) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 3 :
		// triangle 2
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x+y>tailleTile-1) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 4 :
		// triangle 3
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x+tailleTile-1-y<tailleTile-1) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 5 :
		// triangle 4
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x+tailleTile-1-y>tailleTile-1) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 6 :
		// moitié 1
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x<tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 7 :
		// moitié 2
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x>tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 8 :
		// moitié 3
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (y<tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 9 :
		// moitié 4
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (y>tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 10 :
		// carré blanc 1
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x<tailleTile/2 && y<tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 11 :
		// carré blanc 2
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x>tailleTile/2 && y<tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 12 :
		// carré blanc 3
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x>tailleTile/2 && y>tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 13 :
		// carré blanc 4
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x<tailleTile/2 && y>tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,2);
				} else {
					put_pixel1(offset_x+x,offset_y+y,3);
				}
			}
		}
	return;
	case 14 :
		// carré bleu 1
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x<tailleTile/2 && y<=tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,3);
				} else {
					put_pixel1(offset_x+x,offset_y+y,2);
				}
			}
		}
	return;
	case 15 :
		// carré bleu 2
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x>tailleTile/2 && y<=tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,3);
				} else {
					put_pixel1(offset_x+x,offset_y+y,2);
				}
			}
		}
	return;
	case 16 :
		// carré bleu 3
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x>tailleTile/2 && y>=tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,3);
				} else {
					put_pixel1(offset_x+x,offset_y+y,2);
				}
			}
		}
	return;
	case 17 :
		// carré bleu 4
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x<tailleTile/2 && y>=tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,3);
				} else {
					put_pixel1(offset_x+x,offset_y+y,2);
				}
			}
		}
	return;
	case 18 :
		// case vide
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				put_pixel1(offset_x+x,offset_y+y,0);
			}
		}
	return;
	case 19 :
		// bordure rouge
		//for (x=-1;x<=tailleTile;x++) {
		for (x=0;x<tailleTile+2;x++) {
			put_pixel1(offset_x+x-1,offset_y-1,1);
			put_pixel1(offset_x+x-1,offset_y+tailleTile,1);
		}
		//for (y=-1;y<=tailleTile;y++) {
		for (y=0;y<tailleTile+2;y++) {
			put_pixel1(offset_x-1,offset_y+y-1,1);
			put_pixel1(offset_x+tailleTile,offset_y+y-1,1);
		}
	return;
	case 20 :
		// select rouge
		for (x=1;x<tailleTile-1;x++) {
			if (x<=tailleTile/4+1 || x>=tailleTile*3/4) {
				put_pixel1(offset_x+x,offset_y+1,1);
				put_pixel1(offset_x+x,offset_y+tailleTile-2,1);
			}
		}
		for (y=1;y<tailleTile-1;y++) {
			if (y<=tailleTile/4+1 || y>=tailleTile*3/4) {
				put_pixel1(offset_x+1,offset_y+y,1);
				put_pixel1(offset_x+tailleTile-2,offset_y+y,1);
			}
		}
	return;
	case 21 :
		// unselect rouge
		for (x=1;x<tailleTile-1;x++) {
			put_pixel1(offset_x+x,offset_y+1,1);
			put_pixel1(offset_x+x,offset_y+tailleTile-2,1);
		}
		for (y=1;y<tailleTile-1;y++) {
			put_pixel1(offset_x+1,offset_y+y,1);
			put_pixel1(offset_x+tailleTile-2,offset_y+y,1);
		}
	return;
}
}

void fillListe1Piece(char * nbPieces,char n,char curseurHaut,char etatSelect,char etatZone,char bordure) {
char x;char y;
char offset_x;char offset_y;
	x=n/2;
	y=n%2;
	//moveTo
	offset_x=x*(21+3)+2;
	offset_y=y*(21+ESPACEMENT+2*ESPACEMENT)+ESPACEMENT+ESPACEMENT;
	if (bordure==1) {
		piece(offset_x,offset_y,19,21); // bordure rouge
	}
	if (y==0) {
		locate(2+x*3,5);
	} else {
		locate(2+x*3,9);
	}
	printf("%c",nbPieces[n]+48); // texte dessous la case : nombre de pièces
	if (nbPieces[n]>0) {
		piece(offset_x,offset_y,n,21); // la piece
	} else {
		piece(offset_x,offset_y,18,21); // case vide
	}
	if ((n==curseurHaut) && (etatZone==EN_HAUT)) {
		if (etatSelect==SELECT_ON) {
			piece(offset_x,offset_y,20,21);
		} else {
			piece(offset_x,offset_y,21,21);
		}
	}
}

/*
 * nbPieces[]
 * curseurHaut : position du curseur, EN_HAUT
 * etatSelect : si on affiche un carré rouge aux bords continue (OFF) ou discontinue (ON)
 * etatZone : EN_BAS ou EN_HAUT : si EN_BAS alors ne pas afficher de curseur via cette fonction
 */
void fillListePieces(char * nbPieces,char curseurHaut,char etatSelect,char etatZone) {
char n;
for (n=0;n<18;n++) {
	fillListe1Piece(nbPieces,n,curseurHaut,etatSelect,etatZone,1);
}
}


char private_preview[7][7];

/*
 * preview[][]
 * niveauTaille : 15,21,35
 * niveauNb : 3,5,7
 * 
 * https://stackoverflow.com/questions/16724368/how-to-pass-a-2d-array-by-pointer-in-c
 */
void fillPreview(char ** preview,char niveauTaille,char niveauNb) {
	char offset_x;char offset_y;char x; char y;
	//moveTo
	offset_x=2;
	offset_y=2*(21+2*ESPACEMENT)+2*ESPACEMENT+6*ESPACEMENT+2+1;
	piece(offset_x,offset_y,19,105); // bordure rouge
	
	for (x=0;x<niveauNb;x=x+1) {
		for (y=0;y<niveauNb;y=y+1) {
			//piece(offset_x+x*21,offset_y+y*21,*preview[x*niveauNb*2+y*2],niveauTaille); // la piece
			piece(offset_x+x*21,offset_y+y*21,private_preview[x][y],niveauTaille); // la piece
		}
	}
}

char private_grille[7][7];

void fill1Grille(char ** grille,char niveauTaille,char niveauNb,char n, char curseurBas,char etatSelect,char etatZone) {
	char offset_x;char offset_y;char x; char y;
	offset_x=105+2+3;
	offset_y=2*(21+2*ESPACEMENT)+2*ESPACEMENT+5*ESPACEMENT;
		x=n%niveauNb;
		y=n/niveauNb;
		piece(offset_x+x*21,offset_y+y*21,private_grille[x][y],niveauTaille); // la piece
		if ((curseurBas==(x+y*niveauNb)) && (etatZone==EN_BAS)) {
			if (etatSelect==SELECT_ON) {
				piece(offset_x+x*21,offset_y+y*21,20,21);
			} else {
				piece(offset_x+x*21,offset_y+y*21,21,21);
			}
		}

}
void fillSelect(char niveauTaille,char curseurBas,char select,char etatSelect,char etatZone) {
	char offset_x;char offset_y;
	offset_x=2*105+2+3+1;
	offset_y=2*(21+2*ESPACEMENT)+2*ESPACEMENT+5*ESPACEMENT;
	piece(offset_x,offset_y,select,niveauTaille);
	if ((curseurBas==CURSEUR_BAS_SELECT) && (etatZone==EN_BAS)) {
		if (etatSelect==SELECT_ON) {
			piece(offset_x,offset_y,20,niveauTaille);
		} else {
			piece(offset_x,offset_y,21,niveauTaille);
		}
	}
}

/*
 * grille[][]
 * niveauTaille 15,21,35
 * niveauNb : 3,5,7
 * curseurBas : position du curseur, EN_BAS
 * select : la pièce actuellement sélectionnée, CASE_VIDE
 * etatSelect : si on affiche un carré rouge aux bords continue (OFF) ou discontinue (ON)
 * etatZone : EN_BAS ou EN_HAUT : si EN_HAUT alors ne pas afficher de curseur via cette fonction
 */
void fillGrilleEtSelect(char ** grille,char niveauTaille,char niveauNb,char curseurBas,char select,char etatSelect,char etatZone) {
	char offset_x;char offset_y;char n;
	//moveTo
	offset_x=105+2+3;
	offset_y=2*(21+2*ESPACEMENT)+2*ESPACEMENT+5*ESPACEMENT;
	// plateau
	piece(offset_x,offset_y,19,105); // bordure rouge

	for (n=0;n<niveauNb*niveauNb;n++) {
		fill1Grille(grille,niveauTaille,niveauNb,n,curseurBas,etatSelect,etatZone);
	}

	// selection
	offset_x=2*105+2+3+1;
	offset_y=2*(21+2*ESPACEMENT)+2*ESPACEMENT+5*ESPACEMENT;
	piece(offset_x,offset_y,19,niveauTaille); // bordure rouge
	fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
}

/*
 * niveauNb : 5 :p
 */
char ** makePreview(char niveauNb) {
	// de 0 à 17

	private_preview[0][0] = 2;
	private_preview[1][0] = 1;
	private_preview[2][0] = 1;
	private_preview[3][0] = 1;
	private_preview[4][0] = 5;

	private_preview[0][1] = 3;
	private_preview[1][1] = 17;
	private_preview[2][1] = 12;
	private_preview[3][1] = 16;
	private_preview[4][1] = 4;

	private_preview[0][2] = 1;
	private_preview[1][2] = 12;
	private_preview[2][2] = 12;
	private_preview[3][2] = 1;
	private_preview[4][2] = 1;

	private_preview[0][3] = 9;
	private_preview[1][3] = 9;
	private_preview[2][3] = 9;
	private_preview[3][3] = 9;
	private_preview[4][3] = 9;

	private_preview[0][4] = 2;
	private_preview[1][4] = 2;
	private_preview[2][4] = 2;
	private_preview[3][4] = 2;
	private_preview[4][4] = 2;
	
	return private_preview;
}

char ** newEmptyGrille() {
	char x;char y;
	for (x=0;x<7;x=x+1) {
		for (y=0;y<7;y=y+1) {
			private_grille[x][y]=CASE_VIDE;
		}
	}
	return (char **)private_grille;
}

char private_nbPieces[18];
char * computeNbPiece(char ** preview, char niveauNb) {
	char x;char y;
	for (x=0;x<18;x=x+1) {
		private_nbPieces[x]=0;
	}
	for (x=0;x<niveauNb;x=x+1) {
		for (y=0;y<niveauNb;y=y+1) {
			//private_nbPieces[preview[x][y]]=private_nbPieces[preview[x][y]]+1;
			private_nbPieces[private_preview[x][y]]=private_nbPieces[private_preview[x][y]]+1;
		}
	}
	return (char *)private_nbPieces;
}

const unsigned char puzzmem_palette[]=
{
		0,3,26,2,0,0,0,0,0,0,0,0,0,0,0,0
};

//char nbPieces[18]={
//	1, 1,1,1,1, 1,1,1,1,
//    1, 1,1,1,1, 1,1,1,1
//};

char * nbPieces;

char ** preview;

char ** grille;
char select;

void main(void)
{
	//char offset_x; char offset_y;
	char curseurHaut;char curseurBas;char etatSelect;char etatZone;
	char curseurHautOld;char curseurBasOld;
	char niveauNb;char niveauTaille;
	char grille_x;char grille_y;char p;char pp;
	char one_key;
	mode(1);
	set_palette(puzzmem_palette);
	//put_frame(vram(0,0),80,200,bluegirl);
	put_frame(vram(45,0),80,200,bluegirl);
	//put_frame(vram(200,0),80,200,bluegirl);
	//while (1) {}
	//printf("Hello World! ");
	//put_pixel1(20,20,2);
	//offset_x=22;
	//offset_y=22;
	//piece(offset_x,offset_y,5,21);
	//offset_x=22+1;
	//offset_y=22+21;
	//piece(offset_x,offset_y,5,21);

	niveauNb=5;
	niveauTaille=21;
	
	// état
	curseurHaut=0;
	curseurHautOld=0;
	curseurBas=0;
	curseurBasOld=0;
	etatSelect=SELECT_OFF;
	etatZone=EN_BAS;

	// modèle
	preview=makePreview(niveauNb);
	nbPieces=computeNbPiece(preview,niveauNb);
	grille=newEmptyGrille(); // rempli avec des CASE_VIDE
	select=CASE_VIDE;
	
	//private_grille[2][2] = 15;
	//select=14;

	// rendu
	vsync();
	fillListePieces(nbPieces,curseurHaut,etatSelect,etatZone);
	fillPreview(preview,niveauTaille,niveauNb);
	fillGrilleEtSelect(grille,niveauTaille,niveauNb,curseurBas,select,etatSelect,etatZone);

while (1) {
one_key=0;
//do {
	check_controller();
//} while (get_key(Key_CursorUp)+get_key(Key_CursorDown)+get_key(Key_CursorRight)+get_key(Key_CursorLeft)+get_key(Key_Space)+get_key(Key_Return)!=1);
//TOUCHE_HAUT
if (get_key(Key_CursorUp)) {
	if (etatZone==EN_HAUT) {
		if ((curseurHaut % 2) == 1) {
			curseurHautOld=curseurHaut;
			curseurHaut=curseurHaut-1;
			one_key=EN_HAUT;
		}
	} else {
		if (curseurBas != CURSEUR_BAS_SELECT) {
			if (curseurBas > niveauNb - 1) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%niveauNb;
					grille_y=curseurBas/niveauNb;
					// pousser
					for (p=grille_y;p>=0;) {// 0-1==0...
						if (private_grille[grille_x][p]==CASE_VIDE) {
							for (pp=p;pp<grille_y;pp=pp+1) {
								private_grille[grille_x][pp]=private_grille[grille_x][pp+1];
								curseurBasOld=grille_x+pp*niveauNb;
								fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
							}
							private_grille[grille_x][grille_y]=CASE_VIDE;
							curseurBasOld=curseurBas; // leger
							curseurBas=curseurBas-niveauNb;
							one_key=EN_BAS;
							break;
						}
						if (p==0) {
							break;
						} else {
							p=p-1;
						}
					}
				} else {
					curseurBasOld=curseurBas;
					curseurBas=curseurBas-niveauNb;
					one_key=EN_BAS;
				}
			}
		}
	}
}
//TOUCHE_BAS
if (get_key(Key_CursorDown)) {
	if (etatZone==EN_HAUT) {
		if ((curseurHaut % 2) == 0) {
			curseurHautOld=curseurHaut;
			curseurHaut=curseurHaut+1;
			one_key=EN_HAUT;
		}
	} else {
		if (curseurBas != CURSEUR_BAS_SELECT) {
			if (curseurBas < niveauNb*(niveauNb-1)) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%niveauNb;
					grille_y=curseurBas/niveauNb;
					// pousser
					for (p=grille_y;p<niveauNb;p=p+1) {
						if (private_grille[grille_x][p]==CASE_VIDE) {
							for (pp=p;pp>grille_y;pp=pp-1) {
								private_grille[grille_x][pp]=private_grille[grille_x][pp-1];
								curseurBasOld=grille_x+pp*niveauNb;
								fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
							}
							private_grille[grille_x][grille_y]=CASE_VIDE;
							curseurBasOld=curseurBas; // leger
							curseurBas=curseurBas+niveauNb;
							one_key=EN_BAS;
							break;
						}
					}
				} else {
					curseurBasOld=curseurBas;
					curseurBas=curseurBas+niveauNb;
					one_key=EN_BAS;
				}
			}
		}
	}
}
//TOUCHE_DROITE
if (get_key(Key_CursorRight)) {
	if (etatZone==EN_HAUT) {
		if (curseurHaut <20) {
			curseurHautOld=curseurHaut;
			curseurHaut=curseurHaut+2;
			one_key=EN_HAUT;
		}
	} else {
		if (curseurBas != CURSEUR_BAS_SELECT) {
			if (curseurBas % niveauNb < niveauNb - 1) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%niveauNb;
					grille_y=curseurBas/niveauNb;
					// pousser
					for (p=grille_x;p<niveauNb;p=p+1) {
						if (private_grille[p][grille_y]==CASE_VIDE) {
							for (pp=p;pp>grille_x;pp=pp-1) {
								private_grille[pp][grille_y]=private_grille[pp-1][grille_y];
								curseurBasOld=pp+grille_y*niveauNb;
								fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
							}
							private_grille[grille_x][grille_y]=CASE_VIDE;
							curseurBasOld=curseurBas; // leger
							curseurBas=curseurBas+1;
							one_key=EN_BAS;
							break;
						}
					}
				} else {
					curseurBasOld=curseurBas;
					curseurBas=curseurBas+1;
					one_key=EN_BAS;
				}
			} else if (curseurBas < niveauNb) {
				// on peut effectivement y poser une piece mais pas pousser ? oups...
				if (etatSelect==SELECT_ON) {
					if (select==CASE_VIDE) {
						select=private_grille[niveauNb - 1][0];
						private_grille[niveauNb - 1][0]=CASE_VIDE;
						curseurBasOld=curseurBas;
						curseurBas=CURSEUR_BAS_SELECT;
						one_key=EN_BAS;
					}
				} else {
					curseurBasOld=curseurBas;
					curseurBas=CURSEUR_BAS_SELECT;
					one_key=EN_BAS;
				}
			}
		}
	}
}
//TOUCHE_GAUCHE
if (get_key(Key_CursorLeft)) {
	if (etatZone==EN_HAUT) {
		if (curseurHaut >=2) {
			curseurHautOld=curseurHaut;
			curseurHaut=curseurHaut-2;
			one_key=EN_HAUT;
		}
	} else {
		if (curseurBas == CURSEUR_BAS_SELECT) {
			if (etatSelect==SELECT_ON) {
				if (private_grille[niveauNb - 1][0]==CASE_VIDE) {
					private_grille[niveauNb - 1][0]=select;select=CASE_VIDE;
					curseurBasOld=curseurBas;
					curseurBas=niveauNb - 1;
					one_key=EN_BAS;
				} else {
					curseurBas=niveauNb - 1;
					grille_x=curseurBas%niveauNb;
					grille_y=curseurBas/niveauNb;
					// pousser
					if (grille_x>0) {
						for (p=grille_x;p>=0;) { // 0-1==0...
							if (private_grille[p][grille_y]==CASE_VIDE) {
								for (pp=p;pp<grille_x;pp=pp+1) {
									private_grille[pp][grille_y]=private_grille[pp+1][grille_y];
									curseurBasOld=pp+grille_y*niveauNb;
									fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
								}
								private_grille[niveauNb - 1][0]=select;
								select=CASE_VIDE;
								curseurBasOld=curseurBas; // leger
								curseurBas=niveauNb - 1;
								fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
								one_key=EN_BAS;
								break;
							}
							if (p==0) {
								break;
							} else {
								p=p-1;
							}
						}
					}
					// pousser ?
				}
			} else {
				curseurBasOld=curseurBas;
				curseurBas = niveauNb - 1;
				one_key=EN_BAS;
			}
		} else {
			if (curseurBas % niveauNb > 0) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%niveauNb;
					grille_y=curseurBas/niveauNb;
					// pousser
					for (p=grille_x;p>=0;) { // 0-1==0...
						if (private_grille[p][grille_y]==CASE_VIDE) {
							for (pp=p;pp<grille_x;pp=pp+1) {
								private_grille[pp][grille_y]=private_grille[pp+1][grille_y];
								curseurBasOld=pp+grille_y*niveauNb;
								fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
							}
							private_grille[grille_x][grille_y]=CASE_VIDE;
							curseurBasOld=curseurBas; // leger
							curseurBas=curseurBas-1;
							fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
							one_key=EN_BAS;
							break;
						}
						if (p==0) {
							break;
						} else {
							p=p-1;
						}
					}
				} else {
					curseurBasOld=curseurBas;
					curseurBas=curseurBas-1;
					one_key=EN_BAS;
				}
			}
		}
	}
}
//TOUCHE_ESPACE
if (get_key(Key_Space)) {
	one_key=EN_HAUT_ET_EN_BAS;
	if (etatZone==EN_HAUT) {
		etatZone=EN_BAS;
		if ((select==CASE_VIDE) && (nbPieces[curseurHaut]>0)) {
			select=curseurHaut;
			nbPieces[curseurHaut]=nbPieces[curseurHaut]-1;
			etatSelect=SELECT_ON;
		} else if (select==CASE_VIDE) {
			etatSelect=SELECT_OFF;
		} else {
			etatSelect=SELECT_ON;
		}
	} else {
		etatZone=EN_HAUT;
		etatSelect=SELECT_OFF;
	}
	curseurHautOld=curseurHaut;
	curseurHaut=0;
	curseurBasOld=curseurBas;
	curseurBas=CURSEUR_BAS_SELECT;
}
//TOUCHE_ENTREE
if (get_key(Key_Return)) {
	if (etatSelect==SELECT_ON) {
		etatSelect=SELECT_OFF;
		one_key=etatZone; // EN_HAUT ou EN_BAS
	} else {
		if (etatZone==EN_HAUT) {
			if (nbPieces[curseurHaut]>0) {
				if (select!=CASE_VIDE) {
					nbPieces[select]=nbPieces[select]+1;
				}
				select=curseurHaut;
				nbPieces[curseurHaut]=nbPieces[curseurHaut]-1;
				one_key=EN_HAUT_ET_EN_BAS; // le compteur décrémente, et select bouge
				etatZone=EN_BAS;
				etatSelect=SELECT_ON;
				curseurBasOld=curseurBas;
				curseurBas=CURSEUR_BAS_SELECT;
			}
		} else {
			if (curseurBas == CURSEUR_BAS_SELECT) {
				if (select != CASE_VIDE) {
					etatSelect=SELECT_ON;
					curseurBasOld=curseurBas; // cheeting
					one_key=EN_BAS;
				}
			} else {
				grille_x=curseurBas%niveauNb;
				grille_y=curseurBas/niveauNb;
				if (private_grille[grille_x][grille_y] != CASE_VIDE) {
					etatSelect=SELECT_ON;
					curseurBasOld=curseurBas; // cheeting
					one_key=EN_BAS;
				}
			}
		}
	}
}
if (one_key!=0) {
	// reafficher
	vsync();
	//fillPreview(preview,niveauTaille,niveauNb);
	if ((one_key==EN_HAUT) || (one_key==EN_HAUT_ET_EN_BAS)) {
		fillListe1Piece(nbPieces,curseurHaut,curseurHaut,etatSelect,etatZone,0);
		if (curseurHautOld!=curseurHaut) {
			fillListe1Piece(nbPieces,curseurHautOld,curseurHaut,etatSelect,etatZone,0);
		}
	}
	if ((one_key==EN_BAS) || (one_key==EN_HAUT_ET_EN_BAS)) {
		if (curseurBas==CURSEUR_BAS_SELECT) {
			fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
		} else {
			fill1Grille(grille,niveauTaille,niveauNb,curseurBas,curseurBas,etatSelect,etatZone);
		}
		if (curseurBasOld!=curseurBas) {
			if (curseurBasOld==CURSEUR_BAS_SELECT) {
				fillSelect(niveauTaille,curseurBasOld,select,etatSelect,etatZone);
			} else {
				fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
			}
		}
		
	}
}
}
}



