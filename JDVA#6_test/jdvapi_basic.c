

void pen(unsigned char p)
{
	__asm
		ld A,4 (IX)
		call #0xBBDE
	__endasm;
}

/**
 * JDVA#2 Passage en mode 0 et tracé de point lent
 */
// char --> -128 +128
// unsigned --> char 0..255
void mode(unsigned char m)
{
	__asm
		ld A,4 (IX)
		call #0xBC0E
	__endasm;
}

/**
 * JDVA#2 Passage en mode 0 et tracé de point lent
 */
// int : 16bit
void plot(unsigned int x,unsigned int y)
{
	__asm
		// DE (little-endian :p)
		ld E,4 (IX)
		ld D,5 (IX)
		// HL (little-endian :p)
		ld L,6 (IX)
		ld H,7 (IX)
		call #0xBBEA
	__endasm;
}

void move(unsigned int x,unsigned int y)
{
	__asm
		// DE (little-endian :p)
		ld E,4 (IX)
		ld D,5 (IX)
		// HL (little-endian :p)
		ld L,6 (IX)
		ld H,7 (IX)
		call #0xBBC0
	__endasm;
}

void line(unsigned int x,unsigned int y)
{
	__asm
		// DE (little-endian :p)
		ld E,4 (IX)
		ld D,5 (IX)
		// HL (little-endian :p)
		ld L,6 (IX)
		ld H,7 (IX)
		call #0xBBF6
	__endasm;
}

/**
 * JDVA#3 Architecture de la mémoire vidéo en mode 0
 *
 * Organisation d'un octet :
 * mode 1 :
 *   1 octet <=> 4 pixels
 *   [AAAA][BBBB] : superposition des couleurs de [AAAA] et [BBBB]
 *   A+B=0+0=bleu foncé (couleur du fond par défaut)
 *   A+B=0+1=bleu clair
 *   A+B=1+0=jaune
 *   A+B=1+1=rouge
 *  par exemple [1100][0011] donnera 2 pixels jaune suivi de 2 pixels bleu clair &C3
 * mode 0 : 
 *   1 octet <=> 2 pixels
 *   [AA][BB][CC][DD] : superposition des couleurs de AA, BB, CC, DD
 *   comme il y a "trop" de combinaisons pour une sortie RGB sans variation de lumière
 *   ils ont fait clignoter les dernière combinaisons. La variation de lumière a été
 *   ajouté par la suite, avec PEN/PAPER...
 * mode 2 :
 *   1 octet <=> 8 pixels
 *   [AAAAAAAA] : on a donc que 2 couleurs xD
 *
 */
void set_pixel_color0(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
{
	unsigned char nByte = *pByteAddress;
	if (nPixel == 0) {
		nByte&=85; // nByte = nByte & 85
		
		// AND
		// 0&0 --> 0
		// 1&0 --> 0
		// 0&1 --> 0
		// 1&1 --> 1
		
		// OR
		// 0|0 --> 0
		// 1|0 --> 1
		// 0|1 --> 1
		// 1|1 --> 1
		
		if (nColor & 1) nByte |=128;
		if (nColor & 2) nByte |=8;
		if (nColor & 4) nByte |=32;
		if (nColor & 8) nByte |=2;
	} else {
		nByte&=170;
		if (nColor & 1) nByte |=64;
		if (nColor & 2) nByte |=4;
		if (nColor & 4) nByte |=16;
		if (nColor & 8) nByte |=1;
	}
	*pByteAddress = nByte;
}

// 0..159 et 0..199
void put_pixel0(unsigned char nX, unsigned char nY, unsigned char nColor)
{
	unsigned char nPixel = 0;
	unsigned int nAddress = 0xC000 + ((nY / 8) * 80) + ((nY % 8) * 2048) + (nX / 2);
	nPixel = nX % 2;
	set_pixel_color0((unsigned char *)nAddress, nColor, nPixel);
}

void set_pixel_color1(unsigned char *pByteAddress, unsigned char nColor, unsigned char nPixel)
{
	unsigned char nByte = *pByteAddress;
	if (nPixel == 0) {
		nByte&=119;
		if (nColor & 1) nByte |=128;
		if (nColor & 2) nByte |=8;
	} else if (nPixel == 1) {
		nByte&=187;
		if (nColor & 1) nByte |=64;
		if (nColor & 2) nByte |=4;
	} else if (nPixel == 2) {
		nByte&=234;
		if (nColor & 1) nByte |=32;
		if (nColor & 2) nByte |=2;
	} else {
		nByte&=238;
		if (nColor & 1) nByte |=16;
		if (nColor & 2) nByte |=1;
	}
	
	*pByteAddress = nByte;
}

// 0..319 et 0..199
void put_pixel1(unsigned char nX, unsigned char nY, unsigned char nColor)
{
	unsigned char nPixel = 0;
	unsigned int nAddress = 0xC000 + ((nY / 8) * 80) + ((nY % 8) * 2048) + (nX / 4);
	nPixel = nX % 4;
	set_pixel_color1((unsigned char *)nAddress, nColor, nPixel);
}
