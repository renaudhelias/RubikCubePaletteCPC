#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_sync.h"
#include "jdvapi_keyb.h"
// CPCTelera/src/audio/audio.h
#include "arkostracker.h"

#include "jdvapi_floppy.h"

void border_raster_begin()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set a white raster in the BORDER to "see" how much
	; CPU time the player takes.
	ld bc,#0x7F10
	out (c),c
	ld c,#0x4B
	out (c),c
  __endasm;
}

void border_raster_end()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set the BORDER to black
	ld bc,#0x7F54
	out (c),c
  __endasm;
}

void border_raster_end2()
{
  //grimware/official.sks.player.1.2.zip/exemple.asm
  __asm
	; Set the BORDER to un peu de violet...
	ld bc,#0x7F5D
	out (c),c
  __endasm;
}

void main(void)
{
	volatile unsigned char playing=1;
	volatile unsigned char touche_Space=0;
	volatile unsigned char touche_O=0;
	volatile unsigned char touche_P=0;
	
	//musique en &C000
	SetupDOS();
	calque4000();
	bank0123();
	LoadFile("molu4000.bin", (char *)0x4000);

	raster_halt();
	// cpctelera-1.4.2/examples/medium/arkosAudio
	cpct_akp_musicInit((void *)0x4000);
	cpct_akp_SFXInit((void *)0x4000);
	
	while (1) {
		check_controller();
		
		vsync();
		halt();
		halt();
		halt();
		border_raster_begin();
		if (playing) {
			// Play the STarKos song
			cpct_akp_musicPlay();
			
			if (cpct_akp_songLoopTimes > 0) {
				// Song has ended, start it again and set loop to 0
				cpct_akp_musicInit((void *)0x4000);
			}
		}
		
		// Key_Space
		if (!touche_Space && get_key(Key_Space)) {
			touche_Space=1;
			if (playing) {
				cpct_akp_stop(); // does cut also FX :/
				playing=0;
			} else {
				playing=1;
			}
		} else if (!get_key(Key_Space)) {
			touche_Space=0;
		}
		if (!touche_O && get_key(Key_O)) {
			touche_O=1;
			cpct_akp_SFXPlay(13, 15, 36, 20, 0, AY_CHANNEL_A);
		} else if (!get_key(Key_O)) {
			touche_O=0;
		}
		if (!touche_P && get_key(Key_P)) {
			touche_P=1;
			cpct_akp_SFXPlay(3, 15, 60, 0, 40, AY_CHANNEL_C);
		} else if (!get_key(Key_P)) {
			touche_P=0;
		}
		
		if (get_key(Key_O) || get_key(Key_P) || get_key(Key_Space)) {
			border_raster_end2();
		} else {
			border_raster_end();
		}
	}
}