#include <stdio.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_sync.h"
// CPCTelera/src/audio/audio.h
#include "arkostracker.h"
// cpctelera-1.4.2/examples/medium/arkosAudio
#include "molusk.h" // This file is geneated on compilation from music/molusk.aks


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

void main(void)
{
	raster_halt();
	cpct_akp_musicInit(molusk_song);
	
	while (1) {
		vsync();
		halt();
		halt();
		halt();
		border_raster_begin();
		// Play the STarKos song
		cpct_akp_musicPlay();
		border_raster_end();
	}
}