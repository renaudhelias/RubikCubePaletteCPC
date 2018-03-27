#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jdvapi_basic.h"
#include "jdvapi_keyb.h"
#include "jdvapi_frame.h"
#include "jdvapi_sync.h"

#include "pacman_reduce_sprites.h"
#include "blank_reduce_sprites.h"
#include "ghost_reduce_sprites.h"

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
	vram=precalc_vram();
	
	// Image vide
	spr_img[IMG_BLANK] = (unsigned char *)blank_reduce_sprites;
	// Pacman rond
	spr_img[1] = (unsigned char *)pacman_reduce_sprites;
	// Pacman Anim gauche
	spr_img[2] = (unsigned char *)pacman_reduce_sprites;
	spr_img[3] = (unsigned char *)pacman_reduce_sprites + (PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O);
	spr_img[4] = (unsigned char *)pacman_reduce_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*2);
	// Pacman Anim Droite
	spr_img[5] = (unsigned char *)pacman_reduce_sprites;
	spr_img[6] = (unsigned char *)pacman_reduce_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*3);
	spr_img[7] = (unsigned char *)pacman_reduce_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*4);
	// Pacman Anim haut
	spr_img[8] = (unsigned char *)pacman_reduce_sprites;
	spr_img[9] = (unsigned char *)pacman_reduce_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*5);
	spr_img[10] = (unsigned char *)pacman_reduce_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*6);
	// Pacman Anim Bas
	spr_img[11] = (unsigned char *)pacman_reduce_sprites;
	spr_img[12] = (unsigned char *)pacman_reduce_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*7);
	spr_img[13] = (unsigned char *)pacman_reduce_sprites + ((PLAYER_SPRITE_HAUTEUR*PLAYER_SPRITE_LARGEUR_O)*8);
	// Fantome 1
	spr_img[14] = (unsigned char *)ghost_reduce_sprites;
	spr_img[15] = (unsigned char *)ghost_reduce_sprites + (GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O);
	// Fantome 2
	spr_img[16] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*2);
	spr_img[17] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*3);
	// Fantome 3
	spr_img[18] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*4);
	spr_img[19] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*5);
	// Fantome 4
	spr_img[20] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*6);
	spr_img[21] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*7);	
	// Fantome Appeuré
	spr_img[22] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*8);
	spr_img[23] = (unsigned char *)ghost_reduce_sprites + ((GHOST_SPRITE_HAUTEUR*GHOST_SPRITE_LARGEUR_O)*9);
	
	
	mode(0);
	border(0);
	set_palette(game_palette);
	
	player_init();
	ghost_init();
	
	while(1)
	{
		check_controller();
		if ((get_key(Key_Joy1Left)) || (get_key(Key_O))) 
		{
				player.dd = PLAYER_LEFT;
		}
		else
		if ((get_key(Key_Joy1Right)) || (get_key(Key_P))) 		
		{
			player.dd = PLAYER_RIGHT;
		}
		else
		if ((get_key(Key_Joy1Up)) || (get_key(Key_Q))) 
		{
			player.dd = PLAYER_UP;
		}
		else
		if ((get_key(Key_Joy1Right)) || (get_key(Key_A))) 		
		{
			player.dd = PLAYER_DOWN;
		}
		
		player.dc = player.dd;
		
		if ((player.dc==PLAYER_LEFT) && (player.x>0)) {player_move_rel(-2,0);}
		else
		if ((player.dc==PLAYER_RIGHT) && (player.x<(160-PLAYER_SPRITE_LARGEUR_P))) {player_move_rel(2,0);}
		else
		if ((player.dc==PLAYER_UP) && (player.y>0)) {player_move_rel(0,-2);}
		else
		if ((player.dc==PLAYER_DOWN) && (player.y<(200-PLAYER_SPRITE_HAUTEUR))) {player_move_rel(0,2);}

		if (ghost[0].x==0) ghost[0].sensx = 2; else if (ghost[0].x==160-GHOST_SPRITE_LARGEUR_P) ghost[0].sensx = -2;
		ghost_move_rel(0, ghost[0].sensx, ghost[0].sensy);
		
		if (ghost[1].y==0) ghost[1].sensy = 2; else if (ghost[1].y==200-GHOST_SPRITE_HAUTEUR) ghost[1].sensy = -2;
		ghost_move_rel(1, ghost[1].sensx, ghost[1].sensy);

		if (ghost[2].x==0) ghost[2].sensx = 2; else if (ghost[2].x==160-GHOST_SPRITE_LARGEUR_P) ghost[2].sensx = -2;
		if (ghost[2].y==0) ghost[2].sensy = 2; else if (ghost[2].y==200-GHOST_SPRITE_HAUTEUR) ghost[2].sensy = -2;		
		ghost_move_rel(2, ghost[2].sensx, ghost[2].sensy);

		if (ghost[3].x==0) ghost[3].sensx = 1; else if (ghost[3].x==160-GHOST_SPRITE_LARGEUR_P) ghost[3].sensx = -1;
		if (ghost[3].y==0) ghost[3].sensy = 1; else if (ghost[3].y==200-GHOST_SPRITE_HAUTEUR) ghost[3].sensy = -1;		
		ghost_move_rel(3, ghost[3].sensx, ghost[3].sensy);

		
		/* Rendu graphique */		
		vsync();
		put_frame(screen(player.oldx,player.oldy), PLAYER_SPRITE_LARGEUR_O, PLAYER_SPRITE_HAUTEUR, spr_img[IMG_BLANK]);		
		put_frame(screen(player.x,player.y), PLAYER_SPRITE_LARGEUR_O, PLAYER_SPRITE_HAUTEUR, spr_img[player.dc+player.anim]);		

		for (i=0;i<4;i++)
		{
			put_frame(screen(ghost[i].oldx,ghost[i].oldy), GHOST_SPRITE_LARGEUR_O, GHOST_SPRITE_HAUTEUR, spr_img[IMG_BLANK]);		
			put_frame(screen(ghost[i].x,ghost[i].y), GHOST_SPRITE_LARGEUR_O, GHOST_SPRITE_HAUTEUR, spr_img[14+(i<<1)+ghost[i].anim]);				
		}

	}
}