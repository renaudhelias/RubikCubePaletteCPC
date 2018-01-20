#include <stdio.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
#define	CASE_VIDE 18
#define	CURSEUR_BAS_SELECT 7*7
#define EN_HAUT 1
#define EN_BAS 2
#define SELECT_OFF 0
#define SELECT_ON 1
 
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
				if (x+y<tailleTile/2) {
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
				if (x+y>tailleTile/2) {
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
				if (x+tailleTile-y<tailleTile/2) {
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
				if (x+tailleTile-y>tailleTile/2) {
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
				if (x<tailleTile/2 && y<tailleTile/2) {
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
				if (x>tailleTile/2 && y<tailleTile/2) {
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
				if (x>tailleTile/2 && y>tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,3);
				} else {
					put_pixel1(offset_x+x,offset_y+y,2);
				}
			}
		}
	case 17 :
		// carré bleu 4
		for (x=0;x<tailleTile;x++) {
			for (y=0;y<tailleTile;y++) {
				if (x<tailleTile/2 && y>tailleTile/2) {
					put_pixel1(offset_x+x,offset_y+y,3);
				} else {
					put_pixel1(offset_x+x,offset_y+y,2);
				}
			}
		}
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
			put_pixel1(offset_x+x-1,offset_y-1,0);
			put_pixel1(offset_x+x-1,offset_y+tailleTile,1);
		}
		//for (y=-1;y<=tailleTile;y++) {
		for (y=0;y<tailleTile+2;y++) {
			put_pixel1(offset_x-1,offset_y+y-1,0);
			put_pixel1(offset_x+tailleTile,offset_y+y-1,1);
		}
	return;
	case 20 :
		// select rouge
		for (x=0;x<tailleTile;x++) {
			if (x<tailleTile/4 || x>tailleTile*3/4) {
				put_pixel1(offset_x+x,offset_y+0,0);
				put_pixel1(offset_x+x,offset_y+tailleTile,1);
			}
		}
		for (y=0;y<tailleTile;y++) {
			if (y<tailleTile/4 || y>tailleTile*3/4) {
				put_pixel1(offset_x+0,offset_y+y,0);
				put_pixel1(offset_x+tailleTile,offset_y+y,1);
			}
		}
	return;
	case 21 :
		// unselect rouge
		for (x=0;x<tailleTile;x++) {
			put_pixel1(offset_x+x,offset_y+0,0);
			put_pixel1(offset_x+x,offset_y+tailleTile,1);
		}
		for (y=0;y<tailleTile;y++) {
			put_pixel1(offset_x+0,offset_y+y,0);
			put_pixel1(offset_x+tailleTile,offset_y+y,1);
		}
	return;
}
}

/*
 * nbPieces[]
 * curseurHaut : position du curseur, EN_HAUT
 * etatSelect : si on affiche un carré rouge aux bords continue (OFF) ou discontinue (ON)
 * etatZone : EN_BAS ou EN_HAUT : si EN_BAS alors ne pas afficher de curseur via cette fonction
 */
void fillListePieces(char * nbPieces,char curseurHaut,char etatSelect,char etatZone) {
char n;char x;char y;
char offset_x;char offset_y;
for (n=0;n<20-3;n++) {
	x=n/2;
	y=n%2;
	//moveTo
	offset_x=x*(21+4)+10;
	offset_y=y*(21+4)+10;
	piece(offset_x,offset_y,19,21); // bordure rouge
	printf("%c",nbPieces[n]); // texte dessous la case : nombre de pièces
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
}

/*
 * preview[][]
 * niveauTaille : 15,21,35
 * niveauNb : 3,5,7
 */
void fillPreview(char ** preview,char niveauTaille,char niveauNb) {
	char offset_x;char offset_y;char x; char y;
	//moveTo
	offset_x=2*10;
	offset_y=2*(21+4)+2*10;
	piece(offset_x,offset_y,19,105); // bordure rouge
	for (x=0;x<niveauNb;x=x+1) {
		for (y=0;y<niveauNb;y=y+1) {
			piece(offset_x+x*21,offset_y+y*21,preview[x][y],niveauTaille); // la piece
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
	char offset_x;char offset_y;char x; char y;
	//moveTo
	offset_x=105+2*2*10;
	offset_y=2*(21+4)+2*10;
	// plateau
	piece(offset_x,offset_y,19,105); // bordure rouge

	for (x=0;x<niveauNb;x=x+1) {
		for (y=0;y<niveauNb;y=y+1) {
			
			piece(offset_x+x*21,offset_y+y*21,grille[x][y],niveauTaille); // la piece
			if ((curseurBas==(x+y*niveauNb)) && (etatZone==EN_BAS)) {
				if (etatSelect==SELECT_ON) {
					piece(offset_x+x*21,offset_y+y*21,20,21);
				} else {
					piece(offset_x+x*21,offset_y+y*21,21,21);
				}
			}
		}
	}

	// selection
	offset_x=2*105+3*2*10;
	offset_y=2*(21+4)+2*10;
	piece(offset_x,offset_y,select,niveauTaille); // bordure rouge
	
}

char private_preview[5][5] = {
		{1,2,5,2,16},
		{17,3,10,13,12},
		{9,11,15,4,6},
		{8,9,7,4,6},
		{0,1,0,1,0}
	};
/*
 * niveauNb : 5 :p
 */
char ** makePreview(char niveauNb) {
	// de 0 à 17
	//private_preview=
	return (char **)private_preview;
}

char private_grille[7][7];
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
			private_nbPieces[preview[x][y]]=private_nbPieces[preview[x][y]]+1;
		}
	}
	return (char *)private_nbPieces;
}


char ** preview;
char ** grille;
char * nbPieces;
char select;

void main(void) {
char grille_x;char grille_y;char p;char pp; // pour pousser
char niveauNb;char niveauTaille;
char etatZone;char etatSelect;char curseurHaut;char curseurBas;
// mode 1
mode(1);
// niveau
// 3*5*7=105
// 3 35*35
// 5 21*21
// 7 15*15
niveauNb=5;
niveauTaille=21;



// modèle
preview=makePreview(niveauNb);
grille=newEmptyGrille(); // rempli avec des CASE_VIDE
select=CASE_VIDE;
nbPieces=computeNbPiece(preview,niveauNb);
// état
etatZone=EN_HAUT;
etatSelect=SELECT_OFF;
curseurHaut=0;
curseurBas=0;
// rendu
vsync();
fillPreview(preview,niveauTaille,niveauNb);
fillListePieces(nbPieces,curseurHaut,etatSelect,etatZone);
fillGrilleEtSelect(grille,niveauTaille,niveauNb,curseurBas,select,etatSelect,etatZone);

while (1) {
check_controller();
//TOUCHE_HAUT
if (get_key(Key_CursorUp)) {
	if (etatZone==EN_HAUT) {
		if ((curseurHaut % 2) == 0) {
			curseurHaut=curseurHaut+1;
		}
	} else {
		if (curseurBas != CURSEUR_BAS_SELECT) {
			if (curseurBas > 7 - 1) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%7;
					grille_y=curseurBas/7;
					// pousser
					for (p=grille_y;p>0;p=p-1) {
						if (grille[grille_x][p]==CASE_VIDE) {
							for (pp=p+1;pp<grille_y;pp=pp+1) {
								grille[grille_x][pp]=grille[grille_x][pp-1];
							}
							grille[grille_x][grille_y]=CASE_VIDE;
							curseurBas=curseurBas-7;
							break;
						}
					}
				} else {
					curseurBas=curseurBas-7;
				}
			}
		}
	}
}
//TOUCHE_BAS
if (get_key(Key_CursorDown)) {
	if (etatZone==EN_HAUT) {
		if ((curseurHaut % 2) == 1) {
			curseurHaut=curseurHaut-1;
		}
	} else {
		if (curseurBas != CURSEUR_BAS_SELECT) {
			if (curseurBas < 7*(niveauNb-1)) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%7;
					grille_y=curseurBas/7;
					// pousser
					for (p=grille_y;p<niveauNb;p=p+1) {
						if (grille[grille_x][p]==CASE_VIDE) {
							for (pp=p-1;pp>grille_y;pp=pp-1) {
								grille[grille_x][pp]=grille[grille_x][pp+1];
							}
							grille[grille_x][grille_y]=CASE_VIDE;
							curseurBas=curseurBas+7;
							break;
						}
					}
				} else {
					curseurBas=curseurBas+7;
				}
			}
		}
	}
}
//TOUCHE_DROITE
if (get_key(Key_CursorRight)) {
	if (etatZone==EN_HAUT) {
		if (curseurHaut <20) {
			curseurHaut=curseurHaut+2;
		}
	} else {
		if (curseurBas != CURSEUR_BAS_SELECT) {
			if (curseurBas % 7 < niveauNb - 1) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%7;
					grille_y=curseurBas/7;
					// pousser
					for (p=grille_x;p<niveauNb;p=p+1) {
						if (grille[p][grille_y]==CASE_VIDE) {
							for (pp=p-1;pp>grille_x;pp=pp-1) {
								grille[pp][grille_y]=grille[pp+1][grille_y];
							}
							grille[grille_x][grille_y]=CASE_VIDE;
							curseurBas=curseurBas+1;
							break;
						}
					}
				} else {
					curseurBas=curseurBas+1;
				}
			}
		}
	}
}
//TOUCHE_GAUCHE
if (get_key(Key_CursorLeft)) {
	if (etatZone==EN_HAUT) {
		if (curseurHaut >2) {
			curseurHaut=curseurHaut-2;
		}
	} else {
		if (curseurBas == CURSEUR_BAS_SELECT) {
			if (etatSelect==SELECT_ON) {
				if (grille[niveauNb - 1][0]==CASE_VIDE) {
					grille[niveauNb - 1][0]=select;select=CASE_VIDE;
					curseurBas=niveauNb - 1;
				} else {
					curseurBas=niveauNb - 1;
					grille_x=curseurBas%7;
					grille_y=curseurBas/7;
					// pousser
					for (p=grille_x;p>0;p=p-1) {
						if (grille[p][grille_y]==CASE_VIDE) {
							for (pp=p+1;pp<grille_x;pp=pp+1) {
								grille[pp][grille_y]=grille[pp-1][grille_y];
							}
							grille[niveauNb - 1][0]=select;
							select=CASE_VIDE;
							curseurBas=niveauNb - 1;
							break;
						}
					}
					// pousser ?
				}
			} else {
				curseurBas = niveauNb - 1;
			}
		} else {
			if (curseurBas % 7 > 0) {
				if (etatSelect==SELECT_ON) {
					grille_x=curseurBas%7;
					grille_y=curseurBas/7;
					// pousser
					for (p=grille_x;p>0;p=p-1) {
						if (grille[p][grille_y]==CASE_VIDE) {
							for (pp=p+1;pp<grille_x;pp=pp+1) {
								grille[pp][grille_y]=grille[pp-1][grille_y];
							}
							grille[grille_x][grille_y]=CASE_VIDE;
							curseurBas=curseurBas-1;
							break;
						}
					}
				} else {
					curseurBas=curseurBas-1;
				}
			}
		}
	}
}
//TOUCHE_ESPACE
if (get_key(Key_Space)) {
	if (etatZone==EN_HAUT) {
		etatZone=EN_BAS;
	} else {
		etatZone=EN_HAUT;
	}
	etatSelect=SELECT_OFF;
	curseurHaut=0;
	curseurBas=CURSEUR_BAS_SELECT;
}
//TOUCHE_ENTREE
if (get_key(Key_Return)) {
	if (etatSelect==SELECT_ON) {
		etatSelect=SELECT_OFF;
	} else {
		if (etatZone==EN_HAUT) {
			if (nbPieces[curseurHaut]>0) {
				if (select!=CASE_VIDE) {
					nbPieces[select]=nbPieces[select]+1;
				}
				select=curseurHaut;
				nbPieces[curseurHaut]=nbPieces[curseurHaut]-1;
			}
		} else {
			if (curseurBas == CURSEUR_BAS_SELECT) {
				if (select != CASE_VIDE) {
					etatSelect=SELECT_ON;
				}
			} else {
				grille_x=curseurBas%7;
				grille_y=curseurBas/7;
				if (grille[grille_x][grille_y] != CASE_VIDE) {
					etatSelect=SELECT_ON;
				}
			}
		}
	}
}
// reafficher
vsync();
fillPreview(preview,niveauTaille,niveauNb);
fillListePieces(nbPieces,curseurHaut,etatSelect,etatZone);
fillGrilleEtSelect(grille,niveauTaille,niveauNb,curseurBas,select,etatSelect,etatZone);
}
}





