@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
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
sdcc -mz80 -c --std-c99 --opt-code-speed labyPac_map.rel laby_data.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --no-std-crt0 jdvapi_basic1.rel jdvapi_keyb.rel jdvapi_frame.rel jdvapi_sync.rel crt0_cpc.rel putchar_cpc.rel pacman_reduce_sprites.rel ghost_reduce_sprites.rel blank_reduce_sprites.rel player.rel ghost.rel tiles.rel labyPac_map.rel laby_data.rel main.c
hex2bin main.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk jdvpa10.dsk
pause
