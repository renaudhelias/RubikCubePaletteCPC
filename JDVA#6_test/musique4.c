#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_sync.h"
#include "jdvapi_keyb.h"
// CPCTelera/src/audio/audio.h
// #include "sks.player.h"

#include "jdvapi_floppy.h"

/**
 * musique4 : tentative de création d'un sks3000.bin à partir de WinAPE
 * les routines sont protégés par ce qu'elles arrivent bizarrement à toucher ma variable
 * volatile unsigned char playing=1;
 */

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

void cpct_akp_musicInit()
{
	__asm
	;; backup Z80 state
  push af
  push bc
  push de
  push hl
  push ix
  push iy
  exx
  ex af, af'
  push af
  push bc
  push de
  push hl
  
	; sks3000.bin/exemple.asm
	call #0x3000
	
	;; restore Z80 state
  pop hl
  pop de
  pop bc
  pop af
  ex af, af'
  exx
  pop iy
  pop ix
  pop hl
  pop de
  pop bc
  pop af
	__endasm;
}

void cpct_akp_musicPlay()
{
	__asm
	;; backup Z80 state
  push af
  push bc
  push de
  push hl
  push ix
  push iy
  exx
  ex af, af'
  push af
  push bc
  push de
  push hl
	
	; sks3000.bin/exemple.asm
	call #0x3003
	
	;; restore Z80 state
  pop hl
  pop de
  pop bc
  pop af
  ex af, af'
  exx
  pop iy
  pop ix
  pop hl
  pop de
  pop bc
  pop af
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
	// wbar4sks.bin : du wbar.sks en .bin STarKos 1.2 tool run"ds" à l'adresse &4000
	LoadFile("wbar4sks.bin", (char *)0x4000);

	raster_halt();

	// cpctelera-1.4.2/examples/medium/arkosAudio
	cpct_akp_musicInit(); //(void *)0x4000);


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
			
			//if (cpct_akp_songLoopTimes > 0) {
			//	// Song has ended, start it again and set loop to 0
			//	cpct_akp_musicInit((void *)0x4000);
			//}
		}
		border_raster_end();
	}
}