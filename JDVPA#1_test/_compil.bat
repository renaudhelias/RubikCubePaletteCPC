@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
rem sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc lib.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_basic.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_frame.c
sdcc -mz80 -c --std-c99 --opt-code-speed pacman_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed blank_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed player.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --no-std-crt0 jdvapi_basic.rel jdvapi_frame.rel crt0_cpc.rel putchar_cpc.rel pacman_sprites.rel ghost_sprites.rel blank_sprites.rel player.rel ghost.rel main.c
hex2bin main.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk result.dsk
pause