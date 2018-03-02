// pour memcpy
#include <stdio.h>
// pour memcpy
#include <string.h>

void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image)
{
  __asm
    LD L, 4(IX) 		; HL --> Adr destination
    LD H, 5(IX) 
    LD C, 6(IX) 		; C --> Largeur en octet
    LD B, 7(IX)         ; B --> Hauteur
    LD E, 8(IX) 		; DE --> Adresse image source.
    LD D, 9(IX) 

    _loop_alto000:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_ancho000:
       LD A,(DE)			; Met dans A un octet de de la source
       LD (HL),A			; Met dans la destination A
       INC DE				; Avance dans l'adresse de la source
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_ancho000		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_linea000	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea000:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_alto000		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
  __endasm;
}

void put_frame_transparent(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image)
{
  __asm
    LD L, 4(IX) 		; HL --> Adr destination
    LD H, 5(IX) 
    LD C, 6(IX) 		; C --> Largeur en octet
    LD B, 7(IX)         ; B --> Hauteur
    LD E, 8(IX) 		; DE --> Adresse image source.
    LD D, 9(IX) 

    _loop_alto001:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_ancho001:
       LD A,(DE)			; Met dans A un octet de de la source
       OR A,(HL)			; OR A un octet de de la destination
       LD (HL),A			; Met dans la destination A
       INC DE				; Avance dans l'adresse de la source
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_ancho001		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_linea001	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea001:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_alto001		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
  __endasm;
}

void erase_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight)
{
  __asm
    LD L, 4(IX) 		; HL --> Adr destination
    LD H, 5(IX) 
    LD C, 6(IX) 		; C --> Largeur en octet
    LD B, 7(IX)         ; B --> Hauteur

    _loop_alto002:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_ancho002:
       LD (HL),#0x00		; Met 0x00 dans la destination A
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_ancho002		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_linea002	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea002:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_alto002		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
  __endasm;
}

void get_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *backup)
{
	// chie un peu dans la colle mais fait des trucs, utiliser save_frame() de MiGaNuts plutôt :P
  __asm
    LD L, 4(IX) 		; HL --> Adr source
    LD H, 5(IX) 
    LD C, 6(IX) 		; C --> Largeur en octet
    LD B, 7(IX)         ; B --> Hauteur
    LD E, 8(IX) 		; DE --> Adresse backup.
    LD D, 9(IX) 

    _loop_alto003:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_ancho003:
       LD A,(HL)			; Met dans A un octet de la source
       LD (DE),A			; Backup A
       INC DE				; Avance dans l'adresse de la backup
       INC HL				; Avance dans l'adresse de la source
       DJNZ _loop_ancho003		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_linea003	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea003:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_alto003		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
  __endasm;
}

unsigned char* scr_next_line( unsigned char* adresse)
{
	/*
	   &BC26 - SCR NEXT LINE
	   Calculates the screen address of the byte below the specified
	   screen address.
	   ENTRY
	   • L HL contains the screen address.
	   EXIT
	   • L HL contains the screen address of the byte below the original
	   screen address.
	   • F AF is corrupt, and all the other registers are preserved.
	*/
  __asm
	LD L, 4(IX) ; HL --> Adr destination
	LD H, 5(IX)
	call #0xbc26
  __endasm;
}

// idem que get_frame mais qui marche
void save_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *image)
{
	//*pAddress : adresse ou on va "sauver" les données
	//*image : adresse de la zone a découper
	//nWidth et nHeight : largeur et hauteur de la zone
	unsigned char i;
	for (i=0; i<nHeight; i++){
		memcpy(pAddress,image,(unsigned int) nWidth);
		image=scr_next_line(image);
		pAddress=pAddress+nWidth;
	}
}

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
unsigned int private_precalc_vram[200];

unsigned int * precalc_vram()
{
	//char i; //#define screen(x,y) ((unsigned char *)(vram[y]+x))
	unsigned char i; //#define screen(x,y) ((unsigned char*)vram[y]+(x>>1))
	
	for (i=0;i<200;i++)
	{
		private_precalc_vram[i]=(0xC000 + ((i / 8u) * 80u) + ((i % 8u) * 2048u));		
		
	}
	
	return (unsigned int *)private_precalc_vram;
}

