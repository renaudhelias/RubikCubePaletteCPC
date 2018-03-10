#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_sync.h"
#include "jdvapi_keyb.h"
// CPCTelera/src/audio/audio.h
// #include "sks.player.h"

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
	
	
	
	//musique en &4000
	SetupDOS();
	calque4000();
	bank0123();

	//sks3000.bin : la routine SKS de WinAPE qui joue en &4000 placé en &3000
	LoadFile("sks3000.bin", (char *)0x3000);
	// wbar4sks.bin : du wbar.sks en .bin STarKos 1.2 à l'adresse &4000
	LoadFile("wbar4sks.bin", (char *)0x4000);
	


	//justdoit();
	raster_halt();
	
	// cpctelera-1.4.2/examples/medium/arkosAudio
	//cpct_akp_musicInit(); //(void *)0x4000);
	__asm
	; sks3000.bin/exemple.asm
	call #0x3000
	__endasm;


	while (1) {
		check_controller();
		
		vsync();
		halt();
		halt();
		halt();
		border_raster_begin();
		if (playing) {
			// Play the STarKos song
			//cpct_akp_musicPlay();
	__asm
	; sks3000.bin/exemple.asm
	call #0x3003
	__endasm;
			
			//if (cpct_akp_songLoopTimes > 0) {
			//	// Song has ended, start it again and set loop to 0
			//	cpct_akp_musicInit((void *)0x4000);
			//}
		}
		border_raster_end();
	}
}