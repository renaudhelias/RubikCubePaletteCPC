#ifndef JDVAPI_FRAME_H
#define JDVAPI_FRAME_H

#define	vram(nX,nY) (unsigned char *)(0xC000 + ((nY / 8u) * 80u) + ((nY % 8u) * 2048u) + nX)

// x : 0..79
// y : 0..199
#define vramC000(x,y) ((unsigned char *)(0xC000 + vram[y]+x))
#define vram4000(x,y) ((unsigned char *)(0x4000 + vram[y]+x))
// x : 0..159 (on simule un screen 160x200, mais un x sur deux est ignoré en fait)
// y : 0..199
#define screen(x,y) ((unsigned char*)(0xC000 + vram[y]+(x>>1)))

extern void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image);

// extern void put_inversed_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image);

extern void put_frame_transparent(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image);

extern void erase_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight);

//FIXME (désolé MiGaNuTs :p), utiliser plutôt la routine qui est dans combat2.c :
//	// optimisation
//	for (i=120;i<120+50;i++) {
//		memcpy((char *)(0x4000 + vram[i] + 3), (char *)(0xC000 + vram[i] + 3), 6*8+3); // memcpy(destination,source,longueur)
//	}
//void get_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *backup);
// idem que get_frame mais qui marche (par MiGaNuTs)
//void save_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *image);


/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
char * precalc_vram();

#endif