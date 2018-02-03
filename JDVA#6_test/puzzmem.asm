;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module puzzmem
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _computeNbPiece
	.globl _newEmptyGrille
	.globl _makePreview
	.globl _fillGrilleEtSelect
	.globl _fillSelect
	.globl _fill1Grille
	.globl _fillPreview
	.globl _fillListePieces
	.globl _fillListe1Piece
	.globl _piece
	.globl _put_frame
	.globl _vsync
	.globl _get_key
	.globl _check_controller
	.globl _put_pixel_byte1
	.globl _put_pixel1
	.globl _mode
	.globl _locate
	.globl _set_palette
	.globl _printf
	.globl _select
	.globl _grille
	.globl _preview
	.globl _nbPieces
	.globl _private_nbPieces
	.globl _private_grille
	.globl _private_preview
	.globl _puzzmem_palette
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_private_preview::
	.ds 49
_private_grille::
	.ds 49
_private_nbPieces::
	.ds 18
_nbPieces::
	.ds 2
_preview::
	.ds 2
_grille::
	.ds 2
_select::
	.ds 1
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
;puzzmem.c:39: void piece(char offset_x,char offset_y,char noTile,char tailleTile,char noTile2) {
;	---------------------------------
; Function piece
; ---------------------------------
_piece::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-16
	add	hl,sp
	ld	sp,hl
;puzzmem.c:42: char mod4=offset_x%4;
	ld	a,4 (ix)
	and	a, #0x03
	ld	-16 (ix),a
;puzzmem.c:43: if (noTile2==AUCUNE_CASE) {
	ld	a,8 (ix)
	sub	a, #0x16
	jr	NZ,00102$
;puzzmem.c:44: vsync();
	call	_vsync
00102$:
;puzzmem.c:46: switch(noTile) {
	ld	a,#0x15
	sub	a, 6 (ix)
	jp	C,00323$
	ld	e,6 (ix)
	ld	d,#0x00
	ld	hl,#01138$
	add	hl,de
	add	hl,de
	add	hl,de
	jp	(hl)
01138$:
	jp	00103$
	jp	00110$
	jp	00117$
	jp	00123$
	jp	00129$
	jp	00135$
	jp	00141$
	jp	00147$
	jp	00153$
	jp	00167$
	jp	00181$
	jp	00195$
	jp	00209$
	jp	00223$
	jp	00237$
	jp	00251$
	jp	00265$
	jp	00279$
	jp	00293$
	jp	00300$
	jp	00307$
	jp	00316$
;puzzmem.c:47: case 0 :
00103$:
;puzzmem.c:49: for (y=0;y<tailleTile;y++) {
	ld	-15 (ix),#0x00
00330$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:50: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	d,a
	ld	-1 (ix),d
00327$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00331$
;puzzmem.c:51: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	c,7 (ix)
	ld	b,#0x00
	ld	a,c
	add	a,#0xfc
	ld	c,a
	ld	a,b
	adc	a,#0xff
	ld	b,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, b
	jp	PO, 01139$
	xor	a, #0x80
01139$:
	jp	P,00105$
	ld	a,e
	and	a, #0x03
	ld	-2 (ix),a
	ld	c,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, c
	ld	c,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	de
	ld	hl,#0x0004
	push	hl
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	ld	a, -2 (ix)
	ld	b, #0x00
	sub	a, l
	jr	NZ,00105$
	ld	a,b
	sub	a, h
	jr	NZ,00105$
;puzzmem.c:52: put_pixel_byte1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-1 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
;puzzmem.c:53: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00328$
00105$:
;puzzmem.c:55: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	push	de
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
00328$:
;puzzmem.c:50: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00327$
00331$:
;puzzmem.c:49: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00330$
;puzzmem.c:60: case 1 :
00110$:
;puzzmem.c:62: for (y=0;y<tailleTile;y++) {
	ld	-15 (ix),#0x00
00336$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:63: for (x=0;x<tailleTile;x++) {
	ld	b,#0x00
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	e,a
	ld	-2 (ix),e
00333$:
	ld	a,b
	sub	a, 7 (ix)
	jp	NC,00337$
;puzzmem.c:64: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	c,7 (ix)
	ld	d,#0x00
	ld	a,c
	add	a,#0xfc
	ld	c,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,b
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, d
	jp	PO, 01142$
	xor	a, #0x80
01142$:
	jp	P,00112$
	ld	a,b
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	c,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, c
	ld	c,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	l, d
	ld	h, c
	push	hl
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00112$
	ld	a,d
	sub	a, h
	jr	NZ,00112$
;puzzmem.c:65: put_pixel_byte1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, b
	ld	c,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-2 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:66: x+=3; // x+=4;
	inc	b
	inc	b
	inc	b
	jr	00334$
00112$:
;puzzmem.c:68: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, b
	ld	c,a
	push	bc
	push	de
	ld	d,#0x03
	push	de
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00334$:
;puzzmem.c:63: for (x=0;x<tailleTile;x++) {
	inc	b
	jp	00333$
00337$:
;puzzmem.c:62: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00336$
;puzzmem.c:73: case 2 :
00117$:
;puzzmem.c:75: for (x=0;x<tailleTile;x++) {
	ld	-14 (ix),#0x00
00342$:
	ld	a,-14 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:76: for (y=0;y<tailleTile;y++) {
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	b,a
	ld	-2 (ix),b
	ld	-15 (ix),#0x00
00339$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jr	NC,00343$
;puzzmem.c:77: if (x+y<tailleTile-1) {
	ld	l,-14 (ix)
	ld	h,#0x00
	ld	c,-15 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, c
	ld	-4 (ix),a
	ld	a,h
	adc	a, d
	ld	-3 (ix),a
	ld	l, 7 (ix)
	ld	h, #0x00
	dec	hl
	ld	e,l
	ld	c,h
	ld	a,-4 (ix)
	sub	a, e
	ld	a,-3 (ix)
	sbc	a, c
	jp	PO, 01145$
	xor	a, #0x80
01145$:
	jp	P,00119$
;puzzmem.c:78: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	push	bc
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-2 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	bc
	jr	00340$
00119$:
;puzzmem.c:80: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	push	bc
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	bc
00340$:
;puzzmem.c:76: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jr	00339$
00343$:
;puzzmem.c:75: for (x=0;x<tailleTile;x++) {
	inc	-14 (ix)
	jp	00342$
;puzzmem.c:85: case 3 :
00123$:
;puzzmem.c:87: for (x=0;x<tailleTile;x++) {
	ld	-14 (ix),#0x00
00348$:
	ld	a,-14 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:88: for (y=0;y<tailleTile;y++) {
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	b,a
	ld	-4 (ix),b
	ld	-15 (ix),#0x00
00345$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jr	NC,00349$
;puzzmem.c:89: if (x+y>tailleTile-1) {
	ld	l,-14 (ix)
	ld	h,#0x00
	ld	c,-15 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, c
	ld	-6 (ix),a
	ld	a,h
	adc	a, d
	ld	-5 (ix),a
	ld	l, 7 (ix)
	ld	h, #0x00
	dec	hl
	ld	a, l
	ld	c, h
	sub	a, -6 (ix)
	ld	a,c
	sbc	a, -5 (ix)
	jp	PO, 01146$
	xor	a, #0x80
01146$:
	jp	P,00125$
;puzzmem.c:90: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	push	bc
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	bc
	jr	00346$
00125$:
;puzzmem.c:92: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	push	bc
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	bc
00346$:
;puzzmem.c:88: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jr	00345$
00349$:
;puzzmem.c:87: for (x=0;x<tailleTile;x++) {
	inc	-14 (ix)
	jp	00348$
;puzzmem.c:97: case 4 :
00129$:
;puzzmem.c:99: for (x=0;x<tailleTile;x++) {
	ld	-14 (ix),#0x00
00354$:
	ld	a,-14 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:100: for (y=0;y<tailleTile;y++) {
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	-4 (ix), a
	ld	-6 (ix),a
	ld	-15 (ix),#0x00
00351$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jr	NC,00355$
;puzzmem.c:101: if (x+tailleTile-1-y<tailleTile-1) {
	ld	l,-14 (ix)
	ld	h,#0x00
	ld	c,7 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, c
	ld	e,a
	ld	a,h
	adc	a, d
	ld	b,a
	ld	a,e
	add	a,#0xff
	ld	-8 (ix),a
	ld	a,b
	adc	a,#0xff
	ld	-7 (ix),a
	ld	b,-15 (ix)
	ld	e,#0x00
	ld	a,-8 (ix)
	sub	a, b
	ld	b,a
	ld	a,-7 (ix)
	sbc	a, e
	ld	e,a
	ld	l, c
	ld	h, d
	dec	hl
	ld	c,l
	ld	d,h
	ld	a,b
	sub	a, c
	ld	a,e
	sbc	a, d
	jp	PO, 01147$
	xor	a, #0x80
01147$:
	jp	P,00131$
;puzzmem.c:102: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	jr	00352$
00131$:
;puzzmem.c:104: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
00352$:
;puzzmem.c:100: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jr	00351$
00355$:
;puzzmem.c:99: for (x=0;x<tailleTile;x++) {
	inc	-14 (ix)
	jp	00354$
;puzzmem.c:109: case 5 :
00135$:
;puzzmem.c:111: for (x=0;x<tailleTile;x++) {
	ld	-14 (ix),#0x00
00360$:
	ld	a,-14 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:112: for (y=0;y<tailleTile;y++) {
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	-6 (ix), a
	ld	-8 (ix),a
	ld	-15 (ix),#0x00
00357$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jr	NC,00361$
;puzzmem.c:113: if (x+tailleTile-1-y>tailleTile-1) {
	ld	l,-14 (ix)
	ld	h,#0x00
	ld	c,7 (ix)
	ld	d,#0x00
	ld	a,l
	add	a, c
	ld	e,a
	ld	a,h
	adc	a, d
	ld	b,a
	ld	a,e
	add	a,#0xff
	ld	-4 (ix),a
	ld	a,b
	adc	a,#0xff
	ld	-3 (ix),a
	ld	b,-15 (ix)
	ld	e,#0x00
	ld	a,-4 (ix)
	sub	a, b
	ld	b,a
	ld	a,-3 (ix)
	sbc	a, e
	ld	e,a
	ld	l, c
	ld	h, d
	dec	hl
	ld	a, l
	ld	d, h
	sub	a, b
	ld	a,d
	sbc	a, e
	jp	PO, 01148$
	xor	a, #0x80
01148$:
	jp	P,00137$
;puzzmem.c:114: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	jr	00358$
00137$:
;puzzmem.c:116: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
00358$:
;puzzmem.c:112: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jr	00357$
00361$:
;puzzmem.c:111: for (x=0;x<tailleTile;x++) {
	inc	-14 (ix)
	jp	00360$
;puzzmem.c:121: case 6 :
00141$:
;puzzmem.c:123: for (x=0;x<tailleTile;x++) {
	ld	c,7 (ix)
	srl	c
	ld	-14 (ix),#0x00
00366$:
	ld	a,-14 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:124: for (y=0;y<tailleTile;y++) {
	ld	a,-14 (ix)
	sub	a, c
	ld	a,#0x00
	rla
	ld	e,a
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	d,a
	ld	-8 (ix),d
	ld	-15 (ix),#0x00
00363$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jr	NC,00367$
;puzzmem.c:125: if (x<tailleTile/2) {
	ld	a,e
	or	a, a
	jr	Z,00143$
;puzzmem.c:126: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jr	00364$
00143$:
;puzzmem.c:128: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	c, d
	push	bc
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00364$:
;puzzmem.c:124: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jr	00363$
00367$:
;puzzmem.c:123: for (x=0;x<tailleTile;x++) {
	inc	-14 (ix)
	jr	00366$
;puzzmem.c:133: case 7 :
00147$:
;puzzmem.c:135: for (x=0;x<tailleTile;x++) {
	ld	c,7 (ix)
	srl	c
	ld	-14 (ix),#0x00
00372$:
	ld	a,-14 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:136: for (y=0;y<tailleTile;y++) {
	ld	a,c
	sub	a, -14 (ix)
	ld	a,#0x00
	rla
	ld	e,a
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	d,a
	ld	-8 (ix),d
	ld	-15 (ix),#0x00
00369$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jr	NC,00373$
;puzzmem.c:137: if (x>tailleTile/2) {
	ld	a,e
	or	a, a
	jr	Z,00149$
;puzzmem.c:138: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jr	00370$
00149$:
;puzzmem.c:140: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	c, d
	push	bc
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00370$:
;puzzmem.c:136: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jr	00369$
00373$:
;puzzmem.c:135: for (x=0;x<tailleTile;x++) {
	inc	-14 (ix)
	jr	00372$
;puzzmem.c:145: case 8 :
00153$:
;puzzmem.c:147: for (y=0;y<tailleTile;y++) {
	ld	a,7 (ix)
	srl	a
	ld	-1 (ix),a
	ld	-15 (ix),#0x00
00378$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:148: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,-15 (ix)
	sub	a, -1 (ix)
	ld	a,#0x00
	rla
	ld	d,a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-8 (ix), a
	ld	-6 (ix),a
	ld	a,-8 (ix)
	ld	-4 (ix),a
	ld	a,-8 (ix)
	ld	-2 (ix),a
00375$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00379$
;puzzmem.c:149: if (y<tailleTile/2) {
	ld	a,d
	or	a, a
	jp	Z,00163$
;puzzmem.c:150: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	c,7 (ix)
	ld	b,#0x00
	ld	a,c
	add	a,#0xfc
	ld	c,a
	ld	a,b
	adc	a,#0xff
	ld	b,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, b
	jp	PO, 01149$
	xor	a, #0x80
01149$:
	jp	P,00155$
	ld	a,e
	and	a, #0x03
	ld	-9 (ix),a
	ld	c,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, c
	ld	c,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	de
	ld	hl,#0x0004
	push	hl
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	ld	a, -9 (ix)
	ld	b, #0x00
	sub	a, l
	jr	NZ,00155$
	ld	a,b
	sub	a, h
	jr	NZ,00155$
;puzzmem.c:151: put_pixel_byte1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-2 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
;puzzmem.c:152: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jp	00376$
00155$:
;puzzmem.c:154: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	jp	00376$
00163$:
;puzzmem.c:157: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	c,7 (ix)
	ld	b,#0x00
	ld	a,c
	add	a,#0xfc
	ld	c,a
	ld	a,b
	adc	a,#0xff
	ld	b,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, b
	jp	PO, 01152$
	xor	a, #0x80
01152$:
	jp	P,00159$
	ld	a,e
	and	a, #0x03
	ld	-9 (ix),a
	ld	c,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, c
	ld	c,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	de
	ld	hl,#0x0004
	push	hl
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	ld	a, -9 (ix)
	ld	b, #0x00
	sub	a, l
	jr	NZ,00159$
	ld	a,b
	sub	a, h
	jr	NZ,00159$
;puzzmem.c:158: put_pixel_byte1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
;puzzmem.c:159: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00376$
00159$:
;puzzmem.c:161: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
00376$:
;puzzmem.c:148: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00375$
00379$:
;puzzmem.c:147: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00378$
;puzzmem.c:167: case 9 :
00167$:
;puzzmem.c:169: for (y=0;y<tailleTile;y++) {
	ld	a,7 (ix)
	srl	a
	ld	-2 (ix),a
	ld	-15 (ix),#0x00
00384$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:170: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,-2 (ix)
	sub	a, -15 (ix)
	ld	a,#0x00
	rla
	ld	d,a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00381$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00385$
;puzzmem.c:171: if (y>tailleTile/2) {
	ld	a,d
	or	a, a
	jp	Z,00177$
;puzzmem.c:172: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	c,7 (ix)
	ld	b,#0x00
	ld	a,c
	add	a,#0xfc
	ld	c,a
	ld	a,b
	adc	a,#0xff
	ld	b,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, b
	jp	PO, 01155$
	xor	a, #0x80
01155$:
	jp	P,00169$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	c,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, c
	ld	c,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	de
	ld	hl,#0x0004
	push	hl
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	ld	a, -1 (ix)
	ld	b, #0x00
	sub	a, l
	jr	NZ,00169$
	ld	a,b
	sub	a, h
	jr	NZ,00169$
;puzzmem.c:173: put_pixel_byte1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
;puzzmem.c:174: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jp	00382$
00169$:
;puzzmem.c:176: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	jp	00382$
00177$:
;puzzmem.c:179: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	c,7 (ix)
	ld	b,#0x00
	ld	a,c
	add	a,#0xfc
	ld	c,a
	ld	a,b
	adc	a,#0xff
	ld	b,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, b
	jp	PO, 01158$
	xor	a, #0x80
01158$:
	jp	P,00173$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	c,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, c
	ld	c,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	de
	ld	hl,#0x0004
	push	hl
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	ld	a, -1 (ix)
	ld	b, #0x00
	sub	a, l
	jr	NZ,00173$
	ld	a,b
	sub	a, h
	jr	NZ,00173$
;puzzmem.c:180: put_pixel_byte1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
;puzzmem.c:181: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00382$
00173$:
;puzzmem.c:183: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	c,a
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
00382$:
;puzzmem.c:170: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00381$
00385$:
;puzzmem.c:169: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00384$
;puzzmem.c:189: case 10 :
00181$:
;puzzmem.c:191: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00390$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:192: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,-15 (ix)
	sub	a, c
	ld	a,#0x00
	rla
	ld	-2 (ix),a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00387$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00391$
;puzzmem.c:193: if (x<tailleTile/2 && y<tailleTile/2) {
	ld	a,e
	sub	a, c
	jr	NC,00190$
	ld	a,-15 (ix)
	sub	a, c
	jr	NC,00190$
;puzzmem.c:194: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00388$
00190$:
;puzzmem.c:195: } else if (y<tailleTile/2) {
	ld	a,-2 (ix)
	or	a, a
	jr	Z,00187$
;puzzmem.c:196: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00388$
00187$:
;puzzmem.c:198: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	d, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, b
	ld	a,h
	sbc	a, d
	jp	PO, 01161$
	xor	a, #0x80
01161$:
	jp	P,00183$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,d
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00183$
	ld	a,d
	sub	a, h
	jr	NZ,00183$
;puzzmem.c:199: put_pixel_byte1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:200: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00388$
00183$:
;puzzmem.c:202: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00388$:
;puzzmem.c:192: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00387$
00391$:
;puzzmem.c:191: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00390$
;puzzmem.c:208: case 11 :
00195$:
;puzzmem.c:210: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00396$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:211: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,-15 (ix)
	sub	a, c
	ld	a,#0x00
	rla
	ld	-2 (ix),a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00393$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00397$
;puzzmem.c:212: if (x>tailleTile/2 && y<tailleTile/2) {
	ld	a,c
	sub	a, e
	jr	NC,00204$
	ld	a,-15 (ix)
	sub	a, c
	jr	NC,00204$
;puzzmem.c:213: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00394$
00204$:
;puzzmem.c:214: } else if (y<tailleTile/2) {
	ld	a,-2 (ix)
	or	a, a
	jr	Z,00201$
;puzzmem.c:215: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00394$
00201$:
;puzzmem.c:217: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	d, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, b
	ld	a,h
	sbc	a, d
	jp	PO, 01164$
	xor	a, #0x80
01164$:
	jp	P,00197$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,d
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00197$
	ld	a,d
	sub	a, h
	jr	NZ,00197$
;puzzmem.c:218: put_pixel_byte1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:219: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00394$
00197$:
;puzzmem.c:221: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00394$:
;puzzmem.c:211: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00393$
00397$:
;puzzmem.c:210: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00396$
;puzzmem.c:227: case 12 :
00209$:
;puzzmem.c:229: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00402$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:230: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,c
	sub	a, -15 (ix)
	ld	a,#0x00
	rla
	ld	-2 (ix),a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00399$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00403$
;puzzmem.c:231: if (x>tailleTile/2 && y>tailleTile/2) {
	ld	a,c
	cp	a,e
	jr	NC,00218$
	sub	a, -15 (ix)
	jr	NC,00218$
;puzzmem.c:232: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00400$
00218$:
;puzzmem.c:233: } else if (y>tailleTile/2) {
	ld	a,-2 (ix)
	or	a, a
	jr	Z,00215$
;puzzmem.c:234: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00400$
00215$:
;puzzmem.c:236: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	d, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, b
	ld	a,h
	sbc	a, d
	jp	PO, 01167$
	xor	a, #0x80
01167$:
	jp	P,00211$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,d
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00211$
	ld	a,d
	sub	a, h
	jr	NZ,00211$
;puzzmem.c:237: put_pixel_byte1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:238: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00400$
00211$:
;puzzmem.c:240: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00400$:
;puzzmem.c:230: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00399$
00403$:
;puzzmem.c:229: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00402$
;puzzmem.c:246: case 13 :
00223$:
;puzzmem.c:248: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00408$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:249: for (x=0;x<tailleTile;x++) {
	ld	-14 (ix),#0x00
	ld	a,c
	sub	a, -15 (ix)
	ld	a,#0x00
	rla
	ld	d,a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00405$:
	ld	a,-14 (ix)
	sub	a, 7 (ix)
	jp	NC,00409$
;puzzmem.c:250: if (x<tailleTile/2 && y>tailleTile/2) {
	ld	a,-14 (ix)
	sub	a, c
	jr	NC,00232$
	ld	a,c
	sub	a, -15 (ix)
	jr	NC,00232$
;puzzmem.c:251: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00406$
00232$:
;puzzmem.c:252: } else if (y>tailleTile/2) {
	ld	a,d
	or	a, a
	jr	Z,00229$
;puzzmem.c:253: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00406$
00229$:
;puzzmem.c:255: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	e, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,e
	adc	a,#0xff
	ld	e,a
	ld	a, -14 (ix)
	ld	h, #0x00
	sub	a, b
	ld	a,h
	sbc	a, e
	jp	PO, 01170$
	xor	a, #0x80
01170$:
	jp	P,00225$
	ld	a,-14 (ix)
	and	a, #0x03
	ld	-2 (ix),a
	ld	e,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, e
	ld	e,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,e
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -2 (ix)
	ld	e, #0x00
	sub	a, l
	jr	NZ,00225$
	ld	a,e
	sub	a, h
	jr	NZ,00225$
;puzzmem.c:256: put_pixel_byte1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:257: x+=3; // x+=4;
	inc	-14 (ix)
	inc	-14 (ix)
	inc	-14 (ix)
	jr	00406$
00225$:
;puzzmem.c:259: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00406$:
;puzzmem.c:249: for (x=0;x<tailleTile;x++) {
	inc	-14 (ix)
	jp	00405$
00409$:
;puzzmem.c:248: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00408$
;puzzmem.c:265: case 14 :
00237$:
;puzzmem.c:267: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00414$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:268: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,c
	sub	a, -15 (ix)
	ld	a,#0x00
	rla
	ld	-2 (ix),a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00411$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00415$
;puzzmem.c:269: if (x<tailleTile/2 && y<=tailleTile/2) {
	ld	a,e
	sub	a, c
	jr	NC,00246$
	ld	a,c
	sub	a, -15 (ix)
	jr	C,00246$
;puzzmem.c:270: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00412$
00246$:
;puzzmem.c:271: } else if (y<=tailleTile/2) {
	bit	0,-2 (ix)
	jr	NZ,00243$
;puzzmem.c:272: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00412$
00243$:
;puzzmem.c:274: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	d, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, b
	ld	a,h
	sbc	a, d
	jp	PO, 01173$
	xor	a, #0x80
01173$:
	jp	P,00239$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,d
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00239$
	ld	a,d
	sub	a, h
	jr	NZ,00239$
;puzzmem.c:275: put_pixel_byte1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:276: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00412$
00239$:
;puzzmem.c:278: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00412$:
;puzzmem.c:268: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00411$
00415$:
;puzzmem.c:267: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00414$
;puzzmem.c:285: case 15 :
00251$:
;puzzmem.c:287: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00420$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:288: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,c
	sub	a, -15 (ix)
	ld	a,#0x00
	rla
	ld	-2 (ix),a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00417$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00421$
;puzzmem.c:289: if (x>tailleTile/2 && y<=tailleTile/2) {
	ld	a,c
	cp	a,e
	jr	NC,00260$
	sub	a, -15 (ix)
	jr	C,00260$
;puzzmem.c:290: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00418$
00260$:
;puzzmem.c:291: } else if (y<=tailleTile/2) {
	bit	0,-2 (ix)
	jr	NZ,00257$
;puzzmem.c:292: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00418$
00257$:
;puzzmem.c:294: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	d, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, b
	ld	a,h
	sbc	a, d
	jp	PO, 01176$
	xor	a, #0x80
01176$:
	jp	P,00253$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,d
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00253$
	ld	a,d
	sub	a, h
	jr	NZ,00253$
;puzzmem.c:295: put_pixel_byte1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:296: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00418$
00253$:
;puzzmem.c:298: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00418$:
;puzzmem.c:288: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00417$
00421$:
;puzzmem.c:287: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00420$
;puzzmem.c:304: case 16 :
00265$:
;puzzmem.c:306: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00426$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:307: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,-15 (ix)
	sub	a, c
	ld	a,#0x00
	rla
	ld	-2 (ix),a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00423$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00427$
;puzzmem.c:308: if (x>tailleTile/2 && y>=tailleTile/2) {
	ld	a,c
	sub	a, e
	jr	NC,00274$
	ld	a,-15 (ix)
	sub	a, c
	jr	C,00274$
;puzzmem.c:309: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00424$
00274$:
;puzzmem.c:310: } else if (y>=tailleTile/2) {
	bit	0,-2 (ix)
	jr	NZ,00271$
;puzzmem.c:311: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00424$
00271$:
;puzzmem.c:313: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	d, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, b
	ld	a,h
	sbc	a, d
	jp	PO, 01179$
	xor	a, #0x80
01179$:
	jp	P,00267$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,d
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00267$
	ld	a,d
	sub	a, h
	jr	NZ,00267$
;puzzmem.c:314: put_pixel_byte1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:315: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00424$
00267$:
;puzzmem.c:317: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00424$:
;puzzmem.c:307: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00423$
00427$:
;puzzmem.c:306: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00426$
;puzzmem.c:323: case 17 :
00279$:
;puzzmem.c:325: for (y=0;y<tailleTile;y++) {
	ld	c,7 (ix)
	srl	c
	ld	-15 (ix),#0x00
00432$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:326: for (x=0;x<tailleTile;x++) {
	ld	e,#0x00
	ld	a,-15 (ix)
	sub	a, c
	ld	a,#0x00
	rla
	ld	-2 (ix),a
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	-9 (ix), a
	ld	-8 (ix),a
	ld	a,-9 (ix)
	ld	-6 (ix),a
	ld	a,-9 (ix)
	ld	-4 (ix),a
00429$:
	ld	a,e
	sub	a, 7 (ix)
	jp	NC,00433$
;puzzmem.c:327: if (x<tailleTile/2 && y>=tailleTile/2) {
	ld	a,e
	sub	a, c
	jr	NC,00288$
	ld	a,-15 (ix)
	sub	a, c
	jr	C,00288$
;puzzmem.c:328: put_pixel1(offset_x+x,offset_y+y,3);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x03
	push	af
	inc	sp
	ld	a,-4 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00430$
00288$:
;puzzmem.c:329: } else if (y>=tailleTile/2) {
	bit	0,-2 (ix)
	jr	NZ,00285$
;puzzmem.c:330: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-6 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
	jp	00430$
00285$:
;puzzmem.c:332: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	a, 7 (ix)
	ld	d, #0x00
	add	a,#0xfc
	ld	b,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, b
	ld	a,h
	sbc	a, d
	jp	PO, 01182$
	xor	a, #0x80
01182$:
	jp	P,00281$
	ld	a,e
	and	a, #0x03
	ld	-1 (ix),a
	ld	d,-16 (ix)
	ld	b,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, b
	ld	b,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	c,d
	push	bc
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -1 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00281$
	ld	a,d
	sub	a, h
	jr	NZ,00281$
;puzzmem.c:333: put_pixel_byte1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:334: x+=3; // x+=4;
	inc	e
	inc	e
	inc	e
	jr	00430$
00281$:
;puzzmem.c:336: put_pixel1(offset_x+x,offset_y+y,2);
	ld	a,4 (ix)
	add	a, e
	ld	b,a
	push	bc
	push	de
	ld	a,#0x02
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00430$:
;puzzmem.c:326: for (x=0;x<tailleTile;x++) {
	inc	e
	jp	00429$
00433$:
;puzzmem.c:325: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00432$
;puzzmem.c:342: case 18 :
00293$:
;puzzmem.c:344: for (y=0;y<tailleTile;y++) {
	ld	-15 (ix),#0x00
00438$:
	ld	a,-15 (ix)
	sub	a, 7 (ix)
	jp	NC,00323$
;puzzmem.c:345: for (x=0;x<tailleTile;x++) {
	ld	b,#0x00
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	e,a
	ld	-9 (ix),e
00435$:
	ld	a,b
	sub	a, 7 (ix)
	jp	NC,00439$
;puzzmem.c:346: if (x<tailleTile-4 && x%4==(4-mod4)%4) {
	ld	c,7 (ix)
	ld	d,#0x00
	ld	a,c
	add	a,#0xfc
	ld	c,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	l,b
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, d
	jp	PO, 01185$
	xor	a, #0x80
01185$:
	jp	P,00295$
	ld	a,b
	and	a, #0x03
	ld	-8 (ix),a
	ld	d,-16 (ix)
	ld	c,#0x00
	ld	a,#0x04
	sub	a, d
	ld	d,a
	ld	a,#0x00
	sbc	a, c
	ld	c,a
	push	bc
	push	de
	ld	hl,#0x0004
	push	hl
	ld	l, d
	ld	h, c
	push	hl
	call	__modsint
	pop	af
	pop	af
	pop	de
	pop	bc
	ld	a, -8 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00295$
	ld	a,d
	sub	a, h
	jr	NZ,00295$
;puzzmem.c:347: put_pixel_byte1(offset_x+x,offset_y+y,0);
	ld	a,4 (ix)
	add	a, b
	ld	c,a
	push	bc
	push	de
	xor	a, a
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:348: x+=3; // x+=4;
	inc	b
	inc	b
	inc	b
	jr	00436$
00295$:
;puzzmem.c:350: put_pixel1(offset_x+x,offset_y+y,0);
	ld	a,4 (ix)
	add	a, b
	ld	c,a
	push	bc
	push	de
	xor	a, a
	ld	d,a
	push	de
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
00436$:
;puzzmem.c:345: for (x=0;x<tailleTile;x++) {
	inc	b
	jp	00435$
00439$:
;puzzmem.c:344: for (y=0;y<tailleTile;y++) {
	inc	-15 (ix)
	jp	00438$
;puzzmem.c:355: case 19 :
00300$:
;puzzmem.c:358: for (x=0;x<tailleTile+2;x++) {
	ld	c,#0x00
	ld	b,5 (ix)
	dec	b
	ld	a,5 (ix)
	add	a, 7 (ix)
	ld	-9 (ix),a
00441$:
	ld	e,7 (ix)
	ld	d,#0x00
	ld	hl,#0x0002
	add	hl,de
	ld	-6 (ix),l
	ld	-5 (ix),h
	ld	-4 (ix),c
	ld	-3 (ix),#0x00
	ld	a,-4 (ix)
	sub	a, -6 (ix)
	ld	a,-3 (ix)
	sbc	a, -5 (ix)
	jp	PO, 01188$
	xor	a, #0x80
01188$:
	jp	P,00607$
;puzzmem.c:359: if (x<tailleTile-2 && (x+3)%4==(4-mod4)%4) {
	dec	de
	dec	de
	ld	a,-4 (ix)
	sub	a, e
	ld	a,-3 (ix)
	sbc	a, d
	jp	PO, 01189$
	xor	a, #0x80
01189$:
	jp	P,00302$
	ld	e,-4 (ix)
	ld	d,-3 (ix)
	inc	de
	inc	de
	inc	de
	push	bc
	ld	hl,#0x0004
	push	hl
	push	de
	call	__modsint
	pop	af
	pop	af
	ld	-7 (ix),h
	ld	-8 (ix),l
	pop	bc
	ld	e,-16 (ix)
	ld	d,#0x00
	ld	a,#0x04
	sub	a, e
	ld	e,a
	ld	a,#0x00
	sbc	a, d
	ld	d,a
	push	bc
	ld	hl,#0x0004
	push	hl
	push	de
	call	__modsint
	pop	af
	pop	af
	pop	bc
	ld	a,-8 (ix)
	sub	a, l
	jr	NZ,00302$
	ld	a,-7 (ix)
	sub	a, h
	jr	NZ,00302$
;puzzmem.c:360: put_pixel_byte1(offset_x+x-1,offset_y-1,1);
	ld	a,4 (ix)
	add	a, c
	ld	e, a
	dec	e
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,e
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	ld	a,#0x01
	push	af
	inc	sp
	ld	d, -9 (ix)
	push	de
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	bc
;puzzmem.c:362: x+=3; // x+=4;
	inc	c
	inc	c
	inc	c
	jr	00442$
00302$:
;puzzmem.c:364: put_pixel1(offset_x+x-1,offset_y-1,1);
	ld	a,4 (ix)
	add	a, c
	ld	e, a
	dec	e
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,e
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	ld	a,#0x01
	push	af
	inc	sp
	ld	d, -9 (ix)
	push	de
	call	_put_pixel1
	pop	af
	inc	sp
	pop	bc
00442$:
;puzzmem.c:358: for (x=0;x<tailleTile+2;x++) {
	inc	c
	jp	00441$
;puzzmem.c:369: for (y=0;y<tailleTile+2;y++) {
00607$:
	ld	c,4 (ix)
	dec	c
	ld	a,4 (ix)
	add	a, 7 (ix)
	ld	b,a
	ld	e,#0x00
00444$:
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, -6 (ix)
	ld	a,h
	sbc	a, -5 (ix)
	jp	PO, 01192$
	xor	a, #0x80
01192$:
	jp	P,00323$
;puzzmem.c:370: put_pixel1(offset_x-1,offset_y+y-1,1);
	ld	a,5 (ix)
	add	a, e
	ld	d, a
	dec	d
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	push	de
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:371: put_pixel1(offset_x+tailleTile,offset_y+y-1,1);
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	push	de
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:369: for (y=0;y<tailleTile+2;y++) {
	inc	e
	jr	00444$
;puzzmem.c:374: case 20 :
00307$:
;puzzmem.c:376: for (x=1;x<tailleTile-1;x++) {
	ld	c,7 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	ld	-13 (ix),l
	ld	-12 (ix), h
	ld	a, h
	rlca
	and	a,#0x01
	ld	-6 (ix),a
	ld	a,7 (ix)
	rrca
	rrca
	and	a,#0x3f
	ld	-4 (ix),a
	ld	a,5 (ix)
	inc	a
	ld	-9 (ix),a
	ld	a,5 (ix)
	add	a, 7 (ix)
	add	a,#0xfe
	ld	-8 (ix),a
	ld	-14 (ix),#0x01
00447$:
	ld	e,7 (ix)
	ld	d,#0x00
	dec	de
	ld	a,-14 (ix)
	ld	-11 (ix),a
	ld	-10 (ix),#0x00
	ld	a,-11 (ix)
	sub	a, e
	ld	a,-10 (ix)
	sbc	a, d
	jp	PO, 01193$
	xor	a, #0x80
01193$:
	jp	P,00311$
;puzzmem.c:377: if (x<=tailleTile/4+1 || x>=tailleTile*3/4) {
	ld	c, -4 (ix)
	ld	b, #0x00
	inc	bc
	ld	a,c
	sub	a, -11 (ix)
	ld	a,b
	sbc	a, -10 (ix)
	jp	PO, 01194$
	xor	a, #0x80
01194$:
	jp	P,00308$
	ld	c,-13 (ix)
	ld	b,-12 (ix)
	ld	a,-6 (ix)
	or	a, a
	jr	Z,00460$
	ld	c,-13 (ix)
	ld	b,-12 (ix)
	inc	bc
	inc	bc
	inc	bc
00460$:
	ld	l, c
	ld	h, b
	sra	h
	rr	l
	sra	h
	rr	l
	ld	a, -14 (ix)
	ld	b, #0x00
	sub	a, l
	ld	a,b
	sbc	a, h
	jp	PO, 01195$
	xor	a, #0x80
01195$:
	jp	M,00448$
00308$:
;puzzmem.c:378: put_pixel1(offset_x+x,offset_y+1,1);
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	c,a
	push	bc
	ld	a,#0x01
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	bc
;puzzmem.c:379: put_pixel1(offset_x+x,offset_y+tailleTile-2,1);
	ld	a,#0x01
	push	af
	inc	sp
	ld	a,-8 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
00448$:
;puzzmem.c:376: for (x=1;x<tailleTile-1;x++) {
	inc	-14 (ix)
	jp	00447$
00311$:
;puzzmem.c:382: for (y=1;y<tailleTile-1;y++) {
	ld	a,4 (ix)
	inc	a
	ld	-9 (ix),a
	ld	a,4 (ix)
	add	a, 7 (ix)
	add	a,#0xfe
	ld	-11 (ix),a
	ld	-15 (ix),#0x01
00450$:
	ld	a,-15 (ix)
	ld	-8 (ix),a
	ld	-7 (ix),#0x00
	ld	a,-8 (ix)
	sub	a, e
	ld	a,-7 (ix)
	sbc	a, d
	jp	PO, 01196$
	xor	a, #0x80
01196$:
	jp	P,00323$
;puzzmem.c:383: if (y<=tailleTile/4+1 || y>=tailleTile*3/4) {
	ld	c, -4 (ix)
	ld	b, #0x00
	inc	bc
	ld	a,c
	sub	a, -8 (ix)
	ld	a,b
	sbc	a, -7 (ix)
	jp	PO, 01197$
	xor	a, #0x80
01197$:
	jp	P,00312$
	ld	c,-13 (ix)
	ld	b,-12 (ix)
	ld	a,-6 (ix)
	or	a, a
	jr	Z,00461$
	ld	c,-13 (ix)
	ld	b,-12 (ix)
	inc	bc
	inc	bc
	inc	bc
00461$:
	ld	l, c
	ld	h, b
	sra	h
	rr	l
	sra	h
	rr	l
	ld	a, -15 (ix)
	ld	b, #0x00
	sub	a, l
	ld	a,b
	sbc	a, h
	jp	PO, 01198$
	xor	a, #0x80
01198$:
	jp	M,00451$
00312$:
;puzzmem.c:384: put_pixel1(offset_x+1,offset_y+y,1);
	ld	a,5 (ix)
	add	a, -15 (ix)
	ld	c,a
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-9 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:385: put_pixel1(offset_x+tailleTile-2,offset_y+y,1);
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	a,-11 (ix)
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
00451$:
;puzzmem.c:382: for (y=1;y<tailleTile-1;y++) {
	inc	-15 (ix)
	jp	00450$
;puzzmem.c:389: case 21 :
00316$:
;puzzmem.c:391: for (x=1;x<tailleTile-1;x++) {
	ld	c,5 (ix)
	inc	c
	ld	a,5 (ix)
	add	a, 7 (ix)
	ld	b, a
	dec	b
	dec	b
	ld	-14 (ix),#0x01
00453$:
	ld	e,7 (ix)
	ld	d,#0x00
	ld	a,e
	add	a,#0xff
	ld	-11 (ix),a
	ld	a,d
	adc	a,#0xff
	ld	-10 (ix),a
	ld	a,-14 (ix)
	ld	-8 (ix),a
	ld	-7 (ix),#0x00
	ld	a,-8 (ix)
	sub	a, -11 (ix)
	ld	a,-7 (ix)
	sbc	a, -10 (ix)
	jp	PO, 01199$
	xor	a, #0x80
01199$:
	jp	P,00321$
;puzzmem.c:392: if (x<tailleTile-5 && x%4==(4-mod4)%4) {
	ld	a,e
	add	a,#0xfb
	ld	e,a
	ld	a,d
	adc	a,#0xff
	ld	d,a
	ld	a,-8 (ix)
	sub	a, e
	ld	a,-7 (ix)
	sbc	a, d
	jp	PO, 01200$
	xor	a, #0x80
01200$:
	jp	P,00318$
	ld	a,-14 (ix)
	and	a, #0x03
	ld	-13 (ix),a
	ld	e,-16 (ix)
	ld	d,#0x00
	ld	a,#0x04
	sub	a, e
	ld	e,a
	ld	a,#0x00
	sbc	a, d
	ld	d,a
	push	bc
	ld	hl,#0x0004
	push	hl
	push	de
	call	__modsint
	pop	af
	pop	af
	pop	bc
	ld	a, -13 (ix)
	ld	d, #0x00
	sub	a, l
	jr	NZ,00318$
	ld	a,d
	sub	a, h
	jr	NZ,00318$
;puzzmem.c:393: put_pixel_byte1(offset_x+x,offset_y+1,1);
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	e,a
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	ld	d, c
	push	de
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:394: put_pixel_byte1(offset_x+x,offset_y+tailleTile-2,1);
	push	bc
	ld	a,#0x01
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,e
	push	af
	inc	sp
	call	_put_pixel_byte1
	pop	af
	inc	sp
	pop	bc
	jr	00454$
00318$:
;puzzmem.c:396: put_pixel1(offset_x+x,offset_y+1,1);
	ld	a,4 (ix)
	add	a, -14 (ix)
	ld	e,a
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	ld	d, c
	push	de
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:397: put_pixel1(offset_x+x,offset_y+tailleTile-2,1);
	push	bc
	ld	a,#0x01
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,e
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	bc
00454$:
;puzzmem.c:391: for (x=1;x<tailleTile-1;x++) {
	inc	-14 (ix)
	jp	00453$
00321$:
;puzzmem.c:400: for (y=1;y<tailleTile-1;y++) {
	ld	c,4 (ix)
	inc	c
	ld	a,4 (ix)
	add	a, 7 (ix)
	ld	b, a
	dec	b
	dec	b
	ld	e,#0x01
00456$:
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, -11 (ix)
	ld	a,h
	sbc	a, -10 (ix)
	jp	PO, 01203$
	xor	a, #0x80
01203$:
	jp	P,00323$
;puzzmem.c:401: put_pixel1(offset_x+1,offset_y+y,1);
	ld	a,5 (ix)
	add	a, e
	ld	d,a
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	push	de
	inc	sp
	ld	a,c
	push	af
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:402: put_pixel1(offset_x+tailleTile-2,offset_y+y,1);
	push	bc
	push	de
	ld	a,#0x01
	push	af
	inc	sp
	push	de
	inc	sp
	push	bc
	inc	sp
	call	_put_pixel1
	pop	af
	inc	sp
	pop	de
	pop	bc
;puzzmem.c:400: for (y=1;y<tailleTile-1;y++) {
	inc	e
	jr	00456$
;puzzmem.c:405: }
00323$:
;puzzmem.c:406: if (noTile2!=AUCUNE_CASE) {
	ld	a,8 (ix)
	sub	a, #0x16
	jr	Z,00458$
;puzzmem.c:407: piece(offset_x,offset_y,noTile2,tailleTile,AUCUNE_CASE);
	ld	a,#0x16
	push	af
	inc	sp
	ld	h,7 (ix)
	ld	l,8 (ix)
	push	hl
	ld	h,5 (ix)
	ld	l,4 (ix)
	push	hl
	call	_piece
	pop	af
	pop	af
	inc	sp
00458$:
	ld	sp, ix
	pop	ix
	ret
;puzzmem.c:411: void fillListe1Piece(char * nbPieces,char n,char curseurHaut,char etatSelect,char etatZone,char bordure) {
;	---------------------------------
; Function fillListe1Piece
; ---------------------------------
_fillListe1Piece::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	dec	sp
;puzzmem.c:413: char offset_x;char offset_y;char secondePiece=AUCUNE_CASE;
	ld	-3 (ix),#0x16
;puzzmem.c:414: x=n/2;
	ld	b,6 (ix)
	srl	b
;puzzmem.c:415: y=n%2;
	ld	a,6 (ix)
	and	a, #0x01
	ld	c,a
;puzzmem.c:417: offset_x=x*(21+3)+2;
	ld	a,b
	ld	e,a
	add	a, a
	add	a, e
	add	a, a
	add	a, a
	add	a, a
	add	a, #0x02
	ld	-1 (ix),a
;puzzmem.c:418: offset_y=y*(21+ESPACEMENT+2*ESPACEMENT)+ESPACEMENT+ESPACEMENT;
	ld	a,c
	add	a, a
	add	a, a
	add	a, a
	add	a, a
	add	a, a
	add	a, c
	add	a, #0x08
	ld	-2 (ix),a
;puzzmem.c:419: if (bordure==1) {
	ld	a,10 (ix)
	dec	a
	jr	NZ,00102$
;puzzmem.c:420: piece(offset_x,offset_y,19,21,AUCUNE_CASE); // bordure rouge
	push	bc
	ld	hl,#0x1615
	push	hl
	ld	a,#0x13
	push	af
	inc	sp
	ld	h,-2 (ix)
	ld	l,-1 (ix)
	push	hl
	call	_piece
	pop	af
	pop	af
	inc	sp
	pop	bc
00102$:
;puzzmem.c:423: locate(2+x*3,5);
	ld	a,b
	ld	e,a
	add	a, a
	add	a, e
	ld	b,a
	inc	b
	inc	b
;puzzmem.c:422: if (y==0) {
	ld	a,c
	or	a, a
	jr	NZ,00104$
;puzzmem.c:423: locate(2+x*3,5);
	ld	a,#0x05
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_locate
	pop	af
	jr	00105$
00104$:
;puzzmem.c:425: locate(2+x*3,9);
	ld	a,#0x09
	push	af
	inc	sp
	push	bc
	inc	sp
	call	_locate
	pop	af
00105$:
;puzzmem.c:427: printf("%c",nbPieces[n]+48); // texte dessous la case : nombre de pièces
	ld	a,4 (ix)
	add	a, 6 (ix)
	ld	c,a
	ld	a,5 (ix)
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	ld	l,a
	ld	h,#0x00
	ld	de, #0x0030
	add	hl, de
	push	bc
	push	hl
	ld	hl,#___str_0
	push	hl
	call	_printf
	pop	af
	pop	af
	pop	bc
;puzzmem.c:428: if ((n==curseurHaut) && (etatZone==EN_HAUT)) {
	ld	a,6 (ix)
	sub	a, 7 (ix)
	jr	NZ,00110$
	ld	a,9 (ix)
	dec	a
	jr	NZ,00110$
;puzzmem.c:429: if (etatSelect==SELECT_ON) {
	ld	a,8 (ix)
	dec	a
	jr	NZ,00107$
;puzzmem.c:430: secondePiece=20;
	ld	-3 (ix),#0x14
	jr	00110$
00107$:
;puzzmem.c:432: secondePiece=21;
	ld	-3 (ix),#0x15
00110$:
;puzzmem.c:436: if (nbPieces[n]>0) {
	ld	a,(bc)
	or	a, a
	jr	Z,00113$
;puzzmem.c:437: piece(offset_x,offset_y,n,21,secondePiece); // la piece
	ld	d, -3 (ix)
	ld	e,#0x15
	push	de
	ld	h,6 (ix)
	ld	l,-2 (ix)
	push	hl
	ld	a,-1 (ix)
	push	af
	inc	sp
	call	_piece
	pop	af
	pop	af
	inc	sp
	jr	00115$
00113$:
;puzzmem.c:439: piece(offset_x,offset_y,18,21,secondePiece); // case vide
	ld	a,-3 (ix)
	push	af
	inc	sp
	ld	hl,#0x1512
	push	hl
	ld	h,-2 (ix)
	ld	l,-1 (ix)
	push	hl
	call	_piece
	pop	af
	pop	af
	inc	sp
00115$:
	ld	sp, ix
	pop	ix
	ret
___str_0:
	.ascii "%c"
	.db 0x00
;puzzmem.c:449: void fillListePieces(char * nbPieces,char curseurHaut,char etatSelect,char etatZone) {
;	---------------------------------
; Function fillListePieces
; ---------------------------------
_fillListePieces::
	push	ix
	ld	ix,#0
	add	ix,sp
;puzzmem.c:451: for (n=0;n<18;n++) {
	ld	c,#0x00
00102$:
;puzzmem.c:452: fillListe1Piece(nbPieces,n,curseurHaut,etatSelect,etatZone,1);
	push	bc
	ld	a,#0x01
	push	af
	inc	sp
	ld	h,8 (ix)
	ld	l,7 (ix)
	push	hl
	ld	a,6 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	ld	l,4 (ix)
	ld	h,5 (ix)
	push	hl
	call	_fillListe1Piece
	ld	hl,#7
	add	hl,sp
	ld	sp,hl
	pop	bc
;puzzmem.c:451: for (n=0;n<18;n++) {
	inc	c
	ld	a,c
	sub	a, #0x12
	jr	C,00102$
	pop	ix
	ret
;puzzmem.c:466: void fillPreview(char ** preview,char niveauTaille,char niveauNb) {
;	---------------------------------
; Function fillPreview
; ---------------------------------
_fillPreview::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-7
	add	hl,sp
	ld	sp,hl
;puzzmem.c:471: piece(offset_x,offset_y,19,105,22); // bordure rouge
	ld	hl,#0x1669
	push	hl
	ld	hl,#0x135d
	push	hl
	ld	a,#0x02
	push	af
	inc	sp
	call	_piece
	pop	af
	pop	af
	inc	sp
;puzzmem.c:473: for (x=0;x<niveauNb;x=x+1) {
	ld	-6 (ix),#0x00
	ld	de,#0x0000
	ld	-5 (ix),#0x00
00107$:
	ld	a,-6 (ix)
	sub	a, 7 (ix)
	jr	NC,00109$
;puzzmem.c:474: for (y=0;y<niveauNb;y=y+1) {
	ld	hl,#_private_preview
	add	hl,de
	ld	-2 (ix),l
	ld	-1 (ix),h
	ld	a,-5 (ix)
	add	a, #0x02
	ld	-3 (ix),a
	ld	-7 (ix),#0x00
	ld	-4 (ix),#0x00
00104$:
	ld	a,-7 (ix)
	sub	a, 7 (ix)
	jr	NC,00108$
;puzzmem.c:476: piece(offset_x+x*21,offset_y+y*21,private_preview[x][y],niveauTaille,22); // la piece
	ld	a,-2 (ix)
	add	a, -7 (ix)
	ld	c,a
	ld	a,-1 (ix)
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	ld	c,a
	ld	a,-4 (ix)
	add	a, #0x5d
	ld	b,a
	push	de
	ld	a,#0x16
	push	af
	inc	sp
	ld	a,6 (ix)
	push	af
	inc	sp
	ld	a,c
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,-3 (ix)
	push	af
	inc	sp
	call	_piece
	pop	af
	pop	af
	inc	sp
	pop	de
;puzzmem.c:474: for (y=0;y<niveauNb;y=y+1) {
	ld	a,-4 (ix)
	add	a, #0x15
	ld	-4 (ix),a
	inc	-7 (ix)
	jr	00104$
00108$:
;puzzmem.c:473: for (x=0;x<niveauNb;x=x+1) {
	ld	hl,#0x0007
	add	hl,de
	ex	de,hl
	ld	a,-5 (ix)
	add	a, #0x15
	ld	-5 (ix),a
	inc	-6 (ix)
	jr	00107$
00109$:
	ld	sp, ix
	pop	ix
	ret
;puzzmem.c:487: void fill1Grille(char ** grille,char niveauTaille,char niveauNb,char n, char curseurBas,char etatSelect,char etatZone) {
;	---------------------------------
; Function fill1Grille
; ---------------------------------
_fill1Grille::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	dec	sp
;puzzmem.c:488: char offset_x;char offset_y;char x; char y;char secondePiece=AUCUNE_CASE;
	ld	-3 (ix),#0x16
;puzzmem.c:491: x=n%niveauNb;
	ld	h,7 (ix)
	ld	l,8 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	-1 (ix),l
;puzzmem.c:492: y=n/niveauNb;
	ld	h,7 (ix)
	ld	l,8 (ix)
	push	hl
	call	__divuchar
	pop	af
	ld	-2 (ix),l
;puzzmem.c:493: if ((curseurBas==(x+y*niveauNb)) && (etatZone==EN_BAS)) {
	ld	d,-1 (ix)
	ld	c,#0x00
	push	de
	push	bc
	ld	e,7 (ix)
	ld	h,-2 (ix)
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00121$:
	add	hl,hl
	jr	NC,00122$
	add	hl,de
00122$:
	djnz	00121$
	pop	bc
	pop	de
	ld	e,l
	ld	b,h
	ld	a,d
	add	a, e
	ld	d,a
	ld	a,c
	adc	a, b
	ld	c,a
	ld	a, 9 (ix)
	ld	h, #0x00
	sub	a, d
	jr	NZ,00105$
	ld	a,h
	sub	a, c
	jr	NZ,00105$
	ld	a,11 (ix)
	sub	a, #0x02
	jr	NZ,00105$
;puzzmem.c:494: if (etatSelect==SELECT_ON) {
	ld	a,10 (ix)
	dec	a
	jr	NZ,00102$
;puzzmem.c:495: secondePiece=20;
	ld	-3 (ix),#0x14
	jr	00105$
00102$:
;puzzmem.c:497: secondePiece=21;
	ld	-3 (ix),#0x15
00105$:
;puzzmem.c:500: piece(offset_x+x*21,offset_y+y*21,private_grille[x][y],niveauTaille,secondePiece); // la piece
	ld	c,-1 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	a,c
	add	a, -2 (ix)
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	ld	c,a
	ld	a,-2 (ix)
	ld	e,a
	add	a, a
	add	a, a
	add	a, e
	add	a, a
	add	a, a
	add	a, e
	add	a, #0x56
	ld	b,a
	push	de
	ld	a,-1 (ix)
	ld	e,a
	add	a, a
	add	a, a
	add	a, e
	add	a, a
	add	a, a
	add	a, e
	pop	de
	ld	e,a
	add	a, #0x6e
	ld	e,a
	ld	h,-3 (ix)
	ld	l,6 (ix)
	push	hl
	ld	a,c
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	a,e
	push	af
	inc	sp
	call	_piece
	ld	sp,ix
	pop	ix
	ret
;puzzmem.c:506: void fillSelect(char niveauTaille,char curseurBas,char select,char etatSelect,char etatZone) {
;	---------------------------------
; Function fillSelect
; ---------------------------------
_fillSelect::
	push	ix
	ld	ix,#0
	add	ix,sp
;puzzmem.c:507: char offset_x;char offset_y;char secondePiece=AUCUNE_CASE;
	ld	c,#0x16
;puzzmem.c:510: if ((curseurBas==CURSEUR_BAS_SELECT) && (etatZone==EN_BAS)) {
	ld	a,5 (ix)
	sub	a, #0x31
	jr	NZ,00105$
	ld	a,8 (ix)
	sub	a, #0x02
	jr	NZ,00105$
;puzzmem.c:511: if (etatSelect==SELECT_ON) {
	ld	a,7 (ix)
	dec	a
	jr	NZ,00102$
;puzzmem.c:512: secondePiece=20;
	ld	c,#0x14
	jr	00105$
00102$:
;puzzmem.c:514: secondePiece=21;
	ld	c,#0x15
00105$:
;puzzmem.c:517: piece(offset_x,offset_y,select,niveauTaille,secondePiece);
	ld	a,c
	push	af
	inc	sp
	ld	h,4 (ix)
	ld	l,6 (ix)
	push	hl
	ld	hl,#0x56d8
	push	hl
	call	_piece
	pop	af
	pop	af
	inc	sp
	pop	ix
	ret
;puzzmem.c:529: void fillGrilleEtSelect(char ** grille,char niveauTaille,char niveauNb,char curseurBas,char select,char etatSelect,char etatZone) {
;	---------------------------------
; Function fillGrilleEtSelect
; ---------------------------------
_fillGrilleEtSelect::
	push	ix
	ld	ix,#0
	add	ix,sp
;puzzmem.c:535: piece(offset_x,offset_y,19,105,AUCUNE_CASE); // bordure rouge
	ld	hl,#0x1669
	push	hl
	ld	hl,#0x1356
	push	hl
	ld	a,#0x6e
	push	af
	inc	sp
	call	_piece
	pop	af
	pop	af
	inc	sp
;puzzmem.c:537: for (n=0;n<niveauNb*niveauNb;n++) {
	ld	e,7 (ix)
	ld	h,7 (ix)
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00116$:
	add	hl,hl
	jr	NC,00117$
	add	hl,de
00117$:
	djnz	00116$
	ld	c,l
	ld	b,h
	ld	e,#0x00
00103$:
	ld	l,e
	ld	h,#0x00
	ld	a,l
	sub	a, c
	ld	a,h
	sbc	a, b
	jp	PO, 00118$
	xor	a, #0x80
00118$:
	jp	P,00101$
;puzzmem.c:538: fill1Grille(grille,niveauTaille,niveauNb,n,curseurBas,etatSelect,etatZone);
	push	bc
	push	de
	ld	h,11 (ix)
	ld	l,10 (ix)
	push	hl
	ld	d, 8 (ix)
	push	de
	ld	h,7 (ix)
	ld	l,6 (ix)
	push	hl
	ld	l,4 (ix)
	ld	h,5 (ix)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
	pop	de
	pop	bc
;puzzmem.c:537: for (n=0;n<niveauNb*niveauNb;n++) {
	inc	e
	jr	00103$
00101$:
;puzzmem.c:544: piece(offset_x,offset_y,19,niveauTaille,AUCUNE_CASE); // bordure rouge
	ld	a,#0x16
	push	af
	inc	sp
	ld	a,6 (ix)
	push	af
	inc	sp
	ld	hl,#0x1356
	push	hl
	ld	a,#0xd8
	push	af
	inc	sp
	call	_piece
	pop	af
	pop	af
	inc	sp
;puzzmem.c:545: fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
	ld	h,11 (ix)
	ld	l,10 (ix)
	push	hl
	ld	h,9 (ix)
	ld	l,8 (ix)
	push	hl
	ld	a,6 (ix)
	push	af
	inc	sp
	call	_fillSelect
	pop	af
	pop	af
	inc	sp
	pop	ix
	ret
;puzzmem.c:551: char ** makePreview(char niveauNb) {
;	---------------------------------
; Function makePreview
; ---------------------------------
_makePreview::
	push	ix
;puzzmem.c:554: private_preview[0][0] = 2;
	ld	hl,#_private_preview
	ld	(hl),#0x02
;puzzmem.c:555: private_preview[1][0] = 1;
	ld	hl,#(_private_preview + 0x0007)
	ld	(hl),#0x01
;puzzmem.c:556: private_preview[2][0] = 1;
	ld	hl,#(_private_preview + 0x000e)
	ld	(hl),#0x01
;puzzmem.c:557: private_preview[3][0] = 1;
	ld	hl,#(_private_preview + 0x0015)
	ld	(hl),#0x01
;puzzmem.c:558: private_preview[4][0] = 5;
	ld	hl,#(_private_preview + 0x001c)
	ld	(hl),#0x05
;puzzmem.c:560: private_preview[0][1] = 3;
	ld	hl,#(_private_preview + 0x0001)
	ld	(hl),#0x03
;puzzmem.c:561: private_preview[1][1] = 17;
	ld	hl,#(_private_preview + 0x0008)
	ld	(hl),#0x11
;puzzmem.c:562: private_preview[2][1] = 12;
	ld	hl,#(_private_preview + 0x000f)
	ld	(hl),#0x0c
;puzzmem.c:563: private_preview[3][1] = 16;
	ld	hl,#(_private_preview + 0x0016)
	ld	(hl),#0x10
;puzzmem.c:564: private_preview[4][1] = 4;
	ld	hl,#(_private_preview + 0x001d)
	ld	(hl),#0x04
;puzzmem.c:566: private_preview[0][2] = 1;
	ld	hl,#(_private_preview + 0x0002)
	ld	(hl),#0x01
;puzzmem.c:567: private_preview[1][2] = 12;
	ld	hl,#(_private_preview + 0x0009)
	ld	(hl),#0x0c
;puzzmem.c:568: private_preview[2][2] = 12;
	ld	hl,#(_private_preview + 0x0010)
	ld	(hl),#0x0c
;puzzmem.c:569: private_preview[3][2] = 1;
	ld	hl,#(_private_preview + 0x0017)
	ld	(hl),#0x01
;puzzmem.c:570: private_preview[4][2] = 1;
	ld	hl,#(_private_preview + 0x001e)
	ld	(hl),#0x01
;puzzmem.c:572: private_preview[0][3] = 9;
	ld	hl,#(_private_preview + 0x0003)
	ld	(hl),#0x09
;puzzmem.c:573: private_preview[1][3] = 9;
	ld	hl,#(_private_preview + 0x000a)
	ld	(hl),#0x09
;puzzmem.c:574: private_preview[2][3] = 9;
	ld	hl,#(_private_preview + 0x0011)
	ld	(hl),#0x09
;puzzmem.c:575: private_preview[3][3] = 9;
	ld	hl,#(_private_preview + 0x0018)
	ld	(hl),#0x09
;puzzmem.c:576: private_preview[4][3] = 9;
	ld	hl,#(_private_preview + 0x001f)
	ld	(hl),#0x09
;puzzmem.c:578: private_preview[0][4] = 2;
	ld	hl,#(_private_preview + 0x0004)
	ld	(hl),#0x02
;puzzmem.c:579: private_preview[1][4] = 2;
	ld	hl,#(_private_preview + 0x000b)
	ld	(hl),#0x02
;puzzmem.c:580: private_preview[2][4] = 2;
	ld	hl,#(_private_preview + 0x0012)
	ld	(hl),#0x02
;puzzmem.c:581: private_preview[3][4] = 2;
	ld	hl,#(_private_preview + 0x0019)
	ld	(hl),#0x02
;puzzmem.c:582: private_preview[4][4] = 2;
	ld	hl,#(_private_preview + 0x0020)
	ld	(hl),#0x02
;puzzmem.c:584: return private_preview;
	ld	hl,#_private_preview
	pop	ix
	ret
;puzzmem.c:587: char ** newEmptyGrille() {
;	---------------------------------
; Function newEmptyGrille
; ---------------------------------
_newEmptyGrille::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
;puzzmem.c:589: for (x=0;x<7;x=x+1) {
	ld	-3 (ix),#0x00
	ld	de,#0x0000
;puzzmem.c:590: for (y=0;y<7;y=y+1) {
00109$:
	ld	hl,#_private_grille
	add	hl,de
	ld	-2 (ix),l
	ld	-1 (ix),h
	ld	-4 (ix),#0x00
00103$:
;puzzmem.c:591: private_grille[x][y]=CASE_VIDE;
	ld	a,-2 (ix)
	add	a, -4 (ix)
	ld	c,a
	ld	a,-1 (ix)
	adc	a, #0x00
	ld	b,a
	ld	a,#0x12
	ld	(bc),a
;puzzmem.c:590: for (y=0;y<7;y=y+1) {
	inc	-4 (ix)
	ld	a,-4 (ix)
	sub	a, #0x07
	jr	C,00103$
;puzzmem.c:589: for (x=0;x<7;x=x+1) {
	ld	hl,#0x0007
	add	hl,de
	ex	de,hl
	inc	-3 (ix)
	ld	a,-3 (ix)
	sub	a, #0x07
	jr	C,00109$
;puzzmem.c:594: return (char **)private_grille;
	ld	hl,#_private_grille
	ld	sp, ix
	pop	ix
	ret
;puzzmem.c:598: char * computeNbPiece(char ** preview, char niveauNb) {
;	---------------------------------
; Function computeNbPiece
; ---------------------------------
_computeNbPiece::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
;puzzmem.c:600: for (x=0;x<18;x=x+1) {
	ld	c,#0x00
00104$:
;puzzmem.c:601: private_nbPieces[x]=0;
	ld	a,#<(_private_nbPieces)
	add	a, c
	ld	e,a
	ld	a,#>(_private_nbPieces)
	adc	a, #0x00
	ld	d,a
	xor	a, a
	ld	(de),a
;puzzmem.c:600: for (x=0;x<18;x=x+1) {
	inc	c
	ld	a,c
	sub	a, #0x12
	jr	C,00104$
;puzzmem.c:603: for (x=0;x<niveauNb;x=x+1) {
	ld	-3 (ix),#0x00
	ld	de,#0x0000
00110$:
	ld	a,-3 (ix)
	sub	a, 6 (ix)
	jr	NC,00103$
;puzzmem.c:604: for (y=0;y<niveauNb;y=y+1) {
	ld	hl,#_private_preview
	add	hl,de
	ld	-2 (ix),l
	ld	-1 (ix),h
	ld	-4 (ix),#0x00
00107$:
	ld	a,-4 (ix)
	sub	a, 6 (ix)
	jr	NC,00111$
;puzzmem.c:606: private_nbPieces[private_preview[x][y]]=private_nbPieces[private_preview[x][y]]+1;
	ld	a,-2 (ix)
	add	a, -4 (ix)
	ld	c,a
	ld	a,-1 (ix)
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	add	a,#<(_private_nbPieces)
	ld	c,a
	ld	a,#>(_private_nbPieces)
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	inc	a
	ld	(bc),a
;puzzmem.c:604: for (y=0;y<niveauNb;y=y+1) {
	inc	-4 (ix)
	jr	00107$
00111$:
;puzzmem.c:603: for (x=0;x<niveauNb;x=x+1) {
	ld	hl,#0x0007
	add	hl,de
	ex	de,hl
	inc	-3 (ix)
	jr	00110$
00103$:
;puzzmem.c:609: return (char *)private_nbPieces;
	ld	hl,#_private_nbPieces
	ld	sp, ix
	pop	ix
	ret
;puzzmem.c:629: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl,#-14
	add	hl,sp
	ld	sp,hl
;puzzmem.c:638: mode(1);
	ld	a,#0x01
	push	af
	inc	sp
	call	_mode
	inc	sp
;puzzmem.c:639: set_palette(puzzmem_palette);
	ld	hl,#_puzzmem_palette
	push	hl
	call	_set_palette
;puzzmem.c:643: put_frame(vram(45,0),80,200,bluegirl);
	ld	hl, #_bluegirl
	ex	(sp),hl
	ld	hl,#0xc850
	push	hl
	ld	hl,#0xc02d
	push	hl
	call	_put_frame
	ld	hl,#6
	add	hl,sp
	ld	sp,hl
;puzzmem.c:656: niveauNb=5;
	ld	-8 (ix),#0x05
;puzzmem.c:657: niveauTaille=21;
	ld	-9 (ix),#0x15
;puzzmem.c:660: curseurHaut=0;
	ld	-1 (ix),#0x00
;puzzmem.c:661: curseurHautOld=0;
	ld	-6 (ix),#0x00
;puzzmem.c:662: curseurBas=0;
	ld	-2 (ix),#0x00
;puzzmem.c:663: curseurBasOld=0;
	ld	-7 (ix),#0x00
;puzzmem.c:664: etatSelect=SELECT_OFF;
	ld	-3 (ix),#0x00
;puzzmem.c:665: etatZone=EN_BAS;
	ld	-4 (ix),#0x02
;puzzmem.c:668: preview=makePreview(niveauNb);
	ld	a,-8 (ix)
	push	af
	inc	sp
	call	_makePreview
	inc	sp
	ld	c,l
	ld	b,h
	ld	(_preview),bc
;puzzmem.c:669: nbPieces=computeNbPiece(preview,niveauNb);
	ld	a,-8 (ix)
	push	af
	inc	sp
	ld	hl,(_preview)
	push	hl
	call	_computeNbPiece
	pop	af
	inc	sp
	ld	c,l
	ld	b,h
	ld	(_nbPieces),bc
;puzzmem.c:670: grille=newEmptyGrille(); // rempli avec des CASE_VIDE
	call	_newEmptyGrille
	ld	c,l
	ld	b,h
	ld	(_grille),bc
;puzzmem.c:671: select=CASE_VIDE;
	ld	hl,#_select + 0
	ld	(hl), #0x12
;puzzmem.c:677: vsync();
	call	_vsync
;puzzmem.c:678: fillListePieces(nbPieces,curseurHaut,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	a,-1 (ix)
	push	af
	inc	sp
	ld	hl,(_nbPieces)
	push	hl
	call	_fillListePieces
	pop	af
	pop	af
	inc	sp
;puzzmem.c:679: fillPreview(preview,niveauTaille,niveauNb);
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_preview)
	push	hl
	call	_fillPreview
	pop	af
	pop	af
;puzzmem.c:680: fillGrilleEtSelect(grille,niveauTaille,niveauNb,curseurBas,select,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	a,(_select)
	push	af
	inc	sp
	ld	h,-2 (ix)
	ld	l,-8 (ix)
	push	hl
	ld	a,-9 (ix)
	push	af
	inc	sp
	ld	hl,(_grille)
	push	hl
	call	_fillGrilleEtSelect
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
;puzzmem.c:682: while (1) {
00291$:
;puzzmem.c:683: one_key=0;
	ld	-14 (ix),#0x00
;puzzmem.c:684: check_controller();
	call	_check_controller
;puzzmem.c:685: touche=0;
	ld	-5 (ix),#0x00
;puzzmem.c:686: if (get_key(Key_CursorUp) || get_key(Key_Joy1Up)) {
	xor	a, a
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	NZ,00101$
	ld	a,#0x48
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00102$
00101$:
;puzzmem.c:687: touche=TOUCHE_HAUT;
	ld	-5 (ix),#0x01
00102$:
;puzzmem.c:689: if (get_key(Key_CursorDown) || get_key(Key_Joy1Down)) {
	ld	a,#0x02
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	NZ,00106$
	ld	a,#0x49
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00107$
00106$:
;puzzmem.c:690: if (touche!=0) continue;
	ld	a,-5 (ix)
	or	a, a
	jr	NZ,00291$
;puzzmem.c:691: touche=TOUCHE_BAS;
	ld	-5 (ix),#0x02
00107$:
;puzzmem.c:693: if (get_key(Key_CursorRight) || get_key(Key_Joy1Right)) {
	ld	a,#0x01
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	NZ,00111$
	ld	a,#0x4b
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00112$
00111$:
;puzzmem.c:694: if (touche!=0) continue;
	ld	a,-5 (ix)
	or	a, a
	jr	NZ,00291$
;puzzmem.c:695: touche=TOUCHE_DROITE;
	ld	-5 (ix),#0x03
00112$:
;puzzmem.c:697: if (get_key(Key_CursorLeft) || get_key(Key_Joy1Left)) {
	ld	a,#0x08
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	NZ,00116$
	ld	a,#0x4a
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00117$
00116$:
;puzzmem.c:698: if (touche!=0) continue;
	ld	a,-5 (ix)
	or	a, a
	jp	NZ,00291$
;puzzmem.c:699: touche=TOUCHE_GAUCHE;
	ld	-5 (ix),#0x04
00117$:
;puzzmem.c:701: if (get_key(Key_Space) || get_key(Key_Joy1Fire1)) {
	ld	a,#0x2f
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	NZ,00121$
	ld	a,#0x4c
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00122$
00121$:
;puzzmem.c:702: if (touche!=0) continue;
	ld	a,-5 (ix)
	or	a, a
	jp	NZ,00291$
;puzzmem.c:703: touche=TOUCHE_ESPACE;
	ld	-5 (ix),#0x05
00122$:
;puzzmem.c:705: if (get_key(Key_Return) || get_key(Key_Joy1Fire2) || get_key(Key_Joy1Fire3)) {
	ld	a,#0x12
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	NZ,00126$
	ld	a,#0x4d
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	NZ,00126$
	ld	a,#0x4e
	push	af
	inc	sp
	call	_get_key
	inc	sp
	ld	a,l
	or	a, a
	jr	Z,00127$
00126$:
;puzzmem.c:706: if (touche!=0) continue;
	ld	a,-5 (ix)
	or	a, a
	jp	NZ,00291$
;puzzmem.c:707: touche=TOUCHE_ENTREE;
	ld	-5 (ix),#0x06
00127$:
;puzzmem.c:709: switch (touche) {
	ld	l,-5 (ix)
	ld	a,l
	sub	a, #0x01
	jp	C,00271$
	ld	a,#0x06
	sub	a, l
	jp	C,00271$
	ld	c,l
	dec	c
	ld	e,c
	ld	d,#0x00
	ld	hl,#00681$
	add	hl,de
	add	hl,de
	add	hl,de
	jp	(hl)
00681$:
	jp	00130$
	jp	00153$
	jp	00173$
	jp	00201$
	jp	00242$
	jp	00253$
;puzzmem.c:711: case TOUCHE_HAUT:
00130$:
;puzzmem.c:712: if (etatZone==EN_HAUT) {
	ld	a,-4 (ix)
	dec	a
	jr	NZ,00151$
;puzzmem.c:713: curseurHautOld=curseurHaut;
	ld	a,-1 (ix)
	ld	-6 (ix),a
;puzzmem.c:714: one_key=EN_HAUT;
	ld	-14 (ix),#0x01
;puzzmem.c:715: if ((curseurHaut % 2) == 1) {
	ld	a,-1 (ix)
	and	a, #0x01
	dec	a
	jr	NZ,00132$
;puzzmem.c:716: curseurHaut=curseurHaut-1;
	dec	-1 (ix)
	jp	00271$
00132$:
;puzzmem.c:718: curseurHaut=curseurHaut+1;
	inc	-1 (ix)
	jp	00271$
00151$:
;puzzmem.c:721: if (curseurBas != CURSEUR_BAS_SELECT) {
	ld	a,-2 (ix)
	sub	a, #0x31
	jp	Z,00271$
;puzzmem.c:722: if (curseurBas > niveauNb - 1) {
	ld	c,-8 (ix)
	ld	b,#0x00
	dec	bc
	ld	l,-2 (ix)
	ld	h,#0x00
	ld	a,c
	sub	a, l
	ld	a,b
	sbc	a, h
	jp	PO, 00687$
	xor	a, #0x80
00687$:
	jp	P,00271$
;puzzmem.c:723: if (etatSelect==SELECT_ON) {
	ld	a,-3 (ix)
	dec	a
	jp	NZ,00144$
;puzzmem.c:724: grille_x=curseurBas%niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	-10 (ix),l
;puzzmem.c:725: grille_y=curseurBas/niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__divuchar
	pop	af
;puzzmem.c:727: for (p=grille_y;p>=0;) {// 0-1==0...
	ld	-11 (ix), l
	ld	-12 (ix), l
00296$:
;puzzmem.c:728: if (private_grille[grille_x][p]==CASE_VIDE) {
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-12 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	sub	a, #0x12
	jp	NZ,00138$
;puzzmem.c:729: for (pp=p;pp<grille_y;pp=pp+1) {
	ld	a,-12 (ix)
	ld	-13 (ix),a
00294$:
	ld	a,-13 (ix)
	sub	a, -11 (ix)
	jp	NC,00136$
;puzzmem.c:730: private_grille[grille_x][pp]=private_grille[grille_x][pp+1];
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-13 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	e,-10 (ix)
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	ex	de,hl
	ld	hl,#_private_grille
	add	hl,de
	ex	de,hl
	ld	l,-13 (ix)
	inc	l
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	ld	(bc),a
;puzzmem.c:731: curseurBasOld=grille_x+pp*niveauNb;
	ld	e,-8 (ix)
	ld	h,-13 (ix)
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00692$:
	add	hl,hl
	jr	NC,00693$
	add	hl,de
00693$:
	djnz	00692$
	ld	c,l
	ld	a,-10 (ix)
	add	a, c
	ld	-7 (ix),a
;puzzmem.c:732: if (curseurBasOld!=curseurBas-niveauNb) {
	ld	c,-2 (ix)
	ld	b,#0x00
	ld	e,-8 (ix)
	ld	d,#0x00
	ld	a,c
	sub	a, e
	ld	c,a
	ld	a,b
	sbc	a, d
	ld	b,a
	ld	a, -7 (ix)
	ld	h, #0x00
	sub	a, c
	jr	NZ,00694$
	ld	a,h
	sub	a, b
	jr	Z,00295$
00694$:
;puzzmem.c:733: fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-2 (ix)
	ld	l,-7 (ix)
	push	hl
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_grille)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
00295$:
;puzzmem.c:729: for (pp=p;pp<grille_y;pp=pp+1) {
	inc	-13 (ix)
	jp	00294$
00136$:
;puzzmem.c:736: private_grille[grille_x][grille_y]=CASE_VIDE;
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,#0x12
	ld	(bc),a
;puzzmem.c:737: curseurBasOld=curseurBas; // leger
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:738: curseurBas=curseurBas-niveauNb;
	ld	a,-2 (ix)
	sub	a, -8 (ix)
	ld	-2 (ix),a
;puzzmem.c:739: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:740: break;
	jp	00271$
00138$:
;puzzmem.c:742: if (p==0) {
	ld	a,-12 (ix)
	or	a, a
	jp	Z,00271$
;puzzmem.c:745: p=p-1;
	dec	-12 (ix)
	jp	00296$
00144$:
;puzzmem.c:749: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:750: curseurBas=curseurBas-niveauNb;
	ld	a,-2 (ix)
	sub	a, -8 (ix)
	ld	-2 (ix),a
;puzzmem.c:751: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:756: break;
	jp	00271$
;puzzmem.c:758: case TOUCHE_BAS:
00153$:
;puzzmem.c:759: if (etatZone==EN_HAUT) {
	ld	a,-4 (ix)
	dec	a
	jr	NZ,00171$
;puzzmem.c:760: curseurHautOld=curseurHaut;
	ld	a,-1 (ix)
	ld	-6 (ix),a
;puzzmem.c:761: one_key=EN_HAUT;
	ld	-14 (ix),#0x01
;puzzmem.c:762: if ((curseurHaut % 2) == 0) {
	bit	0, -1 (ix)
	jr	NZ,00155$
;puzzmem.c:763: curseurHaut=curseurHaut+1;
	inc	-1 (ix)
	jp	00271$
00155$:
;puzzmem.c:765: curseurHaut=curseurHaut-1;
	dec	-1 (ix)
	jp	00271$
00171$:
;puzzmem.c:768: if (curseurBas != CURSEUR_BAS_SELECT) {
	ld	a,-2 (ix)
	sub	a, #0x31
	jp	Z,00271$
;puzzmem.c:769: if (curseurBas < niveauNb*(niveauNb-1)) {
	ld	c,-8 (ix)
	ld	b,#0x00
	dec	bc
	ld	e,-8 (ix)
	ld	d,#0x00
	push	bc
	push	de
	call	__mulint
	pop	af
	pop	af
	ld	a, -2 (ix)
	ld	b, #0x00
	sub	a, l
	ld	a,b
	sbc	a, h
	jp	PO, 00700$
	xor	a, #0x80
00700$:
	jp	P,00271$
;puzzmem.c:770: if (etatSelect==SELECT_ON) {
	ld	a,-3 (ix)
	dec	a
	jp	NZ,00164$
;puzzmem.c:771: grille_x=curseurBas%niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	-10 (ix),l
;puzzmem.c:772: grille_y=curseurBas/niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__divuchar
	pop	af
;puzzmem.c:774: for (p=grille_y;p<niveauNb;p=p+1) {
	ld	-11 (ix), l
	ld	-12 (ix), l
00303$:
	ld	a,-12 (ix)
	sub	a, -8 (ix)
	jp	NC,00271$
;puzzmem.c:775: if (private_grille[grille_x][p]==CASE_VIDE) {
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-12 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	sub	a, #0x12
	jp	NZ,00304$
;puzzmem.c:776: for (pp=p;pp>grille_y;pp=pp-1) {
	ld	a,-12 (ix)
	ld	-13 (ix),a
00300$:
	ld	a,-11 (ix)
	sub	a, -13 (ix)
	jp	NC,00159$
;puzzmem.c:777: private_grille[grille_x][pp]=private_grille[grille_x][pp-1];
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-13 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	e,-10 (ix)
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	ex	de,hl
	ld	hl,#_private_grille
	add	hl,de
	ex	de,hl
	ld	l,-13 (ix)
	dec	l
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	ld	(bc),a
;puzzmem.c:778: curseurBasOld=grille_x+pp*niveauNb;
	ld	e,-8 (ix)
	ld	h,-13 (ix)
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00705$:
	add	hl,hl
	jr	NC,00706$
	add	hl,de
00706$:
	djnz	00705$
	ld	c,l
	ld	a,-10 (ix)
	add	a, c
	ld	-7 (ix),a
;puzzmem.c:779: if (curseurBasOld!=curseurBas+niveauNb) {
	ld	l,-2 (ix)
	ld	h,#0x00
	ld	c,-8 (ix)
	ld	b,#0x00
	ld	a,l
	add	a, c
	ld	c,a
	ld	a,h
	adc	a, b
	ld	b,a
	ld	a, -7 (ix)
	ld	h, #0x00
	sub	a, c
	jr	NZ,00707$
	ld	a,h
	sub	a, b
	jr	Z,00301$
00707$:
;puzzmem.c:780: fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-2 (ix)
	ld	l,-7 (ix)
	push	hl
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_grille)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
00301$:
;puzzmem.c:776: for (pp=p;pp>grille_y;pp=pp-1) {
	dec	-13 (ix)
	jp	00300$
00159$:
;puzzmem.c:783: private_grille[grille_x][grille_y]=CASE_VIDE;
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,#0x12
	ld	(bc),a
;puzzmem.c:784: curseurBasOld=curseurBas; // leger
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:785: curseurBas=curseurBas+niveauNb;
	ld	a,-2 (ix)
	add	a, -8 (ix)
	ld	-2 (ix),a
;puzzmem.c:786: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:787: break;
	jp	00271$
00304$:
;puzzmem.c:774: for (p=grille_y;p<niveauNb;p=p+1) {
	inc	-12 (ix)
	jp	00303$
00164$:
;puzzmem.c:791: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:792: curseurBas=curseurBas+niveauNb;
	ld	a,-2 (ix)
	add	a, -8 (ix)
	ld	-2 (ix),a
;puzzmem.c:793: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:798: break;
	jp	00271$
;puzzmem.c:800: case TOUCHE_DROITE:
00173$:
;puzzmem.c:801: if (etatZone==EN_HAUT) {
	ld	a,-4 (ix)
	dec	a
	jr	NZ,00199$
;puzzmem.c:802: curseurHautOld=curseurHaut;
	ld	a,-1 (ix)
	ld	-6 (ix),a
;puzzmem.c:803: one_key=EN_HAUT;
	ld	-14 (ix),#0x01
;puzzmem.c:804: if (curseurHaut <16) {
	ld	a,-1 (ix)
	sub	a, #0x10
	jr	NC,00175$
;puzzmem.c:805: curseurHaut=curseurHaut+2;
	inc	-1 (ix)
	inc	-1 (ix)
	jp	00271$
00175$:
;puzzmem.c:807: curseurHaut=curseurHaut-16;
	ld	a,-1 (ix)
	add	a,#0xf0
	ld	-1 (ix),a
	jp	00271$
00199$:
;puzzmem.c:810: if (curseurBas != CURSEUR_BAS_SELECT) {
	ld	a,-2 (ix)
	sub	a, #0x31
	jp	Z,00271$
;puzzmem.c:811: if (curseurBas % niveauNb < niveauNb - 1) {
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	c,l
	ld	e,-8 (ix)
	ld	d,#0x00
	dec	de
	ld	l,c
	ld	h,#0x00
	ld	a,l
	sub	a, e
	ld	a,h
	sbc	a, d
	jp	PO, 00711$
	xor	a, #0x80
00711$:
	jp	P,00194$
;puzzmem.c:812: if (etatSelect==SELECT_ON) {
	ld	a,-3 (ix)
	dec	a
	jp	NZ,00184$
;puzzmem.c:813: grille_x=curseurBas%niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	-10 (ix),l
;puzzmem.c:814: grille_y=curseurBas/niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__divuchar
	pop	af
	ld	-11 (ix),l
;puzzmem.c:816: for (p=grille_x;p<niveauNb;p=p+1) {
	ld	a,-10 (ix)
	ld	-12 (ix),a
00309$:
	ld	a,-12 (ix)
	sub	a, -8 (ix)
	jp	NC,00271$
;puzzmem.c:817: if (private_grille[p][grille_y]==CASE_VIDE) {
	ld	c,-12 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	sub	a, #0x12
	jp	NZ,00310$
;puzzmem.c:818: for (pp=p;pp>grille_x;pp=pp-1) {
	ld	a,-12 (ix)
	ld	-13 (ix),a
00306$:
	ld	a,-10 (ix)
	sub	a, -13 (ix)
	jp	NC,00179$
;puzzmem.c:819: private_grille[pp][grille_y]=private_grille[pp-1][grille_y];
	ld	c,-13 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	l,-13 (ix)
	dec	l
	ld	e,l
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	ex	de,hl
	ld	hl,#_private_grille
	add	hl,de
	ex	de,hl
	ld	l,-11 (ix)
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	ld	(bc),a
;puzzmem.c:820: curseurBasOld=pp+grille_y*niveauNb;
	ld	e,-8 (ix)
	ld	h,-11 (ix)
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00716$:
	add	hl,hl
	jr	NC,00717$
	add	hl,de
00717$:
	djnz	00716$
	ld	c,l
	ld	a,-13 (ix)
	add	a, c
	ld	-7 (ix),a
;puzzmem.c:821: if (curseurBasOld!=curseurBas+1) {
	ld	c, -2 (ix)
	ld	b, #0x00
	inc	bc
	ld	a, -7 (ix)
	ld	h, #0x00
	sub	a, c
	jr	NZ,00718$
	ld	a,h
	sub	a, b
	jr	Z,00307$
00718$:
;puzzmem.c:822: fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-2 (ix)
	ld	l,-7 (ix)
	push	hl
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_grille)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
00307$:
;puzzmem.c:818: for (pp=p;pp>grille_x;pp=pp-1) {
	dec	-13 (ix)
	jp	00306$
00179$:
;puzzmem.c:825: private_grille[grille_x][grille_y]=CASE_VIDE;
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,#0x12
	ld	(bc),a
;puzzmem.c:826: curseurBasOld=curseurBas; // leger
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:827: curseurBas=curseurBas+1;
	inc	-2 (ix)
;puzzmem.c:828: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:829: break;
	jp	00271$
00310$:
;puzzmem.c:816: for (p=grille_x;p<niveauNb;p=p+1) {
	inc	-12 (ix)
	jp	00309$
00184$:
;puzzmem.c:833: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:834: curseurBas=curseurBas+1;
	inc	-2 (ix)
;puzzmem.c:835: one_key=EN_BAS;
	ld	-14 (ix),#0x02
	jp	00271$
00194$:
;puzzmem.c:837: } else if (curseurBas < niveauNb) {
	ld	a,-2 (ix)
	sub	a, -8 (ix)
	jp	NC,00271$
;puzzmem.c:839: if (etatSelect==SELECT_ON) {
	ld	a,-3 (ix)
	dec	a
	jr	NZ,00189$
;puzzmem.c:840: if (select==CASE_VIDE) {
	ld	iy,#_select
	ld	a,0 (iy)
	sub	a, #0x12
	jp	NZ,00271$
;puzzmem.c:841: select=private_grille[niveauNb - 1][0];
	ld	l,-8 (ix)
	dec	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	a,(bc)
	ld	0 (iy),a
;puzzmem.c:842: private_grille[niveauNb - 1][0]=CASE_VIDE;
	ld	l,-8 (ix)
	dec	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	(hl),#0x12
;puzzmem.c:843: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:844: curseurBas=CURSEUR_BAS_SELECT;
	ld	-2 (ix),#0x31
;puzzmem.c:845: one_key=EN_BAS;
	ld	-14 (ix),#0x02
	jp	00271$
00189$:
;puzzmem.c:848: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:849: curseurBas=CURSEUR_BAS_SELECT;
	ld	-2 (ix),#0x31
;puzzmem.c:850: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:855: break;
	jp	00271$
;puzzmem.c:857: case TOUCHE_GAUCHE:
00201$:
;puzzmem.c:858: if (etatZone==EN_HAUT) {
	ld	a,-4 (ix)
	dec	a
	jr	NZ,00240$
;puzzmem.c:859: curseurHautOld=curseurHaut;
	ld	a,-1 (ix)
	ld	-6 (ix),a
;puzzmem.c:860: one_key=EN_HAUT;
	ld	-14 (ix),#0x01
;puzzmem.c:861: if (curseurHaut >=2) {
	ld	a,-1 (ix)
	sub	a, #0x02
	jr	C,00203$
;puzzmem.c:862: curseurHaut=curseurHaut-2;
	dec	-1 (ix)
	dec	-1 (ix)
	jp	00271$
00203$:
;puzzmem.c:864: curseurHaut=curseurHaut+16;
	ld	a,-1 (ix)
	add	a, #0x10
	ld	-1 (ix),a
	jp	00271$
00240$:
;puzzmem.c:867: if (curseurBas == CURSEUR_BAS_SELECT) {
	ld	a,-2 (ix)
	sub	a, #0x31
	jp	NZ,00237$
;puzzmem.c:868: if (etatSelect==SELECT_ON) {
	ld	a,-3 (ix)
	dec	a
	jp	NZ,00220$
;puzzmem.c:869: if (private_grille[niveauNb - 1][0]==CASE_VIDE) {
	ld	l,-8 (ix)
	dec	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	a,(bc)
	sub	a, #0x12
	jr	NZ,00217$
;puzzmem.c:870: private_grille[niveauNb - 1][0]=select;select=CASE_VIDE;
	ld	l,-8 (ix)
	dec	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	iy,#_select
	ld	a,0 (iy)
	ld	(bc),a
	ld	0 (iy),#0x12
;puzzmem.c:871: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:872: curseurBas=niveauNb - 1;
	ld	a,-8 (ix)
	add	a,#0xff
	ld	-2 (ix),a
;puzzmem.c:873: one_key=EN_BAS;
	ld	-14 (ix),#0x02
	jp	00271$
00217$:
;puzzmem.c:875: curseurBas=niveauNb - 1;
	ld	a,-8 (ix)
	add	a,#0xff
	ld	-2 (ix),a
;puzzmem.c:876: grille_x=curseurBas%niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	-10 (ix),l
;puzzmem.c:877: grille_y=curseurBas/niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__divuchar
	pop	af
	ld	-11 (ix),l
;puzzmem.c:879: if (grille_x>0) {
	ld	a,-10 (ix)
	or	a, a
	jp	Z,00271$
;puzzmem.c:880: for (p=grille_x;p>=0;) { // 0-1==0...
	ld	a,-10 (ix)
	ld	-12 (ix),a
00314$:
;puzzmem.c:881: if (private_grille[p][grille_y]==CASE_VIDE) {
	ld	c,-12 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	sub	a, #0x12
	jp	NZ,00209$
;puzzmem.c:882: for (pp=p;pp<grille_x;pp=pp+1) {
	ld	a,-12 (ix)
	ld	-13 (ix),a
00312$:
	ld	a,-13 (ix)
	sub	a, -10 (ix)
	jp	NC,00207$
;puzzmem.c:883: private_grille[pp][grille_y]=private_grille[pp+1][grille_y];
	ld	c,-13 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	l,-13 (ix)
	inc	l
	ld	e,l
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	ex	de,hl
	ld	hl,#_private_grille
	add	hl,de
	ex	de,hl
	ld	l,-11 (ix)
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	ld	(bc),a
;puzzmem.c:884: curseurBasOld=pp+grille_y*niveauNb;
	ld	e,-8 (ix)
	ld	h,-11 (ix)
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00733$:
	add	hl,hl
	jr	NC,00734$
	add	hl,de
00734$:
	djnz	00733$
	ld	c,l
	ld	a,-13 (ix)
	add	a, c
	ld	-7 (ix),a
;puzzmem.c:885: if (curseurBasOld!=niveauNb-1) {
	ld	c,-8 (ix)
	ld	b,#0x00
	dec	bc
	ld	a, -7 (ix)
	ld	h, #0x00
	sub	a, c
	jr	NZ,00735$
	ld	a,h
	sub	a, b
	jr	Z,00313$
00735$:
;puzzmem.c:886: fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-2 (ix)
	ld	l,-7 (ix)
	push	hl
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_grille)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
00313$:
;puzzmem.c:882: for (pp=p;pp<grille_x;pp=pp+1) {
	inc	-13 (ix)
	jp	00312$
00207$:
;puzzmem.c:889: private_grille[niveauNb - 1][0]=select;
	ld	l,-8 (ix)
	dec	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	iy,#_select
	ld	a,0 (iy)
	ld	(bc),a
;puzzmem.c:890: select=CASE_VIDE;
	ld	0 (iy),#0x12
;puzzmem.c:891: curseurBasOld=curseurBas; // leger
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:892: curseurBas=niveauNb - 1;
	ld	a,-8 (ix)
	add	a,#0xff
	ld	-2 (ix),a
;puzzmem.c:893: fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
	ld	a,-4 (ix)
	push	af
	inc	sp
	ld	d, -3 (ix)
	ld	e,#0x12
	push	de
	ld	h,-2 (ix)
	ld	l,-9 (ix)
	push	hl
	call	_fillSelect
	pop	af
	pop	af
	inc	sp
;puzzmem.c:894: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:895: break;
	jp	00271$
00209$:
;puzzmem.c:897: if (p==0) {
	ld	a,-12 (ix)
	or	a, a
	jp	Z,00271$
;puzzmem.c:900: p=p-1;
	dec	-12 (ix)
	jp	00314$
00220$:
;puzzmem.c:907: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:908: curseurBas = niveauNb - 1;
	ld	a,-8 (ix)
	add	a,#0xff
	ld	-2 (ix),a
;puzzmem.c:909: one_key=EN_BAS;
	ld	-14 (ix),#0x02
	jp	00271$
00237$:
;puzzmem.c:912: if (curseurBas % niveauNb > 0) {
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	a,l
	or	a, a
	jp	Z,00271$
;puzzmem.c:913: if (etatSelect==SELECT_ON) {
	ld	a,-3 (ix)
	dec	a
	jp	NZ,00232$
;puzzmem.c:914: grille_x=curseurBas%niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	-10 (ix),l
;puzzmem.c:915: grille_y=curseurBas/niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__divuchar
	pop	af
	ld	-11 (ix),l
;puzzmem.c:917: for (p=grille_x;p>=0;) { // 0-1==0...
	ld	a,-10 (ix)
	ld	-12 (ix),a
00320$:
;puzzmem.c:918: if (private_grille[p][grille_y]==CASE_VIDE) {
	ld	c,-12 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	sub	a, #0x12
	jp	NZ,00226$
;puzzmem.c:919: for (pp=p;pp<grille_x;pp=pp+1) {
	ld	a,-12 (ix)
	ld	-13 (ix),a
00318$:
	ld	a,-13 (ix)
	sub	a, -10 (ix)
	jp	NC,00224$
;puzzmem.c:920: private_grille[pp][grille_y]=private_grille[pp+1][grille_y];
	ld	c,-13 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	l,-13 (ix)
	inc	l
	ld	e,l
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, de
	ex	de,hl
	ld	hl,#_private_grille
	add	hl,de
	ex	de,hl
	ld	l,-11 (ix)
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	ld	(bc),a
;puzzmem.c:921: curseurBasOld=pp+grille_y*niveauNb;
	ld	e,-8 (ix)
	ld	h,-11 (ix)
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00740$:
	add	hl,hl
	jr	NC,00741$
	add	hl,de
00741$:
	djnz	00740$
	ld	c,l
	ld	a,-13 (ix)
	add	a, c
	ld	-7 (ix),a
;puzzmem.c:922: if (curseurBasOld!=curseurBas-1) {
	ld	c,-2 (ix)
	ld	b,#0x00
	dec	bc
	ld	a, -7 (ix)
	ld	h, #0x00
	sub	a, c
	jr	NZ,00742$
	ld	a,h
	sub	a, b
	jr	Z,00319$
00742$:
;puzzmem.c:923: fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-2 (ix)
	ld	l,-7 (ix)
	push	hl
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_grille)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
00319$:
;puzzmem.c:919: for (pp=p;pp<grille_x;pp=pp+1) {
	inc	-13 (ix)
	jp	00318$
00224$:
;puzzmem.c:926: private_grille[grille_x][grille_y]=CASE_VIDE;
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,#0x12
	ld	(bc),a
;puzzmem.c:927: curseurBasOld=curseurBas; // leger
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:928: curseurBas=curseurBas-1;
	dec	-2 (ix)
;puzzmem.c:929: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:930: break;
	jp	00271$
00226$:
;puzzmem.c:932: if (p==0) {
	ld	a,-12 (ix)
	or	a, a
	jp	Z,00271$
;puzzmem.c:935: p=p-1;
	dec	-12 (ix)
	jp	00320$
00232$:
;puzzmem.c:939: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:940: curseurBas=curseurBas-1;
	dec	-2 (ix)
;puzzmem.c:941: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:946: break;
	jp	00271$
;puzzmem.c:948: case TOUCHE_ESPACE:
00242$:
;puzzmem.c:949: one_key=EN_HAUT_ET_EN_BAS;
	ld	-14 (ix),#0x03
;puzzmem.c:950: if (etatZone==EN_HAUT) {
	ld	a,-4 (ix)
	dec	a
	jr	NZ,00251$
;puzzmem.c:951: etatZone=EN_BAS;
	ld	-4 (ix),#0x02
;puzzmem.c:952: if ((select==CASE_VIDE) && (nbPieces[curseurHaut]>0)) {
	ld	a,(#_select + 0)
	sub	a, #0x12
	jr	NZ,00247$
	ld	iy,#_nbPieces
	ld	a,0 (iy)
	add	a, -1 (ix)
	ld	c,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	or	a, a
	jr	Z,00247$
;puzzmem.c:953: select=curseurHaut;
	ld	a,-1 (ix)
	ld	(#_select + 0),a
;puzzmem.c:954: nbPieces[curseurHaut]=nbPieces[curseurHaut]-1;
	ld	iy,#_nbPieces
	ld	a,0 (iy)
	add	a, -1 (ix)
	ld	c,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	b,a
	ld	a,0 (iy)
	add	a, -1 (ix)
	ld	e,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	add	a,#0xff
	ld	(bc),a
;puzzmem.c:955: etatSelect=SELECT_ON;
	ld	-3 (ix),#0x01
	jr	00252$
00247$:
;puzzmem.c:956: } else if (select==CASE_VIDE) {
	ld	a,(#_select + 0)
	sub	a, #0x12
	jr	NZ,00244$
;puzzmem.c:957: etatSelect=SELECT_OFF;
	ld	-3 (ix),#0x00
	jr	00252$
00244$:
;puzzmem.c:959: etatSelect=SELECT_ON;
	ld	-3 (ix),#0x01
	jr	00252$
00251$:
;puzzmem.c:962: etatZone=EN_HAUT;
	ld	-4 (ix),#0x01
;puzzmem.c:963: etatSelect=SELECT_OFF;
	ld	-3 (ix),#0x00
00252$:
;puzzmem.c:965: curseurHautOld=curseurHaut;
	ld	a,-1 (ix)
	ld	-6 (ix),a
;puzzmem.c:966: curseurHaut=0;
	ld	-1 (ix),#0x00
;puzzmem.c:967: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:968: curseurBas=CURSEUR_BAS_SELECT;
	ld	-2 (ix),#0x31
;puzzmem.c:969: break;
	jp	00271$
;puzzmem.c:971: case TOUCHE_ENTREE:
00253$:
;puzzmem.c:972: if (etatSelect==SELECT_ON) {
	ld	a,-3 (ix)
	dec	a
	jr	NZ,00269$
;puzzmem.c:973: etatSelect=SELECT_OFF;
	ld	-3 (ix),#0x00
;puzzmem.c:974: one_key=etatZone; // EN_HAUT ou EN_BAS
	ld	a,-4 (ix)
	ld	-14 (ix),a
	jp	00271$
00269$:
;puzzmem.c:976: if (etatZone==EN_HAUT) {
	ld	a,-4 (ix)
	dec	a
	jp	NZ,00266$
;puzzmem.c:977: if (nbPieces[curseurHaut]>0) {
	ld	iy,#_nbPieces
	ld	a,0 (iy)
	add	a, -1 (ix)
	ld	c,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	or	a, a
	jp	Z,00271$
;puzzmem.c:978: etatZone=EN_BAS;
	ld	-4 (ix),#0x02
;puzzmem.c:979: if (select!=CASE_VIDE) {
	ld	a,(#_select + 0)
	sub	a, #0x12
	jr	Z,00255$
;puzzmem.c:980: nbPieces[select]=nbPieces[select]+1;
	ld	hl,#_select
	ld	iy,#_nbPieces
	ld	a,0 (iy)
	add	a, (hl)
	ld	c,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	inc	a
	ld	(bc),a
;puzzmem.c:981: fillListe1Piece(nbPieces,select,select,etatSelect,etatZone,0);
	xor	a, a
	push	af
	inc	sp
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	a,(_select)
	push	af
	inc	sp
	ld	a,(_select)
	push	af
	inc	sp
	ld	hl,(_nbPieces)
	push	hl
	call	_fillListe1Piece
	ld	hl,#7
	add	hl,sp
	ld	sp,hl
00255$:
;puzzmem.c:983: select=curseurHaut;
	ld	a,-1 (ix)
	ld	(#_select + 0),a
;puzzmem.c:984: nbPieces[curseurHaut]=nbPieces[curseurHaut]-1;
	ld	iy,#_nbPieces
	ld	a,0 (iy)
	add	a, -1 (ix)
	ld	c,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	b,a
	ld	a,0 (iy)
	add	a, -1 (ix)
	ld	e,a
	ld	a,1 (iy)
	adc	a, #0x00
	ld	d,a
	ld	a,(de)
	add	a,#0xff
	ld	(bc),a
;puzzmem.c:985: one_key=EN_HAUT_ET_EN_BAS; // le compteur décrémente, et select bouge
	ld	-14 (ix),#0x03
;puzzmem.c:986: etatSelect=SELECT_ON;
	ld	-3 (ix),#0x01
;puzzmem.c:987: curseurBasOld=curseurBas;
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:988: curseurBas=CURSEUR_BAS_SELECT;
	ld	-2 (ix),#0x31
	jr	00271$
00266$:
;puzzmem.c:991: if (curseurBas == CURSEUR_BAS_SELECT) {
	ld	a,-2 (ix)
	sub	a, #0x31
	jr	NZ,00263$
;puzzmem.c:992: if (select != CASE_VIDE) {
	ld	a,(#_select + 0)
	sub	a, #0x12
	jr	Z,00271$
;puzzmem.c:993: etatSelect=SELECT_ON;
	ld	-3 (ix),#0x01
;puzzmem.c:994: curseurBasOld=curseurBas; // cheeting
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:995: one_key=EN_BAS;
	ld	-14 (ix),#0x02
	jr	00271$
00263$:
;puzzmem.c:998: grille_x=curseurBas%niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__moduchar
	pop	af
	ld	-10 (ix),l
;puzzmem.c:999: grille_y=curseurBas/niveauNb;
	ld	h,-8 (ix)
	ld	l,-2 (ix)
	push	hl
	call	__divuchar
	pop	af
	ld	-11 (ix),l
;puzzmem.c:1000: if (private_grille[grille_x][grille_y] != CASE_VIDE) {
	ld	c,-10 (ix)
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, bc
	ld	bc,#_private_grille
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	l,-11 (ix)
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, #0x00
	ld	b,a
	ld	a,(bc)
	sub	a, #0x12
	jr	Z,00271$
;puzzmem.c:1001: etatSelect=SELECT_ON;
	ld	-3 (ix),#0x01
;puzzmem.c:1002: curseurBasOld=curseurBas; // cheeting
	ld	a,-2 (ix)
	ld	-7 (ix),a
;puzzmem.c:1003: one_key=EN_BAS;
	ld	-14 (ix),#0x02
;puzzmem.c:1009: }
00271$:
;puzzmem.c:1010: if (one_key!=0) {
	ld	a,-14 (ix)
	or	a, a
	jp	Z,00291$
;puzzmem.c:1013: if ((one_key==EN_HAUT) || (one_key==EN_HAUT_ET_EN_BAS)) {
	ld	a,-14 (ix)
	dec	a
	jr	Z,00274$
	ld	a,-14 (ix)
	sub	a, #0x03
	jr	NZ,00275$
00274$:
;puzzmem.c:1014: if (curseurHautOld!=curseurHaut) {
	ld	a,-6 (ix)
	sub	a, -1 (ix)
	jr	Z,00273$
;puzzmem.c:1015: fillListe1Piece(nbPieces,curseurHautOld,curseurHaut,etatSelect,etatZone,0);
	xor	a, a
	push	af
	inc	sp
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-1 (ix)
	ld	l,-6 (ix)
	push	hl
	ld	hl,(_nbPieces)
	push	hl
	call	_fillListe1Piece
	ld	hl,#7
	add	hl,sp
	ld	sp,hl
00273$:
;puzzmem.c:1017: fillListe1Piece(nbPieces,curseurHaut,curseurHaut,etatSelect,etatZone,0);
	xor	a, a
	push	af
	inc	sp
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-1 (ix)
	ld	l,-1 (ix)
	push	hl
	ld	hl,(_nbPieces)
	push	hl
	call	_fillListe1Piece
	ld	hl,#7
	add	hl,sp
	ld	sp,hl
00275$:
;puzzmem.c:1019: if ((one_key==EN_BAS) || (one_key==EN_HAUT_ET_EN_BAS)) {
	ld	a,-14 (ix)
	sub	a, #0x02
	jr	Z,00285$
	ld	a,-14 (ix)
	sub	a, #0x03
	jp	NZ,00291$
00285$:
;puzzmem.c:1020: if (curseurBasOld!=curseurBas) {
	ld	a,-7 (ix)
	sub	a, -2 (ix)
	jr	Z,00281$
;puzzmem.c:1021: if (curseurBasOld==CURSEUR_BAS_SELECT) {
	ld	a,-7 (ix)
	sub	a, #0x31
	jr	NZ,00278$
;puzzmem.c:1022: fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	a,(_select)
	push	af
	inc	sp
	ld	h,-2 (ix)
	ld	l,-9 (ix)
	push	hl
	call	_fillSelect
	pop	af
	pop	af
	inc	sp
	jr	00281$
00278$:
;puzzmem.c:1024: fill1Grille(grille,niveauTaille,niveauNb,curseurBasOld,curseurBas,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-2 (ix)
	ld	l,-7 (ix)
	push	hl
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_grille)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
00281$:
;puzzmem.c:1027: if (curseurBas==CURSEUR_BAS_SELECT) {
	ld	a,-2 (ix)
	sub	a, #0x31
	jr	NZ,00283$
;puzzmem.c:1028: fillSelect(niveauTaille,curseurBas,select,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	a,(_select)
	push	af
	inc	sp
	ld	h,-2 (ix)
	ld	l,-9 (ix)
	push	hl
	call	_fillSelect
	pop	af
	pop	af
	inc	sp
	jp	00291$
00283$:
;puzzmem.c:1030: fill1Grille(grille,niveauTaille,niveauNb,curseurBas,curseurBas,etatSelect,etatZone);
	ld	h,-4 (ix)
	ld	l,-3 (ix)
	push	hl
	ld	h,-2 (ix)
	ld	l,-2 (ix)
	push	hl
	ld	h,-8 (ix)
	ld	l,-9 (ix)
	push	hl
	ld	hl,(_grille)
	push	hl
	call	_fill1Grille
	ld	hl,#8
	add	hl,sp
	ld	sp,hl
	jp	00291$
_puzzmem_palette:
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x1a	; 26
	.db #0x02	; 2
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
