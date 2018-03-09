nolist
;	org #2000
;	run $

;	STarKos Player V1.2 - Official Release.

;	By Targhan/Arkos
;	17/04/09
;

;	There are three kind of players included. To use one or another, simply comment/uncomment the two labels SAVEBCAF
;	and BASICINT according to the one you want.

;	- Normal ('ASM'). No registers are saved, all are modified. You have to call the player by yourself.
;	Will be used by most coders in Assembler.
;	Use =
;	ld de,SongAddress
;	call PlayerAddress   / INITZIC		to initialise the song
;	call PlayerAddress+3 / PLAY 		to play the song. Call it whenever it needs to be (50, 100 times a second...)
SAVEBCAF equ 0
BASICINT equ 0

;	- 'BASIC'. Registers are saved. You have to call the player by yourself.
;	Especially used by coders in Basic. But you can use it in Assembler too.
;	Use in ASM = see above.
;	Use in BASIC = call PlayerAddress,SongAddress to initialise the song
;		       call PlayerAddress+3    whenever it needs to be called (50, 100 times a second...)
;SAVEBCAF equ 1
;BASICINT equ 0

;	- 'INTERRUPTION'. Launch it once and it will call the song on its own. It of course uses the system interruptions,
;	So do not disable them !
;	Interruption Player must be set at >#4000 !!
;	Use in ASM =
;	ld de,SongAddress
;	call PlayerAddress		and that's it.
;	call PlayerAddress+3		To stop the song.
;	Use In BASIC =
;	call PlayerAddress,SongAddress	Once and for all.
;	call PlayerAddress+3		To stop the song.

;SAVEBCAF equ 1
;BASICINT equ 1






SIZEINSTRNEWHEADER equ 7	;Taille nouveau header son.





;******* Enclenchement interruptions
	if BASICINT

	jp INTERON
	jp INTEROFF
	defw $-6			;Pour connaitre l'adr d'origine du player

DIGI	defb 0				;Digidrum a jouer
SPLCHAN	defb 0				;Chanel du digidrum (1,2,3)

INTERON	call INITZIC
	ld hl,FREQCONV
REPFREQ ld a,0		;a=low byte de frequence (13,25,50,100,150,44)
REPFRLP	cp (hl)
	jr z,REPOK
	inc hl
	inc hl
	jr REPFRLP
REPOK
	inc hl
	ld a,(hl)	;Chope nbinter wait
	ld (IPWAIT+1),a
	xor a
	ld (IPWCPT+1),a

	ld hl,BLOCCTRL
	ld bc,%10000001*256+0
	ld de,INTERPLAY
	jp #bce0
INTEROFF ld hl,BLOCCTRL
	call #bce6
	jp STOPSNDS

BLOCCTRL defs 10,0

;Routine qui va lancer PLAY en fct de frequence replay.
INTERPLAY di

IPWCPT	ld a,0
	sub 1
	jr c,IPPLAY
	ld (IPWCPT+1),a
	ret

IPPLAY
IPWAIT	ld a,0
	ld (IPWCPT+1),a
	jp PLAY


;Sert a convertir freq --> no freq
;Format=lowbyte freq et nb inter wait
FREQCONV defb 13,17,  25,11,  50,5,  100,2,  150,1,  44,0


	else
;******* Player Basic RAW ou ASM.
	jp INITZIC
	jp PLAY
	jp STOPSNDS

	defw $-9			;Pour connaitre l'adr d'origine du player

DIGI	defb 0				;Digidrum a jouer
SPLCHAN	defb 0				;Chanel du digidrum (1,2,3)
	endif





;Joue la musique
PLAY	xor a			;0=pas de digidrum
	ld (DIGI),a
	ld (RETRIG+1),a


	if SAVEBCAF
	 di
	 ex af,af'
	 exx
	 push af
	 push bc
	 push ix
	 push iy
	endif


PLAYWAIT ld a,0			;Nb VBL avant prochaine ligne (speed). inc.
PLAYSPEED cp 0			;Si pas a =speed, on continue les sons
	jr z,PLAYNEWLINE
	inc a
	ld (PLAYWAIT+1),a
	jp CONTSNDS

;On va entamer une nouvelle ligne dans pattern
PLAYNEWLINE xor a
	ld (PLAYWAIT+1),a
ISPATTEND or a			;Signal pour tester fin patt, envoyé par lecteur de patt. ('or a'=#b7  /'scf'=#37)
	jp nc,READPATT		;Pas de carry=continue pattern



;Nouvelle pattern.
	ld (TR1WAIT+1),a
	ld (TR2WAIT+1),a
	ld (TR3WAIT+1),a
	ld a,#b7		;Remet un OR A
	ld (ISPATTEND),a




;Gere transp.

;DB oct1 = bit 0=1=pas de transp pdt (bit 7-1) lignes
;          bit 0=0=TR1=bit (7-3) + bit(2-1)TR2 (=bits de poids fort)
;	          DB oct2. TR2=bit (7-5) (=faible) TR3=bit (4-0)

TRWAIT	ld a,0			;Nb lignes a attendre
	sub 1
	jr nc,TRFIN

PTTRANSPSTAB ld hl,0		;Lis nouvelle donnee TRANSP
	ld a,(hl)
	inc hl

	srl a
	jr c,TRFI0		;Carry=wait. Bit 7-1=wait.
				;Transp trouvee
	ld b,a			;S'occupe du transp1 (sauve a vers b)
	and %11111
	bit 4,a
	jr z,TRT1
	or %11100000
TRT1	ld (TRANSP1+1),a
;
	rl b
	rl b			;tr2 presente ?
	jr nc,TRF2
	ld a,(hl)
	ld (TRANSP2+1),a
	inc hl

TRF2	rl b			;tr3 presente ?
	jr nc,TRF3
	ld a,(hl)
	ld (TRANSP3+1),a
	inc hl

TRF3
	ld (PTTRANSPSTAB+1),hl
	jr TRFI2

TRFI0	ld (PTTRANSPSTAB+1),hl
TRFIN	ld (TRWAIT+1),a
TRFI2




;Lis HEIGHTSTAB
HTWAIT	ld a,0			;Nb pattern avant de lire encore HEIGHTSTAB
	sub 1
	jr c,PTHEIGHTSTAB
	ld (HTWAIT+1),a
HTOLDHEIGHT ld a,0		;Stocke l'ancienne hauteur stockee si several hauteur
	jr HTFI2

PTHEIGHTSTAB ld hl,0		;Lis nouvelle donnee HEIGHTSTAB
	ld a,(hl)
	inc hl
	srl a
	jr c,HTSEVERAL
;
	ld (PTHEIGHTSTAB+1),hl	;One height trouvee. Set nouvelle hauteur
	jr HTFI2
HTSEVERAL 
	ld (HTOLDHEIGHT+1),a	;Plusieurs heights trouvee. Set nouvelle hauteur pour now et plus tard aussi.
	ld b,a
	ld a,(hl)		;Chope la qqt de cette hauteur
	inc hl
	ld (PTHEIGHTSTAB+1),hl
;
HTFIN	ld (HTWAIT+1),a
 	 ld a,b
HTFI2	 ld (PATTHEIGHT+1),a



;Lis TRACKSTAB
PTTRACKSTAB ld hl,0
	ld de,PTTRACK1+1
	ldi
	ldi
	ld de,PTTRACK2+1
	ldi
	ldi
	ld de,PTTRACK3+1
	ldi
	ldi
	ld (PTTRACKSTAB+1),hl




;Lis STRACKSTAB
STSTATE	ld a,0		;0=egal 1=diff
	or a
	jr nz,STDIFF

STEWAIT	ld a,0
	sub 1
	jr c,STNEW

STECONT	ld (STEWAIT+1),a
STESTR	ld hl,0		;STRACK sauvee a repeter
	jr PTSTR2



STDIFF
STDWAIT ld a,0
	sub 1
	jr c,STNEW
	ld (STDWAIT+1),a
	ld hl,(PTSTRACKSTAB+1)
	jr STNDGET


STNEW
PTSTRACKSTAB ld hl,0
	ld a,(hl)		;Chope new state
	inc hl
	srl a
	jr c,STNEWDIFF
	ld (STEWAIT+1),a	;New identique
	xor a
	ld (STSTATE+1),a
	ld e,(hl)		;Chope strack adr identique et inc compteur
	inc hl
	ld d,(hl)
	inc hl
	ld (PTSTRACKSTAB+1),hl
	ex de,hl
	ld (STESTR+1),hl
	jr PTSTR2		;On se permet de skipper le test wait car on sait qu'il est a 0 !
STNEWDIFF ld (STDWAIT+1),a	;New diff
	ld a,1
	ld (STSTATE+1),a
STNDGET	ld e,(hl)		;Chope strack adr diff et inc compteur
	inc hl
	ld d,(hl)
	inc hl
	ld (PTSTRACKSTAB+1),hl
	ex de,hl
	jr PTSTR2		;On se permet de skipper le test wait car on sait qu'il est a 0 !








;Lis pattern (=strack+tracks)
READPATT


;Lis STRACK
STRWAIT	ld a,0			;Nb lignes vides a attendre avant lecture nouvelle ligne
	sub 1
	jr nc,STRFIN

PTSTRACK ld hl,0
PTSTR2	ld a,(hl)
	inc hl
	srl a
	jr c,STRSETW		;Carry=new wait
;
	srl a
	jr c,STRDIGI
	ld (PLAYSPEED+1),a	;Set speed
	jr STRSETX
STRDIGI	ld (DIGI),a		;Set digidrum
NOSPLCHAN ld a,1		;Set Spl Chan (cette val est settee lors de l'init)
	ld (SPLCHAN),a
STRSETX	xor a
STRSETW	ld (PTSTRACK+1),hl
STRFIN	ld (STRWAIT+1),a






;Lis les 3 TRACKS
TR1WAIT	ld a,0			;Nb ligne vides pour TRACK 1
	sub 1
	jr nc,TR1FIN

;d=transp
;e=instr   c=vol
;b=channel (1,2,3)
;hl'=now pitch
PTTRACK1 ld hl,0
;TRANSP1 ld d,0
DECVOL1 ld bc,#0100
INSTR1	ld de,0
TRANSP1 equ INSTR1+1
NOTE1	defb #dd : ld l,0

;
	call READTRACK
;
	defb #dd : ld a,l	;Chope note modifiee ou non.
	ld (NOTE1+2),a
;
	ld (PITADD1+1),hl
	exx
	ld (PTTRACK1+1),hl
	ld a,c
	ld (DECVOL1+1),a
	ld (DECVOL12+1),a
;
	xor a
	;ld (INOWSTP1+1),a
	defb #fd : or h		;Recalcule instr ? 0=oui. Si 1, l'instr continue.
	jr nz,TR1FI0
;
TR1NEW	ld (INOWSTP1+1),a
	ld d,a

	ld a,e
	ld (INSTR1+1),a

	ld l,d			;Si nouvo son, pitch=0 (pitchadd deja updaté)
	ld h,l
	ld (PITCH1+1),hl

PTINSTRS1 ld hl,0
	ex de,hl
	add hl,hl
	add hl,de
;
	ld a,(hl)
	inc hl
	ld h,(hl)
	ld l,a
	ld de,ADILOOP1+1
	ldi
	ldi
	ld de,ADIEND1+1
	ldi
	ldi
	ld de,ISTEP1+1
	ldi

	ld de,ADIISLOOP1
	ldi

	ld a,(hl)
	inc hl
	ld (PTSND1+1),hl

	ld hl,RETRIG+1
	or (hl)
	ld (hl),a

TR1FI0	defb #fd : ld a,l		;Recupere TRWAIT depuis lix
TR1FIN
	ld (TR1WAIT+1),a




TR2WAIT	ld a,0			;Nb ligne vides pour TRACK 2
	sub 1
	jr nc,TR2FIN

PTTRACK2 ld hl,0
;TRANSP2	ld d,0
DECVOL2 ld bc,#0200
INSTR2	ld de,0
TRANSP2	equ INSTR2+1
NOTE2	defb #dd : ld l,0

	call READTRACK
;
	defb #dd : ld a,l	;Chope note modifiee ou non.
	ld (NOTE2+2),a
;
	ld (PITADD2+1),hl
	exx
	ld (PTTRACK2+1),hl
	ld a,c
	ld (DECVOL2+1),a
	ld (DECVOL22+1),a
;
	xor a
	defb #fd : or h		;Recalcule instr ? 0=oui. Si 1, l'instr continue.
	jr nz,TR2FI0
;
TR2NEW	ld (INOWSTP2+1),a
	ld d,a
;
	ld a,e
	ld (INSTR2+1),a

	ld l,d			;Si nouvo son, pitch=0 (pitchadd deja updaté)
	ld h,l
	ld (PITCH2+1),hl

PTINSTRS2 ld hl,0
	ex de,hl
	add hl,hl
	add hl,de
;
	ld a,(hl)
	inc hl
	ld h,(hl)
	ld l,a
	ld de,ADILOOP2+1
	ldi
	ldi
	ld de,ADIEND2+1
	ldi
	ldi
	ld de,ISTEP2+1
	ldi

	ld de,ADIISLOOP2
	ldi

	ld a,(hl)
	inc hl
	ld (PTSND2+1),hl

	ld hl,RETRIG+1
	or (hl)
	ld (hl),a

TR2FI0	defb #fd : ld a,l		;Recupere TRWAIT depuis lix
TR2FIN
	ld (TR2WAIT+1),a





TR3WAIT	ld a,0			;Nb ligne vides pour TRACK 3
	sub 1
	jr nc,TR3FIN

PTTRACK3 ld hl,0
;TRANSP3	ld d,0
DECVOL3 ld bc,#0300
INSTR3	ld de,0
TRANSP3	equ INSTR3+1
NOTE3	defb #dd : ld l,0

	call READTRACK
;
	defb #dd : ld a,l	;Chope note modifiee ou non.
	ld (NOTE3+2),a
;
	ld (PITADD3+1),hl
	exx
	ld (PTTRACK3+1),hl
	ld a,c
	ld (DECVOL3+1),a
	ld (DECVOL32+1),a
;
	xor a
	defb #fd : or h		;Recalcule instr ? 0=oui. Si 1, l'instr continue.
	jr nz,TR3FI0
;
TR3NEW	ld (INOWSTP3+1),a
	ld d,a
;
	ld a,e
	ld (INSTR3+1),a

	ld l,d			;Si nouvo son, pitch=0 (pitchadd deja updaté)
	ld h,l
	ld (PITCH3+1),hl

PTINSTRS3 ld hl,0
	ex de,hl
	add hl,hl
	add hl,de
;
	ld a,(hl)
	inc hl
	ld h,(hl)
	ld l,a
	ld de,ADILOOP3+1
	ldi
	ldi
	ld de,ADIEND3+1
	ldi
	ldi
	ld de,ISTEP3+1
	ldi

	ld de,ADIISLOOP3
	ldi

	ld a,(hl)
	inc hl
	ld (PTSND3+1),hl

	ld hl,RETRIG+1
	or (hl)
	ld (hl),a

TR3FI0	defb #fd : ld a,l		;Recupere TRWAIT depuis lix
TR3FIN
	ld (TR3WAIT+1),a











;Gere la fin de pattern
PATTHEIGHT ld a,0
	sub 1
	jr c,PATTHEIGH2		;Carry=fin de zic
	ld (PATTHEIGHT+1),a
	jr CONTSNDS
PATTHEIGH2 ld a,#37		;Place un SCF quand pattern finie.
	ld (ISPATTEND),a





;Teste fin musique
	ld hl,(PTTRACKSTAB+1)
ADENDPOS ld de,0		;Adresse se trouvant APRES TRACKSTAB, utile pour tester si fin zic atteinte
	xor a
	sbc hl,de
	jr nz,ADENDPO2
;Fin musique !
	ld (TRWAIT+1),a
	ld (HTWAIT+1),a
	ld (STRWAIT+1),a
ADTRANSPSLOOP ld hl,0
	ld (PTTRANSPSTAB+1),hl
ADHEIGHTSLOOP ld hl,0
	ld (PTHEIGHTSTAB+1),hl
ADTRACKSLOOP ld hl,0
	ld (PTTRACKSTAB+1),hl
ADSTRACKSLOOP ld hl,0
	ld (PTSTRACKSTAB+1),hl
STSTATLOOP ld a,0		;Place etat de bouclage pour strack (egal/diff)
	ld (STSTATE+1),a
;
ADENDPO2



;On continue de jouer les sons
CONTSNDS
;Entree PLAYSND=
;HL=adresse des DONNEES du son (pas le header!)
;IY=REG0+1 ou 2/3
;D'=decvol
;LIX=note DEJA TRANSPOSEE
;PITCH+1=pitch actuel pour track
 ;A=NOWSTEP (utilisé si snd hard)
 ;HL'=RETRIG+1

;retour=
;HL=nouvelle adresse des donnees
;HIX=Masque REG7 (0000x00x) a ORer
	ld hl,RETRIG+1			;HL'=RETRIG+1 une fois pour toute
DECVOL12 ld d,0 			;d' chargé.
	exx
PITCH1	ld hl,0
PITADD1	ld de,0
	add hl,de
	ld (PITCH1+1),hl
	ld (CPITCH+1),hl
;
	ld a,(NOTE1+2)
	defb #dd : ld l,a
;
PTSND1	ld hl,0
	ld iy,REG0+1
	ld a,(INOWSTP1+1)
	call PLAYSND
	ex de,hl
INOWSTP1 ld a,0
ISTEP1	cp 0
	jr z,ADIEND1
	inc a			;On n'avance pas dans le son, car step pas encore atteint
	jr SND1FI2		
ADIEND1 ld hl,0			;Adresse ENDINSTR
	xor a			;Si son fini, nowstp=0
	sbc hl,de
	jr nz,SND1FIN		;Si END pas atteinte, on sauve la pos instr rendue par fct PLAYSND
ADILOOP1 ld de,0		;Sinon, on pos le pt instr sur ADR LOOP ! (qui peut etre = DATA INSTR 0 !)
ADIISLOOP1 or a			;Loop ? or a=non  scf=oui
	jr c,SND1FIN		;si oui (jump), alors PTSND1 et STEP ne changent pas.
				;si non, alors step=255
ADILOOPVIDE1 ld hl,0		;Et on resette le END sur fin data instr 0 (a calculer par init)
	ld (ADIEND1+1),hl	;Le adptson pointe automatiquement sur data instr0
	dec a
	ld (ISTEP1+1),a
	inc a
SND1FIN	ld (PTSND1+1),de
SND1FI2	ld (INOWSTP1+1),a
	defb #dd : ld a,h
	ld (R7S1+1),a









	exx
DECVOL22 ld d,0			;d' chargé.
	exx
PITCH2	ld hl,0
PITADD2	ld de,0
	add hl,de
	ld (PITCH2+1),hl
	ld (CPITCH+1),hl
;
	ld a,(NOTE2+2)
	defb #dd : ld l,a
;
PTSND2	ld hl,0
	ld iy,REG2+1
	ld a,(INOWSTP2+1)
	call PLAYSND
	ex de,hl
INOWSTP2 ld a,0
ISTEP2	cp 0
	jr z,ADIEND2
	inc a
	jr SND2FI2		;On n'avance pas dans le son, car step pas encore atteint
ADIEND2 ld hl,0			;Adresse ENDINSTR
	xor a			;Si son fini, nowstp=0
	sbc hl,de
	jr nz,SND2FIN		;Si END pas atteinte, on sauve la pos instr rendue par fct PLAYSND
ADILOOP2 ld de,0		;Sinon, on pos le pt instr sur ADR LOOP ! (qui peut etre = DATA INSTR 0 !)
ADIISLOOP2 or a			;Loop ? or a=non  scf=oui
	jr c,SND2FIN		;si oui (jump), alors PTSND1 et STEP ne changent pas.
				;si non, alors step=255
ADILOOPVIDE2 ld hl,0		;Et on resette le END sur fin data instr 0 (a calculer par init)
	ld (ADIEND2+1),hl	;Le adptson pointe automatiquement sur data instr0
	dec a
	ld (ISTEP2+1),a
	inc a
SND2FIN	ld (PTSND2+1),de
SND2FI2	ld (INOWSTP2+1),a
	defb #dd : ld a,h
	ld (R7S2+1),a









	exx
DECVOL32 ld d,0 		;d' chargé.
	exx
PITCH3	ld hl,0
PITADD3	ld de,0
	add hl,de
	ld (PITCH3+1),hl
	ld (CPITCH+1),hl
;
	ld a,(NOTE3+2)
	defb #dd : ld l,a
;
PTSND3	ld hl,0
	ld iy,REG4+1
	ld a,(INOWSTP3+1)
	call PLAYSND
	ex de,hl
INOWSTP3 ld a,0
ISTEP3	cp 0
	jr z,ADIEND3
	inc a
	jr SND3FI2		;On n'avance pas dans le son, car step pas encore atteint
ADIEND3 ld hl,0			;Adresse ENDINSTR
	xor a			;Si son fini, nowstp=0
	sbc hl,de
	jr nz,SND3FIN		;Si END pas atteinte, on sauve la pos instr rendue par fct PLAYSND
ADILOOP3 ld de,0		;Sinon, on pos le pt instr sur ADR LOOP ! (qui peut etre = DATA INSTR 0 !)
ADIISLOOP3 or a			;Loop ? or a=non  scf=oui
	jr c,SND3FIN		;si oui (jump), alors PTSND1 et STEP ne changent pas.
				;si non, alors step=255
ADILOOPVIDE3 ld hl,0		;Et on resette le END sur fin data instr 0 (a calculer par init)
	ld (ADIEND3+1),hl	;Le adptson pointe automatiquement sur data instr0
	dec a
	ld (ISTEP3+1),a
	inc a
SND3FIN	ld (PTSND3+1),de
SND3FI2	ld (INOWSTP3+1),a
	defb #dd : ld a,h
	;ld (R7S3+1),a



;Gere le REG7
	sla a
R7S2	or 0
	rla
R7S1	or 0
	jp SENDREG






;Routine generale pour lire les tracks dune voix selectionnee
;hl=pt track
;d=transp
;e=instr   c=decvol
;b=now channel (1,2,3)
;lix=ancienne note
;
;RET=
;hl=nouv pt track
;hl'=pitchADD donne par track
;hiy=0=recalculer instr (pitch=0)  1=continue instr
;liy=nouv nbwait
;e=instr nouv or old       lix=note, changee ou non.
;c=decvol
;ATTENTION ! RETOUR SUR REGISTRES AUXILIAIRES ! (Comme ca, on sauve le pitchadd direct)
.READTRACK
	ld a,(hl)
	inc hl
	srl a
	jr c,RTFULLOPT		;Full Optimisation
	cp 96
	jr nc,RTSPECIAL		;Cas special
;
	defb #fd		;hiy=0 car nouv instr
	ld h,0

	add a,d			;Note a jouer, avec ou sans effets derriere
	defb #dd : ld l,a	;lix=note
;
	ld b,(hl)		;chope vol s'il existe
	inc hl
	ld a,b
	rra
	jr nc,RTNOVOL		;Jump si pas de volume. C n'est pas modif
	and %1111
	ld c,a
RTNOVOL

	rl b
	jr nc,RTANCINS
	ld e,(hl)		;Nouv instr
	inc hl
RTANCINS rl b
	jr nc,RTNOPITCH
RTPITCH	ld a,(hl)		;Le SPECIAL PITCH/VOLPITCH jump ici aussi.
	inc hl
	exx			;Set pitchadd.
	ld l,a
	ld h,0
	rla			;Test signe pitchadd. Si neg, alors mets poids fort a #ff
	jr nc,RTPOSPIT
	dec h
RTPOSPIT

	defb #fd : ld l,0
	ret

RTNOPITCH exx			;Nouv instr mais pas de pitchadd
	ld hl,0

	defb #fd : ld l,0
	ret

;Full optimisation = note + pitch a 0 + instr et vol pareil qu'avant
RTFULLOPT
	defb #fd		;hiy=0 car meme instr, mais il faut le resetter
	ld h,0

	add a,d
	defb #dd : ld l,a	;Note a jouer
;
	jr RTNOPITCH


;Special. Pas de note, mais un ou deux effets (vol/pitch)
RTSPECIAL
	defb #fd		;hiy=1 car instr cont
	ld h,1

	sub 96
	jr z,RTSWAIT
	dec a
	jr z,RTSFINTRACK
	dec a
	jr z,RTSVOL
	dec a
	jr z,RTPITCH
	dec a
	jr z,RTSVOLPITCH
	dec a
	jr z,RTSRESET
	dec a
	jr z,RTSDIGI
	dec a			;Wait 0-24 lignes
	exx
	defb #fd : ld l,a
	ld hl,0
	ret
RTSIMPAIR			;Fonction speciale, impair


RTSWAIT	ld a,(hl)		;Wait X lignes
	inc hl
	exx
	defb #fd : ld l,a
	ld hl,0
	ret

RTSVOL	ld c,(hl)		;Vol only
	inc hl
	exx
	defb #fd : ld l,0
	ld hl,0
	ret

RTSVOLPITCH 
	ld c,(hl)		;Vol+pitch
	inc hl
	jr RTPITCH

RTSFINTRACK defb #fd : ld l,255
	exx
	ld hl,0
	ret

RTSDIGI ld a,(hl)
	inc hl
	ld (DIGI),a
	ld a,b
	ld (SPLCHAN),a
RTSRESET ld iy,#0000		;nouvo son et nbbwait a 0.
	ld e,0			;instr 0 car digidrum coupe la voie !
	exx
	ld hl,0
	ret









;PLAYSND. Joue un son dans un canal
;Entree=
;HL=adresse des DONNEES du son (pas le header!)
;IY=REG0+1 ou 2/4
;D'=decvol
;LIX=note DEJA TRANSPOSEE
 ;HL'=RETRIG+1
 ;A=nowstep

;retour=
;HL=nouvelle adresse des donnees
;HIX=Masque REG7 (0000x00x) a ORer


;pd la gestion = e=valeur 1er octet  d=mask reg 7 pour ce canal



.PLAYSND
	ld e,(hl)		;Son hard ou non
	inc hl
	bit 7,e
	jp nz,CGSHARD

;Son non hard
CNOHARD
	bit 4,e			;Noise ?
	jr z,CNHNONOIS
	ld a,(hl)
	bit 6,a			;Freq donnee? Cas particulier!
	jr z,CNHNOISE

	;Cas particulier (freq donnee pour son normal).
	ld d,%1000 ;%111110		;freq donnee. son forcement on.
	inc hl
	and %11111		;Teste si le noise=0
	jr z,CNHFGV
	ld (REG6+1),a		;Modif reg noise, autoriz noise
	res 3,d
;
CNHFGV				;noise geré.
	ld a,e			;On balance le volume
	and %1111
	exx
	sub d			;sub (ix+0)		;Volumedec de track
	exx
	jr nc,CDECVOLF4
	xor a
CDECVOLF4 ld (iy+#36),a		;Code volume
	defb #dd : ld h,d ;ld (ix+2),d

CNHFGFREQ			;lis freq
	ld a,(hl)
	ld (iy+0),a
	inc hl
	ld a,(hl)
	ld (iy+#1b),a
	inc hl
	ret



	;Cas normal
CNHNOISE 			;Modif reg noise, freq calculee (normal, quoi)
	ld (REG6+1),a
	inc hl
	ld d,%0001 ;%110111		;autorise noise sur ce canal
	bit 5,a			;Noise=1 donc on a un bit designe etat son
	jr z,CNHNOISNOS
	res 0,d			;Noise et son. Enclenche son
	ld a,e			;On balance le volume
	and %1111
	exx
	sub d			;(ix+0)		;Volumedec de track
	exx
	jr nc,CDECVOLF1
	xor a
CDECVOLF1 ld (iy+#36),a		;Code volume
	defb #dd : ld h,d
	jr CNHGARP
CNHNOISNOS 			;Noise mais pas de sons
	ld a,e			;On balance le vol qd meme (pour bruit)
	and %1111
	exx
	sub d			;(ix+0)		;Volumedec de track
	exx
	jr nc,CDECVOLF2
	xor a
CDECVOLF2 ld (iy+#36),a		;Code volume
CNHNNNS2 
	defb #dd : ld h,d
	ret			;Si on coupe le son, rien ne sert de gerer freq!

CNHNONOISNOSND			;pas de son pas de bruit (appellee plus bas)
	ld (iy+#36),0		;Code volume, utile pour couper hard
	ld d,%1001
	jr CNHNNNS2
CNHNONOIS ld d,%1000		;Pas de noise mais peut etre sound
	ld a,e
	and %1111		;Si vol alors son=1 sinon son=0
	jr z,CNHNONOISNOSND
	exx
	sub d			;(ix+0)		;Volumedec de track
	exx
	jr nc,CDECVOLF3
	xor a
CDECVOLF3 ld (iy+#36),a		;Code volume. pas de noise mais son
	defb #dd : ld h,%1000	;Enclenche son et coupe noise


CNHGARP
	bit 5,e			;arp?
	jr z,CNHNOARP
	ld a,(hl)		;Get arp
	inc hl
	jr CNHARPF
CNHNOARP xor a
CNHARPF

	bit 6,e			;Pitch?
	jr z,CNHNOPITCH
	ld e,(hl)		;Get pitch
	inc hl
	ld d,(hl)
	inc hl
	jr CNHPITCHF
CNHNOPITCH ld de,0
CNHPITCHF

;On va maintenant gerer la frequence.
;Freq = note clavier/track + transp patt + arp + pitch instr + pitch patt

	
	defb #dd : add a,l	;note canal1/clavier
	cp 96			;Note >95?
	jr c,CNHOK
CNHNOK	ld a,95			;Si oui, rétabli
CNHOK
	push hl

	add a,a			;On trouve la periode
	ld l,a
	ld h,0
	ld bc,TABPERIODS
	add hl,bc
	ld c,(hl)
	inc hl
	ld b,(hl)		;bc=periode

CPITCH	ld hl,0			;add pattern pitch
	 sra h
	 rr l
	add hl,bc
	add hl,de		;add instr pitch
	ld (iy+0),l
	ld (iy+#1b),h

	pop hl
	ret








;Son hard
CGSHARD
	 or a			;Chope retrig
	 jr nz,CHNORETR		;Seulement si NOWSTEP=0 !
	 ld a,e
	 exx
	 and %01000000
	 or (hl)
	 ld (hl),a
	 exx
 CHNORETR


	ld a,e			;Code le SND = bit 0. Coupe NOISE pour l instant
	or  %1000		;si bit 0 de e = 1(pas de snd)->000001 ;111111
	and %1001
	ld d,a


CHSNDF				;On mets le bit 5 du vol a 5 (activ hard).
	ld (iy+#36),%10000 ;a	;Code volume


	ld b,(hl)		;Prends 2e octet
	inc hl

	ld a,b			;Trouve courbe hard 8/A/C/E
	and %11
	add a,a
	add a,8
	ld (REG13+1),a


	bit 3,e			;noise ?
	jr z,CHNONOIS
	ld a,(hl)
	inc hl
	ld (REG6+1),a		;Noise.
	res 3,d			;autorise noise sur ce canal
	jr CHNOISF
CHNONOIS 			;No noise. Le canal noise est deja coupe
CHNOISF defb #dd : ld h,d	;set reg7

;On chope le Finetune eventuel, le SHIFT (*2 car on l'utilise pour saut)
	xor a
	bit 7,b			;Hardsync
	jr z,CHGETSHIFT
	bit 6,b			;Finetune?
	jr z,CHNOFTUNE
	ld a,(hl)		;Get Finetune
	inc hl
CHNOFTUNE ld (CHHSYFTUNE+1),a
	ld a,1
CHGETSHIFT ld (CHISHARDSYNC+1),a
	ld a,b
	rra			;Chope le shift
	and %00001110
	ld (CHSHIFT+1),a


	bit 4,e			;freq auto/donnee?
	jp nz,CHFREQDONNEE	;freq donnee=arp et pitch inexistants
;Freq auto. On doit dabord choper l arp et pitch sils existent
	bit 1,e			;arp?
	jr z,CHNOARP

	ld a,(hl)
	inc hl
	jr CHARPF
CHNOARP xor a
CHARPF
	ex af,af'
	 ld a,e			;sauve e
	ex af,af'

	bit 2,e			;pitch?
	jr z,CHNOPITCH
	ld e,(hl)
	inc hl
	ld d,(hl)
	inc hl
	jr CHPITCHF
CHNOPITCH ld de,0
CHPITCHF

;On peut maintenant calculer freq auto
;Freq = note clavier/track + transp patt + arp + pitch instr + pitch patt


	defb #dd : add a,l	;note canal1/clavier

	cp 96			;Note >95?
	jr c,CHOK
	ld a,95			;Si oui, rétabli
CHOK
	push hl

	add a,a			;On trouve la periode
	ld l,a
	ld h,0
	ld bc,TABPERIODS
	add hl,bc
	ld c,(hl)
	inc hl
	ld b,(hl)		;de=periode

	ld hl,(CPITCH+1)	;add pattern pitch
	 sra h
	 rr l
	add hl,bc
	add hl,de		;add instr pitch

	ld c,l
	ld b,h

CHISHARDSYNC ld a,0		;Utilise t on HARDSYNC ?
	or a			;Si oui, pas la peine de sauver sfreq !
	jr nz,CHSHIFT		;Mais elle va servir pour calcul hfreq.

;
CHFREQF	ex af,af'		;a=e sauve plus haut
	bit 5,a			;FREQHARD donnée?
	jr nz,CHFREQHARDDONNEE



;FREQHARD Auto. On la calcule en fct de freq.
CHFREQ	ld a,c
	ld (iy+0),c
	ld (iy+#1b),b

CHSHIFT	ld e,0				;Shift deja *2
	ld a,e				;Multiple Shift par 3
	srl a				;Pour trouver ou sauter
	add a,e
	ld (CHSHJP+1),a
	ld a,c

CHSHJP	jr CHS7
CHS7	srl b
	rra
CHS6	srl b
	rra
CHS5	srl b
	rra
CHS4	srl b
	rra
CHS3	srl b
	rra
CHS2	srl b
	rra
CHS1	srl b
	rra
CHS0	ld c,a
	jr nc,CHSHIFTF2
	inc bc

CHSHIFTF2
	ld a,c
	ld (REG11+1),a
	ld a,b
	ld (REG12+1),a
;
	ld a,(CHISHARDSYNC+1)		;Utilise t on HARDSYNC ? (bis)
	or a
	jr z,CHSHIFTF

	ld a,(CHSHIFT+1)		;Fin calcul HARDSYNC.
	ld e,a				;Sfreq=hfreq*2 puissance SHIFT
	srl a
	add a,e
	ld (CHSHJP2+1),a
	ld a,b
CHSHJP2	jr CHHS7
CHHS7	sla c
	rla
	sla c
	rla
	sla c
	rla
	sla c
	rla
	sla c
	rla
	sla c
	rla
	sla c
	rla
	ld b,a
CHHSYFTUNE ld hl,0		;FineTune
	add hl,bc
	ld (iy+0),l		;On poke la sfreq calcule
	ld (iy+#1b),h
CHSHIFTF pop hl
	ret

;




CHFREQDONNEE
	ld c,(hl)		;Freq donnee. On la chope
	inc hl
	ld b,(hl)
	inc hl
	push hl
	bit 5,e
	jr z,CHFREQ


CHFREQHARDDONNEE
	pop hl
	;On poke la freq precedement calcule
	ld (iy+0),c
	ld (iy+#1b),b
	ld a,(hl)		;Periode donnee. On la chope
	ld (REG11+1),a
	inc hl
	ld a,(hl)
	ld (REG12+1),a
	inc hl
	ret




;Table des periodes
.TABPERIODS
	defw 3822,3608,3405,3214,3034,2863,2703,2551,2408,2273,2145,2025
	defw 1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012
	defw 956,902,851,804,758,716,676,638,602,568,536,506
	defw 478,451,426,402,379,358,338,319,301,284,268,253
	defw 239,225,213,201,190,179,169,159,150,142,134,127
	defw 119,113,106,100,95,89,84,80,75,71,67,63
	defw 60,56,53,50,47,45,42,40,38,36,34,32
	defw 30,28,27,25,24,22,21,20,19,18,17,16






;Balance les registres aux PSG
;a=val REG7
	;list
.SENDREG
	;nolist

	ld h,a

	ld b,#f4
	exx
	ld bc,#f6c0
	ld e,#80
	exx
;
.REG0	ld a,0			;NE PAS RAJOUTER DINSTRUCT NULLE PART
REG0OLD	cp 0			;ENTRE REG0/1, 2/3, 4/5 car on se sert
	jr z,REG1		;de iy pour les adresser !!!
	ld d,0
	out (c),d		;reg 0 select
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG0OLD+1),a
	exx

.REG1	ld a,0
REG1OLD	cp 0
	jr z,REG8
	ld d,1		;reg 1 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG1OLD+1),a
	exx

.REG8	ld a,0
REG8OLD	cp 0
	jr z,REG2
	ld d,8		;reg 8 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG8OLD+1),a
	exx





.REG2	ld a,0
REG2OLD	cp 0
	jr z,REG3
	ld d,2		;reg 2 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG2OLD+1),a
	exx

.REG3	ld a,0
REG3OLD	cp 0
	jr z,REG9
	ld d,3		;reg 3 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG3OLD+1),a
	exx

.REG9	ld a,0
REG9OLD	cp 0
	jr z,REG4
	ld d,9		;reg 9 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG9OLD+1),a
	exx





.REG4	ld a,0
REG4OLD	cp 0
	jr z,REG5
	ld d,4		;reg 4 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG4OLD+1),a
	exx

.REG5	ld a,0
REG5OLD	cp 0
	jr z,REG10
	ld d,5		;reg 5 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG5OLD+1),a
	exx

.REG10	ld a,0
REG10OLD cp 0
	jr z,REG6
	ld d,10		;reg 10 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG10OLD+1),a
	exx










.REG6	ld a,0
REG6OLD	cp 0
	jr z,REG7
REG62	ld d,6		;reg 6 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG6OLD+1),a
	exx

.REG7	ld a,h
REG7OLD	cp %11000000
	jr z,REG11
	ld d,7		;reg 7 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG7OLD+1),a
	exx









.REG11	ld a,0
REG11OLD cp 0
	jr z,REG12
	ld d,11		;reg 11 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG11OLD+1),a
	exx

.REG12	ld a,0
REG12OLD cp 0
	jr z,REG13
	ld d,12		;reg 12 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG12OLD+1),a
	exx


.REG13	ld a,0
REG13OLD cp 255
	jr nz,REG13G
	ld h,a
RETRIG	ld a,0		;retrig donne par colonne dans instr ou header instr
	or a

	if SAVEBCAF
	jr z,ENDSENDPSG
	else
	ret z
	endif

	ld a,h
REG13G	ld d,13		;reg 13 select
	out (c),d
	exx
	out (c),c
	defb #ed,#71
	exx
	out (c),a
	exx
	out (c),e
	defb #ed,#71
	ld (REG13OLD+1),a

ENDSENDPSG
	if SAVEBCAF
	pop iy
	pop ix
	pop bc
	pop af
	exx
	ex af,af'

	;ei
	endif

	ret	






;Resette les VALEURS du psg.
	;list
.STOPSNDS
	;nolist

	if SAVEBCAF
	 di
	 ex af,af'
	 exx
	 push af
	 push bc
	 push ix
	 push iy
	endif

	xor a
	ld (REG8+1),a
	ld (REG9+1),a
	ld (REG10+1),a
	dec a
	ld (REG8OLD+1),a	;Ainsi, on est sur que les vals seront changees
	ld (REG9OLD+1),a
	ld (REG10OLD+1),a
	ld (REG7OLD+1),a

	ld a,%00111111
	jp SENDREG



;Init la musique.
;DE=zic
	;list
.INITZIC
	;nolist

	;; by freemac
	ld de,#4000

	ld hl,6
	add hl,de
	ld a,(hl)
	ld (NOSPLCHAN+1),a
	if BASICINT
	 inc hl			;Si INTERRUPTIONS, chope freqreplay (le low byte suffit)
	 ld a,(hl)
	 ld (REPFREQ+1),a
	 inc hl
	 inc hl
	else
	 ld de,3
	 add hl,de
	endif
;
	ld de,PTHEIGHTSTAB+1	;Si on veut initialiser sur une song vide, modifier ca. Attention
	ldi			;a ENDPOS et LOOPTO ! Dans cas les faire reinit aussi dans INITSNGTABS.
	ldi
	ld de,PTTRACKSTAB+1
	ldi
	ldi
	ld de,PTSTRACKSTAB+1
	ldi
	ldi
	ld de,PTINSTRS1+1
	ldi
	ldi

	ld de,ADTRANSPSLOOP+1
	ldi
	ldi
	ld de,ADHEIGHTSLOOP+1
	ldi
	ldi
	ld de,ADTRACKSLOOP+1
	ldi
	ldi
	ld de,ADSTRACKSLOOP+1
	ldi
	ldi

	ld a,(hl)
	inc hl
	ld (PLAYSPEED+1),a	;Chope begspd
	ld (PLAYWAIT+1),a

	ld (PTTRANSPSTAB+1),hl

	ld hl,(PTSTRACKSTAB+1)
	ld (ADENDPOS+1),hl	;ADENDPOS correspond a l'adr qui se situe APRES la TRACKSTAB
	ld a,(hl)		;Cherche l'etat de debut de strack (diff/egal)
	and %1
	ld (STSTATE+1),a

	ld hl,(ADSTRACKSLOOP+1)
	ld a,(hl)		;De meme avec lors du bouclage.
	and %1
	ld (STSTATLOOP+1),a


	ld hl,(PTINSTRS1+1)
	ld (PTINSTRS2+1),hl
	ld (PTINSTRS3+1),hl

	ld e,(hl)		;Chope adresse de DATA INSTR0 (pour que canaux debutent sur son vide)
	inc hl
	ld d,(hl)
	inc hl
	ex de,hl
	ld bc,SIZEINSTRNEWHEADER
	add hl,bc
	ld (PTSND1+1),hl
	ld (PTSND2+1),hl
	ld (PTSND3+1),hl
	ld (ADILOOP1+1),hl
	ld (ADILOOP2+1),hl
	ld (ADILOOP3+1),hl
	ex de,hl


	;ld hl,(PTINSTRS1+1)	;Chope adresse de fin de instr0, cad debut instr 1 !
	;inc hl			;Elle sert a setter le END d'un instr qui ne boucle pas, puisque pointeur
	;inc hl			;d'un tel instr pointera sur instr0 qd son fini.
	ld e,(hl)
	inc hl
	ld d,(hl)
	ld (ADILOOPVIDE1+1),de
	ld (ADILOOPVIDE2+1),de
	ld (ADILOOPVIDE3+1),de

	ld (ADIEND1+1),de
	ld (ADIEND2+1),de
	ld (ADIEND3+1),de


	ld a,#37
	ld (ISPATTEND),a

;
	ld hl,SETTO0LIST
SETLISTINI ld a,(hl)
	or a
	ret z
	ld b,a
	inc hl
	ld a,(hl)
	inc hl
;
SETLISTLP ld e,(hl)
	inc hl
	ld d,(hl)
	inc hl
	ld (de),a
	djnz SETLISTLP
	jr SETLISTINI
;



SETTO0LIST defb 24,0		;NbIt (0=fini), fillbyte
	defw REG0+1,REG1+1,REG2+1,REG3+1,REG4+1,REG5+1
	defw REG6+1,REG8+1,REG9+1,REG10+1
	defw REG11+1,REG12+1,REG13+1

	defw TRWAIT+1,HTWAIT+1,STEWAIT+1,STDWAIT+1,STRWAIT+1
	defw INOWSTP1+1,INOWSTP2+1,INOWSTP3+1
	defw DECVOL1+1,DECVOL2+1,DECVOL3+1

SETTOFFLIST defb 17,#ff
	defw REG0OLD+1,REG1OLD+1,REG2OLD+1,REG3OLD+1,REG4OLD+1,REG5OLD+1
	defw REG6OLD+1,REG7OLD+1,REG8OLD+1,REG9OLD+1,REG10OLD+1
	defw REG11OLD+1,REG12OLD+1,REG13OLD+1

	defw ISTEP1+1,ISTEP2+1,ISTEP3+1


	defb 3,#b7
	defw ADIISLOOP1,ADIISLOOP2,ADIISLOOP3

	defb 0





	list
	;Fin Player Starkos 1.2
	nolist
