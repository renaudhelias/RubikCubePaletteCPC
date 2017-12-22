const unsigned char poisson_palette[]=
{
		2,16,0,26,17,25,14,18,20,0,0,0,0,0,0,0
};

const unsigned char poisson1[]=
{
      0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x08, 0x40, 0xC0, 0xC0, 0x00, 0x00
        ,      0x08, 0xC0, 0xC0, 0xE0, 0x00, 0x00, 0x08, 0xC0
        ,      0xC0, 0xD0, 0x80, 0x00, 0x08, 0xCC, 0xD0, 0xC0
        ,      0xA0, 0x00, 0x08, 0xF0, 0xF0, 0xC0, 0x80, 0x80
        ,      0x08, 0xC0, 0xC0, 0xC0, 0xC0, 0xA0, 0x08, 0xC0
        ,      0xC0, 0xD0, 0xC0, 0xA0, 0x08, 0xC0, 0xC0, 0xD0
        ,      0xC0, 0xA0, 0x08, 0xF0, 0xE0, 0xC0, 0xC0, 0xA0
        ,      0x08, 0xC0, 0xC0, 0xC0, 0xC0, 0xA0, 0x08, 0xF0
        ,      0xE0, 0xC0, 0x80, 0x80, 0x08, 0xC0, 0xC0, 0xC0
        ,      0x00, 0x80, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char poisson2[]=
{
      0x00, 0x00, 0x0C, 0x0C, 0x08, 0x00, 0x00, 0x00
        ,      0xFC, 0xFC, 0x0C, 0x00, 0x00, 0x54, 0xEC, 0xDC
        ,      0x0C, 0x08, 0x00, 0x0C, 0xFC, 0xFC, 0x0C, 0x08
        ,      0x00, 0x0C, 0x5C, 0xFC, 0xAC, 0x0C, 0x00, 0xCC
        ,      0xCC, 0xFC, 0xFC, 0x0C, 0x00, 0xCC, 0xCC, 0xFC
        ,      0xFC, 0x0C, 0x4C, 0x8C, 0xCC, 0xFC, 0xFC, 0x0C
        ,      0x0C, 0x0C, 0xEC, 0xFC, 0xFC, 0x5C, 0x5C, 0xAC
        ,      0xAC, 0xFC, 0x0C, 0x5C, 0x5C, 0xAC, 0xAC, 0x5C
        ,      0x5C, 0x5C, 0x54, 0xFC, 0xFC, 0x5C, 0x5C, 0x5C
        ,      0x00, 0xA8, 0xFC, 0xFC, 0x5C, 0x5C, 0x00, 0xFC
        ,      0xFC, 0xFC, 0x5C, 0xAC, 0x00, 0x0C, 0x0C, 0x0C
        ,      0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	
};

const unsigned char poisson_groupe[]=
{
      0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x40, 0x80, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0
        ,      0x00, 0x00, 0x40, 0xC0, 0xC0, 0xE0, 0x80, 0x00
        ,      0x40, 0xC0, 0xC0, 0xD0, 0x80, 0x00, 0xC4, 0xCC
        ,      0xE0, 0xC0, 0xF0, 0x00, 0x40, 0xC0, 0xE0, 0xC0
        ,      0xC0, 0x40, 0xD0, 0xF0, 0xE0, 0xC0, 0xC0, 0xC0
        ,      0x40, 0xC0, 0xC0, 0xC0, 0xC0, 0xD0, 0x40, 0xC0
        ,      0xC0, 0xD0, 0xC0, 0xD0, 0x40, 0xC0, 0xC0, 0xD0
        ,      0xE0, 0xD0, 0xC0, 0xC0, 0xE0, 0xD0, 0xE0, 0xD0
        ,      0xD0, 0xF0, 0xC0, 0xC0, 0xC0, 0xD0, 0xC0, 0xC0
        ,      0xE0, 0xC0, 0xC0, 0xD0, 0x50, 0xF0, 0xC0, 0xC0
        ,      0x80, 0xC0, 0x40, 0xC0, 0xC0, 0xC0, 0x00, 0x40
        ,      0x00, 0x00, 0x0C, 0x0C, 0x08, 0x00, 0x00, 0x00
        ,      0xC0, 0x84, 0x0C, 0x00, 0x00, 0x40, 0xC0, 0xC0
        ,      0x0C, 0x08, 0x00, 0x0C, 0x48, 0xC0, 0x0C, 0x08
        ,      0x00, 0x0C, 0x48, 0xC0, 0x84, 0x0C, 0x00, 0xCC
        ,      0xCC, 0xC0, 0xC0, 0x0C, 0x00, 0xCC, 0xCC, 0xC0
        ,      0xC0, 0x0C, 0x4C, 0x8C, 0xCC, 0xC0, 0xC0, 0x0C
        ,      0x0C, 0x0C, 0xC4, 0xC0, 0xC0, 0x48, 0x48, 0x84
        ,      0x84, 0xC0, 0x0C, 0x48, 0x48, 0x84, 0x84, 0x48
        ,      0x48, 0x48, 0x40, 0xC0, 0xC0, 0x48, 0x48, 0x48
        ,      0x00, 0x80, 0xC0, 0xC0, 0x48, 0x48, 0x00, 0xC0
        ,      0xC0, 0xC0, 0x48, 0x84, 0x00, 0x0C, 0x0C, 0x0C
        ,      0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x40, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x40
        ,      0xF0, 0xF0, 0xA0, 0x00, 0x00, 0x80, 0xC0, 0xC0
        ,      0xA0, 0x00, 0x40, 0x80, 0xF0, 0xF0, 0xF0, 0x00
        ,      0x40, 0xC0, 0xF0, 0xF0, 0xF0, 0x00, 0xC0, 0xD0
        ,      0xF0, 0xF0, 0xF0, 0x50, 0xC0, 0xD0, 0xF0, 0xF0
        ,      0xF0, 0x50, 0xD0, 0xF0, 0xF0, 0xF0, 0xF0, 0xD0
        ,      0xD0, 0xD0, 0xE0, 0xF0, 0xF0, 0xF0, 0xC0, 0xF0
        ,      0xF0, 0xF0, 0xE0, 0xD0, 0xC0, 0xD0, 0xF0, 0xF0
        ,      0xC0, 0xF0, 0x40, 0xC0, 0xF0, 0xE0, 0xC0, 0x40
        ,      0x40, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xC0
        ,      0xC0, 0xC0, 0x80, 0x00, 0x00, 0xC0, 0xF0, 0xE0
        ,      0x80, 0x00, 0x00, 0x40, 0xC0, 0xC0, 0x00, 0x00
        ,      0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x00, 0x04
        ,      0x0C, 0x08, 0x00, 0x04, 0x04, 0x0C, 0x48, 0x84
        ,      0x08, 0x04, 0x48, 0xC0, 0xC0, 0xC0, 0x0C, 0x48
        ,      0x0C, 0xC0, 0x0C, 0xC0, 0x84, 0x48, 0x84, 0xC0
        ,      0x0C, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x84, 0xC0
        ,      0xC0, 0x48, 0x48, 0x84, 0x0C, 0xC0, 0xC0, 0x48
        ,      0x48, 0xC0, 0xC0, 0xC0, 0xC0, 0x48, 0x48, 0xC0
        ,      0xC0, 0xC0, 0xC0, 0xC0, 0x48, 0x84, 0xC0, 0xC0
        ,      0x84, 0xC0, 0x04, 0x0C, 0x48, 0x48, 0x84, 0x48
        ,      0x40, 0xC0, 0x84, 0xC0, 0x0C, 0x04, 0x00, 0xC0
        ,      0xC0, 0xC0, 0x0C, 0x04, 0x00, 0xC0, 0xC0, 0x84
        ,      0x0C, 0x00, 0x00, 0x04, 0x0C, 0x08, 0x00, 0x00
        ,      0x00, 0x00, 0x0C, 0x0C, 0x08, 0x00, 0x00, 0x00
        ,      0xFC, 0xFC, 0x0C, 0x00, 0x00, 0x54, 0xEC, 0xDC
        ,      0x0C, 0x08, 0x00, 0x0C, 0xFC, 0xFC, 0x0C, 0x08
        ,      0x00, 0x0C, 0x5C, 0xFC, 0xAC, 0x0C, 0x00, 0xCC
        ,      0xCC, 0xFC, 0xFC, 0x0C, 0x00, 0xCC, 0xCC, 0xFC
        ,      0xFC, 0x0C, 0x4C, 0x8C, 0xCC, 0xFC, 0xFC, 0x0C
        ,      0x0C, 0x0C, 0xEC, 0xFC, 0xFC, 0x5C, 0x5C, 0xAC
        ,      0xAC, 0xFC, 0x0C, 0x5C, 0x5C, 0xAC, 0xAC, 0x5C
        ,      0x5C, 0x5C, 0x54, 0xFC, 0xFC, 0x5C, 0x5C, 0x5C
        ,      0x00, 0xA8, 0xFC, 0xFC, 0x5C, 0x5C, 0x00, 0xFC
        ,      0xFC, 0xFC, 0x5C, 0xAC, 0x00, 0x0C, 0x0C, 0x0C
        ,      0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x04, 0x0C, 0x00, 0x00, 0x04, 0x04, 0x1C
        ,      0x3C, 0x08, 0x00, 0x04, 0x1C, 0x3C, 0x0C, 0x8C
        ,      0x00, 0x04, 0x1C, 0x3C, 0x0C, 0xCC, 0x08, 0x0C
        ,      0x3C, 0x3C, 0x8C, 0xCC, 0x08, 0x0C, 0x3C, 0x2C
        ,      0x1C, 0x3C, 0x2C, 0x2C, 0x1C, 0x3C, 0x3C, 0x3C
        ,      0x3C, 0x0C, 0x1C, 0x3C, 0x3C, 0x3C, 0x3C, 0x0C
        ,      0x2C, 0x1C, 0x3C, 0x3C, 0x3C, 0x0C, 0x0C, 0x0C
        ,      0x3C, 0x3C, 0x3C, 0x0C, 0x2C, 0x0C, 0x1C, 0x3C
        ,      0x2C, 0x2C, 0x2C, 0x1C, 0x9C, 0x3C, 0x2C, 0x2C
        ,      0x1C, 0x3C, 0x3C, 0x1C, 0x3C, 0x28, 0x04, 0x3C
        ,      0x9C, 0x3C, 0x0C, 0x28, 0x00, 0x0C, 0x9C, 0x3C
        ,      0x3C, 0x00, 0x00, 0x00, 0x0C, 0x08, 0x00, 0x00
        ,      0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x00, 0x04
        ,      0x0C, 0x08, 0x00, 0x04, 0x04, 0x0C, 0x4C, 0x8C
        ,      0x08, 0x04, 0x4C, 0xCC, 0xCC, 0xCC, 0x0C, 0x4C
        ,      0x0C, 0xCC, 0x0C, 0xCC, 0x8C, 0x4C, 0x8C, 0xCC
        ,      0x0C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x8C, 0xCC
        ,      0xCC, 0x4C, 0x4C, 0x8C, 0x0C, 0xCC, 0xCC, 0x4C
        ,      0x4C, 0xCC, 0xCC, 0xCC, 0xCC, 0x4C, 0x4C, 0xCC
        ,      0xCC, 0xCC, 0xCC, 0xCC, 0x4C, 0x8C, 0xCC, 0xCC
        ,      0x8C, 0xCC, 0x04, 0x0C, 0x4C, 0x4C, 0x8C, 0x4C
        ,      0x44, 0xCC, 0x8C, 0xCC, 0x0C, 0x04, 0x00, 0xCC
        ,      0xCC, 0xCC, 0x0C, 0x04, 0x00, 0xCC, 0xCC, 0x8C
        ,      0x0C, 0x00, 0x00, 0x04, 0x0C, 0x08, 0x00, 0x00
        ,      0x00, 0x00, 0x30, 0x20, 0x00, 0x00, 0x00, 0x10
        ,      0x12, 0x12, 0x20, 0x00, 0x00, 0x30, 0x30, 0x21
        ,      0x30, 0x00, 0x00, 0x38, 0x03, 0x21, 0x34, 0x20
        ,      0x00, 0x34, 0x21, 0x21, 0x12, 0x30, 0x10, 0x34
        ,      0x21, 0x21, 0x12, 0x30, 0x10, 0x30, 0x21, 0x21
        ,      0x21, 0x30, 0x30, 0x64, 0x03, 0x21, 0x21, 0x30
        ,      0x0C, 0x0C, 0x21, 0x03, 0x21, 0x30, 0x30, 0x64
        ,      0x21, 0x03, 0x21, 0x30, 0x34, 0x34, 0x12, 0x03
        ,      0x21, 0x30, 0x14, 0x30, 0x12, 0x21, 0x21, 0x30
        ,      0x10, 0x34, 0x12, 0x21, 0x30, 0x30, 0x14, 0x3C
        ,      0x03, 0x21, 0x12, 0x30, 0x10, 0x3C, 0x21, 0x21
        ,      0x30, 0x20, 0x00, 0x30, 0x30, 0x30, 0x30, 0x00
        ,      0x00, 0x44, 0x00, 0x44, 0x88, 0x00, 0x00, 0xCC
        ,      0x88, 0x44, 0x10, 0x00, 0x44, 0xCC, 0x44, 0x00
        ,      0x10, 0x00, 0x44, 0xCC, 0x44, 0x00, 0x10, 0x00
        ,      0x00, 0x44, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00
        ,      0x00, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0xCC, 0x88, 0x44, 0x00, 0x10, 0x00, 0x9C, 0x88
        ,      0x10, 0x00, 0x10, 0x00, 0xCC, 0x00, 0x00, 0x20
        ,      0x20, 0x00, 0xCC, 0x00, 0x00, 0x10, 0x00, 0x44
        ,      0x44, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x10
        ,      0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00
        ,      0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00
        ,      0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        ,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};