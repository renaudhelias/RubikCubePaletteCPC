;
; Routine d'affichage d'une image en overscan (version CPC +)
; On positionne la mémoire vidéo à partir de l'adresse #200
; La zone #800 à #9FF est libre, et peut donc être utilisée
; pour le stockage du mode, des couleurs, et de la routine d'affichage.
;
        ORG    #800
Mode:
        DB      0
Palette:
        DS      32

        DI
        LD      BC,#BC11
        LD      HL,UnlockAsic
SetSeq:
        INC B
        OUTI
        DEC     C
        JR      NZ,SetSeq

        LD      HL,Overscan
        CALL    SetCrtc
        LD      BC,#7FB8                ; ASIC Page On
        LD      A,(Mode)                ; Mode écran
        OUT     (C),C
        OUT     (C),A
        LD      HL,Palette              ; Palette CPC+
        LD      DE,#6400
        LD      BC,16*2
        LDIR
Boucle:
;
; Lecture clavier (et notamment la touche espace...)
;
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
        JR      C,Boucle                ; Si non, attendre
        LD      BC,#7FA0                ; ASIC Page Off
        OUT     (C),C
        EI
        LD      HL,NoOverscan
SetCrtc:
        LD      BC,#BC
Bcl:
        LD      A,(HL)
        AND     A
        RET     Z
        OUT     (C),A
        INC     B
        INC     HL
        LD      A,(HL)
        OUT     (C),A
        INC     HL
        DEC     B
        JR      Bcl

UnlockAsic:
        DB      #FF, #00, #FF, #77, #B3, #51, #A8, #D4
        DB      #62, #39, #9C, #46, #2B, #15, #8A, #CD, #EE
Overscan:
        DB      1,48,2,50,6,34,7,35,12,13,13,0,0,0
NoOverscan:
        DB      1,40,2,46,6,25,7,30,12,48,0,0
