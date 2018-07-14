// pour memcpy
// #include <stdio.h>
// pour memcpy
// #include <string.h>

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

/* public class mode1inverse {
	public static void main(String [] args) {
		for (int i=0;i<256;i++) {
			String binary = "00000000000000000000"+Integer.toBinaryString(i);
			binary=binary.substring(binary.length()-8,binary.length());
			//System.out.print(binary);
			String binary2= ""+binary.charAt(3)+binary.charAt(2)+binary.charAt(1)+binary.charAt(0)+binary.charAt(7)+binary.charAt(6)+binary.charAt(5)+binary.charAt(4);
			//System.out.println("=>"+binary2);
			System.out.print(Integer.parseInt(binary2,2));
			System.out.print(",");
		}
		System.out.println();
	}
} */

const unsigned char inverse_frame_mode1[]=
{
		0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15,128,136,132,140,130,138,134,142,129,137,133,141,131,139,135,143,64,72,68,76,66,74,70,78,65,73,69,77,67,75,71,79,192,200,196,204,194,202,198,206,193,201,197,205,195,203,199,207,32,40,36,44,34,42,38,46,33,41,37,45,35,43,39,47,160,168,164,172,162,170,166,174,161,169,165,173,163,171,167,175,96,104,100,108,98,106,102,110,97,105,101,109,99,107,103,111,224,232,228,236,226,234,230,238,225,233,229,237,227,235,231,239,16,24,20,28,18,26,22,30,17,25,21,29,19,27,23,31,144,152,148,156,146,154,150,158,145,153,149,157,147,155,151,159,80,88,84,92,82,90,86,94,81,89,85,93,83,91,87,95,208,216,212,220,210,218,214,222,209,217,213,221,211,219,215,223,48,56,52,60,50,58,54,62,49,57,53,61,51,59,55,63,176,184,180,188,178,186,182,190,177,185,181,189,179,187,183,191,112,120,116,124,114,122,118,126,113,121,117,125,115,123,119,127,240,248,244,252,242,250,246,254,241,249,245,253,243,251,247,255
};

void put_inversed_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image)
{
  __asm
    LD L, 4(IX) 		; HL --> Adr destination
    LD H, 5(IX) 
    LD C, 6(IX) 		; C --> Largeur en octet
    LD B, 7(IX)         ; B --> Hauteur
    LD E, 8(IX) 		; DE --> Adresse image source.
    LD D, 9(IX) 

    _loop_alto004:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
	   
	  LD B,#0x0
	  ADD HL, BC
	  DEC HL
	  
      LD B,C				; Charge C (width) dans B
      
    _loop_ancho004:
       LD A,(DE)			; Met dans A un octet de de la source
	   
	   PUSH BC
	   PUSH HL
	   LD C,A
	   LD B,#0x0
	   LD HL, #_inverse_frame_mode1
	   ADD HL, BC
	   LD A,(HL)
	   POP HL
	   POP BC
	   
       LD (HL),A			; Met dans la destination A
	   
       INC DE				; Avance dans l'adresse de la source
      ; INC HL				; Avance dans l'adresse de la destination
	   DEC HL
	   
       DJNZ _loop_ancho004		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_linea004	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea004:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_alto004		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
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

/*void get_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *backup)
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
	
	//   &BC26 - SCR NEXT LINE
	//   Calculates the screen address of the byte below the specified
	//   screen address.
	//   ENTRY
	//   • L HL contains the screen address.
	//   EXIT
	//   • L HL contains the screen address of the byte below the original
	//   screen address.
	//   • F AF is corrupt, and all the other registers are preserved.
  __asm
	LD L, 4(IX) ; HL --> Adr destination
	LD H, 5(IX)
	call #0xbc26
  __endasm;
}

// idem que get_frame mais qui marche
void save_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, unsigned char *image)
{
	// *pAddress : adresse ou on va "sauver" les données
	// *image : adresse de la zone a découper
	//nWidth et nHeight : largeur et hauteur de la zone
	unsigned char i;
	for (i=0; i<nHeight; i++){
		memcpy(pAddress,image,(unsigned int) nWidth);
		image=scr_next_line(image);
		pAddress=pAddress+nWidth;
	}
}*/

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
unsigned int private_precalc_vram[200];

unsigned int * precalc_vram()
{
	unsigned char i;
	
	for (i=0;i<200;i++)
	{
		//private_precalc_vram[i]=(0xC000 + ((i / 8u) * 80u) + ((i % 8u) * 2048u));
		private_precalc_vram[i]=(((i / 8u) * 80u) + ((i % 8u) * 2048u));
	}
	
	return (unsigned int *)private_precalc_vram;
}

