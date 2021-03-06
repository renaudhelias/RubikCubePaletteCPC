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

const unsigned char combat_palette[]=
{
		26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void main(void)
{
	int x;char xmod8;int x2;char x2mod8;char layer=0;char direction=0;
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
	set_palette(combat_palette);
	//vsync();
	put_frame(vram(0,0),6,50,perso1A[0]);
	put_frame(vram(0+8,0),7,50,perso1A[1]);
	put_frame(vram(8+8,0),7,50,perso1A[2]);
	put_frame(vram(8+8+8,0),7,50,perso1A[3]);
	put_frame(vram(8+8+8+8,0),7,50,perso1A[4]);
	put_frame(vram(8+8+8+8+8,0),7,50,perso1A[5]);
	put_frame(vram(8+8+8+8+8+8,0),7,50,perso1A[6]);
	put_frame(vram(8+8+8+8+8+8+8,0),7,50,perso1A[7]);
	put_frame(vram(0,50),6,50,perso2A[0]+((6*50)*1));
	put_frame(vram(8,50),7,50,perso2A[1]+((7*50)*1));
	put_frame(vram(8+8,50),7,50,perso2A[2]+((7*50)*1));
	put_frame(vram(8+8+8,50),7,50,perso2A[3]+((7*50)*1));
	put_frame(vram(8+8+8+8,50),7,50,perso2A[4]+((7*50)*1));
	put_frame(vram(8+8+8+8+8,50),7,50,perso2A[5]+((7*50)*1));
	put_frame(vram(8+8+8+8+8+8,50),7,50,perso2A[6]+((7*50)*1));
	put_frame(vram(8+8+8+8+8+8+8,50),7,50,perso2A[7]+((7*50)*1));

	while(1){
		check_controller();
		layer=3;
		if (get_key(Key_CursorLeft) && direction==0) {
			if (x>0) x--;
			direction=1;
		}
		if (get_key(Key_CursorRight) && direction==0) {
			if (x<640/2-57) x++;
			direction=1;
		}
		
		if (!get_key(Key_CursorLeft) && !get_key(Key_CursorRight)) {
			direction=0;
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
		
		// if (direction==1) {
			// if (x>0) x--; else {direction=0; layer=(layer+1)%4;}
		// } else {		
			// if (x<640/2-57) x++; else {direction=1; layer=(layer+1)%4;}
		// }
		
		xmod8=x%8;
		x2=640-x-57;
		x2mod8=x2%8;
		vsync();
		// 6sec
		// (640/2)/25=12sec donc effectivement le calcul est juste (c'est pas du 25Hz l'Amstrad, c'es du 50Hz), je suis bien dans temps
		if (xmod8==0) {
			put_frame((unsigned char *)(vram[120]+x/8),6,50,perso1A[xmod8]+((6*50)*layer));
		} else {
			put_frame((unsigned char *)(vram[120]+x/8),7,50,perso1A[xmod8]+((7*50)*layer));
		}
		if (x2mod8==0) {
			put_frame((unsigned char *)(vram[120]+x2/8),6,50,perso2A[x2mod8]+((6*50)*layer));
		} else {
			put_frame((unsigned char *)(vram[120]+x2/8),7,50,perso2A[x2mod8]+((7*50)*layer));
		}
//		combat.c:135: error 9: FATAL Compiler Internal Error in file '/home/sdcc-builder
//		/build/sdcc-build/orig/sdcc/src/z80/ralloc.c' line number '1354' : isSymbolEqual
//		(sym, OP_SYMBOL (IC_RESULT (ic)))
		// vsync();
		// if (xmod8==0) {
			// put_frame((unsigned char *)(vram[100]+x/8),6,50,perso1A[xmod8]+((6*50)*((layer+1)%4)));
		// } else {
			// put_frame((unsigned char *)(vram[100]+x/8),7,50,perso1A[xmod8]+((7*50)*((layer+1)%4)));
		// }
		// if (x2mod8==0) {
			// put_frame((unsigned char *)(vram[100]+x2/8),6,50,perso2A[x2mod8]+((6*50)*((layer+1)%4)));
		// } else {
			// put_frame((unsigned char *)(vram[100]+x2/8),7,50,perso2A[x2mod8]+((7*50)*((layer+1)%4)));
		// }
	}
}