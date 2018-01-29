////////////////////////////////////////////////////////////////////////
// Load01.c
// Mochilote - www.cpcmania.com
////////////////////////////////////////////////////////////////////////

#ifndef JDVAPI_FLOPPY_H
#define JDVAPI_FLOPPY_H

/**
 * http://www.cpcmania.com/Docs/Programming/Files.htm
 */
//SetupDOS - Prepare DOS for file load
void SetupDOS();
//Load filename to address :
// SetupDOS();
// LoadFile("01.scr", (char *)0xC000);
//ou :
// int nImage = 0;
// char sFile[32];
// sprintf(sFile, "0%d.scr", nImage);
// LoadFile(sFile, (char *)0xC000);
void LoadFile(char *sFileName, char *pLoadAddress);

#endif