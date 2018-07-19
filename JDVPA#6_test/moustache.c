#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jdvapi_basic1.h"
#include "jdvapi_frame.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"
#include "jdvapi_floppy.h"

const unsigned char palette_chat[]=
{
		5,0,18,6,0,0,0,0,0,0,0,0,0,0,0,0
};

unsigned int *vram;

#include "test_vsync.c"
#include "test_int.c"
#include "test_palette.c"

// Moustache : chat de Gaston Lagaffe

void main() {
	vram=precalc_vram();
	SetupDOS();
	mode(1);// à cause de la publicité ParaDOS ;)
	border(5);
	set_palette(palette_chat);
	bank0123();
//	LoadFile("chat1.scr", (char *)0x4000);
	LoadFile("chat2.scr", (char *)0x5000);
	LoadFile("chat3.scr", (char *)0x7800);
	put_frame_transparent((unsigned char *)(0xC000 + vram[0]+30),50,200,0x5000);
	//put_frame_transparent((unsigned char *)(0xC000 + vram[148]+20),40,48,0x7800);
	test_vsync();
	test_int();
	printf("\r\n\r\n\r\n V0.0c4");
	test_palette();
	while(1) {} // keyboard scan does perturbate raster palette, so no keyb by here :p
}