#include "RSXABOUTconfig.h"

void border(unsigned char nColorIndex)
{
#ifdef RSXABOUT
  __asm
    LD b, #0x00
    LD c, 4 (ix)
    LD (TABLE), bc

    LD A,#0x01 ;un seul paramètre
    LD IX,#TABLE ; le paramètre : 4 (border 4)
    LD HL,#0xC00C ; un jp c'est 3, un defw c'est 2
    LD C,#0x04 ; ùhelp dit 4
    CALL #0x001B ;lancer la commande RSX

TABLE:
    .DB 5 ; border 5
    .DB 0 ; sinon ça bug, ça semble manger du word
  __endasm;
#else
  __asm
    ld b, 4 (ix)
    ld c, b
    call #0xBC38 ;SCR SET INK
  __endasm;
#endif
}


void set_color(unsigned char nColorIndex, unsigned char nPaletteIndex)
{
#ifdef RSXABOUT
  __asm
	
;	LD b, #0x00 ;4 (ix)
;	LD c, #0x01
;	LD h, #0x00; 5 (ix)
;	LD l, #0x05
;	LD (TABLE2), bc
;	LD (TABLE2bis), hl
	
	
    LD A,#0x02 ;un seul paramètre
    LD IX,#TABLE2 ; le paramètre : 4 (border 4)
    LD HL,#0xC00F ; un jp c'est 3, un defw c'est 2
    LD C,#0x04 ; ùhelp dit 4
    CALL #0x001B ;lancer la commande RSX

TABLE2:
    .DB 1 ; setcolor 6,1
    .DB 0 ; sinon ça bug, ça semble manger du word
TABLE2bis:
	.DB 6
	.DB 0
  __endasm;
#else
  __asm
    ld a, 4 (ix)
    ld b, 5 (ix)
    ld c, b
    call #0xBC32 ;SCR SET INK
  __endasm;
#endif
}

void set_palette(unsigned char *pPalette)
{
  unsigned char nColor = 0;

  for(nColor = 0; nColor < 16; nColor++)
    set_color(nColor, pPalette[nColor]);
}

/**
 * JDVA#2 Passage en mode 0 et tracé de point lent
 */
// char --> -128 +128
// unsigned --> char 0..255
void mode(unsigned char m)
{
	__asm
		ld A,4 (IX)
		call #0xBC0E
	__endasm;
}


