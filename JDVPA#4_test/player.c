#include "player.h"

s_player player;

void player_init()
{
	player.oldx=0;
	player.oldy=0;
	player.x=0;
	player.y=0;
	player.dd = PLAYER_STOP;
	player.dc = PLAYER_STOP;
	player.timer=0;
	player.anim=0;
	
}

void player_move_rel(char mx,char my)
{
		player.oldx = player.x;
		player.oldy = player.y;
		
		player.x+=mx; 
		player.y+=my;
		player.timer++;
		if ((player.timer&3)==0)  
		{
			player.anim++;
			if (player.anim==3) player.anim=0;
		}
			
		

}