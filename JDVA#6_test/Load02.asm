;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module Load02
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _LoadLoop
	.globl _SetMode
	.globl _SetPalette
	.globl _SetColor
	.globl _LoadFile
	.globl _SetupDOS
	.globl _strlen
	.globl _sprintf
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
;Load02.c:12: void SetupDOS()
;	---------------------------------
; Function SetupDOS
; ---------------------------------
_SetupDOS::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load02.c:45: __endasm;
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
;Load02.c:54: void LoadFile(char *sFileName, char *pLoadAddress)
;	---------------------------------
; Function LoadFile
; ---------------------------------
_LoadFile::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load02.c:56: nFileNameLen = strlen(sFileName);
	ld	l,4 (ix)
	ld	h,5 (ix)
	push	hl
	call	_strlen
	pop	af
	ld	c,l
	ld	b,h
	ld	iy,#_nFileNameLen
	ld	0 (iy),c
;Load02.c:88: __endasm;
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
	LD	L, 6 (IX) ;sFileName
	LD	H, 7 (IX) ;sFileName
;;	read file
	call	#0xbc83 ;;cas_in_direct
;;	firmware function to close a file opened for reading
	call	#0xbc7a ;;cas_in_close
	pop	ix
	ret
;Load02.c:96: void SetColor(unsigned char nColorIndex, unsigned char nPaletteIndex)
;	---------------------------------
; Function SetColor
; ---------------------------------
_SetColor::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load02.c:103: __endasm;
	ld	a, 4 (ix)
	ld	b, 5 (ix)
	ld	c, b
	call	#0xBC32 ;SCR SET INK
	pop	ix
	ret
;Load02.c:111: void SetPalette(const unsigned char *pPalette, unsigned char nNumColors)
;	---------------------------------
; Function SetPalette
; ---------------------------------
_SetPalette::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load02.c:115: for(nColor = 0; nColor < nNumColors; nColor++)
	ld	c,#0x00
00103$:
	ld	a,c
	sub	a, 6 (ix)
	jr	NC,00105$
;Load02.c:116: SetColor(nColor, pPalette[nColor]);
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
;Load02.c:115: for(nColor = 0; nColor < nNumColors; nColor++)
	inc	c
	jr	00103$
00105$:
	pop	ix
	ret
;Load02.c:124: void SetMode(unsigned char nMode)
;	---------------------------------
; Function SetMode
; ---------------------------------
_SetMode::
	push	ix
	ld	ix,#0
	add	ix,sp
;Load02.c:129: __endasm;
	ld	a, 4 (ix)
	call	#0xBC0E ;SCR_SET_MODE
	pop	ix
	ret
;Load02.c:137: void LoadLoop()
;	---------------------------------
; Function LoadLoop
; ---------------------------------
_LoadLoop::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-56
	add	hl,sp
	ld	sp,hl
;Load02.c:139: unsigned char BlackPalette[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ld	hl,#0x0022
	add	hl,sp
	ld	c,l
	ld	b,h
	xor	a, a
	ld	(bc),a
	ld	e, c
	ld	d, b
	inc	de
	xor	a, a
	ld	(de),a
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	xor	a, a
	ld	(de),a
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	inc	de
	xor	a, a
	ld	(de),a
	ld	hl,#0x0004
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x0005
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x0006
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x0007
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x0008
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x0009
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x000a
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x000b
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x000c
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x000d
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x000e
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
	ld	hl,#0x000f
	add	hl,bc
	ex	de,hl
	xor	a, a
	ld	(de),a
;Load02.c:145: for(nImage = 1; nImage < 10; nImage++)
00109$:
	ld	hl,#0x0000
	add	hl,sp
	ld	-6 (ix),l
	ld	-5 (ix),h
	ld	a,-6 (ix)
	ld	-2 (ix),a
	ld	a,-5 (ix)
	ld	-1 (ix),a
	ld	-4 (ix),c
	ld	-3 (ix),b
	ld	-24 (ix),#0x01
	ld	-23 (ix),#0x00
00105$:
;Load02.c:147: sprintf(sFile, "0%d.scr", nImage);
	ld	e,-6 (ix)
	ld	d,-5 (ix)
	push	bc
	ld	l,-24 (ix)
	ld	h,-23 (ix)
	push	hl
	ld	hl,#___str_0
	push	hl
	push	de
	call	_sprintf
	pop	af
	pop	af
	pop	af
	pop	bc
;Load02.c:148: LoadFile(sFile, (char *)0x6000);
	ld	e,-2 (ix)
	ld	d,-1 (ix)
	push	bc
	ld	hl,#0x6000
	push	hl
	push	de
	call	_LoadFile
	pop	af
	pop	af
	pop	bc
;Load02.c:149: SetPalette((char *)BlackPalette, 16);
	ld	e,-4 (ix)
	ld	d,-3 (ix)
	push	bc
	ld	a,#0x10
	push	af
	inc	sp
	push	de
	call	_SetPalette
	pop	af
	inc	sp
	ld	de,#0xc000
	ld	hl,#0x6000
	ld	bc,#0x3fff
	ldir
	ld	a,#0x10
	push	af
	inc	sp
	ld	hl,#0xd7d1
	push	hl
	call	_SetPalette
	pop	af
	inc	sp
	pop	bc
;Load02.c:145: for(nImage = 1; nImage < 10; nImage++)
	inc	-24 (ix)
	jr	NZ,00122$
	inc	-23 (ix)
00122$:
	ld	a,-24 (ix)
	sub	a, #0x0a
	ld	a,-23 (ix)
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	C,00105$
	jp	00109$
___str_0:
	.ascii "0%d.scr"
	.db 0x00
;Load02.c:161: main()
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
;Load02.c:163: SetupDOS();
	call	_SetupDOS
;Load02.c:165: SetMode(0);
	xor	a, a
	push	af
	inc	sp
	call	_SetMode
	inc	sp
;Load02.c:167: LoadLoop();
	call	_LoadLoop
;Load02.c:169: return 0;
	ld	hl,#0x0000
	pop	ix
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__nFileNameLen:
	.db #0x00	; 0
	.area _CABS (ABS)
