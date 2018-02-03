
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

void calqueC000()
{
  __asm
    ld bc,#0xBC00+12 ; On met la valeur 48 dans
    out (c),c      ; le registre 12 du CRTC
    ld bc,#0xBD00+48
    out (c),c
  __endasm;
}

void calque4000()
{
  __asm
    ld bc,#0xBC00+12 ; On met la valeur 16 dans
    out (c),c      ; le registre 12 du CRTC
    ld bc,#0xBD00+16
    out (c),c
  __endasm;
}

void calque4C00()
{
  __asm
    ld bc,#0xBC00+12 ; On met la valeur 28 dans
    out (c),c      ; le registre 12 du CRTC
    ld bc,#0xBD00+28
    out (c),c
  __endasm;
}

void bank0123()
{
  __asm
    ld bc,#0x7FC0+0 ; RAM rétablie
	out (c),c
  __endasm;
}

void bank7_C000()
{
  __asm
    ld bc,#0x7FC0+1 ; RAM_7 sur &C000-&FFFF
	out (c),c
  __endasm;
}

void bank4_4000()
{
  __asm
    ld bc,#0x7FC0+4 ; RAM_4 sur &4000-&7FFF
	out (c),c
  __endasm;
}

void bank5_4000()
{
  __asm
    ld bc,#0x7FC0+5 ; RAM_5 sur &4000-&7FFF
	out (c),c
  __endasm;
}

void bank6_4000()
{
  __asm
    ld bc,#0x7FC0+6 ; RAM_6 sur &4000-&7FFF
	out (c),c
  __endasm;
}

void bank7_4000()
{
  __asm
    ld bc,#0x7FC0+7 ; RAM_7 sur &4000-&7FFF
	out (c),c
  __endasm;
}

void scroll(unsigned char h)
{
	__asm
		ld A,4 (IX)
		ld bc,#0xBC00+12
		out (c),c
		ld b,#0xBD
		ld c,A
		out (c),c
	__endasm;
}

void overscan()
{
  __asm
    ld bc,#0xBC00+1 ; On met la valeur 48 dans
    out (c),c      ; le registre 1 du CRTC -- RHdisp
    ld bc,#0xBD00+48
    out (c),c
    ld bc,#0xBC00+2 ; On met la valeur 50 dans
    out (c),c      ; le registre 2 du CRTC -- RHsyncpos
    ld bc,#0xBD00+50
    out (c),c
    ld bc,#0xBC00+6 ; On met la valeur 34 dans
    out (c),c      ; le registre 6 du CRTC -- RVdisp
    ld bc,#0xBD00+34
    out (c),c
    ld bc,#0xBC00+7 ; On met la valeur 35 dans
    out (c),c      ; le registre 7 du CRTC -- RVsyncpos
    ld bc,#0xBD00+35
    out (c),c
 __endasm;
}

void scan()
{
  __asm
    ld bc,#0xBC00+1 ; On remet la valeur 40 dans
    out (c),c      ; le registre 1 du CRTC -- RHdisp
    ld bc,#0xBD00+40
    out (c),c
    ld bc,#0xBC00+2 ; On remet la valeur 46 dans
    out (c),c      ; le registre 2 du CRTC -- RHsyncpos
    ld bc,#0xBD00+46
    out (c),c
    ld bc,#0xBC00+6 ; On remet la valeur 25 dans
    out (c),c      ; le registre 6 du CRTC -- RVdisp
    ld bc,#0xBD00+25
    out (c),c
    ld bc,#0xBC00+7 ; On remet la valeur 30 dans
    out (c),c      ; le registre 7 du CRTC -- RVsyncpos
    ld bc,#0xBD00+30
    out (c),c
 __endasm;
}
