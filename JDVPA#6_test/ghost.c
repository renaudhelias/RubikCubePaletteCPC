#include "ghost.h"

s_ghost ghost[4];

void ghost_init()
{
	char i;
	
	for (i=0;i<4;i++)
	{
		ghost[i].oldx=0;
		ghost[i].oldy=0;
		ghost[i].x=0;
		ghost[i].y=0;	
		ghost[i].sensx=0;
		ghost[i].sensy=0;
		ghost[i].timer=0;
		ghost[i].anim=0;		
	}
	
}

void ghost_move_rel(char i,char mx,char my)
{
		ghost[i].oldx = ghost[i].x;
		ghost[i].oldy = ghost[i].y;
		
		ghost[i].x+=mx;
		ghost[i].y+=my;
		
		ghost[i].timer++;
		if ((ghost[i].timer&3)==0) 
		{
			ghost[i].anim++;
			if (ghost[i].anim==2) ghost[i].anim=0;
		}

}