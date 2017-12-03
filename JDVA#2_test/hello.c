#include <stdio.h>
#include <stdlib.h>

void pen(unsigned char p)
{
	__asm
		ld A,4 (IX)
		call #0xBBDE
	__endasm;
}

// char --> -128 +128
// unsigned --> char 0..255
void mode(unsigned char m)
{
	__asm
		ld A,4 (IX)
		call #0xBC0E
	__endasm;
}

void mode2(void)
{
	__asm
		ld A,#2
		call #0xBC0E
	__endasm;
}

// int : 16bit
void plot(unsigned int x,unsigned int y)
{
	__asm
		// DE (little-endian :p)
		ld E,4 (IX)
		ld D,5 (IX)
		// HL (little-endian :p)
		ld L,6 (IX)
		ld H,7 (IX)
		call #0xBBEA
	__endasm;
}

void move(unsigned int x,unsigned int y)
{
	__asm
		// DE (little-endian :p)
		ld E,4 (IX)
		ld D,5 (IX)
		// HL (little-endian :p)
		ld L,6 (IX)
		ld H,7 (IX)
		call #0xBBC0
	__endasm;
}

void line(unsigned int x,unsigned int y)
{
	__asm
		// DE (little-endian :p)
		ld E,4 (IX)
		ld D,5 (IX)
		// HL (little-endian :p)
		ld L,6 (IX)
		ld H,7 (IX)
		call #0xBBF6
	__endasm;
}

void main(void)
{
	mode2();
	mode(0);
	printf("Hello World !");
	pen(1);
	plot(0,0);
	pen(2);
	// 160*200
	plot(159,199);
	// 640*400
	plot(639,399);
	pen(3);
	plot(1,4);
	plot(2,8);
	plot(3,12);
	plot(4,16);
	pen(4);
	move(10,0);
	line(100,100);
	while(1){}
}