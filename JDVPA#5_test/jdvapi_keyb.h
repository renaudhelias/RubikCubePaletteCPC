#ifndef JDVAPI_KEYB_H
#define JDVAPI_KEYB_H

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
typedef enum _eKey
{
  Key_CursorUp = 0,
  Key_CursorRight,
  Key_CursorDown,
  Key_F9,
  Key_F6,
  Key_F3,
  Key_Enter,
  Key_FDot,
  Key_CursorLeft, //8
  Key_Copy,
  Key_F7,
  Key_F8,
  Key_F5,
  Key_F1,
  Key_F2,
  Key_F0,
  Key_Clr, //16
  Key_BraceOpen,
  Key_Return,
  Key_BraceClose,
  Key_F4,
  Key_Shift,
  Key_BackSlash,
  Key_Control,
  Key_Caret, //24
  Key_Hyphen,
  Key_At,
  Key_P,
  Key_SemiColon,
  Key_Colon,
  Key_Slash,
  Key_Dot,
  Key_0, //32
  Key_9,
  Key_O,
  Key_I,
  Key_L,
  Key_K,
  Key_M,
  Key_Comma,
  Key_8, //40
  Key_7,
  Key_U,
  Key_Y,
  Key_H,
  Key_J,
  Key_N,
  Key_Space,
  Key_6_Joy2Up, //48
  Key_5_Joy2Down,
  Key_R_Joy2Left,
  Key_T_Joy2Right,
  Key_G_Joy2Fire1,
  Key_F_Joy2Fire2,
  Key_B,
  Key_V,
  Key_4, //56
  Key_3,
  Key_E,
  Key_W,
  Key_S,
  Key_D,
  Key_C,
  Key_X,
  Key_1, //64
  Key_2,
  Key_Esc,
  Key_Q,
  Key_Tab,
  Key_A,
  Key_CapsLock,
  Key_Z,
  Key_Joy1Up, //72
  Key_Joy1Down,
  Key_Joy1Left,
  Key_Joy1Right,
  Key_Joy1Fire1,
  Key_Joy1Fire2,
  Key_Joy1Fire3,
  Key_Del,
  Key_Max //80
}_ekey;
void check_controller();

unsigned char get_key(enum _eKey eKey);

#endif