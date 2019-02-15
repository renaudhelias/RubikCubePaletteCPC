#ifndef JDVAPI_KEYB_H
#define JDVAPI_KEYB_H

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
 // unsigned char enum (optim)
#define Key_CursorUp 0

extern unsigned char aKeyboard[10];

void check_controller();

//unsigned char get_key(unsigned char eKey);

#define get_key(eKey) ((1 << (eKey%8) & aKeyboard[eKey/8]) == 0)

#endif