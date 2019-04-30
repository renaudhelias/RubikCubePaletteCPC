BuffTmp EQU     #6400                   ; Buffer décompactage temporaire
BuffCmp EQU     #2000                   ; Buffer image compactée

        ORG     #A400

        ;
        ; Vérifier fichier est bien image compactée
        ;
        LD      HL,BuffCmp
        LD      A,(HL)                  ; Vérifier en-tête du fichier
        CP      'P'
        RET     NZ
        INC     HL
        LD      A,(HL)                  ; Doit commencer par "PKS"
        CP      'K'
        RET     NZ
        INC     HL
        LD      A,(HL)
        CP      'S'
        RET     NZ
        INC     HL
        LD      A,(HL)                  ; Puis, 4e octet = type d'image
        CP      'L'                     ; 'L' = image "normale"
        JR      Z,ImgType1
        CP      'P'                     ; 'P' = image CPC+
        JR      Z,ImgType2
        CP      '3'                     ; '3' = image "mode 3"
        JR      Z,ImgType3
        RET                             ; Si pas identifié, retour...

;
; Image type 1 - CPC "OLD" en mode 0, 1 ou 2
;
ImgType1:
        LD      HL,BuffCmp+21           ; Données image en #2015
        CALL    DecompImage
        EI
        LD      A,(BuffCmp+4)           ; Mode en #2004
        CALL    #BD1C                   ; Chgt Mode sans effacer l'écran
        LD      HL,BuffCmp+5            ; Palette en #2005
        XOR     A
SetCol:
        PUSH    AF
        PUSH    HL
        LD      B,(HL)
        LD      C,B
        CALL    #BC32                   ; Initialisation palette de couleurs
        POP     HL
        POP     AF
        INC     HL
        INC     A
        CP      16
        JR      C,SetCol
        JP      #BB18                   ; Attendre appui sur une touche

;
; Image type 2 - CPC + en mode 0, 1 ou 2
;
ImgType2:
        LD      HL,BuffCmp+37           ; Données image en #2025
        CALL    DecompImage
        LD      BC,#BC11
        LD      HL,UnlockAsic           ; Séquence de déverouillage de l'ASIC
SetSeq:
        LD      A,(HL)
        OUT     (C),A                   ; Envoi des données
        INC     HL
        DEC     C
        JR      NZ,SetSeq
        LD      A,(BuffCmp+4)           ; Mode écran en #2004
        LD      BC,#7FB8
        OUT     (C),C
        OUT     (C),A
        LD      HL,BuffCmp+5            ; Palette CPC+ en #2005
        LD      de,#6400
        LD      BC,17*2
        LDIR
Boucle:
        CALL    TstEspace               ; Test touche espace appuyée
        JR      C,Boucle                ; Si non, attendre
        LD      BC,#7FA0
        OUT     (C),C
        EI
        RET

;
; Image type 3 - CPC old en mode "3" (Mode 1 avec 6 couleurs/lignes)
;
ImgType3:
        LD      HL,BuffCmp+1206         ; Données image en #24B6
        CALL    DecompImage
        LD      HL,(#38)
        LD      (RestoreIRQ+1),HL       ; Sauvegarde ancien vecteur #38
        LD      HL,#C9FB
        LD      (#38),HL                ; EI et RET en #38
        LD      BC,#7F8D
        OUT     (C),C                   ; Mode 1
        XOR     A
        OUT     (C),A                   ; Sélectionner couleur 0
        LD      HL,BuffCmp+4            ; Adresse de la valeur de la couleur 0
        OUTI                            ; Et affecter
BoucleImg3:
        LD      B,#F5
WaitVBL:
        IN      A,(C)                   ; Attendre la VBL
        RRA
        JR      NC,WaitVBL
        CALL    TstEspace               ; test touche espace appuyée
        JR      NC,FIN                  ; si oui, fini
        EI
        HALT                            ; Attendre 2 interruptions
        HALT
        DI
        LD      B,158
Wait1:
        LD      HL,0                    ; Pause pour se synchroniser au début
        DJNZ    Wait1                   ; de l'écran visible
        XOR     A                       ; A = 0 pour tester fin des couleurs
        LD      BC,#7F01                ; C = ink 1
        LD      HL,BuffCmp+5            ; Palette en #2005
        LD      DE,#203                 ; D = ink 2, E = ink 3
SetCoul:
        OUT     (C),C                   ; ink 1
        OUTI
        OUT     (C),D                   ; ink 2
        OUTI
        OUT     (C),E                   ; ink 3
        OUTI
        NOP
        NOP                             ; Temps d'attente
        LD      BC,#7F01                ; Repositionner registre B
        OUT     (C),C                   ; ink 1
        OUTI
        OUT     (C),D                   ; ink 2
        OUTI
        OUT     (C),E                   ; ink 3
        OUTI
        CP      (HL)                    ; Valeur = 0 ?
        JR      NZ,SetCoul              ; Si non, on continue
        JR      BoucleImg3              ; Boucle attente touche

Fin:
        DI
RestoreIRQ:
        LD      HL,0
        LD      (#38),HL                ; Restaurer ancien vecteur #38
        EI
        RET

        ;
        ; Décompacter l'image dans un buffer temporaire
        ;
DecompImage:
        DI
        LD      DE,BuffTmp
        CALL    DepkLzw

        ;
        ; Efface l'écran (toutes les couleurs à 0)
        ;
        LD      BC,#7F54
        LD      A,#11
Cls:
        DEC     A
        OUT     (C),A
        OUT     (C),C
        JR      NZ,Cls

        ;
        ; Affiche la nouvelle image
        ;
        LD      DE,BuffTmp
        LD      HL,#C000
Draw1:
        LD      A,200
Draw2:
        EX      DE,HL
        LDI
        EX      DE,HL
        LD      BC,#7FF
        ADD     HL,BC
        JR      NC,Draw3
        LD      BC,#C050
        ADD     HL,BC
Draw3:
        DEC     A
        JR      NZ,Draw2
        LD      BC,#7CF
        SBC     HL,BC
        LD      A,L
        CP      #50
        JR      C,Draw1
        RET

;
; Lecture clavier (et notamment la touche espace...)
;
TstEspace:
        XOR     A
        LD      BC,#F40E                ; Registre 14 du PSG
        OUT     (C),C
        LD      BC,#F6C0                ; Ecriture numéro registre
        OUT     (C),C
        OUT     (C),A
        LD      BC,#F792                ; Port A PPI en lecture
        OUT     (C),C
        LD      BC,#F645                ; ligne = 5 (pour touche espace)
        OUT     (C),C
        LD      B,#F4                   ; Lecture registre
        IN      A,(C)
        LD      BC,#F782                ; Repasse port A PPI en écriture
        OUT     (C),C
        RLA                             ; Bit 7 dans Flag C
        RET

UnlockAsic:
        DB      #FF, #00, #FF, #77, #B3, #51, #A8, #D4
        DB      #62, #39, #9C, #46, #2B, #15, #8A, #CD, #EE

        read    "DepkLzw.asm"
