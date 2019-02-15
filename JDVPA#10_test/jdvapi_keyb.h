#ifndef JDVAPI_KEYB_H
#define JDVAPI_KEYB_H

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
 // unsigned char enum (optim)
#define Key_CursorUp 0#define Key_CursorRight 1#define Key_CursorDown 2#define Key_F9 3#define Key_F6 4#define Key_F3 5#define Key_Enter 6#define Key_FDot 7#define Key_CursorLeft 8#define Key_Copy 9#define Key_F7 10#define Key_F8 11#define Key_F5 12#define Key_F1 13#define Key_F2 14#define Key_F0 15#define Key_Clr 16#define Key_BraceOpen 17#define Key_Return 18#define Key_BraceClose 19#define Key_F4 20#define Key_Shift 21#define Key_BackSlash 22#define Key_Control 23#define Key_Caret 24#define Key_Hyphen 25#define Key_At 26#define Key_P 27#define Key_SemiColon 28#define Key_Colon 29#define Key_Slash 30#define Key_Dot 31#define Key_0 32#define Key_9 33#define Key_O 34#define Key_I 35#define Key_L 36#define Key_K 37#define Key_M 38#define Key_Comma 39#define Key_8 40#define Key_7 41#define Key_U 42#define Key_Y 43#define Key_H 44#define Key_J 45#define Key_N 46#define Key_Space 47#define Key_6_Joy2Up 48#define Key_5_Joy2Down 49#define Key_R_Joy2Left 50#define Key_T_Joy2Right 51#define Key_G_Joy2Fire1 52#define Key_F_Joy2Fire2 53#define Key_B 54#define Key_V 55#define Key_4 56#define Key_3 57#define Key_E 58#define Key_W 59#define Key_S 60#define Key_D 61#define Key_C 62#define Key_X 63#define Key_1 64#define Key_2 65#define Key_Esc 66#define Key_Q 67#define Key_Tab 68#define Key_A 69#define Key_CapsLock 70#define Key_Z 71#define Key_Joy1Up 72#define Key_Joy1Down 73#define Key_Joy1Left 74#define Key_Joy1Right 75#define Key_Joy1Fire1 76#define Key_Joy1Fire2 77#define Key_Joy1Fire3 78#define Key_Del 79#define Key_Max 80

extern unsigned char aKeyboard[10];

void check_controller();

//unsigned char get_key(unsigned char eKey);

#define get_key(eKey) ((1 << (eKey%8) & aKeyboard[eKey/8]) == 0)

#endif