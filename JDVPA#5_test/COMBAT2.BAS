1 MODE 2:INK 1,6:INK 0,0:BORDER 0:GOTO 90
5 OUT &7FC4,&C4
7 POKE &5FFE,0
8 b$="NO
9 REM LOCATE 39,20 :PRINT "-------------------------"
10 LOCATE 39,20:PRINT " 1. Liu Kang vs Sub Zero "
20 LOCATE 39,21:PRINT " 2. Sub Zero vs Liu Kang "
30 LOCATE 39,22:PRINT " 3. Liu Kang vs Liu Kang "
35 LOCATE 39,23:PRINT " 4. ARCADE : "+b$+"            "
36 LOCATE 39,24 :PRINT "-------------------------"
40 a$=INKEY$:IF a$="" THEN 40
60 IF a$="2" THEN POKE &5FFF,1
70 IF a$="3" THEN POKE &5FFF,2
75 IF a$="4" AND b$="NO" THEN b$="YES":POKE &5FFE,1:GOTO 9
78 IF a$="4" THEN 7
80 GOTO 460
90 LOCATE 1,25:REM PRINT "Ascii art by Blazej Kozlowski
100 PRINT "                                _..gggggppppp.._                       
110 PRINT "                           _.gd$$$$$$$$$$$$$$$$$$bp._                  
120 PRINT "                        .g$$$$$$P^^";CHR$(34);"";CHR$(34);"j$$b";CHR$(34);"";CHR$(34);"";CHR$(34);"";CHR$(34);"^^T$$$$$$p.               
130 PRINT "                     .g$$$P^T$$b    d$P T;       ";CHR$(34);"";CHR$(34);"^^T$$$p.            
140 PRINT "                   .d$$P^";CHR$(34);"  :$; `  :$;                ";CHR$(34);"^T$$b.          
150 PRINT "                 .d$$P'      T$b.   T$b                  `T$$b.        
160 PRINT "                d$$P'      .gg$$$$bpd$$$p.d$bpp.           `T$$b       
170 PRINT "               d$$P      .d$$$$$$$$$$$$$$$$$$$$bp.           T$$b      
180 PRINT "              d$$P      d$$$$$$$$$$$$$$$$$$$$$$$$$b.          T$$b     
190 PRINT "             d$$P      d$$$$$$$$$$$$$$$$$$P^^T$$$$P            T$$b    
200 PRINT "            d$$P    '-'T$$$$$$$$$$$$$$$$$$bggpd$$$$b.           T$$b   
210 PRINT "           :$$$      .d$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$p._.g.     $$$;  
220 PRINT "           $$$;     d$$$$$$$$$$$$$$$$$$$$$$$P^";CHR$(34);"^T$$$$P^^T$$$;    :$$$  
230 PRINT "          :$$$     :$$$$$$$$$$$$$$:$$$$$$$$$_    ";CHR$(34);"^T$bpd$$$$,     $$$; 
240 PRINT "          $$$;     :$$$$$$$$$$$$$$bT$$$$$P^^T$p.    `T$$$$$$;     :$$$ 
250 PRINT "         :$$$      :$$$$$$$$$$$$$$P `^^^'    ";CHR$(34);"^T$p.    lb`TP       $$$;
260 PRINT "         :$$$      $$$$$$$$$$$$$$$              `T$$p._;$b         $$$;
270 PRINT "         $$$;      $$$$$$$$$$$$$$;                `T$$$$:Tb        :$$$
280 PRINT "         $$$;      $$$$$$$$$$$$$$$                        Tb    _  :$$$
290 PRINT "         :$$$     d$$$$$$$$$$$$$$$.                        $b.__Tb $$$;
300 PRINT "         :$$$  .g$$$$$$$$$$$$$$$$$$$p...______...gp._      :$`^^^' $$$;
310 PRINT "          $$$;  `^^'T$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$p.    Tb._, :$$$ 
320 PRINT "          :$$$       T$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$b.   ";CHR$(34);"^";CHR$(34);"  $$$; 
330 PRINT "           $$$;       `$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$b      :$$$  
340 PRINT "           :$$$        $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$;     $$$;  
350 PRINT "            T$$b    _  :$$`$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$;   d$$P   
360 PRINT "             T$$b   T$g$$; :$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  d$$P    
370 PRINT "              T$$b   `^^'  :$$ ";CHR$(34);"^T$$$$$$$$$$$$$$$$$$$$$$$$$$$ d$$P     
380 PRINT "               T$$b        $P     T$$$$$$$$$$$$$$$$$$$$$$$$$;d$$P      
390 PRINT "                T$$b.      '       $$$$$$$$$$$$$$$$$$$$$$$$$$$$P       
400 PRINT "                 `T$$$p.   bug    d$$$$$$$$$$$$$$$$$$$$$$$$$$P'        
410 PRINT "                   `T$$$$p..__..g$$$$$$$$$$$$$$$$$$$$$$$$$$P'          
420 PRINT "                     ";CHR$(34);"^$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$^";CHR$(34);"            
450 GOTO 5
460 LOCATE 1,25:INK 1,24:INK 0,1:BORDER 1
470 PRINT "                     ";CHR$(34);"^$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$^";CHR$(34);"            
480 PRINT "                        ";CHR$(34);"^T$$$$$$$$$$$$$$$$$$$$$$$$$$P^";CHR$(34);"               
490 PRINT "                            ";CHR$(34);"";CHR$(34);"";CHR$(34);"^^^T$$$$$$$$$$P^^^";CHR$(34);"";CHR$(34);"";CHR$(34);"
520 PRINT
530 PRINT "              чооооооооооооооэ ";chr$(237);" MUSIC SAMPLES ";chr$(237);" щооооооооооооооэ"
540 PRINT "             чSuTeKH/Epyteor - mk-bo.sks / DMA-Sc - mk-bo.mod    "
550 PRINT "            чоTom&Jerry - Sudoku - Theme 1.sks
560 PRINT "           чооTom&jerry - Sudoku - Theme 2.sks
580 PRINT "          чооооооооооооооооооэ ";chr$(237);" MUSIC ROUTINE ";chr$(237);" щооооооооооооооэ"
590 PRINT "         чооооTarghan - STarKos www.julien-nevo.com/starkos/
600 PRINT
610 PRINT "              чоооооооооооооооооооэ ";chr$(250);" GFX ";chr$(251);" щоооооооооооооооооооэ"
620 PRINT "             чSuTeKH/Epyteor - loading screen
630 PRINT "            чоSuTeKH/Epyteor - loading screen
640 PRINT "           чооBlazej Kozlowski - Ascii Art
650 PRINT "          чоооRenaud Helias - Blood and Hadouken particules
660 PRINT
670 PRINT "              чоооооооооооооооооэ ";chr$(241);" CODING ";chr$(242);chr$(242);" щоооооооооооооооооэ"
680 PRINT "             чRenaud Helias - for THSF 2018
700 PRINT "            чооооооооооооооэ ";chr$(240);" CODING RESOURCES ";chr$(243);chr$(243);" щооооооооооооэ"
710 PRINT "           чооOldschool is beautiful - JDVA - youtube tutorials
720 PRINT "          чоооCPCMANIA - SDCC routines + CPCDiskXP
730 PRINT "         чооооCPCWiki - CPCWiki - CPCWiki
740 PRINT
750 PRINT "              чооооооооооооооооъ ";chr$(224);" GREETINGS ";chr$(224);" щооооооооооооооооъ"
760 PRINT "             чDevilMarkus, MiGaNuts, Michel Louvet, Tth.        щъ"
770 PRINT "            чо                                                   оъ"
780 PRINT "           чошSee you next time at Toulouse Hacker Space Factory!ыоъ"
790 PRINT
800 RUN"combat2.bin
821 print "0123456789ABCDEF A0
822 print "═║╒ё╓╔╕╖╗╘╙╚╛╜╝╞
823 print "0123456789ABCDEF B0
824 print "╟╠╡Ё╢╣╤╥╦╧╨╩╪╫╬©
825 print "0123456789ABCDEF C0
826 print "юабцдефгхийклмно
827 print "0123456789ABCDEF D0
828 print "пярстужвьызшэщчъ
829 print "0123456789ABCDEF E0
830 print "ЮАБЦДЕФГХИЙКЛМНО
831 print "0123456789ABCDEF F0
832 print "ПЯРСТУЖВЬЫЗШЭЩЧЪ
