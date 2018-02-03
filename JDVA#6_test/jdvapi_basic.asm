;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module jdvapi_basic
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _put_pixel_byte1
	.globl _put_pixel1
	.globl _set_pixel_color1
	.globl _copy_pixel0bytes
	.globl _put_pixel0
	.globl _set_pixel_color0
	.globl _line
	.globl _move
	.globl _plot
	.globl _mode
	.globl _set_palette
	.globl _border
	.globl _set_color
	.globl _locate
	.globl _pen
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
;jdvapi_basic.c:3: void pen(unsigned char p)
;	---------------------------------
; Function pen
; ---------------------------------
_pen::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:8: __endasm;
	ld	A,4 (IX)
	call	#0xBBDE
	pop	ix
	ret
;jdvapi_basic.c:11: void locate(unsigned char x,unsigned char y)
;	---------------------------------
; Function locate
; ---------------------------------
_locate::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:18: __endasm;
	ld	A,4 (IX)
	call	#0xBB6F
	ld	A,5 (IX)
	call	#0xBB72
	pop	ix
	ret
;jdvapi_basic.c:21: void set_color(unsigned char nColorIndex, unsigned char nPaletteIndex)
;	---------------------------------
; Function set_color
; ---------------------------------
_set_color::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:28: __endasm;
	ld	a, 4 (ix)
	ld	b, 5 (ix)
	ld	c, b
	call	#0xBC32 ;SCR SET INK
	pop	ix
	ret
;jdvapi_basic.c:31: void border(unsigned char nColorIndex)
;	---------------------------------
; Function border
; ---------------------------------
_border::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:37: __endasm;
	ld	b, 4 (ix)
	ld	c, b
	call	#0xBC38 ;SCR SET INK
	pop	ix
	ret
;jdvapi_basic.c:40: void set_palette(unsigned char *pPalette)
;	---------------------------------
; Function set_palette
; ---------------------------------
_set_palette::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:44: for(nColor = 0; nColor < 16; nColor++)
	ld	c,#0x00
00102$:
;jdvapi_basic.c:45: set_color(nColor, pPalette[nColor]);
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
	call	_set_color
	pop	af
	pop	bc
;jdvapi_basic.c:44: for(nColor = 0; nColor < 16; nColor++)
	inc	c
	ld	a,c
	sub	a, #0x10
	jr	C,00102$
	pop	ix
	ret
;jdvapi_basic.c:53: void mode(unsigned char m)
;	---------------------------------
; Function mode
; ---------------------------------
_mode::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:58: __endasm;
	ld	A,4 (IX)
	call	#0xBC0E
	pop	ix
	ret
;jdvapi_basic.c:65: void plot(unsigned int x,unsigned int y)
;	---------------------------------
; Function plot
; ---------------------------------
_plot::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:75: __endasm;
	ld	E,4 (IX)
	ld	D,5 (IX)
	ld	L,6 (IX)
	ld	H,7 (IX)
	call	#0xBBEA
	pop	ix
	ret
;jdvapi_basic.c:78: void move(unsigned int x,unsigned int y)
;	---------------------------------
; Function move
; ---------------------------------
_move::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:88: __endasm;
	ld	E,4 (IX)
	ld	D,5 (IX)
	ld	L,6 (IX)
	ld	H,7 (IX)
	call	#0xBBC0
	pop	ix
	ret
;jdvapi_basic.c:91: void line(unsigned int x,unsigned int y)
;	---------------------------------
; Function line
; ---------------------------------
_line::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:101: __endasm;
	ld	E,4 (IX)
	ld	D,5 (IX)
	ld	L,6 (IX)
	ld	H,7 (IX)
	call	#0xBBF6
	pop	ix
	ret
;jdvapi_basic.c:127: void set_pixel_color0(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
;	---------------------------------
; Function set_pixel_color0
; ---------------------------------
_set_pixel_color0::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;jdvapi_basic.c:129: unsigned char nByte = *pByteAddress;
	ld	l,4 (ix)
	ld	h,5 (ix)
	ld	a,(hl)
	ld	-2 (ix),a
;jdvapi_basic.c:145: if (nColor & 1) nByte |=128;
	ld	a,6 (ix)
	and	a, #0x01
	ld	b,a
;jdvapi_basic.c:146: if (nColor & 2) nByte |=8;
	ld	a,6 (ix)
	and	a, #0x02
	ld	e,a
;jdvapi_basic.c:147: if (nColor & 4) nByte |=32;
	ld	a,6 (ix)
	and	a, #0x04
	ld	d,a
;jdvapi_basic.c:148: if (nColor & 8) nByte |=2;
	ld	a,6 (ix)
	and	a, #0x08
	ld	-1 (ix),a
;jdvapi_basic.c:130: if (nPixel == 0) {
	ld	a,7 (ix)
	or	a, a
	jr	NZ,00118$
;jdvapi_basic.c:131: nByte&=85; // nByte = nByte & 85
	ld	a,-2 (ix)
	and	a, #0x55
	ld	c,a
;jdvapi_basic.c:145: if (nColor & 1) nByte |=128;
	ld	a,b
	or	a, a
	jr	Z,00102$
	set	7, c
00102$:
;jdvapi_basic.c:146: if (nColor & 2) nByte |=8;
	ld	a,e
	or	a, a
	jr	Z,00104$
	set	3, c
00104$:
;jdvapi_basic.c:147: if (nColor & 4) nByte |=32;
	ld	a,d
	or	a, a
	jr	Z,00106$
	set	5, c
00106$:
;jdvapi_basic.c:148: if (nColor & 8) nByte |=2;
	ld	a,-1 (ix)
	or	a, a
	jr	Z,00119$
	set	1, c
	jr	00119$
00118$:
;jdvapi_basic.c:150: nByte&=170;
	ld	a,-2 (ix)
	and	a, #0xaa
	ld	c,a
;jdvapi_basic.c:151: if (nColor & 1) nByte |=64;
	ld	a,b
	or	a, a
	jr	Z,00110$
	set	6, c
00110$:
;jdvapi_basic.c:152: if (nColor & 2) nByte |=4;
	ld	a,e
	or	a, a
	jr	Z,00112$
	set	2, c
00112$:
;jdvapi_basic.c:153: if (nColor & 4) nByte |=16;
	ld	a,d
	or	a, a
	jr	Z,00114$
	set	4, c
00114$:
;jdvapi_basic.c:154: if (nColor & 8) nByte |=1;
	ld	a,-1 (ix)
	or	a, a
	jr	Z,00119$
	set	0, c
00119$:
;jdvapi_basic.c:156: *pByteAddress = nByte;
	ld	(hl),c
	ld	sp, ix
	pop	ix
	ret
;jdvapi_basic.c:160: void put_pixel0(unsigned char nX, unsigned char nY, unsigned char nColor)
;	---------------------------------
; Function put_pixel0
; ---------------------------------
_put_pixel0::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:163: unsigned int nAddress = 0xC000 + ((nY / 8) * 80) + ((nY % 8) * 2048) + (nX / 2);
	ld	l,5 (ix)
	srl	l
	srl	l
	srl	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	a,h
	add	a,#0xc0
	ld	b,a
	ld	a,5 (ix)
	and	a, #0x07
	rlca
	rlca
	rlca
	and	a,#0xf8
	ld	h,a
	ld	l,#0x00
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, h
	ld	b,a
	ld	l,4 (ix)
	srl	l
	ld	h,#0x00
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, h
	ld	b,a
	ld	l, c
	ld	h, b
;jdvapi_basic.c:164: nPixel = nX % 2;
	ld	a,4 (ix)
	and	a, #0x01
	ld	c,a
;jdvapi_basic.c:165: set_pixel_color0((unsigned char *)nAddress, nColor, nPixel);
	ex	de,hl
	ld	a,c
	push	af
	inc	sp
	ld	a,6 (ix)
	push	af
	inc	sp
	push	de
	call	_set_pixel_color0
	pop	af
	pop	af
	pop	ix
	ret
;jdvapi_basic.c:183: void copy_pixel0bytes(unsigned char nXFrom, unsigned char nYFrom,unsigned char nXTo, unsigned char nYTo, unsigned char tailleX, unsigned char tailleY)
;	---------------------------------
; Function copy_pixel0bytes
; ---------------------------------
_copy_pixel0bytes::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
;jdvapi_basic.c:186: unsigned char * pByteAddressFrom = 0xC000 + ((nYFrom / 8) * 80) + ((nYFrom % 8) * 2048) + (nXFrom / 2);
	ld	l,5 (ix)
	srl	l
	srl	l
	srl	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	a,h
	add	a,#0xc0
	ld	b,a
	ld	a,5 (ix)
	and	a, #0x07
	rlca
	rlca
	rlca
	and	a,#0xf8
	ld	h,a
	ld	l,#0x00
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, h
	ld	b,a
	ld	l,4 (ix)
	srl	l
	ld	h,#0x00
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, h
	ld	-2 (ix), c
	ld	-1 (ix), a
;jdvapi_basic.c:187: unsigned char * pByteAddressTo = 0xC000 + ((nYTo / 8) * 80) + ((nYTo % 8) * 2048) + (nXTo / 2);
	ld	l,7 (ix)
	srl	l
	srl	l
	srl	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	e, l
	ld	a,h
	add	a,#0xc0
	ld	d,a
	ld	a,7 (ix)
	and	a, #0x07
	rlca
	rlca
	rlca
	and	a,#0xf8
	ld	h,a
	ld	l,#0x00
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, h
	ld	d,a
	ld	l,6 (ix)
	srl	l
	ld	h,#0x00
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, h
	ld	d,a
	inc	sp
	inc	sp
	push	de
;jdvapi_basic.c:188: for (x=0;x<tailleX/2;x++) {
	ld	e,8 (ix)
	srl	e
	ld	d,#0x00
00107$:
	ld	a,d
	sub	a, e
	jr	NC,00109$
;jdvapi_basic.c:189: for (y=0;y<tailleY;y++) {
	ld	c,#0x00
00104$:
	ld	a,c
	sub	a, 9 (ix)
	jr	NC,00108$
;jdvapi_basic.c:190: *pByteAddressTo=*pByteAddressFrom;
	ld	l,-2 (ix)
	ld	h,-1 (ix)
	ld	a,(hl)
	pop	hl
	push	hl
	ld	(hl),a
;jdvapi_basic.c:189: for (y=0;y<tailleY;y++) {
	inc	c
	jr	00104$
00108$:
;jdvapi_basic.c:188: for (x=0;x<tailleX/2;x++) {
	inc	d
	jr	00107$
00109$:
	ld	sp, ix
	pop	ix
	ret
;jdvapi_basic.c:195: void set_pixel_color1(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
;	---------------------------------
; Function set_pixel_color1
; ---------------------------------
_set_pixel_color1::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:197: unsigned char nByte = *pByteAddress;
	ld	l,4 (ix)
	ld	h,5 (ix)
	ld	c,(hl)
;jdvapi_basic.c:200: if (nColor & 1) nByte |=128; //1000 0000
	ld	a,6 (ix)
	and	a, #0x01
	ld	b,a
;jdvapi_basic.c:201: if (nColor & 2) nByte |=8;   //0000 1000
	ld	a,6 (ix)
	and	a, #0x02
	ld	e,a
;jdvapi_basic.c:198: if (nPixel == 0) {
	ld	a,7 (ix)
	or	a, a
	jr	NZ,00124$
;jdvapi_basic.c:199: nByte&=119;                  //0111 0111
	ld	a,c
	and	a, #0x77
	ld	d,a
;jdvapi_basic.c:200: if (nColor & 1) nByte |=128; //1000 0000
	ld	a,b
	or	a, a
	jr	Z,00102$
	set	7, d
00102$:
;jdvapi_basic.c:201: if (nColor & 2) nByte |=8;   //0000 1000
	ld	a,e
	or	a, a
	jr	Z,00125$
	set	3, d
	jr	00125$
00124$:
;jdvapi_basic.c:202: } else if (nPixel == 1) {
	ld	a,7 (ix)
	dec	a
	jr	NZ,00121$
;jdvapi_basic.c:203: nByte&=187;                  //1011 1011
	ld	a,c
	and	a, #0xbb
	ld	d,a
;jdvapi_basic.c:204: if (nColor & 1) nByte |=64;  //0100 0000
	ld	a,b
	or	a, a
	jr	Z,00106$
	set	6, d
00106$:
;jdvapi_basic.c:205: if (nColor & 2) nByte |=4;   //0000 0100
	ld	a,e
	or	a, a
	jr	Z,00125$
	set	2, d
	jr	00125$
00121$:
;jdvapi_basic.c:206: } else if (nPixel == 2) {
	ld	a,7 (ix)
	sub	a, #0x02
	jr	NZ,00118$
;jdvapi_basic.c:207: nByte&=221;                  //1101 1101
	ld	a,c
	and	a, #0xdd
	ld	d,a
;jdvapi_basic.c:208: if (nColor & 1) nByte |=32;  //0010 0000
	ld	a,b
	or	a, a
	jr	Z,00110$
	set	5, d
00110$:
;jdvapi_basic.c:209: if (nColor & 2) nByte |=2;   //0000 0010
	ld	a,e
	or	a, a
	jr	Z,00125$
	set	1, d
	jr	00125$
00118$:
;jdvapi_basic.c:211: nByte&=238;                  //1110 1110
	ld	a,c
	and	a, #0xee
	ld	d,a
;jdvapi_basic.c:212: if (nColor & 1) nByte |=16;  //0001 0000
	ld	a,b
	or	a, a
	jr	Z,00114$
	set	4, d
00114$:
;jdvapi_basic.c:213: if (nColor & 2) nByte |=1;   //0000 0001
	ld	a,e
	or	a, a
	jr	Z,00125$
	set	0, d
00125$:
;jdvapi_basic.c:216: *pByteAddress = nByte;
	ld	(hl),d
	pop	ix
	ret
;jdvapi_basic.c:220: void put_pixel1(unsigned char nX, unsigned char nY, unsigned char nColor)
;	---------------------------------
; Function put_pixel1
; ---------------------------------
_put_pixel1::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:223: unsigned int nAddress = 0xC000 + ((nY / 8) * 80) + ((nY % 8) * 2048) + (nX / 4);
	ld	l,5 (ix)
	srl	l
	srl	l
	srl	l
	ld	c,l
	ld	b,#0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	a,h
	add	a,#0xc0
	ld	b,a
	ld	a,5 (ix)
	and	a, #0x07
	rlca
	rlca
	rlca
	and	a,#0xf8
	ld	h,a
	ld	l,#0x00
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, h
	ld	b,a
	ld	l,4 (ix)
	srl	l
	srl	l
	ld	h,#0x00
	ld	a,c
	add	a, l
	ld	c,a
	ld	a,b
	adc	a, h
	ld	b,a
	ld	l, c
	ld	h, b
;jdvapi_basic.c:224: nPixel = nX % 4;
	ld	a,4 (ix)
	and	a, #0x03
	ld	c,a
;jdvapi_basic.c:225: set_pixel_color1((unsigned char *)nAddress, nColor, nPixel);
	ex	de,hl
	ld	a,c
	push	af
	inc	sp
	ld	a,6 (ix)
	push	af
	inc	sp
	push	de
	call	_set_pixel_color1
	pop	af
	pop	af
	pop	ix
	ret
;jdvapi_basic.c:246: void put_pixel_byte1(unsigned char nX, unsigned char nY, unsigned char nColor0123)
;	---------------------------------
; Function put_pixel_byte1
; ---------------------------------
_put_pixel_byte1::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_basic.c:248: unsigned char nByte=0;
	ld	c,#0x00
;jdvapi_basic.c:249: unsigned char * pByteAddress = 0xC000 + ((nY / 8) * 80) + ((nY % 8) * 2048) + (nX / 4);
	ld	l,5 (ix)
	srl	l
	srl	l
	srl	l
	ld	e,l
	ld	d,#0x00
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	e, l
	ld	a,h
	add	a,#0xc0
	ld	d,a
	ld	a,5 (ix)
	and	a, #0x07
	rlca
	rlca
	rlca
	and	a,#0xf8
	ld	h,a
	ld	l,#0x00
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, h
	ld	d,a
	ld	l,4 (ix)
	srl	l
	srl	l
	ld	h,#0x00
	ld	a,e
	add	a, l
	ld	e,a
	ld	a,d
	adc	a, h
	ld	d,a
;jdvapi_basic.c:250: switch(nColor0123) {
	ld	a,#0x03
	sub	a, 6 (ix)
	jr	C,00105$
	push	de
	ld	e,6 (ix)
	ld	d,#0x00
	ld	hl,#00112$
	add	hl,de
	add	hl,de
;jdvapi_basic.c:251: case 0 :
	pop	de
	jp	(hl)
00112$:
	jr	00101$
	jr	00102$
	jr	00103$
	jr	00104$
00101$:
;jdvapi_basic.c:252: nByte=0;
	ld	c,#0x00
;jdvapi_basic.c:253: break;
	jr	00105$
;jdvapi_basic.c:254: case 1 :
00102$:
;jdvapi_basic.c:255: nByte=240;
	ld	c,#0xf0
;jdvapi_basic.c:256: break;
	jr	00105$
;jdvapi_basic.c:257: case 2 :
00103$:
;jdvapi_basic.c:258: nByte=15;
	ld	c,#0x0f
;jdvapi_basic.c:259: break;
	jr	00105$
;jdvapi_basic.c:260: case 3 :
00104$:
;jdvapi_basic.c:261: nByte=255;
	ld	c,#0xff
;jdvapi_basic.c:263: }
00105$:
;jdvapi_basic.c:265: *pByteAddress = nByte;
	ld	a,c
	ld	(de),a
	pop	ix
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
