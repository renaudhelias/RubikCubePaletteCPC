#ifndef GHOST_H
#define GHOST_H

#define GHOST_SPRITE_LARGEUR_O	2
#define GHOST_SPRITE_LARGEUR_P	4
#define	GHOST_SPRITE_HAUTEUR	8

#define GHOST_VITESSE_H		1
#define	GHOST_VITESSE_V		1

#define	GHOST_HAUT		0
#define GHOST_BAS		1
#define	GHOST_GAUCHE	2
#define GHOST_DROITE	3

typedef struct
{
	unsigned char oldx;
	unsigned char oldy;	
	unsigned char x;
	unsigned char y;
	char sensx;
	char sensy;
	unsigned char timer;
	unsigned char anim;
	
	unsigned int wait_timer;		/* Combien de temps il attend en zone d'attente */
	unsigned int scatter_timer;		/* Combien de temps il est en scatter mode */
	unsigned int fear_timer;		/* Combien de temps il peut être bouffé */
	
}
s_ghost;

void ghost_init();
void ghost_move_rel(char i,char mx,char my);
//void ghost_ia(void);
void ghost_update(void);

extern s_ghost ghost[4];

#endif