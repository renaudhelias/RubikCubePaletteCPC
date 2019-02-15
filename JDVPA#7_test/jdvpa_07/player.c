#include "player.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

s_player player;
extern unsigned char laby[];

void player_init()
{
	player.oldx=0;
	player.oldy=0;
	player.x=19<<2;
	player.y=22<<3;
	player.dd = PLAYER_STOP;
	player.dc = PLAYER_STOP;
	player.timer=0;
	player.anim=0;
	player.score = 0;
	
}

void player_move_rel(char mx,char my)
{
		player.oldx = player.x;
		player.oldy = player.y;
		
		player.x+=mx;
		player.y+=my;
		player.timer++;
		if (player.dc!=PLAYER_STOP)
		{		
			if ((player.timer&3)==0) 
			{
				player.anim++;
				if (player.anim==3) player.anim=0;
			}
		} else player.anim=0;
			
		

}

// 0 - Libre
// 1 - Pac Gum
// 2 - Mega Pac
// 3 - Mur
unsigned char player_return_tile_type(unsigned char x,unsigned char y)
{
		unsigned int ntile;
		
		// Récupération du code tile en x,y
		ntile = (unsigned int)((y>>3)*40)+(x>>2);
		if (laby[ntile]==1) return 0;
		if (laby[ntile]==10) return 1;
		if (laby[ntile]==11) return 2;
		
		return 3;
}

void player_control(void)
{		unsigned int ntile;

		/* On check les contrôles pour savoir ou désire aller le joueur --> Positionnement de la variable direction désirée */
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
		else
			player.dd = PLAYER_STOP;

		

		/* Si le joueur est positionné à en endroit ou il peut changer de direction */
		/* On va vérifier qu'il peut bien aller dans la direction désirée */
		/* Si oui la direction désirée devient la direction courante */
		if (((player.x&3)==0) && ((player.y&7)==0))
		{
			if ((player.dd==PLAYER_LEFT) && (player_return_tile_type(player.x-4,player.y)!=3))
				player.dc = player.dd;
			else
			if ((player.dd==PLAYER_RIGHT) && (player_return_tile_type(player.x+4,player.y)!=3))
				player.dc = player.dd;
			else
			if ((player.dd==PLAYER_UP) && (player_return_tile_type(player.x,player.y-8)!=3))
				player.dc = player.dd;
			else
			if ((player.dd==PLAYER_DOWN) && (player_return_tile_type(player.x,player.y+8)!=3))
				player.dc = player.dd;				
		}
		
		/* On déplace le joueur par rapport à la direction courante, si il n'y à pas d'obstacle */
		/* Sinon, on le stoppe et la direction courante devient PLAYER_STOP */
		if (player.dc==PLAYER_LEFT) 
		{
				if ((((player.x&3)==0) && ((player.y&7)==0)) && (player_return_tile_type(player.x-4,player.y)==3)) player.dc = PLAYER_STOP;
				if (player.dc!=PLAYER_STOP)	player_move_rel(-2,0);
		}
		else
		if (player.dc==PLAYER_RIGHT)  
		{
				if ((((player.x&3)==0) && ((player.y&7)==0)) && (player_return_tile_type(player.x+4,player.y)==3)) player.dc = PLAYER_STOP;
				if (player.dc!=PLAYER_STOP)	player_move_rel(2,0);
		}
		else
		if (player.dc==PLAYER_UP) 
		{
				if ((((player.x&3)==0) && ((player.y&7)==0)) && (player_return_tile_type(player.x,player.y-8)==3)) player.dc = PLAYER_STOP;
				if (player.dc!=PLAYER_STOP)	player_move_rel(0,-2);
		}
		else
		if (player.dc==PLAYER_DOWN) 
		{
				if ((((player.x&3)==0) && ((player.y&7)==0)) && (player_return_tile_type(player.x,player.y+8)==3)) player.dc = PLAYER_STOP;
				if (player.dc!=PLAYER_STOP)	player_move_rel(0,2);
		}			
		
		/* Mangeage de Pacgum ... MIAM */
		if ((((player.x&3)==0) && ((player.y&7)==0)) && (player_return_tile_type(player.x,player.y)<3))
		{
			ntile = (unsigned int)((player.y>>3)*40)+(player.x>>2);
			laby[ntile]=1;
		}
		
}