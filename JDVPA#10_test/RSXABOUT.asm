org #c000
             defb #01           ; ; bg ROM
             defb #03,#02,#01    ; Version 1.00
             defw RSX_TABLE      ; Adresses des noms des Commandes externes
             JP INIT_AZERTY      ; Adresse d'execution lors du demarrage
             jp ABOUT
			 jp BORDER
			 jp SET_COLOR
			 jp MODE
RSX_TABLE:
             defb "RENAU","D"+#80
             defb "ABOU","T"+#80
			 defb "BORDE","R"+#80
			 defb "SETCOLO","R"+#80
			 defb "MOD","E"+#80
             defb 0 ; FIN
INIT_AZERTY:
             push hl
             PUSH DE
             call ABOUT
             pop DE
             pop hl
AND A
LD BC,32:SBC HL,BC ;grab 32 bytes from top of memory
SCF
             ret
ABOUT:
             ld hl,ABOUT_TEXT1
textout:
             ld a,(hl)
             call #BB5A
             inc hl
             or a
             jr nz,textout
             ret

BORDER: ; void border(unsigned char nColorIndex)
    ;ld b, 4 (ix)
	ld b, (ix+0)
    ld c, b
    call #BC38 ;SCR SET INK
ret
SET_COLOR: ; void set_color(unsigned char nColorIndex, unsigned char nPaletteIndex)
    ld a, (ix+0)
    ld b, (ix+2)
    ld c, b
    call #BC32 ;SCR SET INK
ret
MODE:
	ld A, (IX+0)
	call #BC0E
ret

ABOUT_TEXT1:
defb " Renaud test RSX ABOUT,",10,13
defb "      tester aussi HELP",10,13
defb 10,13
defb 0 ; 7 ça fait beep en fait ^^
