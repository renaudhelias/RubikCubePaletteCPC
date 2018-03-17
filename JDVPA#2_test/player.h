#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_STOP		0
#define	PLAYER_LEFT		2
#define	PLAYER_RIGHT	5
#define PLAYER_UP		8
#define	PLAYER_DOWN		11

#define PLAYER_SPRITE_LARGEUR_O	2
#define PLAYER_SPRITE_LARGEUR_P	4
#define PLAYER_SPRITE_HAUTEUR	8

typedef struct
{
	unsigned char oldx;
	unsigned char oldy;	
	unsigned char x;
	unsigned char y;	
	unsigned char dd; // direction désirée
	unsigned char dc; // direction courante
	unsigned char timer;
	unsigned char anim;

}
s_player;

void player_init();
void player_move_rel(char x,char y);

#endif