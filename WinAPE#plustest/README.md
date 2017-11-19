# [WinAPE#plustest] WinAPE plustest.asm to plustest.dsk

WinAPE comprend un assembleur Maxam.

http://www.winape.net/downloads.jsp :
- Plus Test Source : plustest.asm
- ASM Library : asic.asm, firmware.asm, inks.asm, keys.asm


Si j'utilise Maxam directement sur mon CPC pour compiler plustest.asm :
- ROM Maxam insérré (en emplacement 05)
- ùmaxam
- T (Text editor)
- L (Load)
- plustest.asm (Enter filename:)
- A (Assemble text)
- ** FATAL ERROR ** Out of memory

Si j'utilise WinAPE (sans ROM Maxam) :
- menu File > Drive A > New Blank Disc
- menu File > Drive A > Format disk "DATA (SS 40)"
- menu Assembler > Show Assembler
	- J'ouvre plustest.asm
	- menu Assemble > Assemble
	- menu Assemble > Run
- Là l'application se lance avec écrit en haut "Select a test to run".
	- Je reviens dans l'Assembler, j'ajoute en première ligne les trois lignes suivantes :
		-org &8000
		-run &8000
		-write direct "a:plustest.bin"
	-menu Assemble > Assemble
- cat

Voilà :)