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

void ghost_ia(void)
{
		if (ghost[0].x==0) ghost[0].sensx = 2; else if (ghost[0].x==160-(GHOST_SPRITE_LARGEUR_P<<1)) ghost[0].sensx = -2;
		ghost_move_rel(0, ghost[0].sensx, ghost[0].sensy);
		
		if (ghost[1].y==0) ghost[1].sensy = 2; else if (ghost[1].y==200-(GHOST_SPRITE_HAUTEUR<<1)) ghost[1].sensy = -2;
		ghost_move_rel(1, ghost[1].sensx, ghost[1].sensy);

		if (ghost[2].x==0) ghost[2].sensx = 2; else if (ghost[2].x==160-(GHOST_SPRITE_LARGEUR_P<<1)) ghost[2].sensx = -2;
		if (ghost[2].y==0) ghost[2].sensy = 2; else if (ghost[2].y==200-(GHOST_SPRITE_HAUTEUR<<1)) ghost[2].sensy = -2;		
		ghost_move_rel(2, ghost[2].sensx, ghost[2].sensy);

		if (ghost[3].x==0) ghost[3].sensx = 1; else if (ghost[3].x==160-(GHOST_SPRITE_LARGEUR_P<<1)) ghost[3].sensx = -1;
		if (ghost[3].y==0) ghost[3].sensy = 1; else if (ghost[3].y==200-(GHOST_SPRITE_HAUTEUR<<1)) ghost[3].sensy = -1;		
		ghost_move_rel(3, ghost[3].sensx, ghost[3].sensy);	
}