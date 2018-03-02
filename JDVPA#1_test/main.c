#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jdvapi_basic.h"
#include "jdvapi_frame.h"

#include "pacman_sprites.h"
#include "blank_sprites.h"
#include "ghost_sprites.h"

#include "player.h"
#include "ghost.h"

#define IMG_BLANK 0

unsigned int *vram;

unsigned char *spr_img[25];

const unsigned char game_palette[]=
{
		0,25,7,8,11,16,22,26,0,0,0,0,0,0,0,0
};

void main(void)
{
	char i;

	vram=precalc_vram();
	
	// Image vide
	spr_img[IMG_BLANK] = (unsigned char *)blank_sprites;
	// Pacman rond
	spr_img[1] = (unsigned char *)pacman_sprites;
	// Pacman Anim gauche
	spr_img[2] = (unsigned char *)pacman_sprites;
	spr_img[3] = (unsigned char *)pacman_sprites + (PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O);
	spr_img[4] = (unsigned char *)pacman_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*2);
	// Pacman Anim Droite
	spr_img[5] = (unsigned char *)pacman_sprites;
	spr_img[6] = (unsigned char *)pacman_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*3);
	spr_img[7] = (unsigned char *)pacman_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*4);
	// Pacman Anim haut
	spr_img[8] = (unsigned char *)pacman_sprites;
	spr_img[9] = (unsigned char *)pacman_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*5);
	spr_img[10] = (unsigned char *)pacman_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*6);
	// Pacman Anim Bas
	spr_img[11] = (unsigned char *)pacman_sprites;
	spr_img[12] = (unsigned char *)pacman_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*7);
	spr_img[13] = (unsigned char *)pacman_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*8);
	// Fantome 1
	spr_img[14] = (unsigned char *)ghost_sprites;
	spr_img[15] = (unsigned char *)ghost_sprites + (GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O);
	// Fantome 2
	spr_img[16] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*2);
	spr_img[17] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*3);
	// Fantome 3
	spr_img[18] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*4);
	spr_img[19] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*5);
	// Fantome 4
	spr_img[20] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*6);
	spr_img[21] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*7);	
	// Fantome Appeuré
	spr_img[22] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*8);
	spr_img[23] = (unsigned char *)ghost_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*9);
	
	
	mode(0);
	set_palette(game_palette);
	printf("Hello World !");
		
	put_frame(screen(10,100),GHOST_SPRITE_LARGEUR_O,GHOST_SPRITE_HAUTEUR,spr_img[3]);		
	put_frame(screen(200,100),GHOST_SPRITE_LARGEUR_O,GHOST_SPRITE_HAUTEUR,spr_img[23]);		
	
	for (i=0;i<24;i++)
	{
		put_frame(screen(i*6,120),GHOST_SPRITE_LARGEUR_O,GHOST_SPRITE_HAUTEUR,spr_img[i]);
	}
	
	while(1)
	{
		
	}
}