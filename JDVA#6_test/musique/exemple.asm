save "winapmus.bin",&3000,&5000

		; Exemple how to play a 50Hz STarKos song with the ASM Player.
		; Written with WinAPE, load this file in the assembler and hit
		; F9 (Compile and Run).

		org &3000
		run $

		; disable the firmware interrupt service routine
		ld hl,&C9FB
		ld (&38),hl
		im 1		; select IM1 just in case
 
; void calque4000()
;{
;  __asm
    ld bc,&BC00+12 ; On met la valeur 16 dans
    out (c),c      ; le registre 12 du CRTC
    ld bc,&BD00+16
    out (c),c
;  __endasm;
;}
 
		; Initialize the STarKos player
;by freemac
;ld de,songdata
		call player
 
		; Synchronisation with the frame flyback
		; which should be a 50Hz signal (if no
		; one messed up with the CRTC before =)
wait_vsync	ld b,&F5
		in a,(c)
		rra
		jr nc,wait_vsync+2
 
		; wait for a few 300Hz interrupts
		halt
		halt
		halt
 
		; Set a white raster in the BORDER to "see" how much
		; CPU time the player takes.
		ld bc,&7F10
		out (c),c
		ld c,&4B
		out (c),c
 
		; Play the STarKos song
		call player+3
 
		; Set the BORDER to black
		ld bc,&7F54
		out (c),c
 
		jr wait_vsync
 
		; Stop the STarKos player / Mute sounds
		;call player+6
		
		; Exit
		;ret		

		; Include the player
player		read "sks.player.asm"

		; Include the compiled song data
		; the song was compiled at &5000
		ORG &4000
songdata	incbin "wbar4sks.BIN"
