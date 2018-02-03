;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW32)
;--------------------------------------------------------
	.module jdvapi_frame
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _precalc_vram
	.globl _erase_frame
	.globl _put_frame_transparent
	.globl _put_frame
	.globl _private_precalc_vram
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_private_precalc_vram::
	.ds 400
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
;jdvapi_frame.c:2: void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image)
;	---------------------------------
; Function put_frame
; ---------------------------------
_put_frame::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_frame.c:34: __endasm;
	LD	L, 4(IX) ; HL --> Adr destination
	LD	H, 5(IX)
	LD	C, 6(IX) ; C --> Largeur en octet
	LD	B, 7(IX) ; B --> Hauteur
	LD	E, 8(IX) ; DE --> Adresse image source.
	LD	D, 9(IX)
	    _loop_alto000:
	PUSH	BC ; Sauvegarde de BC sur la pile (width et height)
	LD	B,C ; Charge C (width) dans B
	PUSH	HL ; Sauvegarde de HL (adresse de la destination)
	    _loop_ancho000:
	LD	A,(DE) ; Met dans A un octet de de la source
	LD	(HL),A ; Met dans la destination A
	INC	DE ; Avance dans l'adresse de la source
	INC	HL ; Avance dans l'adresse de la destination
	DJNZ	_loop_ancho000 ; Décrémente B qui contient la largeur. Si on à pas finit de copier
;	l'équivalent de la largeur on saute à _loop_ancho.
	POP	HL ; récupère l'adresse de la cible sauvegardé sur la pile
	LD	A,H ; Charge la partie haute dans A
	ADD	#0x08 ; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
	LD	H,A ; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
	SUB	#0xC0 ; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
	JP	NC, _sig_linea000 ; Non, elle est à la suite en mémoire donc tout va bien
	LD	BC, #0xC050 ; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
	ADD	HL,BC ; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
	    _sig_linea000:
	POP	BC ; Récupère BC --> pour récupérer la hauteur
	DJNZ	_loop_alto000 ; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
	pop	ix
	ret
;jdvapi_frame.c:37: void put_frame_transparent(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image)
;	---------------------------------
; Function put_frame_transparent
; ---------------------------------
_put_frame_transparent::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_frame.c:70: __endasm;
	LD	L, 4(IX) ; HL --> Adr destination
	LD	H, 5(IX)
	LD	C, 6(IX) ; C --> Largeur en octet
	LD	B, 7(IX) ; B --> Hauteur
	LD	E, 8(IX) ; DE --> Adresse image source.
	LD	D, 9(IX)
	    _loop_alto001:
	PUSH	BC ; Sauvegarde de BC sur la pile (width et height)
	LD	B,C ; Charge C (width) dans B
	PUSH	HL ; Sauvegarde de HL (adresse de la destination)
	    _loop_ancho001:
	LD	A,(DE) ; Met dans A un octet de de la source
	OR	A,(HL) ; OR A un octet de de la destination
	LD	(HL),A ; Met dans la destination A
	INC	DE ; Avance dans l'adresse de la source
	INC	HL ; Avance dans l'adresse de la destination
	DJNZ	_loop_ancho001 ; Décrémente B qui contient la largeur. Si on à pas finit de copier
;	l'équivalent de la largeur on saute à _loop_ancho.
	POP	HL ; récupère l'adresse de la cible sauvegardé sur la pile
	LD	A,H ; Charge la partie haute dans A
	ADD	#0x08 ; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
	LD	H,A ; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
	SUB	#0xC0 ; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
	JP	NC, _sig_linea001 ; Non, elle est à la suite en mémoire donc tout va bien
	LD	BC, #0xC050 ; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
	ADD	HL,BC ; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
	    _sig_linea001:
	POP	BC ; Récupère BC --> pour récupérer la hauteur
	DJNZ	_loop_alto001 ; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
	pop	ix
	ret
;jdvapi_frame.c:73: void erase_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight)
;	---------------------------------
; Function erase_frame
; ---------------------------------
_erase_frame::
	push	ix
	ld	ix,#0
	add	ix,sp
;jdvapi_frame.c:101: __endasm;
	LD	L, 4(IX) ; HL --> Adr destination
	LD	H, 5(IX)
	LD	C, 6(IX) ; C --> Largeur en octet
	LD	B, 7(IX) ; B --> Hauteur
	    _loop_alto002:
	PUSH	BC ; Sauvegarde de BC sur la pile (width et height)
	LD	B,C ; Charge C (width) dans B
	PUSH	HL ; Sauvegarde de HL (adresse de la destination)
	    _loop_ancho002:
	LD	(HL),#0x00 ; Met 0x00 dans la destination A
	INC	HL ; Avance dans l'adresse de la destination
	DJNZ	_loop_ancho002 ; Décrémente B qui contient la largeur. Si on à pas finit de copier
;	l'équivalent de la largeur on saute à _loop_ancho.
	POP	HL ; récupère l'adresse de la cible sauvegardé sur la pile
	LD	A,H ; Charge la partie haute dans A
	ADD	#0x08 ; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
	LD	H,A ; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
	SUB	#0xC0 ; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
	JP	NC, _sig_linea002 ; Non, elle est à la suite en mémoire donc tout va bien
	LD	BC, #0xC050 ; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
	ADD	HL,BC ; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
	    _sig_linea002:
	POP	BC ; Récupère BC --> pour récupérer la hauteur
	DJNZ	_loop_alto002 ; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
	pop	ix
	ret
;jdvapi_frame.c:109: unsigned int * precalc_vram()
;	---------------------------------
; Function precalc_vram
; ---------------------------------
_precalc_vram::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	dec	sp
;jdvapi_frame.c:113: for (i=0;i<200;i++)
	ld	-3 (ix),#0x00
00102$:
;jdvapi_frame.c:115: private_precalc_vram[i]=(0xC000 + ((i / 8u) * 80u) + ((i % 8u) * 2048u));		
	ld	l,-3 (ix)
	ld	h,#0x00
	add	hl, hl
	ld	a,#<(_private_precalc_vram)
	add	a, l
	ld	-2 (ix),a
	ld	a,#>(_private_precalc_vram)
	adc	a, h
	ld	-1 (ix),a
	ld	c,-3 (ix)
	ld	b,#0x00
	ld	e, c
	ld	d, b
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ex	de,hl
	ld	hl,#0xc000
	add	hl,de
	ex	de,hl
	ld	a,c
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
	ld	l,-2 (ix)
	ld	h,-1 (ix)
	ld	(hl),e
	inc	hl
	ld	(hl),d
;jdvapi_frame.c:113: for (i=0;i<200;i++)
	inc	-3 (ix)
	ld	a,-3 (ix)
	sub	a, #0xc8
	jr	C,00102$
;jdvapi_frame.c:119: return (unsigned int *)private_precalc_vram;
	ld	hl,#_private_precalc_vram
	ld	sp, ix
	pop	ix
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
