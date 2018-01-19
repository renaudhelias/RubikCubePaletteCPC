#include <stdio.h>
#include <stdlib.h>

#include "poisson.h"
#include "jdvapi_basic.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"

unsigned char *fish[12];

void main(void)
{
	char x;
	x=10;
	
	fish[0]=poisson1;
	fish[1]=poisson2;
	fish[2]=poisson_groupe;
	fish[3]=poisson_groupe+(6*16);
	fish[4]=poisson_groupe+((6*16)*2);
	fish[5]=poisson_groupe+((6*16)*9); // fond vide
	
	mode(0);
	set_palette(poisson_palette);
	

	while(1){
		check_controller();
		
//		if (get_key(Key_A) || get_key(Key_Space)) {
//			put_frame(vram(10,100),6,16,fish[1]);
//		}
		
		// synchro en bas de l'écran
		vsync();
		// effacer poisson
		put_frame(vram(x,100),6,16,fish[5]);
		if (get_key(Key_O)) {
			x--;
		}		
		if (get_key(Key_P)) {
			x++;
		}
		// afficher poisson
		put_frame(vram(x,100),6,16,fish[1]);
	}
}