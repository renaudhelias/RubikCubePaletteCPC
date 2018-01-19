#include <stdio.h>
#include <stdlib.h>

/**
 * JDVA#5 On affiche enfin des images, et on commence à ranger notre code
 */
#include "azrael.h"
#include "gargamel.h"
#include "jdvapi_useless.h"
#include "jdvapi_basic.h"
#include "jdvapi_frame.h"

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
	put_frame(vram(30,0),23,120,gargamel);
	while(1){
		for (c=0;c<15;c=c+1) {
			put_frame(vram(25,100),10,16,chats[c]);
			for (d=0;d<30000;d=d+1) {}
		}
	}
}