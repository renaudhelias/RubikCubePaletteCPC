;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module jdvapi_sync
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _scan
	.globl _overscan
	.globl _scroll
	.globl _bank7_4000
	.globl _bank6_4000
	.globl _bank5_4000
	.globl _bank4_4000
	.globl _bank7_C000
	.globl _bank0123
	.globl _calque4C00
	.globl _calque4000
	.globl _calqueC000
	.globl _vsync
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
;jdvapi_sync.c:2: void vsync()
;	---------------------------------
; Function vsync
; ---------------------------------
_vsync::
;jdvapi_sync.c:12: __endasm;
	ld	b,#0xf5 ;; PPI port B input
	    _wait_vsync:
	in	a,(c) ;; [4] read PPI port B input
;;	(bit 0 = "1" if vsync is active,
;;	or bit 0 = "0" if vsync is in-active)
	rra	;; [1] put bit 0 into carry flag
	jp	nc,_wait_vsync ;; [3] if carry not set, loop, otherwise continue
	ret
;jdvapi_sync.c:15: void calqueC000()
;	---------------------------------
; Function calqueC000
; ---------------------------------
_calqueC000::
;jdvapi_sync.c:22: __endasm;
	ld	bc,#0xBC00+12 ; On met la valeur 48 dans
	out	(c),c ; le registre 12 du CRTC
	ld	bc,#0xBD00+48
	out	(c),c
	ret
;jdvapi_sync.c:25: void calque4000()
;	---------------------------------
; Function calque4000
; ---------------------------------
_calque4000::
;jdvapi_sync.c:32: __endasm;
	ld	bc,#0xBC00+12 ; On met la valeur 16 dans
	out	(c),c ; le registre 12 du CRTC
	ld	bc,#0xBD00+16
	out	(c),c
	ret
;jdvapi_sync.c:35: void calque4C00()
;	---------------------------------
; Function calque4C00
; ---------------------------------
_calque4C00::
;jdvapi_sync.c:42: __endasm;
	ld	bc,#0xBC00+12 ; On met la valeur 28 dans
	out	(c),c ; le registre 12 du CRTC
	ld	bc,#0xBD00+28
	out	(c),c
	ret
;jdvapi_sync.c:45: void bank0123()
;	---------------------------------
; Function bank0123
; ---------------------------------
_bank0123::
;jdvapi_sync.c:50: __endasm;
	ld	bc,#0x7FC0+0 ; RAM rétablie
	out	(c),c
	ret
;jdvapi_sync.c:53: void bank7_C000()
;	---------------------------------
; Function bank7_C000
; ---------------------------------
_bank7_C000::
;jdvapi_sync.c:58: __endasm;
	ld	bc,#0x7FC0+1 ; RAM_7 sur &C000-&FFFF
	out	(c),c
	ret
;jdvapi_sync.c:61: void bank4_4000()
;	---------------------------------
; Function bank4_4000
; ---------------------------------
_bank4_4000::
;jdvapi_sync.c:66: __endasm;
	ld	bc,#0x7FC0+4 ; RAM_4 sur &4000-&7FFF
	out	(c),c
	ret
;jdvapi_sync.c:69: void bank5_4000()
;	---------------------------------
; Function bank5_4000
; ---------------------------------
_bank5_4000::
;jdvapi_sync.c:74: __endasm;
	ld	bc,#0x7FC0+5 ; RAM_5 sur &4000-&7FFF
	out	(c),c
	ret
;jdvapi_sync.c:77: void bank6_4000()
;	---------------------------------
; Function bank6_4000
; ---------------------------------
_bank6_4000::
;jdvapi_sync.c:82: __endasm;
	ld	bc,#0x7FC0+6 ; RAM_6 sur &4000-&7FFF
	out	(c),c
	ret
;jdvapi_sync.c:85: void bank7_4000()
;	---------------------------------
; Function bank7_4000
; ---------------------------------
_bank7_4000::
;jdvapi_sync.c:90: __endasm;
	ld	bc,#0x7FC0+7 ; RAM_7 sur &4000-&7FFF
	out	(c),c
	ret
;jdvapi_sync.c:93: void scroll(unsigned char h)
;	---------------------------------
; Function scroll
; ---------------------------------
_scroll::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_sync.c:102: __endasm;
	ld	A,4 (IX)
	ld	bc,#0xBC00+12
	out	(c),c
	ld	b,#0xBD
	ld	c,A
	out	(c),c
	pop	ix
	ret
;jdvapi_sync.c:105: void overscan()
;	---------------------------------
; Function overscan
; ---------------------------------
_overscan::
;jdvapi_sync.c:124: __endasm;
	ld	bc,#0xBC00+1 ; On met la valeur 48 dans
	out	(c),c ; le registre 1 du CRTC -- RHdisp
	ld	bc,#0xBD00+48
	out	(c),c
	ld	bc,#0xBC00+2 ; On met la valeur 50 dans
	out	(c),c ; le registre 2 du CRTC -- RHsyncpos
	ld	bc,#0xBD00+50
	out	(c),c
	ld	bc,#0xBC00+6 ; On met la valeur 34 dans
	out	(c),c ; le registre 6 du CRTC -- RVdisp
	ld	bc,#0xBD00+34
	out	(c),c
	ld	bc,#0xBC00+7 ; On met la valeur 35 dans
	out	(c),c ; le registre 7 du CRTC -- RVsyncpos
	ld	bc,#0xBD00+35
	out	(c),c
	ret
;jdvapi_sync.c:127: void scan()
;	---------------------------------
; Function scan
; ---------------------------------
_scan::
;jdvapi_sync.c:146: __endasm;
	ld	bc,#0xBC00+1 ; On remet la valeur 40 dans
	out	(c),c ; le registre 1 du CRTC -- RHdisp
	ld	bc,#0xBD00+40
	out	(c),c
	ld	bc,#0xBC00+2 ; On remet la valeur 46 dans
	out	(c),c ; le registre 2 du CRTC -- RHsyncpos
	ld	bc,#0xBD00+46
	out	(c),c
	ld	bc,#0xBC00+6 ; On remet la valeur 25 dans
	out	(c),c ; le registre 6 du CRTC -- RVdisp
	ld	bc,#0xBD00+25
	out	(c),c
	ld	bc,#0xBC00+7 ; On remet la valeur 30 dans
	out	(c),c ; le registre 7 du CRTC -- RVsyncpos
	ld	bc,#0xBD00+30
	out	(c),c
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
