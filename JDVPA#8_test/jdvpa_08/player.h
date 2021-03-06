#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_STOP		1
#define	PLAYER_LEFT		2
#define	PLAYER_RIGHT	5
#define PLAYER_UP		8
#define	PLAYER_DOWN		11

#define PLAYER_SPRITE_LARGEUR_O	2
#define PLAYER_SPRITE_LARGEUR_P	4
#define PLAYER_SPRITE_HAUTEUR	8

#define PLAYER_VITESSE_H		1
#define	PLAYER_VITESSE_V		1

typedef struct
{
	unsigned char oldx;
	unsigned char oldy;	
	unsigned char x;
	unsigned char y;	
	unsigned char dd; // direction d�sir�e
	unsigned char dc; // direction courante
	unsigned char timer;
	unsigned char anim;
	unsigned int score;

}
s_player;

void player_init();
void player_move_rel(char x,char y);
void player_control(void);

#endif