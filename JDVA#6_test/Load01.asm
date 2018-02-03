;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module Load01
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _SetMode
	.globl _SetPalette
	.globl _SetColor
	.globl _LoadFile
	.globl _SetupDOS
	.globl _strlen
	.globl _nFileNameLen
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_nFileNameLen::
	.ds 1
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;Load01.c:12: void SetupDOS()
;	---------------------------------
; Function SetupDOS
; ---------------------------------
_SetupDOS::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load01.c:45: __endasm;
	ld	l, 2 (ix) ;stack return address
	ld	h, 3 (ix) ;stack return address
	ld	(_stack+1), hl
;;------------------------------------------------------------------------
;;	store the drive number the loader was run from
	ld	hl,(#0xbe7d)
	ld	a,(hl)
	ld	(_drive+1),a
;;------------------------------------------------------------------------
	ld	c,#0xff ;; disable all roms
	ld	hl, #_start222 ;; execution address for program
	call	#0xbd16 ;;mc_start_program ;; start it
	  _start222::
	nop
	call	#0xbccb ;;kl_rom_walk ;; enable all roms
;;------------------------------------------------------------------------
;;	when AMSDOS is enabled, the drive reverts back to drive 0!
;;	This will restore the drive number to the drive the loader was run from
	  _drive:
	ld a, #0x00
	ld	hl,(#0xbe7d)
	ld	(hl),a
	  _stack:
	ld hl, #0x0000
	push	hl
	push	hl
	pop	ix
	ret
;Load01.c:54: void LoadFile(char *sFileName, char *pLoadAddress)
;	---------------------------------
; Function LoadFile
; ---------------------------------
_LoadFile::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load01.c:56: nFileNameLen = strlen(sFileName);
	ld	l,4 (ix)
	ld	h,5 (ix)
	push	hl
	call	_strlen
	pop	af
	ld	c,l
	ld	b,h
	ld	iy,#_nFileNameLen
	ld	0 (iy),c
;Load01.c:88: __endasm;
;;	B = length of the filename in characters
	ld	hl, #_nFileNameLen;
	ld	b, (hl)
;;	HL = address of the start of the filename
	LD	L, 4 (IX) ;sFileName
	LD	H, 5 (IX) ;sFileName
;;	DE = address of a 2k buffer
;;	in disc mode: this buffer is not used when CAS IN DIRECT
;;	firmware function is used, so it is safe to put it anywhere
;;	you want.
	ld	de, #0x0
;;	firmware function to open a file for reading
	call	#0xbc77 ;;cas_in_open
;;	firmware function to load the entire file
;;	this will work with files that have a AMSDOS header (ASCII
;;	files do not have a header)
;;	HL = load address
	LD	L, 6 (IX) ;pLoadAddress
	LD	H, 7 (IX) ;pLoadAddress
;;	read file
	call	#0xbc83 ;;cas_in_direct
;;	firmware function to close a file opened for reading
	call	#0xbc7a ;;cas_in_close
	pop	ix
	ret
;Load01.c:96: void SetColor(unsigned char nColorIndex, unsigned char nPaletteIndex)
;	---------------------------------
; Function SetColor
; ---------------------------------
_SetColor::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load01.c:103: __endasm;
	ld	a, 4 (ix)
	ld	b, 5 (ix)
	ld	c, b
	call	#0xBC32 ;SCR SET INK
	pop	ix
	ret
;Load01.c:111: void SetPalette(const unsigned char *pPalette, unsigned char nNumColors)
;	---------------------------------
; Function SetPalette
; ---------------------------------
_SetPalette::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load01.c:115: for(nColor = 0; nColor < nNumColors; nColor++)
	ld	c,#0x00
00103$:
	ld	a,c
	sub	a, 6 (ix)
	jr	NC,00105$
;Load01.c:116: SetColor(nColor, pPalette[nColor]);
	ld	a,4 (ix)
	add	a, c
	ld	e,a
	ld	a,5 (ix)
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	ld	l,a
	push	bc
	ld	a,l
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_SetColor
	pop	af
	pop	bc
;Load01.c:115: for(nColor = 0; nColor < nNumColors; nColor++)
	inc	c
	jr	00103$
00105$:
	pop	ix
	ret
;Load01.c:124: void SetMode(unsigned char nMode)
;	---------------------------------
; Function SetMode
; ---------------------------------
_SetMode::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load01.c:129: __endasm;
	ld	a, 4 (ix)
	call	#0xBC0E ;SCR_SET_MODE
	pop	ix
	ret
;Load01.c:138: main()
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
;Load01.c:140: SetupDOS();
	call	_SetupDOS
;Load01.c:142: SetMode(0);
	xor	a, a
	push	af
	inc	sp
	call	_SetMode
	inc	sp
;Load01.c:144: LoadFile("01.scr", (char *)0xC000);
	ld	hl,#0xc000
	push	hl
	ld	hl,#___str_0
	push	hl
	call	_LoadFile
	pop	af
;Load01.c:145: SetPalette((char *)0xD7D1, 16);
	ld	h,#0x10
	ex	(sp),hl
	inc	sp
	ld	hl,#0xd7d1
	push	hl
	call	_SetPalette
	pop	af
	inc	sp
;Load01.c:147: while(1);
00102$:
	jr	00102$
;Load01.c:149: return 0;
	pop	ix
	ret
___str_0:
	.ascii "01.scr"
	.db 0x00
	.area _CODE
	.area _INITIALIZER
__xinit__nFileNameLen:
	.db #0x00	; 0
	.area _CABS (ABS)
