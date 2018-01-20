#include <stdio.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
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
				if (x+y<tailleTile) {
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
				if (x+y>tailleTile) {
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
				if (x+tailleTile-y<tailleTile) {
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
				if (x+tailleTile-y>tailleTile) {
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
	return;
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
for (n=0;n<18;n++) {
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
	offset_x=2*10;
	offset_y=2*(21+4)+2*10;
	piece(offset_x,offset_y,19,105); // bordure rouge
	
	for (x=0;x<niveauNb;x=x+1) {
		for (y=0;y<niveauNb;y=y+1) {
			//piece(offset_x+x*21,offset_y+y*21,*preview[x*niveauNb*2+y*2],niveauTaille); // la piece
			piece(offset_x+x*21,offset_y+y*21,private_preview[x][y],niveauTaille); // la piece
		}
	}
}


/*
 * niveauNb : 5 :p
 */
char ** makePreview(char niveauNb) {
	// de 0 à 17

	private_preview[0][0] = 1;
	private_preview[1][0] = 2;
	private_preview[2][0] = 5;
	private_preview[3][0] = 2;
	private_preview[4][0] = 16;

	private_preview[0][1] = 17;
	private_preview[1][1] = 3;
	private_preview[2][1] = 10;
	private_preview[3][1] = 13;
	private_preview[4][1] = 12;

	private_preview[0][2] = 9;
	private_preview[1][2] = 11;
	private_preview[2][2] = 15;
	private_preview[3][2] = 4;
	private_preview[4][2] = 6;

	private_preview[0][3] = 8;
	private_preview[1][3] = 9;
	private_preview[2][3] = 7;
	private_preview[3][3] = 4;
	private_preview[4][3] = 6;

	private_preview[0][4] = 0;
	private_preview[1][4] = 1;
	private_preview[2][4] = 0;
	private_preview[3][4] = 1;
	private_preview[4][4] = 0;
	
	return private_preview;
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

//char nbPieces[18]={
//	1, 1,1,1,1, 1,1,1,1,
//    1, 1,1,1,1, 1,1,1,1
//};

char * nbPieces;

char ** preview;

void main(void)
{
	char offset_x; char offset_y;
	char curseurHaut;char etatSelect; char etatZone;
	char niveauNb;char niveauTaille;
	mode(1);
	printf("Hello World !");
	put_pixel1(20,20,2);
	offset_x=22;
	offset_y=22;
	piece(offset_x,offset_y,5,21);
	offset_x=22+1;
	offset_y=22+21;
	piece(offset_x,offset_y,5,21);
	
	curseurHaut=0;
	etatSelect=SELECT_OFF;
	etatZone=EN_HAUT;

	niveauNb=5;
	niveauTaille=21;
	preview=makePreview(niveauNb);
	nbPieces=computeNbPiece(preview,niveauNb);

	fillListePieces(nbPieces,curseurHaut,etatSelect,etatZone);
	fillPreview(preview,niveauTaille,niveauNb);
	

	while(1){}
}



