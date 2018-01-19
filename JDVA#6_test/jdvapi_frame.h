#ifndef JDVAPI_FRAME_H
#define JDVAPI_FRAME_H

#define	vram(nX,nY) (unsigned char *)(0xC000 + ((nY / 8u) * 80u) + ((nY % 8u) * 2048u) + nX)

extern void set_color(unsigned char nColorIndex, unsigned char nPaletteIndex);

extern void set_palette(const unsigned char *pPalette);

extern void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image);

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
char * precalc_vram();

#endif