@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
copy sks8000.bin.vo sks8000.bin
copy MKBO9000.BIN.vo MKBO9000.BIN
copy MK-BO.SKS.vo MK-BO.SKS
copy sudoku-1.sks.vo sudoku-1.sks
copy sudoku-2.sks.vo sudoku-2.sks
copy SUDOKU-1.BIN.vo SUDOKU-1.BIN
copy SUDOKU-2.BIN.vo SUDOKU-2.BIN
copy J1.MAP.vo J1.MAP
copy J1.DIR.vo J1.DIR
copy J1.PHA.vo J1.PHA
copy J2.MAP.vo J2.MAP
copy J2.DIR.vo J2.DIR
copy J2.PHA.vo J2.PHA
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_basic1.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_basic2.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_keyb.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_frame.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_sync.c
sdcc -mz80 -c --std-c99 --opt-code-speed --fno-omit-frame-pointer --oldralloc jdvapi_floppy.c
perl ConvImgCpc_asm2c.pl Pacman_reduce.asm
perl ConvImgCpc_asm2c.pl Ghost_reduce.asm
perl ConvImgCpc_asm2c.pl Blank_reduce.asm
perl Tiled_tmx2c.pl labyPac.tmx
sdcc -mz80 -c --std-c99 --opt-code-speed pacman_reduce_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost_reduce_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed blank_reduce_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed player.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost.c
sdcc -mz80 -c --std-c99 --opt-code-speed tiles.c
sdcc -mz80 -c --std-c99 --opt-code-speed labyPac_map.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --no-std-crt0 jdvapi_basic1.rel jdvapi_keyb.rel jdvapi_frame.rel jdvapi_sync.rel crt0_cpc.rel putchar_cpc.rel pacman_reduce_sprites.rel ghost_reduce_sprites.rel blank_reduce_sprites.rel player.rel ghost.rel tiles.rel labyPac_map.rel main.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel jdvapi_basic1.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel jdvapi_floppy.rel combat2.c
hex2bin main.ihx
hex2bin combat2.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk jdvpa5.dsk
CPCDiskXP -File combat2.bin -AddAmsdosHeader 100 -AddToNewDsk jdvpa5_combat2.dsk
CPCDiskXP -File J1A.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J1R.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J2A.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J2R.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File fond1.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File fond2.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File fond3.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File CHOICE.BAS -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File intro-oh.scr -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File sks8000.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File MK-BO.SKS -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File MKBO9000.BIN -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J1.MAP -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J1.DIR -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J1.PHA -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J2.MAP -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J2.DIR -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File J2.PHA -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
rem CPCDiskXP -File sudoku-1.sks -AddToExistingDsk jdvpa5_combat2.dsk
rem CPCDiskXP -File sudoku-2.sks -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File SUDOKU-1.BIN -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
CPCDiskXP -File SUDOKU-2.BIN -AddAmsdosHeader 100 -AddToExistingDsk jdvpa5_combat2.dsk
pause

