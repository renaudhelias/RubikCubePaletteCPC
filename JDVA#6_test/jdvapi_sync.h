#ifndef JDVAPI_SYNC_H
#define JDVAPI_SYNC_H

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
void vsync();

// VRAM en &C000-&FFFF
void calqueC000();
// VRAM en &4000-&7FFF
void calque4000();
// RAM rétablie
void bank0123();
// RAM_7 sur &C000-&FFFF
void bank7_C000();
// RAM_4 sur &4000-&7FFF
void bank4_4000();
// RAM_5 sur &4000-&7FFF
void bank5_4000();
// RAM_6 sur &4000-&7FFF
void bank6_4000();
// RAM_7 sur &4000-&7FFF
void bank7_4000();

// 0-255 h
void scroll(unsigned char h);

void overscan();
void overscan24K();
void overscanH();
void scan();
void calque4C00();

#endif