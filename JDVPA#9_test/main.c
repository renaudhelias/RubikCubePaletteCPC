#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jdvapi_basic1.h"
#include "jdvapi_keyb.h"
#include "jdvapi_frame.h"
#include "jdvapi_sync.h"

#include "pacman_reduce_sprites.h"
#include "blank_reduce_sprites.h"
#include "ghost_reduce_sprites.h"

#include "player.h"
#include "ghost.h"
#include "tiles.h"
//#include "labypac_map.h"
#include "laby_data.h"

#define IMG_BLANK 0

unsigned int *vram;

unsigned char *spr_img[25];
unsigned char *tiles_img[26];
unsigned char timer;


const unsigned char game_palette[]=
{
		0,25,7,8,11,16,22,26,0,0,0,0,0,0,0,0
};

void render_background(unsigned char x,unsigned char y)
{
		unsigned int xtile,ytile;
		unsigned int ntile;
		unsigned int xpix,ypix;
//		unsigned int addr;
		
		// Récupération du code tile en x,y
		xtile = (unsigned int)x>>2; // Diviser par 4
		ytile = (unsigned int)y>>3; // Diviser par 8
		ntile = (unsigned int)(ytile*40)+xtile;
		
		xpix = (xtile<<2);
		ypix = (ytile<<3);
		
		put_frame(screen(xpix,ypix),2,8,tiles_img[laby[ntile]]);
		put_frame(screen((xpix+4),ypix),2,8,tiles_img[laby[ntile+1]]);

		put_frame(screen(xpix,(ypix+8)),2,8,tiles_img[laby[ntile+40]]);
		put_frame(screen((xpix+4),(ypix+8)),2,8,tiles_img[laby[ntile+41]]);

/* Autre écriture*/
/*
		addr = *(precalc_vram+ypix);
		put_frame((unsigned char *)(addr+(xpix>>1)),2,8,tiles_img[laby[ntile]]);
		put_frame((unsigned char*)(addr+((xpix+4)>>1)),2,8,tiles_img[laby[ntile+1]]);

		addr = *(precalc_vram+ypix+8);
		put_frame((unsigned char *)(addr+(xpix>>1)),2,8,tiles_img[laby[ntile+40]]);
		put_frame((unsigned char*)(addr+((xpix+4)>>1)),2,8,tiles_img[laby[ntile+41]]);
*/
}

void waito(void)
{
		
}

void main(void)
{
	char i;
	unsigned int cpt,x,y;
	//unsigned int addr;
	
	
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
	
	// Les tiles démarrent à 1, la tile 0 est une tile transparente dans
	// Tiled. Non utilisé ici.
	for (i=0;i<26;i++)
		tiles_img[i+1]= (unsigned char *)tiles + ((2*8)*i);
	
	mode(0);
	border(0);
	set_palette(game_palette);
	vsync();
	
	cpt=0;
	
	laby_init();
	
	
	for (y=0;y<25;y++)
	{
		for (x=0;x<40;x++)
		{
			// x et y doivent être des UNSIGNED INT PASSE A CETTE FONCTION
			// Sinon glitch, certainement du à une conversion de type foireuse qqpart ...
			// cpt --> Unsigned int car peut aller jusqu'à 25*40
			put_frame(screen((x*4),(y*8)),2,8,tiles_img[laby[cpt]]);
			cpt++;
			
		}
	}
		
	/* Autre écriture*/
/*	
	for (y=0;y<200;y+=8)
	{
		addr = *(precalc_vram+y);
		for (x=0;x<160;x+=4)
		{			
			put_frame((unsigned char*)addr,2,8,tiles_img[laby[cpt]]);
			addr+=2;
			cpt++;
		}
	}	
*/	
	player_init();
	ghost_init();
	
	timer=0;
	while(1)
	{
		check_controller();
		player_control();			
		if ((timer&7)==0) {} else {ghost_update();}
		
		/* Rendu graphique */		
		vsync();		
		render_background(player.oldx,player.oldy);
		put_frame(screen(player.x,player.y), PLAYER_SPRITE_LARGEUR_O, PLAYER_SPRITE_HAUTEUR, spr_img[player.dc+player.anim]);		
		//put_frame(screen(player.x,player.y), PLAYER_SPRITE_LARGEUR_O, PLAYER_SPRITE_HAUTEUR, spr_img[tile_dc[player.dc]+player.anim]);		
	
		for (i=0;i<4;i++)
		{	
			render_background(ghost[i].oldx,ghost[i].oldy);
			put_frame(screen(ghost[i].x,ghost[i].y), GHOST_SPRITE_LARGEUR_O, GHOST_SPRITE_HAUTEUR, spr_img[14+(i<<1)+ghost[i].anim]);				
		}
		timer++;

	}
}