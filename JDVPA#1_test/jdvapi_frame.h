#ifndef JDVAPI_FRAME_H
#define JDVAPI_FRAME_H

#define	vram(nX,nY) (unsigned char *)(0xC000 + ((nY / 8u) * 80u) + ((nY % 8u) * 2048u) + nX)

//#define screen(x,y) ((unsigned char *)(vram[y]+x))
#define screen(x,y) ((unsigned char*)vram[y]+(x>>1))

extern void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image);

extern void put_frame_transparent(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image);

extern void erase_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight);

void get_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *backup);
// idem que get_frame mais qui marche (par MiGaNuTs)
void save_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *image);


/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
char * precalc_vram();

#endif