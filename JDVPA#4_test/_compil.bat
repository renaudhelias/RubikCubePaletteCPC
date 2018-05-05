@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
copy sks2000.bin.vo sks2000.bin
copy akg2000.bin.vo akg2000.bin
copy akx2000.bin.vo akx2000.bin
copy sudo3000.bin.vo sudo3000.bin
copy MK-BO.BIN.vo MK-BO.BIN
copy mk3000.akg mk3000.bin
copy akx2D20.akx akx2D20.bin
copy MK-BO.SKS.vo MK-BO.SKS
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
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel jdvapi_basic1.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel jdvapi_floppy.rel combat2m.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel jdvapi_basic1.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel jdvapi_floppy.rel combat2e.c
hex2bin main.ihx
hex2bin combat2.ihx
hex2bin combat2m.ihx
hex2bin combat2e.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk jdvpa4.dsk
CPCDiskXP -File combat2.bin -AddAmsdosHeader 100 -AddToNewDsk jdvpa4_combat2.dsk
CPCDiskXP -File combat2m.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File combat2e.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File J1A.scr -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File J1R.scr -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File J2A.scr -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File J2R.scr -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File fond2.scr -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File intro-oh.scr -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File sudo3000.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File mk3000.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File sks2000.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File akg2000.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File akx2000.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File akx2D20.bin -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File MK-BO.SKS -AddToExistingDsk jdvpa4_combat2.dsk
CPCDiskXP -File MK-BO.BIN -AddAmsdosHeader 100 -AddToExistingDsk jdvpa4_combat2.dsk
pause

