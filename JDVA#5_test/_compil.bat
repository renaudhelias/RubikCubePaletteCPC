@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
rem sdcc -mz80 -c --std-c99 --opt-code-speed poisson.c
rem sdcc -mz80 -c --std-c99 --opt-code-speed jdvapi_frame.c
sdcc -mz80 -c --std-c99 --opt-code-speed poisson.c
rem sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel poisson.rel jdvapi_frame.rel jdva5.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel poisson.rel main.c
hex2bin main.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk jdva5.dsk
pause