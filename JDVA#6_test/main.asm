;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module main
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _vsync
	.globl _get_key
	.globl _check_controller
	.globl _precalc_vram
	.globl _put_frame
	.globl _mode
	.globl _set_palette
	.globl _vram
	.globl _fish
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_fish::
	.ds 24
_vram::
	.ds 2
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
;main.c:14: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	dec	sp
;main.c:17: x=10;
	ld	-3 (ix),#0x0a
;main.c:19: vram=precalc_vram();
	call	_precalc_vram
	ex	de,hl
	ld	(_vram),de
;main.c:21: fish[0]=poisson1;
	ld	hl,#_poisson1
	ld	(_fish), hl
;main.c:22: fish[1]=poisson2;
	ld	hl,#_poisson2
	ld	((_fish + 0x0002)), hl
;main.c:23: fish[2]=poisson_groupe;
	ld	hl,#_poisson_groupe
	ld	((_fish + 0x0004)), hl
;main.c:24: fish[3]=poisson_groupe+(6*16);
	ld	hl,#(_poisson_groupe + 0x0060)
	ld	((_fish + 0x0006)), hl
;main.c:25: fish[4]=poisson_groupe+((6*16)*2);
	ld	hl,#(_poisson_groupe + 0x00c0)
	ld	((_fish + 0x0008)), hl
;main.c:26: fish[5]=poisson_groupe+((6*16)*9); // fond vide
	ld	hl,#(_poisson_groupe + 0x0360)
	ld	((_fish + 0x000a)), hl
;main.c:28: mode(0);
	xor	a, a
	push	af
	inc	sp
	call	_mode
	inc	sp
;main.c:29: set_palette(poisson_palette);
	ld	hl,#_poisson_palette
	push	hl
	call	_set_palette
	pop	af
;main.c:31: while(1){
00106$:
;main.c:32: check_controller();
	call	_check_controller
;main.c:39: vsync();
	call	_vsync
;main.c:41: put_frame(vram(x,50),6,16,fish[5]);
	ld	hl, #(_fish + 0x000a) + 0
	ld	a,(hl)
	ld	-2 (ix),a
	inc	hl
	ld	a,(hl)
	ld	-1 (ix),a
	ld	c, -3 (ix)
	ld	b, #0x00
	ld	hl,#0xd1e0
	add	hl,bc
	ex	de,hl
	push	bc
	ld	l,-2 (ix)
	ld	h,-1 (ix)
	push	hl
	ld	hl,#0x1006
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
	pop	bc
;main.c:42: put_frame((unsigned char *)(vram[100]+x),6,16,fish[5]);
	ld	de, (#(_fish + 0x000a) + 0)
	ld	hl,(_vram)
	push	bc
	ld	bc, #0x00c8
	add	hl, bc
	pop	bc
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	add	a, c
	ld	c,a
	ld	a,h
	adc	a, b
	ld	b,a
	push	de
	ld	hl,#0x1006
	push	hl
	push	bc
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;main.c:43: if (get_key(Key_O)) {
	ld	a,#0x22
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00102$
;main.c:44: x--;
	dec	-3 (ix)
00102$:
;main.c:46: if (get_key(Key_P)) {
	ld	a,#0x1b
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00104$
;main.c:47: x++;
	inc	-3 (ix)
00104$:
;main.c:50: put_frame(vram(x,50),6,16,fish[4]);
	ld	hl, #(_fish + 0x0008) + 0
	ld	a,(hl)
	ld	-2 (ix),a
	inc	hl
	ld	a,(hl)
	ld	-1 (ix),a
	ld	e, -3 (ix)
	ld	d, #0x00
	ld	hl,#0xd1e0
	add	hl,de
	ld	c,l
	ld	b,h
	push	de
	ld	l,-2 (ix)
	ld	h,-1 (ix)
	push	hl
	ld	hl,#0x1006
	push	hl
	push	bc
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
	pop	de
;main.c:51: put_frame((unsigned char *)(vram[100]+x),6,16,fish[1]);
	ld	bc, (#(_fish + 0x0002) + 0)
	ld	hl,(_vram)
	push	bc
	ld	bc, #0x00c8
	add	hl, bc
	pop	bc
	ld	a, (hl)
	inc	hl
	ld	h,(hl)
	add	a, e
	ld	e,a
	ld	a,h
	adc	a, d
	ld	d,a
	push	bc
	ld	hl,#0x1006
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
	jp	00106$
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
