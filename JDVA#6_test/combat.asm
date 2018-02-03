;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module combat
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
	.globl _perso2A
	.globl _perso1A
	.globl _combat_palette
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_perso1A::
	.ds 16
_perso2A::
	.ds 16
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
;combat.c:22: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-22
	add	hl,sp
	ld	sp,hl
;combat.c:24: int x;char xmod8;int x2;char x2mod8;char layer=0;char direction=0;
	ld	-22 (ix),#0x00
;combat.c:25: x=0;x2=640-x-57;
	ld	-17 (ix),#0x00
	ld	-16 (ix),#0x00
;combat.c:27: vram=precalc_vram();
	call	_precalc_vram
	ld	c,l
	ld	b,h
	ld	(_vram),bc
;combat.c:29: perso1A[0]=J1A1;
	ld	hl,#_J1A1
	ld	(_perso1A), hl
;combat.c:30: perso1A[1]=J1A2;
	ld	hl,#_J1A2
	ld	((_perso1A + 0x0002)), hl
;combat.c:31: perso1A[2]=J1A3;
	ld	hl,#_J1A3
	ld	((_perso1A + 0x0004)), hl
;combat.c:32: perso1A[3]=J1A4;
	ld	hl,#_J1A4
	ld	((_perso1A + 0x0006)), hl
;combat.c:33: perso1A[4]=J1A5;
	ld	hl,#_J1A5
	ld	((_perso1A + 0x0008)), hl
;combat.c:34: perso1A[5]=J1A6;
	ld	hl,#_J1A6
	ld	((_perso1A + 0x000a)), hl
;combat.c:35: perso1A[6]=J1A7;
	ld	hl,#_J1A7
	ld	((_perso1A + 0x000c)), hl
;combat.c:36: perso1A[7]=J1A8;
	ld	hl,#_J1A8
	ld	((_perso1A + 0x000e)), hl
;combat.c:47: perso2A[0]=J2A1;
	ld	hl,#_J2A1
	ld	(_perso2A), hl
;combat.c:48: perso2A[1]=J2A2;
	ld	hl,#_J2A2
	ld	((_perso2A + 0x0002)), hl
;combat.c:49: perso2A[2]=J2A3;
	ld	hl,#_J2A3
	ld	((_perso2A + 0x0004)), hl
;combat.c:50: perso2A[3]=J2A4;
	ld	hl,#_J2A4
	ld	((_perso2A + 0x0006)), hl
;combat.c:51: perso2A[4]=J2A5;
	ld	hl,#_J2A5
	ld	((_perso2A + 0x0008)), hl
;combat.c:52: perso2A[5]=J2A6;
	ld	hl,#_J2A6
	ld	((_perso2A + 0x000a)), hl
;combat.c:53: perso2A[6]=J2A7;
	ld	hl,#_J2A7
	ld	((_perso2A + 0x000c)), hl
;combat.c:54: perso2A[7]=J2A8;
	ld	hl,#_J2A8
	ld	((_perso2A + 0x000e)), hl
;combat.c:65: mode(2);
	ld	a,#0x02
	push	af
	inc	sp
	call	_mode
	inc	sp
;combat.c:66: set_palette(combat_palette);
	ld	hl,#_combat_palette
	push	hl
	call	_set_palette
	pop	af
;combat.c:68: put_frame(vram(0,0),6,50,perso1A[0]);
	ld	hl, (#_perso1A + 0)
	push	hl
	ld	hl,#0x3206
	push	hl
	ld	hl,#0xc000
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:69: put_frame(vram(0+8,0),7,50,perso1A[1]);
	ld	hl, (#(_perso1A + 0x0002) + 0)
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xc008
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:70: put_frame(vram(8+8,0),7,50,perso1A[2]);
	ld	hl, (#(_perso1A + 0x0004) + 0)
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xc010
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:71: put_frame(vram(8+8+8,0),7,50,perso1A[3]);
	ld	hl, (#(_perso1A + 0x0006) + 0)
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xc018
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:72: put_frame(vram(8+8+8+8,0),7,50,perso1A[4]);
	ld	hl, (#(_perso1A + 0x0008) + 0)
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xc020
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:73: put_frame(vram(8+8+8+8+8,0),7,50,perso1A[5]);
	ld	hl, (#(_perso1A + 0x000a) + 0)
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xc028
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:74: put_frame(vram(8+8+8+8+8+8,0),7,50,perso1A[6]);
	ld	hl, (#(_perso1A + 0x000c) + 0)
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xc030
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:75: put_frame(vram(8+8+8+8+8+8+8,0),7,50,perso1A[7]);
	ld	hl, (#(_perso1A + 0x000e) + 0)
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xc038
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:76: put_frame(vram(0,50),6,50,perso2A[0]+((6*50)*1));
	ld	hl, (#_perso2A + 0)
	ld	bc, #0x012c
	add	hl,bc
	push	hl
	ld	hl,#0x3206
	push	hl
	ld	hl,#0xd1e0
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:77: put_frame(vram(8,50),7,50,perso2A[1]+((7*50)*1));
	ld	hl, (#(_perso2A + 0x0002) + 0)
	ld	bc, #0x015e
	add	hl,bc
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xd1e8
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:78: put_frame(vram(8+8,50),7,50,perso2A[2]+((7*50)*1));
	ld	hl, (#(_perso2A + 0x0004) + 0)
	ld	bc, #0x015e
	add	hl,bc
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xd1f0
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:79: put_frame(vram(8+8+8,50),7,50,perso2A[3]+((7*50)*1));
	ld	hl, (#(_perso2A + 0x0006) + 0)
	ld	bc, #0x015e
	add	hl,bc
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xd1f8
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:80: put_frame(vram(8+8+8+8,50),7,50,perso2A[4]+((7*50)*1));
	ld	hl, (#(_perso2A + 0x0008) + 0)
	ld	bc, #0x015e
	add	hl,bc
	ld	c, l
	ld	a,h
	ld	b,a
	push	bc
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xd200
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:81: put_frame(vram(8+8+8+8+8,50),7,50,perso2A[5]+((7*50)*1));
	ld	hl, (#(_perso2A + 0x000a) + 0)
	ld	bc, #0x015e
	add	hl,bc
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xd208
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:82: put_frame(vram(8+8+8+8+8+8,50),7,50,perso2A[6]+((7*50)*1));
	ld	hl, (#(_perso2A + 0x000c) + 0)
	ld	bc, #0x015e
	add	hl,bc
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xd210
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:83: put_frame(vram(8+8+8+8+8+8+8,50),7,50,perso2A[7]+((7*50)*1));
	ld	hl, (#(_perso2A + 0x000e) + 0)
	ld	bc, #0x015e
	add	hl,bc
	push	hl
	ld	hl,#0x3207
	push	hl
	ld	hl,#0xd218
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;combat.c:85: while(1){
00127$:
;combat.c:86: check_controller();
	call	_check_controller
;combat.c:87: layer=3;
	ld	c,#0x03
;combat.c:88: if (get_key(Key_CursorLeft) && direction==0) {
	push	bc
	ld	a,#0x08
	push	af
	inc	sp
	call	_get_key
	inc	sp
	pop	bc
	ld	a,l
	or	a, a
	jr	Z,00104$
	ld	a,-22 (ix)
	or	a, a
	jr	NZ,00104$
;combat.c:89: if (x>0) x--;
	xor	a, a
	cp	a, -17 (ix)
	sbc	a, -16 (ix)
	jp	PO, 00207$
	xor	a, #0x80
00207$:
	jp	P,00102$
	ld	l,-17 (ix)
	ld	h,-16 (ix)
	dec	hl
	ld	-17 (ix),l
	ld	-16 (ix),h
00102$:
;combat.c:90: direction=1;
	ld	-22 (ix),#0x01
00104$:
;combat.c:92: if (get_key(Key_CursorRight) && direction==0) {
	push	bc
	ld	a,#0x01
	push	af
	inc	sp
	call	_get_key
	inc	sp
	pop	bc
	ld	a,l
	or	a, a
	jr	Z,00109$
	ld	a,-22 (ix)
	or	a, a
	jr	NZ,00109$
;combat.c:93: if (x<640/2-57) x++;
	ld	a,-17 (ix)
	sub	a, #0x07
	ld	a,-16 (ix)
	rla
	ccf
	rra
	sbc	a, #0x81
	jr	NC,00107$
	inc	-17 (ix)
	jr	NZ,00208$
	inc	-16 (ix)
00208$:
00107$:
;combat.c:94: direction=1;
	ld	-22 (ix),#0x01
00109$:
;combat.c:97: if (!get_key(Key_CursorLeft) && !get_key(Key_CursorRight)) {
	push	bc
	ld	a,#0x08
	push	af
	inc	sp
	call	_get_key
	inc	sp
	pop	bc
	ld	a,l
	or	a, a
	jr	NZ,00112$
	push	bc
	ld	a,#0x01
	push	af
	inc	sp
	call	_get_key
	inc	sp
	pop	bc
	ld	a,l
	or	a, a
	jr	NZ,00112$
;combat.c:98: direction=0;
	ld	-22 (ix),#0x00
00112$:
;combat.c:100: if (get_key(Key_Space)) {
	push	bc
	ld	a,#0x2f
	push	af
	inc	sp
	call	_get_key
	inc	sp
	pop	bc
	ld	a,l
	or	a, a
	jr	Z,00119$
;combat.c:101: layer=1;
	ld	c,#0x01
;combat.c:102: if (get_key(Key_CursorUp)) {
	push	bc
	xor	a, a
	push	af
	inc	sp
	call	_get_key
	inc	sp
	pop	bc
	ld	a,l
	or	a, a
	jr	Z,00115$
;combat.c:103: layer=0;
	ld	c,#0x00
00115$:
;combat.c:105: if (get_key(Key_CursorDown)) {
	push	bc
	ld	a,#0x02
	push	af
	inc	sp
	call	_get_key
	inc	sp
	pop	bc
	ld	a,l
	or	a, a
	jr	Z,00119$
;combat.c:106: layer=2;
	ld	c,#0x02
00119$:
;combat.c:116: xmod8=x%8;
	push	bc
	ld	hl,#0x0008
	push	hl
	ld	l,-17 (ix)
	ld	h,-16 (ix)
	push	hl
	call	__modsint
	pop	af
	pop	af
	pop	bc
	ld	-18 (ix),l
;combat.c:117: x2=640-x-57;
	ld	a,#0x47
	sub	a, -17 (ix)
	ld	-20 (ix),a
	ld	a,#0x02
	sbc	a, -16 (ix)
	ld	-19 (ix),a
;combat.c:118: x2mod8=x2%8;
	push	bc
	ld	hl,#0x0008
	push	hl
	ld	l,-20 (ix)
	ld	h,-19 (ix)
	push	hl
	call	__modsint
	pop	af
	pop	af
	pop	bc
	ld	-21 (ix),l
;combat.c:119: vsync();
	push	bc
	call	_vsync
	pop	bc
;combat.c:123: put_frame((unsigned char *)(vram[120]+x/8),6,50,perso1A[xmod8]+((6*50)*layer));
	ld	a,-18 (ix)
	ld	-2 (ix),a
	ld	-1 (ix),#0x00
	ld	e,c
	ld	d,#0x00
	ld	hl,(_vram)
	ld	-7 (ix),l
	ld	-6 (ix),h
	ld	a,-16 (ix)
	rlca
	and	a,#0x01
	ld	-3 (ix),a
	ld	a,-17 (ix)
	add	a, #0x07
	ld	-5 (ix),a
	ld	a,-16 (ix)
	adc	a, #0x00
	ld	-4 (ix),a
	ld	c,-2 (ix)
	ld	b,-1 (ix)
	sla	c
	rl	b
	push	de
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
	pop	de
	ld	-2 (ix),l
	ld	-1 (ix),h
	ld	l,-7 (ix)
	ld	h,-6 (ix)
	push	bc
	ld	bc, #0x00f0
	add	hl, bc
	pop	bc
	ld	a,(hl)
	ld	-7 (ix),a
	inc	hl
	ld	a,(hl)
	ld	-6 (ix),a
;combat.c:125: put_frame((unsigned char *)(vram[120]+x/8),7,50,perso1A[xmod8]+((7*50)*layer));
	push	de
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	add	hl, hl
	pop	de
	ld	-13 (ix),l
	ld	-12 (ix),h
;combat.c:123: put_frame((unsigned char *)(vram[120]+x/8),6,50,perso1A[xmod8]+((6*50)*layer));
	ld	hl,#_perso1A
	add	hl,bc
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
;combat.c:122: if (xmod8==0) {
	ld	a,-18 (ix)
	or	a, a
	jr	NZ,00121$
;combat.c:123: put_frame((unsigned char *)(vram[120]+x/8),6,50,perso1A[xmod8]+((6*50)*layer));
	ld	a,c
	add	a, -2 (ix)
	ld	-9 (ix),a
	ld	a,b
	adc	a, -1 (ix)
	ld	-8 (ix),a
	ld	c,-17 (ix)
	ld	b,-16 (ix)
	ld	a,-3 (ix)
	or	a, a
	jr	Z,00131$
	ld	c,-5 (ix)
	ld	b,-4 (ix)
00131$:
	ld	l, c
	ld	h, b
	sra	h
	rr	l
	sra	h
	rr	l
	sra	h
	rr	l
	ld	a,-7 (ix)
	add	a, l
	ld	e,a
	ld	a,-6 (ix)
	adc	a, h
	ld	d,a
	ld	l,-9 (ix)
	ld	h,-8 (ix)
	push	hl
	ld	hl,#0x3206
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
	jr	00122$
00121$:
;combat.c:125: put_frame((unsigned char *)(vram[120]+x/8),7,50,perso1A[xmod8]+((7*50)*layer));
	ld	a,c
	add	a, -13 (ix)
	ld	c,a
	ld	a,b
	adc	a, -12 (ix)
	ld	b,a
	ld	e,-17 (ix)
	ld	d,-16 (ix)
	ld	a,-3 (ix)
	or	a, a
	jr	Z,00132$
	ld	e,-5 (ix)
	ld	d,-4 (ix)
00132$:
	ex	de,hl
	sra	h
	rr	l
	sra	h
	rr	l
	sra	h
	rr	l
	ld	a,-7 (ix)
	add	a, l
	ld	e,a
	ld	a,-6 (ix)
	adc	a, h
	ld	d,a
	push	bc
	ld	hl,#0x3207
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
00122$:
;combat.c:123: put_frame((unsigned char *)(vram[120]+x/8),6,50,perso1A[xmod8]+((6*50)*layer));
	ld	iy,#_vram
	ld	a,0 (iy)
	add	a, #0xf0
	ld	c,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	b,a
;combat.c:128: put_frame((unsigned char *)(vram[120]+x2/8),6,50,perso2A[x2mod8]+((6*50)*layer));
	ld	e,-21 (ix)
	ld	d,#0x00
	ld	a,-19 (ix)
	rlca
	and	a,#0x01
	ld	-11 (ix),a
	ld	a,-20 (ix)
	add	a, #0x07
	ld	-9 (ix),a
	ld	a,-19 (ix)
	adc	a, #0x00
	ld	-8 (ix),a
;combat.c:123: put_frame((unsigned char *)(vram[120]+x/8),6,50,perso1A[xmod8]+((6*50)*layer));
	ld	a,(bc)
	ld	-15 (ix),a
	inc	bc
	ld	a,(bc)
	ld	-14 (ix),a
	dec	bc
;combat.c:128: put_frame((unsigned char *)(vram[120]+x2/8),6,50,perso2A[x2mod8]+((6*50)*layer));
	ex	de,hl
	add	hl, hl
	ld	a,#<(_perso2A)
	add	a, l
	ld	e,a
	ld	a,#>(_perso2A)
	adc	a, h
	ld	d,a
	ex	de,hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
;combat.c:127: if (x2mod8==0) {
	ld	a,-21 (ix)
	or	a, a
	jr	NZ,00124$
;combat.c:128: put_frame((unsigned char *)(vram[120]+x2/8),6,50,perso2A[x2mod8]+((6*50)*layer));
	ld	a,e
	add	a, -2 (ix)
	ld	-7 (ix),a
	ld	a,d
	adc	a, -1 (ix)
	ld	-6 (ix),a
	pop	de
	pop	bc
	push	bc
	push	de
	ld	a,-11 (ix)
	or	a, a
	jr	Z,00133$
	ld	c,-9 (ix)
	ld	b,-8 (ix)
00133$:
	ld	l, c
	ld	h, b
	sra	h
	rr	l
	sra	h
	rr	l
	sra	h
	rr	l
	ld	a,-15 (ix)
	add	a, l
	ld	c,a
	ld	a,-14 (ix)
	adc	a, h
	ld	b,a
	ld	l,-7 (ix)
	ld	h,-6 (ix)
	push	hl
	ld	hl,#0x3206
	push	hl
	push	bc
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
	jp	00127$
00124$:
;combat.c:130: put_frame((unsigned char *)(vram[120]+x2/8),7,50,perso2A[x2mod8]+((7*50)*layer));
	ld	a,e
	add	a, -13 (ix)
	ld	c,a
	ld	a,d
	adc	a, -12 (ix)
	ld	b,a
	ld	e,-20 (ix)
	ld	d,-19 (ix)
	ld	a,-11 (ix)
	or	a, a
	jr	Z,00134$
	ld	e,-9 (ix)
	ld	d,-8 (ix)
00134$:
	ex	de,hl
	sra	h
	rr	l
	sra	h
	rr	l
	sra	h
	rr	l
	ld	a,-15 (ix)
	add	a, l
	ld	e,a
	ld	a,-14 (ix)
	adc	a, h
	ld	d,a
	push	bc
	ld	hl,#0x3207
	push	hl
	push	de
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
	jp	00127$
_combat_palette:
	.db #0x1a	; 26
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
	.db #0x00	; 0
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
