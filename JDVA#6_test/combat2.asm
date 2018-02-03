;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module combat2
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _transfertEtDecoupe
	.globl _LoadFile
	.globl _SetupDOS
	.globl _calque4C00
	.globl _scan
	.globl _overscan
	.globl _bank7_4000
	.globl _bank6_4000
	.globl _bank5_4000
	.globl _bank4_4000
	.globl _bank0123
	.globl _calque4000
	.globl _calqueC000
	.globl _vsync
	.globl _precalc_vram
	.globl _erase_frame
	.globl _put_frame_transparent
	.globl _put_frame
	.globl _mode
	.globl _border
	.globl _set_palette
	.globl _strlen
	.globl _nFileNameLen
	.globl _vram
	.globl _intro_palette
	.globl _combat2_palette
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_vram::
	.ds 2
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
;jdvapi_floppy.c:15: void SetupDOS()
;	---------------------------------
; Function SetupDOS
; ---------------------------------
_SetupDOS::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_floppy.c:48: __endasm;
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
;jdvapi_floppy.c:58: void LoadFile(char *sFileName, char *pLoadAddress)
;	---------------------------------
; Function LoadFile
; ---------------------------------
_LoadFile::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_floppy.c:60: nFileNameLen = strlen(sFileName);
	ld	l,4 (ix)
	ld	h,5 (ix)
	push	hl
	call	_strlen
	pop	af
	ld	c,l
	ld	b,h
	ld	iy,#_nFileNameLen
	ld	0 (iy),c
;jdvapi_floppy.c:92: __endasm;
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
;combat2.c:25: void transfertEtDecoupe()
;	---------------------------------
; Function transfertEtDecoupe
; ---------------------------------
_transfertEtDecoupe::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-17
	add	hl,sp
	ld	sp,hl
;combat2.c:28: n=0;
	ld	e,#0x00
;combat2.c:29: for (j=0;j<TAILLE_Y/TAILLE_Y_SPRITE;j++) {
	ld	-15 (ix),#0x00
	ld	-14 (ix),#0x00
	ld	bc,#0x0000
;combat2.c:30: for (i=0;i<TAILLE_X/TAILLE_X_SPRITE;i++) {
00119$:
	ld	-1 (ix),e
	ld	-13 (ix),#0x00
	ld	-12 (ix),#0x00
	ld	-3 (ix),#0x00
	ld	-2 (ix),#0x00
;combat2.c:31: for (x=0;x<TAILLE_X_SPRITE;x++) {
00117$:
	ld	-9 (ix),#0x00
	ld	-8 (ix),#0x00
;combat2.c:32: for (y=0;y<TAILLE_Y_SPRITE;y++) {
00115$:
	ld	-11 (ix),#0x00
	ld	-10 (ix),#0x00
	ld	-5 (ix),#0x00
	ld	-4 (ix),#0x00
	ld	-7 (ix),#0x00
	ld	-6 (ix),#0x00
00105$:
;combat2.c:33: addressFrom=0xC000+y*TAILLE_X +j*TAILLE_X*TAILLE_Y_SPRITE+x+i*TAILLE_X_SPRITE;
	ld	a,-5 (ix)
	add	a, #0x00
	ld	e,a
	ld	a,-4 (ix)
	adc	a, #0xc0
	ld	d,a
	ld	a,e
	add	a, c
	ld	e,a
	ld	a,d
	adc	a, b
	ld	d,a
	ld	a,e
	add	a, -9 (ix)
	ld	e,a
	ld	a,d
	adc	a, -8 (ix)
	ld	d,a
	ld	a,e
	add	a, -3 (ix)
	ld	e,a
	ld	a,d
	adc	a, -2 (ix)
	ld	d,a
	inc	sp
	inc	sp
	push	de
;combat2.c:34: addressTo=0x4000+n*TAILLE_X_SPRITE*TAILLE_Y_SPRITE + y*TAILLE_X_SPRITE+x;
	ld	e,-1 (ix)
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	ld	de, #0x4000
	add	hl, de
	ld	a,l
	add	a, -7 (ix)
	ld	e,a
	ld	a,h
	adc	a, -6 (ix)
	ld	d,a
	ld	a,e
	add	a, -9 (ix)
	ld	e,a
	ld	a,d
	adc	a, -8 (ix)
	ld	d,a
;combat2.c:35: *addressTo=*addressFrom;
	pop	hl
	push	hl
	ld	a,(hl)
	ld	(de),a
;combat2.c:32: for (y=0;y<TAILLE_Y_SPRITE;y++) {
	ld	a,-5 (ix)
	add	a, #0x4e
	ld	-5 (ix),a
	ld	a,-4 (ix)
	adc	a, #0x00
	ld	-4 (ix),a
	ld	a,-7 (ix)
	add	a, #0x06
	ld	-7 (ix),a
	ld	a,-6 (ix)
	adc	a, #0x00
	ld	-6 (ix),a
	inc	-11 (ix)
	jr	NZ,00147$
	inc	-10 (ix)
00147$:
	ld	a,-11 (ix)
	sub	a, #0x32
	ld	a,-10 (ix)
	sbc	a, #0x00
	jp	C,00105$
;combat2.c:31: for (x=0;x<TAILLE_X_SPRITE;x++) {
	inc	-9 (ix)
	jr	NZ,00148$
	inc	-8 (ix)
00148$:
	ld	a,-9 (ix)
	sub	a, #0x06
	ld	a,-8 (ix)
	sbc	a, #0x00
	jp	C,00115$
;combat2.c:38: n++;
	inc	-1 (ix)
;combat2.c:30: for (i=0;i<TAILLE_X/TAILLE_X_SPRITE;i++) {
	ld	a,-3 (ix)
	add	a, #0x06
	ld	-3 (ix),a
	ld	a,-2 (ix)
	adc	a, #0x00
	ld	-2 (ix),a
	inc	-13 (ix)
	jr	NZ,00149$
	inc	-12 (ix)
00149$:
	ld	a,-13 (ix)
	sub	a, #0x0d
	ld	a,-12 (ix)
	sbc	a, #0x00
	jp	C,00117$
;combat2.c:29: for (j=0;j<TAILLE_Y/TAILLE_Y_SPRITE;j++) {
	ld	e,-1 (ix)
	ld	hl,#0x0f3c
	add	hl,bc
	ld	c,l
	ld	b,h
	inc	-15 (ix)
	jr	NZ,00150$
	inc	-14 (ix)
00150$:
	ld	a,-15 (ix)
	sub	a, #0x04
	ld	a,-14 (ix)
	sbc	a, #0x00
	jp	C,00119$
	ld	sp, ix
	pop	ix
	ret
;combat2.c:55: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;combat2.c:58: volatile char layer=0;volatile char x=10;//char z=0;
	ld	-1 (ix),#0x00
	ld	-2 (ix),#0x0a
;combat2.c:61: SetupDOS();
	call	_SetupDOS
;combat2.c:62: calque4000();
	call	_calque4000
;combat2.c:63: mode(0); // à cause de la publicité ParaDOS ;)
	xor	a, a
	push	af
	inc	sp
	call	_mode
	inc	sp
;combat2.c:64: border(0);
	xor	a, a
	push	af
	inc	sp
	call	_border
	inc	sp
;combat2.c:65: set_palette(intro_palette);
	ld	hl,#_intro_palette
	push	hl
	call	_set_palette
	pop	af
;combat2.c:66: overscan();
	call	_overscan
;combat2.c:68: calque4C00();
	call	_calque4C00
;combat2.c:69: bank0123();
	call	_bank0123
;combat2.c:70: LoadFile("intro-oc.scr", (char *)0x4000);
	ld	hl,#0x4000
	push	hl
	ld	hl,#___str_0
	push	hl
	call	_LoadFile
	pop	af
	pop	af
;combat2.c:72: vram=precalc_vram();
	call	_precalc_vram
	ld	c,l
	ld	b,h
	ld	(_vram),bc
;combat2.c:74: bank0123();
	call	_bank0123
;combat2.c:75: LoadFile("J1A.scr", (char *)0xC000); // un scr exporté "linéaire"
	ld	hl,#0xc000
	push	hl
	ld	hl,#___str_1
	push	hl
	call	_LoadFile
	pop	af
	pop	af
;combat2.c:76: bank4_4000();
	call	_bank4_4000
;combat2.c:77: transfertEtDecoupe();
	call	_transfertEtDecoupe
;combat2.c:79: bank0123();
	call	_bank0123
;combat2.c:80: LoadFile("J1R.scr", (char *)0xC000); // un scr exporté "linéaire"
	ld	hl,#0xc000
	push	hl
	ld	hl,#___str_2
	push	hl
	call	_LoadFile
	pop	af
	pop	af
;combat2.c:81: bank5_4000();
	call	_bank5_4000
;combat2.c:82: transfertEtDecoupe();
	call	_transfertEtDecoupe
;combat2.c:84: bank0123();
	call	_bank0123
;combat2.c:85: LoadFile("J2A.scr", (char *)0xC000); // un scr exporté "linéaire"
	ld	hl,#0xc000
	push	hl
	ld	hl,#___str_3
	push	hl
	call	_LoadFile
	pop	af
	pop	af
;combat2.c:86: bank6_4000();
	call	_bank6_4000
;combat2.c:87: transfertEtDecoupe();
	call	_transfertEtDecoupe
;combat2.c:89: bank0123();
	call	_bank0123
;combat2.c:90: LoadFile("J2R.scr", (char *)0xC000); // un scr exporté "linéaire"
	ld	hl,#0xc000
	push	hl
	ld	hl,#___str_4
	push	hl
	call	_LoadFile
	pop	af
	pop	af
;combat2.c:91: bank7_4000();
	call	_bank7_4000
;combat2.c:92: transfertEtDecoupe();
	call	_transfertEtDecoupe
;combat2.c:95: calqueC000();
	call	_calqueC000
;combat2.c:96: bank0123();
	call	_bank0123
;combat2.c:97: mode(2);
	ld	a,#0x02
	push	af
	inc	sp
	call	_mode
	inc	sp
;combat2.c:98: border(0);
	xor	a, a
	push	af
	inc	sp
	call	_border
	inc	sp
;combat2.c:99: set_palette(combat2_palette);
	ld	hl,#_combat2_palette
	push	hl
	call	_set_palette
	pop	af
;combat2.c:100: scan();
	call	_scan
;combat2.c:101: bank0123();
	call	_bank0123
;combat2.c:102: LoadFile("fond2.scr", (char *)0xC000);
	ld	hl,#0xc000
	push	hl
	ld	hl,#___str_5
	push	hl
	call	_LoadFile
	pop	af
	pop	af
;combat2.c:104: erase_frame((unsigned char *)(vram[120]+3),6*7+3,50);
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	b, (hl)
	ld	c, a
	inc	bc
	inc	bc
	inc	bc
	ld	hl,#0x322d
	push	hl
	push	bc
	call	_erase_frame
	pop	af
	pop	af
;combat2.c:107: while(1){
00102$:
;combat2.c:110: vsync();
	call	_vsync
;combat2.c:111: calqueC000();
	call	_calqueC000
;combat2.c:112: bank0123();
	call	_bank0123
;combat2.c:113: memcpy((char *)0x4000, (char *)0xC000, 0x3FFF); // memcpy(destination,source,longueur)
	ld	de,#0x4000
	ld	hl,#0xc000
	ld	bc,#0x3fff
	ldir
;combat2.c:117: vsync();
	call	_vsync
;combat2.c:118: calque4000();
	call	_calque4000
;combat2.c:119: bank4_4000();
	call	_bank4_4000
;combat2.c:120: x=7;
	ld	-2 (ix),#0x07
;combat2.c:122: put_frame((unsigned char *)(vram[120]+x),6,50,0x4000+((6*50)*layer));
	ld	c,-1 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#0x4000
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	e,-2 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, e
	ld	e,a
	ld	a,h
	adc	a, d
	ld	d,a
	push	bc
	ld	hl,#0x3206
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat2.c:124: put_frame((unsigned char *)(vram[120]+x+6+6+6+6+3),6,50,0x4000+((6*50)*layer));
	ld	c,-1 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#0x4000
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	e,-2 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, e
	ld	e,a
	ld	a,h
	adc	a, d
	ld	d,a
	ld	hl,#0x001b
	add	hl,de
	ex	de,hl
	push	bc
	ld	hl,#0x3206
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat2.c:125: bank6_4000();
	call	_bank6_4000
;combat2.c:127: erase_frame((unsigned char *)(vram[120]+x+6),4,50);
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	c,-2 (ix)
	ld	b,#0x00
	ld	a,l
	add	a, c
	ld	c,a
	ld	a,h
	adc	a, b
	ld	b,a
	ld	hl,#0x0006
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	hl,#0x3204
	push	hl
	push	bc
	call	_erase_frame
	pop	af
	pop	af
;combat2.c:128: put_frame_transparent((unsigned char *)(vram[120]+x+3+1),6,50,0x4000+((6*50)*layer));
	ld	c,-1 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#0x4000
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	e,-2 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, e
	ld	e,a
	ld	a,h
	adc	a, d
	ld	d,a
	inc	de
	inc	de
	inc	de
	inc	de
	push	bc
	ld	hl,#0x3206
	push	hl
	push	de
	call	_put_frame_transparent
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat2.c:130: put_frame((unsigned char *)(vram[120]+x+6+6+6+6+6+3),6,50,0x4000+((6*50)*layer));
	ld	c,-1 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#0x4000
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	e,-2 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, e
	ld	e,a
	ld	a,h
	adc	a, d
	ld	d,a
	ld	hl,#0x0021
	add	hl,de
	ex	de,hl
	push	bc
	ld	hl,#0x3206
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat2.c:131: bank5_4000();
	call	_bank5_4000
;combat2.c:133: put_frame((unsigned char *)(vram[120]+x+6+6),6,50,0x4000+((6*50)*layer));
	ld	c,-1 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#0x4000
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	e,-2 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, e
	ld	e,a
	ld	a,h
	adc	a, d
	ld	d,a
	ld	hl,#0x000c
	add	hl,de
	ex	de,hl
	push	bc
	ld	hl,#0x3206
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat2.c:134: bank7_4000();
	call	_bank7_4000
;combat2.c:136: put_frame((unsigned char *)(vram[120]+x+6+6+6),6,50,0x4000+((6*50)*layer));
	ld	c,-1 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#0x4000
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	hl,(_vram)
	ld	de, #0x00f0
	add	hl, de
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	e,-2 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, e
	ld	e,a
	ld	a,h
	adc	a, d
	ld	d,a
	ld	hl,#0x0012
	add	hl,de
	ex	de,hl
	push	bc
	ld	hl,#0x3206
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat2.c:140: layer=(layer+1)%(13*4);
	ld	c, -1 (ix)
	ld	b, #0x00
	inc	bc
	ld	hl,#0x0034
	push	hl
	push	bc
	call	__modsint
	pop	af
	pop	af
	ld	-1 (ix),l
	jp	00102$
_combat2_palette:
	.db #0x00	; 0
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
_intro_palette:
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x04	; 4
	.db #0x0b	; 11
	.db #0x05	; 5
	.db #0x03	; 3
	.db #0x10	; 16
	.db #0x19	; 25
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x1a	; 26
	.db #0x0e	; 14
	.db #0x17	; 23
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x00	; 0
___str_0:
	.ascii "intro-oc.scr"
	.db 0x00
___str_1:
	.ascii "J1A.scr"
	.db 0x00
___str_2:
	.ascii "J1R.scr"
	.db 0x00
___str_3:
	.ascii "J2A.scr"
	.db 0x00
___str_4:
	.ascii "J2R.scr"
	.db 0x00
___str_5:
	.ascii "fond2.scr"
	.db 0x00
	.area _CODE
	.area _INITIALIZER
__xinit__nFileNameLen:
	.db #0x00	; 0
	.area _CABS (ABS)
