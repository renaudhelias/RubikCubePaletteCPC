
void mode2(void)
{
	__asm
		ld A,#2
		call #0xBC0E
	__endasm;
}