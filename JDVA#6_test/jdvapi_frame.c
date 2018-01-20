
void put_frame(unsigned char *pAddress, unsigned char nWidth, unsigned char nHeight, const unsigned char *image)
{
  __asm
    LD L, 4(IX) 		; HL --> Adr destination
    LD H, 5(IX) 
    LD C, 6(IX) 		; C --> Largeur en octet
    LD B, 7(IX)         ; B --> Hauteur
    LD E, 8(IX) 		; DE --> Adresse image source.
    LD D, 9(IX) 

    _loop_alto:
       PUSH BC				; Sauvegarde de BC sur la pile (width et height)
       LD B,C				; Charge C (width) dans B
       PUSH HL				; Sauvegarde de HL (adresse de la destination)
    _loop_ancho:
       LD A,(DE)			; Met dans A un octet de de la source
       LD (HL),A			; Met dans la destination A
       INC DE				; Avance dans l'adresse de la source
       INC HL				; Avance dans l'adresse de la destination
       DJNZ _loop_ancho		; Décrémente B qui contient la largeur. Si on à pas finit de copier 
							; l'équivalent de la largeur on saute à _loop_ancho.
       POP HL				; récupère l'adresse de la cible sauvegardé sur la pile
       LD A,H				; Charge la partie haute dans A
       ADD #0x08			; Ajoute la valeur 8 à A --> Permet de passer à la ligne suivante
       LD H,A				; Réinjecte A dans H, HL nous donne ainsi l'adresse de début de la ligne suivante
       SUB #0xC0			; On vérifie que la ligne suivante en mémoire n'est pas à remonter ... 
       JP NC, _sig_linea	; Non, elle est à la suite en mémoire donc tout va bien
       LD BC, #0xC050		; On doit remonter, on va ajouter C000 (notre page par défaut + 0x080 pour la ligne suivante)
       ADD HL,BC			; Ajoute ça dans l'adresse de destination --> On est sur la nouvelle ligne
    _sig_linea:
       POP BC				; Récupère BC --> pour récupérer la hauteur
       DJNZ _loop_alto		; Enlève 1 à la hauteur, si on à pas tout traité, on reboucle au début _loop_alto
  __endasm;
}

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */
unsigned int private_precalc_vram[200];

unsigned int * precalc_vram()
{
	char i;
	
	for (i=0;i<200;i++)
	{
		private_precalc_vram[i]=(0xC000 + ((i / 8u) * 80u) + ((i % 8u) * 2048u));		
		
	}
	
	return (unsigned int *)private_precalc_vram;
}
