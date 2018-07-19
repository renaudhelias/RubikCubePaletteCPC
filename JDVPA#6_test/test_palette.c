// color BASIC 0
#define FIRM_COLOR_0 84
// color BASIC 1
#define FIRM_COLOR_1 68
// color BASIC 2
#define FIRM_COLOR_2 85
// color BASIC 3
#define FIRM_COLOR_3 92
// color BASIC 4
#define FIRM_COLOR_4 88 
// color BASIC 5
#define FIRM_COLOR_5 93

//void set_firmcolor(unsigned char firmColor)
void set_firmcolor(char firmColor)
{
  __asm
    ld a, 4 (ix)
	
	//ld	hl, #2+0
	//add	hl, sp
	//ld	a, (hl)
	
    ld bc, #0x7f00
    out (c), c
    out (c), a
    ld bc, #0x7f10
    out (c), c
    out (c), a
  __endasm;
}



void set_firmcolor1()
{
  __asm
	ld A,#0x5D
    ld bc, #0x7f00
    out (c), c
    out (c), a
    ld bc, #0x7f10
    out (c), c
    out (c), a
  __endasm;
}

void set_firmcolor2()
{
  __asm
	ld A,#0x54
    ld bc, #0x7f00
    out (c), c
    out (c), a
    ld bc, #0x7f10
    out (c), c
    out (c), a
  __endasm;
}

void callback_roulette2(unsigned char roulette)
{
	//set_firmcolor(FIRM_COLOR_0);
	set_firmcolor2();
	__asm
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
	__endasm;
	//set_firmcolor(FIRM_COLOR_5);
	set_firmcolor1();
}

// chat_gaston-prudent.png
void test_palette() {
	bank0123();
	put_frame_transparent((unsigned char *)(0xC000 + vram[148]+20),40,48,0x7800);
	//3) raster palette
	while (get_vsync()==1) {}
	vsync();
	handle_raster(callback_roulette2);
	raster();
}
