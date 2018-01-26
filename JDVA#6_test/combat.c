#include <stdio.h>
#include <stdlib.h>

#include "joueurs.h"
#include "jdvapi_basic.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"

unsigned char *perso[8];

unsigned int *vram;

void main(void)
{
	char x;char xmod8;
	x=10;
	
	vram=precalc_vram();
	
	perso[0]=J1A1;
	perso[1]=J1A2;
	perso[2]=J1A3;
	perso[3]=J1A4;
	perso[4]=J1A1;
	perso[5]=J1A1;
	perso[6]=J1A1;
	perso[7]=J1A1;
	
	mode(2);
	vsync();
	put_frame(vram(0,0),6,50,perso[0]);
	put_frame(vram(1,50),7,50,perso[1]);
	put_frame(vram(2,100),7,50,perso[2]);
	put_frame(vram(3,150),7,50,perso[3]);
	//	set_palette(combat_palette);

	while(1){
		check_controller();
		
		if (get_key(Key_O)) {
			x--;
		}		
		if (get_key(Key_P)) {
			x++;
		}
		xmod8=x%8;
		vsync();
		//put_frame(vram(x,50),80,50,perso[xmod8]);
		if (xmod8==1 || xmod8==2 || xmod8==3) {
			put_frame((unsigned char *)(vram[50]+x),7,50,perso[xmod8]);
		} else {
			put_frame((unsigned char *)(vram[50]+x),6,50,perso[xmod8]);
		}
	}
}