#include <stdio.h>
#include <stdlib.h>

#include "joueurs.h"
#include "jdvapi_basic.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"

unsigned char *perso1A[8];
//unsigned char *perso1R[8];
unsigned char *perso2A[8];
//unsigned char *perso2R[8];

unsigned int *vram;

void main(void)
{
	char x;char xmod8;char x2;char x2mod8;char layer=0;
	x=0;x2=640-x-57;
	
	vram=precalc_vram();
	
	perso1A[0]=J1A1;
	perso1A[1]=J1A2;
	perso1A[2]=J1A3;
	perso1A[3]=J1A4;
	perso1A[4]=J1A5;
	perso1A[5]=J1A6;
	perso1A[6]=J1A7;
	perso1A[7]=J1A8;
	
	// perso1R[0]=J1R1;
	// perso1R[1]=J1R2;
	// perso1R[2]=J1R3;
	// perso1R[3]=J1R4;
	// perso1R[4]=J1R5;
	// perso1R[5]=J1R6;
	// perso1R[6]=J1R7;
	// perso1R[7]=J1R8;
	
	perso2A[0]=J2A1;
	perso2A[1]=J2A2;
	perso2A[2]=J2A3;
	perso2A[3]=J2A4;
	perso2A[4]=J2A5;
	perso2A[5]=J2A6;
	perso2A[6]=J2A7;
	perso2A[7]=J2A8;
	
	// perso2R[0]=J2R1;
	// perso2R[1]=J2R2;
	// perso2R[2]=J2R3;
	// perso2R[3]=J2R4;
	// perso2R[4]=J2R5;
	// perso2R[5]=J2R6;
	// perso2R[6]=J2R7;
	// perso2R[7]=J2R8;
	
	mode(2);
	vsync();
	put_frame(vram(0,0),6,50,perso1A[0]);
	put_frame(vram(0+8,0),7,50,perso1A[1]);
	put_frame(vram(2+8+8,0),7,50,perso1A[2]);
	put_frame(vram(3+8+8+8,0),7,50,perso1A[3]);
	put_frame(vram(3+8+8+8+8,0),7,50,perso1A[4]);
	put_frame(vram(3+8+8+8+8+8,0),7,50,perso1A[5]);
	put_frame(vram(3+8+8+8+8+8+8,0),7,50,perso1A[6]);
	put_frame(vram(3+8+8+8+8+8+8+8,0),7,50,perso1A[7]);
	put_frame(vram(0,50),6,50,perso2A[0]+((6*50)*1));
	put_frame(vram(1+8,50),7,50,perso2A[1]+((7*50)*1));
	put_frame(vram(2+8+8,50),7,50,perso2A[2]+((7*50)*1));
	put_frame(vram(3+8+8+8,50),7,50,perso2A[3]+((7*50)*1));
	put_frame(vram(3+8+8+8+8,50),7,50,perso2A[4]+((7*50)*1));
	put_frame(vram(3+8+8+8+8+8,50),7,50,perso2A[5]+((7*50)*1));
	put_frame(vram(3+8+8+8+8+8+8,50),7,50,perso2A[6]+((7*50)*1));
	put_frame(vram(3+8+8+8+8+8+8+8,50),7,50,perso2A[7]+((7*50)*1));
	//	set_palette(combat_palette);

	while(1){
		check_controller();
		layer=3;
		if (get_key(Key_CursorLeft)) {
			if (x>0) x--;
		}		
		if (get_key(Key_CursorRight)) {
			if (x<33*2) x++;
		}
		if (get_key(Key_Space)) {
			layer=1;
			if (get_key(Key_CursorUp)) {
				layer=0;
			}
			if (get_key(Key_CursorDown)) {
				layer=2;
			}
		}
		
		xmod8=x%8;
		x2=x+8;//640-x-57;
		x2mod8=x2%8;
		vsync();
		if (xmod8==0) {
			put_frame((unsigned char *)(vram[120]+x),6,50,perso1A[xmod8]+((6*50)*layer));
		} else {
			put_frame((unsigned char *)(vram[120]+x),7,50,perso1A[xmod8]+((7*50)*layer));
		}
		if (x2mod8==0) {
			put_frame((unsigned char *)(vram[120]+x2),6,50,perso2A[x2mod8]+((6*50)*layer));
		} else {
			put_frame((unsigned char *)(vram[120]+x2),7,50,perso2A[x2mod8]+((7*50)*layer));
		}
	}
}