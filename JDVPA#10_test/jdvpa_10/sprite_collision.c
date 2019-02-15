#include "player.h"
#include "ghost.h"
#include "sprite_collision.h"

extern s_player player;
extern s_ghost ghost[4];

unsigned char isCollision(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	if(x1 > x2+4) return 0;
	if(x1+4 < x2) return 0;
	if(y1 > y2+8) return 0;
	if(y1+8 < y2) return 0;
	
	return 1;
}

void col_check(void)
{
	unsigned char i;
		
	for (i=0;i<4;i++)
	{		
			if (isCollision(player.x,player.y,ghost[i].x,ghost[i].y))
			{
					if (ghost[i].fear_timer>0)
					{
						// Ennemi à la niche
						ghost[i].oldx = ghost[i].x;
						ghost[i].oldy = ghost[i].y;
						ghost[i].y=12<<3;
						ghost[i].fear_timer=0;

						if (i==0) 
						{
							ghost[i].base_image = 14;
							ghost[i].wait_timer=100;
							ghost[i].x=16<<2;
						}
						if (i==1) 
						{
							ghost[i].base_image = 16;
							ghost[i].wait_timer=140;
							ghost[i].x=18<<2;
						}
						if (i==2) 
						{
							ghost[i].base_image = 18;
							ghost[i].wait_timer=120;
							ghost[i].x=20<<2;
						}
						if (i==3) 
						{
							ghost[i].base_image = 20;
							ghost[i].wait_timer=150;
							ghost[i].x=22<<2;
						}						
					}
					else
					{
						player.oldx=player.x;
						player.oldy=player.y;
						player.x=19<<2;
						player.y=22<<3;
						break;			
					}
			}
	
	}
}
