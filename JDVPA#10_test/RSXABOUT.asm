org #c000
             defb #01           ; ; bg ROM
             defb #03,#02,#01    ; Version 1.00
             defw RSX_TABLE      ; Adresses des noms des Commandes externes
             JP INIT_AZERTY      ; Adresse d'execution lors du demarrage
             jp ABOUT
RSX_TABLE:
             defb "RENAU","D"+#80
             defb "ABOU","T"+#80
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
ABOUT_TEXT1:
defb " Renaud test RSX ABOUT,",10,13
defb "      tester aussi HELP",10,13
defb 10,13
defb 0 ; 7 ça fait beep en fait ^^


