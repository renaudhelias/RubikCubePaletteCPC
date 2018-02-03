;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module jdvapi_keyb
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _aKeyboard
	.globl _get_key
	.globl _check_controller
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_aKeyboard::
	.ds 10
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
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
;jdvapi_keyb.c:8: unsigned char get_key(enum _eKey eKey)
;	---------------------------------
; Function get_key
; ---------------------------------
_get_key::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_keyb.c:10: unsigned char nKeyLine = eKey / 8;
	ld	c,4 (ix)
	srl	c
	srl	c
	srl	c
;jdvapi_keyb.c:11: unsigned char nBit = eKey % 8;
	ld	a,4 (ix)
	and	a, #0x07
;jdvapi_keyb.c:13: if(((unsigned char)1 << nBit & aKeyboard[nKeyLine]) == 0)
	push	af
	ld	b,#0x01
	ld	e,#0x00
	pop	af
	inc	a
	jr	00110$
00109$:
	sla	b
	rl	e
00110$:
	dec	a
	jr	NZ,00109$
	ld	a,#<(_aKeyboard)
	add	a, c
	ld	l, a
	ld	a, #>(_aKeyboard)
	adc	a, #0x00
	ld	h, a
	ld	l,(hl)
	ld	h,#0x00
	ld	a,l
	and	a, b
	ld	l,a
	ld	a,h
	and	a, e
	or	a,l
	jr	NZ,00102$
;jdvapi_keyb.c:14: return 1;
	ld	l,#0x01
	jr	00103$
00102$:
;jdvapi_keyb.c:16: return 0;
	ld	l,#0x00
00103$:
	pop	ix
	ret
;jdvapi_keyb.c:19: void check_controller()
;	---------------------------------
; Function check_controller
; ---------------------------------
_check_controller::
;jdvapi_keyb.c:49: __endasm;
	di
	ld	hl, #_aKeyboard
	ld	bc,#0xf782 ; PPI port A out /C out
	out	(c),c
	ld	bc,#0xf40e ; Select Ay reg 14 on ppi port A
	ld	e,b
	out	(c),c
	ld	bc,#0xf6c0 ; This value is an AY index (R14)
	ld	d,b
	out	(c),c
	ld	c,#0x00 ; Validate!! out (c),0
	out	(c),c
	ld	bc,#0xf792 ; PPI port A in/C out
	out	(c),c
	ld	a,#0x40
	ld	c,#0x4a
	    _loop:
	ld	b,d
	out	(c),a
	ld	b,e
	ini
	inc	a
	cp	c
	jr	c,_loop
	ld	bc,#0xf782 ; PPI port A out / C out
	out	(c),c
	ei	; 211 microseconds
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
