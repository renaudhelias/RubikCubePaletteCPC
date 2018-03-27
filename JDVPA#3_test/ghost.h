#ifndef GHOST_H
#define GHOST_H

#define GHOST_SPRITE_LARGEUR_O	2
#define GHOST_SPRITE_LARGEUR_P	4
#define	GHOST_SPRITE_HAUTEUR	8

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
}
s_ghost;

void ghost_init();
void ghost_move_rel(char i,char mx,char my);

extern s_ghost ghost[4];

#endif