# [JDVA#1] Hello World en C sur Amstrad CPC !
# Tested by Renaud

Basé sur la vidéo CPC de Oldschool is beautiful : http://www.youtube.com/watch?v=hSEadYkiBrc

Je vais tester ce hello.c

- http://www.retroactif.f RETROACTIF le collectif de videastes retrogaming
- CPCMania

- SDCC http://sdcc.sourceforge.net (je prend 3.6.0 pour win32)
- CPCDiskXP http://www.cpcmania.com/cpcdiskxp/cpcdiskxp.htm
- Hex2Bin http://hex2bin.sourceforge.net http://gnuwin32.sourceforge.net/packages/hex2bin.htm

Alors les gnuwin32 : faut pas en abuser, si on install gnuwin32 complet Windows se transforme en unix et ne marche plus, mais installer les commandes souhaitées (wget, curl, hex2bin, grep) ça marche très très bien <3

Une commande gnuwin32, par exemple hex2bin est généralement divisé en deux zip téléchargeable : binary (le .exe) et dependencies (les .dll)

Je fais l'installation barbare : SDCC sur le disque principal, j'autorise l'ajout au PATH, et je pose hex2bin.exe (et mot2bin.exe) dans "C:\Program Files (x86)\SDCC\bin" de façon bête et méchante. Je fais de même pour CPCDiskXP tout les .exe dans "C:\Program Files (x86)\SDCC\bin"

- patching _compil.bat afin d'ignorer la seconde ligne : je met "rem " au début de cette seconde ligne.
- patchinh _compil.bat afin d'obtenir jdva1.dsk et non pas result.dsk

Je lance _compil.bat, j'obtiens jdva1.dsk

Je test : ça marche :)
