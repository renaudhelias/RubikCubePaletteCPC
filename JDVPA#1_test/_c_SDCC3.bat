@echo off
set path=%path%;\SDCC3\bin
echo COMPILING TECHNICAL LIB ...
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc lib.c
echo COMPILING SPRITES ...
sdcc -mz80 -c --std-c99 --opt-code-speed pacman_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost_sprites.c
sdcc -mz80 -c --std-c99 --opt-code-speed blank_sprites.c
echo COMPILING SOURCES ...
sdcc -mz80 -c --std-c99 --opt-code-speed player.c
sdcc -mz80 -c --std-c99 --opt-code-speed ghost.c
echo COMPILING MAIN PROGRAM ...
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --no-std-crt0 lib.rel crt0_cpc.rel putchar_cpc.rel pacman_sprites.rel ghost_sprites.rel blank_sprites.rel player.rel ghost.rel main.c
echo HEX2BIN ...
hex2bin main.ihx
echo CPCDISK ...
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk result.dsk
del *.lst
del *.map
del *.noi
del *.sym
del *.asm
del *.bin
del *.ihx
del *.rel
del *.lk
pause