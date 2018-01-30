#ifndef JDVAPI_BASIC_H
#define JDVAPI_BASIC_H

void set_palette(const unsigned char *pPalette);

void pen(unsigned char p);

void locate(unsigned char x,unsigned char y);

/**
 * JDVA#2 Passage en mode 0 et tracé de point lent
 */
// char --> -128 +128
// unsigned --> char 0..255
void mode(unsigned char m);
/**
 * JDVA#2 Passage en mode 0 et tracé de point lent
 */
// int : 16bit
void plot(unsigned int x,unsigned int y);

void move(unsigned int x,unsigned int y);

void line(unsigned int x,unsigned int y);

/**
 * JDVA#3 Architecture de la mémoire vidéo en mode 0
 */
//void set_pixel_color0(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
 
// 0..159 et 0..199
void put_pixel0(unsigned char nX, unsigned char nY, unsigned char nColor);
 
//  // 0..159 et 0..199
// unsigned char get_pixel0byte(unsigned char nX, unsigned char nY);

// // 0..159 et 0..199
// void put_pixel0byte(unsigned char nX, unsigned char nY, unsigned char nByte);

// 0..159 et 0..199
// voir aussi :
// #include <stdio.h>
// #include <string.h>
// memcpy((char *)0xC000, (char *)0x6000, 0x3FFF);
// memcpy(destination,source,longueur)
void copy_pixel0bytes(unsigned char nXFrom, unsigned char nYFrom,unsigned char nXTo, unsigned char nYTo, unsigned char tailleX, unsigned char tailleY);
 
 // 0..319 et 0..199
 void put_pixel1(unsigned char nX, unsigned char nY, unsigned char nColor);
 
 // 0..319 et 0..199
 //void put_pixel_byte1(unsigned char nX, unsigned char nY, unsigned char nColor0, unsigned char nColor1, unsigned char nColor2, unsigned char nColor3);
 
 // 0..319 et 0..199
 void put_pixel_byte1(unsigned char nX, unsigned char nY, unsigned char nColor0123);
 
 #endif