#include "ghost.h"
#include "player.h"
//#include "labypac_map.h"
#include "laby_data.h"

s_ghost ghost[4];

void ghost_init()
{
	char i;
	
	for (i=0;i<4;i++)
	{
		ghost[i].oldx=0;
		ghost[i].oldy=0;
		ghost[i].x=0;
		ghost[i].y=12<<3;	
		ghost[i].sensx=GHOST_VITESSE_H;	/* Va à droite de 2 pixels */
		ghost[i].sensy=0;
		ghost[i].timer=0;
		ghost[i].anim=0;	
		ghost[i].scatter_timer = 0;
		ghost[i].fear_timer = 0;

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
	
}

// 0 - Libre
// 3 - Mur
unsigned char ghost_return_tile_type(unsigned char x,unsigned char y)
{
		unsigned int ntile;
		
		// Récupération du code tile en x,y
		ntile = (unsigned int)((y>>3)*40)+(x>>2);
		// case vide ou (pate gum petite ou grosse)
		if ((laby[ntile]==1) || (laby[ntile]==10) || (laby[ntile]==11)) return 0;
		
		return 1;
}

void ghost_move_rel(char i,char mx,char my)
{
// dans les choux
//if (ghost_return_tile_type(ghost[i].x+mx,ghost[i].y+my)!=0)
//	return;
		
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

/* IA très très basique et spécifique au labyrinthe !! */
void ghost_ia_wait(unsigned char gid)
{		
		/* N'est plus en mode attente ?*/
		if (ghost[gid].wait_timer==0)
		{
			/* On le fait sortir du labyrinthe, et on lui donne un sens */
			/* par rapport à la position courant du joueur */
			ghost[gid].oldx=ghost[gid].x;
			ghost[gid].oldy=ghost[gid].y;
			ghost[gid].x=19<<2;
			ghost[gid].y=10<<3;		
			ghost[gid].sensy=0;
			if (ghost[gid].x<=player.x) ghost[gid].sensx=-GHOST_VITESSE_H; else ghost[gid].sensx=GHOST_VITESSE_H;			
		}
		else	/* Toujours en mode attente */
		{
			if ((ghost[gid].x==(15<<2)) || (ghost[gid].x==(23<<2)))
			{
				ghost[gid].sensx = ghost[gid].sensx * -1;
			}
		
			ghost_move_rel(gid,ghost[gid].sensx,0);		
		}
}


void ghost_ia(unsigned char gno,unsigned char destx,unsigned char desty)
{
	/* On arrive à une possible intersection */
	if (((ghost[gno].x&3)==0) && ((ghost[gno].y&7)==0))
	{	
		
		if (ghost[gno].sensx!=0)
		{
			if ((ghost[gno].y>desty) && (ghost_return_tile_type(ghost[gno].x,ghost[gno].y-8)==0))
			{
				ghost[gno].sensx=0;
				ghost[gno].sensy=-GHOST_VITESSE_V;
			} else
			if ((ghost[gno].y<desty) && (ghost_return_tile_type(ghost[gno].x,ghost[gno].y+8)==0))
			{
				ghost[gno].sensx=0;
				ghost[gno].sensy=GHOST_VITESSE_V;
			} else	
			if ((ghost[gno].sensx>0) && (ghost_return_tile_type(ghost[gno].x+4,ghost[gno].y)!=0))
			{
				ghost[gno].sensx = ghost[gno].sensx *-1;
			} else
			if ((ghost[gno].sensx<0) && (ghost_return_tile_type(ghost[gno].x-4,ghost[gno].y)!=0))
			{
				ghost[gno].sensx = ghost[gno].sensx *-1;
			} 	
			
		}
		else if (ghost[gno].sensy!=0)
		{
			if ((ghost[gno].x>destx) && (ghost_return_tile_type(ghost[gno].x-4,ghost[gno].y)==0))
			{
				ghost[gno].sensx=-GHOST_VITESSE_H;
				ghost[gno].sensy=0;
			} else
			if ((ghost[gno].x<destx) && (ghost_return_tile_type(ghost[gno].x+4,ghost[gno].y)==0))
			{
				ghost[gno].sensx=GHOST_VITESSE_H;
				ghost[gno].sensy=0;
			} else	
			if ((ghost[gno].sensy>0) && (ghost_return_tile_type(ghost[gno].x,ghost[gno].y+8)!=0))
			{
				ghost[gno].sensy = ghost[gno].sensy *-1;
			} else
			if ((ghost[gno].sensy<0) && (ghost_return_tile_type(ghost[gno].x,ghost[gno].y-8)!=0))
			{
				ghost[gno].sensy = ghost[gno].sensy *-1;
			} 			
		}
		
	}
	
	if (ghost_return_tile_type(ghost[gno].x+ghost[gno].sensx,ghost[gno].y+ghost[gno].sensy)!=0) {
		// dans les choux
		ghost[gno].sensx=-ghost[gno].sensx;
		ghost[gno].sensy=-ghost[gno].sensy;
	}
	ghost_move_rel(gno,ghost[gno].sensx,ghost[gno].sensy);

}

void ghost_fear(void)
{
	ghost[0].fear_timer = 200;
	ghost[1].fear_timer = 200;
	ghost[2].fear_timer = 200;
	ghost[3].fear_timer = 200;
	
}

void ghost_update(void)
{
	unsigned char i;
	unsigned char destx=0;
	unsigned char desty=0;
	
	for (i=0;i<4;i++)
	{
		/* Le fantome est en mode attente */
		if (ghost[i].wait_timer>0)
		{
			/* Appeler l'IA du mode attente */
			ghost[i].wait_timer--;
			ghost_ia_wait(i);
		}
		else if (ghost[i].scatter_timer>0) /* Se barre */
		{
		}
		else if ((ghost[i].fear_timer>0) && (ghost[i].wait_timer==0))/* Se barrre et prêt à se faire bouffer ! */
		{
			ghost[i].fear_timer--;			
			if (ghost[i].fear_timer==0)
			{
				ghost[i].base_image=14+(i<<1);
			} else
			{
				ghost_ia(i,0,0);
				ghost[i].base_image=22;
			}
		}
		else	/* IA d'attaque classique */
		{				
			if (i==0) 
			{
				ghost_ia(0,player.x,player.y);	
			}
			else if (i==1)
			{
				ghost_ia(1,player.x+3,player.y+3);
			}
			else if (i==2)
			{
				ghost_ia(2,player.x-ghost[0].y,player.y-ghost[0].x);
			}
			else if (i==3)
			{
				if (player.dc==PLAYER_UP)
				{
					destx = player.x;
					desty = player.y-3;
				}else
				if (player.dc==PLAYER_DOWN)
				{
					destx = player.x;
					desty = player.y+3;
				}else
				if (player.dc==PLAYER_LEFT)
				{
					destx = player.x-3;
					desty = player.y;
				}else
				if (player.dc==PLAYER_RIGHT)
				{
					destx = player.x+3;
					desty = player.y;
				}			
				ghost_ia(3,destx,desty);
			}			
		}
	}
}