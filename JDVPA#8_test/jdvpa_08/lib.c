#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTI 1

unsigned char char1,char2,char3,char4;
unsigned char aKeyboard[KEYBOARD_HW_LINES];
unsigned int precalc_vram[200];
unsigned char flags;
int err;
unsigned char dx,dy;

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

void init_cpc_lib()
{
	unsigned char i;
	
	for (i=0;i<200;i++)
	{
		precalc_vram[i]=(0xC000 + ((i / 8u) * 80u) + ((i % 8u) * 2048u));		
		
	}
}

void intern_screen_mode0()
{
  __asm
    ld a, #0
    call #0xBC0E
  __endasm;
  
  //PALETE
  __asm
    ld a, #0
    ld b, #0 ;black
    ld c, b
    call #0xBC32 ;SCR SET INK

    ld a, #1
    ld b, #12 ;Yellow
    ld c, b
    call #0xBC32 ;SCR SET INK

    ld a, #2
    ld b, #25 ;Pastel Yellow    
    ld c, b
    call #0xBC32 ;SCR SET INK

    ld a, #3
    ld b, #24 ;Bright Yellow
    ld c, b
    call #0xBC32 ;SCR SET INK
  __endasm;

  //SCR SET BORDER 0
  __asm
    ld b, #0 ;black
    ld c, b
    call #0xBC38
  __endasm;  
}

void screen_mode0()
{
	intern_screen_mode0();
	init_cpc_lib();
}

unsigned int get_time()
{
  unsigned int nTime = 0;

  __asm
    CALL #0xBD0D ;KL TIME PLEASE
    PUSH HL
    POP DE
    LD HL, #_char3
    LD (HL), D
    LD HL, #_char4
    LD (HL), E
  __endasm;

  nTime = (char3 << 8) + char4;

  return nTime;
}

void set_pixel_color0(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
{
  unsigned char nByte = *pByteAddress;

  if(nPixel == 0)
  {
    nByte &= 85;

    if(nColor & 1)
      nByte |= 128;

    if(nColor & 2)
      nByte |= 8;

    if(nColor & 4)
      nByte |= 32;

    if(nColor & 8)
      nByte |= 2;
  }
  else
  {
    nByte &= 170;

    if(nColor & 1)
      nByte |= 64;

    if(nColor & 2)
      nByte |= 4;

    if(nColor & 4)
      nByte |= 16;

    if(nColor & 8)
      nByte |= 1;
  }

  *pByteAddress = nByte;
}

void set_color(unsigned char nColorIndex, unsigned char nPaletteIndex)
{
  __asm
    ld a, 4 (ix)
    ld b, 5 (ix)
    ld c, b
    call #0xBC32 ;SCR SET INK
    __endasm;
}

void set_palette(const unsigned char *pPalette)
{
  unsigned char nColor = 0;

  for(nColor = 0; nColor < 16; nColor++)
    set_color(nColor, pPalette[nColor]);
}

void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *pSprite)
{
  __asm
    LD L, 4(IX) 
    LD H, 5(IX) 
    LD C, 6(IX) 
    LD B, 7(IX)            
    LD E, 8(IX) 
    LD D, 9(IX) 

    _loop_alto:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_ancho:
       LD A,(DE)			; Met dans A un octet de de la source
       LD (HL),A			; Met dans la destination A
       INC DE				; Avance dans l'adresse de la source
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_ancho		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_linea	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_alto		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
  __endasm;
}

void cmemcpy( void *dst, void *src, short len )
{
	__asm
		ld e, 4(ix)
		ld d, 5(ix)
		ld l, 6(ix)
		ld h, 7(ix)
		ld c, 8(ix)
		ld b, 9(ix)
		ldir
	__endasm;
}

void vsync()
{
  __asm
    ld b,#0xf5          ;; PPI port B input
    _wait_vsync:
    in a,(c)            ;; [4] read PPI port B input
                        ;; (bit 0 = "1" if vsync is active,
                        ;;  or bit 0 = "0" if vsync is in-active)
    rra                 ;; [1] put bit 0 into carry flag
    jp nc,_wait_vsync   ;; [3] if carry not set, loop, otherwise continue
  __endasm;
}

void put_frameXOR(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *pSprite)
{
  __asm
    LD L, 4(IX) 
    LD H, 5(IX) 
    LD C, 6(IX) 
    LD B, 7(IX)            
    LD E, 8(IX) 
    LD D, 9(IX) 

    _loop_altox:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_anchox:
       LD A,(DE)			; Met dans A un octet de de la source
	   XOR (HL)				; Inverse la destination
       LD (HL),A			; Met dans la destination A
       INC DE				; Avance dans l'adresse de la source
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_anchox		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_lineax	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_lineax:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_altox		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
  __endasm;
}
	