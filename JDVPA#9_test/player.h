#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_STOP		0
#define	PLAYER_LEFT		1
#define	PLAYER_RIGHT	2
#define PLAYER_UP		4
#define	PLAYER_DOWN		8

#define PLAYER_STOP_TILE		1
#define	PLAYER_LEFT_TILE		2
#define	PLAYER_RIGHT_TILE	5
#define PLAYER_UP_TILE		8
#define	PLAYER_DOWN_TILE		11

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
	unsigned char dd; // direction désirée
	unsigned char dc; // direction courante
	unsigned char timer;
	unsigned char anim;
	unsigned int score;

}
s_player;

extern const unsigned char tile_dc[];

void player_init();
void player_move_rel(char x,char y);
void player_control(void);

extern s_player player;

#endif