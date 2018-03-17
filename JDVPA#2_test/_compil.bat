@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_basic.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_frame.c
perl ConvImgCpc_asm2c.pl Pacman_reduce.asm
perl ConvImgCpc_asm2c.pl Ghost_reduce.asm
perl ConvImgCpc_asm2c.pl Blank_reduce.asm
sdcc -mz80 -c --std-c99 --opt-code-speed pacman_reduce_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost_reduce_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed blank_reduce_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed player.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --no-std-crt0 jdvapi_basic.rel jdvapi_frame.rel crt0_cpc.rel putchar_cpc.rel pacman_reduce_sprites.rel ghost_reduce_sprites.rel blank_reduce_sprites.rel player.rel ghost.rel main.c
hex2bin main.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk jdvpa2.dsk
pause