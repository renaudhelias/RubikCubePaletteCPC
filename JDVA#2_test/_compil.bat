@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel hello.c
hex2bin hello.ihx
CPCDiskXP -File hello.bin -AddAmsdosHeader 100 -AddToNewDsk jdva2.dsk
pause