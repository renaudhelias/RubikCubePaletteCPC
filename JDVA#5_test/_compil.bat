@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed poisson.c
sdcc -mz80 -c --std-c99 --opt-code-speed jdvapi_frame.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_frame.rel poisson.rel jdva5.c
hex2bin jdva5.ihx
CPCDiskXP -File jdva5.bin -AddAmsdosHeader 100 -AddToNewDsk jdva5.dsk
pause