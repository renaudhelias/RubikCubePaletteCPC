#ifndef JDVAPI_BASIC_H
#define JDVAPI_BASIC_H

void set_palette(const unsigned char *pPalette);

void pen(unsigned char p);
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
 
 // 0..319 et 0..199
 void put_pixel1(unsigned char nX, unsigned char nY, unsigned char nColor);
 
 #endif