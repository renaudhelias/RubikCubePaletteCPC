#ifndef JDVAPI_BASIC1_H
#define JDVAPI_BASIC1_H

void set_palette(unsigned char *pPalette);

void border(unsigned char nColorIndex);

/**
 * JDVA#2 Passage en mode 0 et tracé de point lent
 */
// char --> -128 +128
// unsigned --> char 0..255
void mode(unsigned char m);

#endif