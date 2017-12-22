#include <stdio.h>
#include <stdlib.h>

/**
 * JDVA#5 On affiche enfin des images, et on commence à ranger notre code
 */
#include "azrael.h"
#include "jdvapi_frame.h"
#include "jdvapi_frame.c"


void pen(unsigned char p)
{
	__asm
		ld A,4 (IX)
		call #0xBBDE
	__endasm;
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

void mode2(void)
{
	__asm
		ld A,#2
		call #0xBC0E
	__endasm;
}

/**
 * JDVA#2 Passage en mode 0 et tracé de point lent
 */
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

/**
 * JDVA#3 Architecture de la mémoire vidéo en mode 0
 */
 void set_pixel_color0(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
 {
	unsigned char nByte = *pByteAddress;
	if (nPixel == 0) {
		nByte&=85; // nByte = nByte & 85
		
		// AND
		// 0&0 --> 0
		// 1&0 --> 0
		// 0&1 --> 0
		// 1&1 --> 1
		
		// OR
		// 0|0 --> 0
		// 1|0 --> 1
		// 0|1 --> 1
		// 1|1 --> 1
		
		if (nColor & 1) nByte |=128;
		if (nColor & 2) nByte |=8;
		if (nColor & 4) nByte |=32;
		if (nColor & 8) nByte |=2;
	} else {
		nByte&=170;
		if (nColor & 1) nByte |=64;
		if (nColor & 2) nByte |=4;
		if (nColor & 4) nByte |=16;
		if (nColor & 8) nByte |=1;
	}
	*pByteAddress = nByte;
 }
 
 // 0..159 et 0..199
 void put_pixel0(unsigned char nX, unsigned char nY, unsigned char nColor)
{
	unsigned char nPixel = 0;
	unsigned int nAddress = 0xC000 + ((nY / 8) * 80) + ((nY % 8) * 2048) + (nX / 2);
	nPixel = nX % 2;
	set_pixel_color0((unsigned char *)nAddress, nColor, nPixel);
}

unsigned char *chats[15];

void main(void)
{
	unsigned char c = 0;
	unsigned int d = 0;
	mode2();
	mode(0);
	// JDVA#1 Hello World en C sur Amstrad CPC !
	printf("Hello World !");
	pen(1);
	plot(0,0);
	for (c=0;c<100;c=c+1) {
		put_pixel0(c,c,8);
	}
	pen(2);
	// 160*200
	plot(159,199);
	put_pixel0(159,199,9);
	// 640*400
	plot(639,399);
	put_pixel0(639,399,9);
	pen(3);
	plot(1,4);
	put_pixel0(1,4,7);
	plot(2,8);
	put_pixel0(2,8,7);
	plot(3,12);
	put_pixel0(3,12,7);
	plot(4,16);
	put_pixel0(4,16,7);
	pen(4);
	move(10+1,1);
	line(10+100,100);
	line(10+200,1);
	
	// JDVA#5
	for (c=0;c<15;c=c+1) {
		chats[c]=azrael+((10*16)*c);
	}
	set_palette(azrael_palette);
	while(1){
		for (c=0;c<15;c=c+1) {
			put_frame(vram(20,100),10,16,chats[c]);
			for (d=0;d<30000;d=d+1) {}
		}
		
	}
}