@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed poisson.c
sdcc -mz80 -c --std-c99 --opt-code-speed azrael.c
sdcc -mz80 -c --std-c99 --opt-code-speed gargamel.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel poisson.rel main.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel azrael.rel gargamel.rel hello.c
hex2bin main.ihx
hex2bin hello.ihx
CPCDiskXP -File hello.bin -AddAmsdosHeader 100 -AddToNewDsk jdva5.dsk
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToExistingDsk jdva5.dsk
pause