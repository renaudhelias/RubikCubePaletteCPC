#include "jdvapi_keyb.h"

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
unsigned char aKeyboard[10];

unsigned char get_key(enum _eKey eKey)
{
  unsigned char nKeyLine = eKey / 8;
  unsigned char nBit = eKey % 8;
  
  if(((unsigned char)1 << nBit & aKeyboard[nKeyLine]) == 0)
    return 1;
  
  return 0;
}

void check_controller()
{
  __asm
    di
    ld hl, #_aKeyboard
    ld bc,#0xf782
    out (c),c
    ld bc,#0xf40e
    ld e,b
    out (c),c
    ld bc,#0xf6c0
    ld d,b
    out (c),c
    ld c,#0x00
    out (c),c
    ld bc,#0xf792
    out (c),c
    ld a,#0x40
    ld c,#0x4a
    _loop:
    ld b,d
    out (c),a
    ld b,e
    ini
    inc a
    cp c
    jr c,_loop
    ld bc,#0xf782
    out (c),c
    ei
  __endasm;
}
