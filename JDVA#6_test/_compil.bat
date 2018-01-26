@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_basic.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_frame.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_keyb.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_sync.c
sdcc -mz80 -c --std-c99 --opt-code-speed poisson.c
sdcc -mz80 -c --std-c99 --opt-code-speed bluegirl.c
sdcc -mz80 -c --std-c99 --opt-code-speed joueurs.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel poisson.rel main.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel bluegirl.rel puzzmem.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel joueurs.rel combat.c
hex2bin main.ihx
hex2bin puzzmem.ihx
hex2bin combat.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk jdva6.dsk
CPCDiskXP -File puzzmem.bin -AddAmsdosHeader 100 -AddToExistingDsk jdva6.dsk
CPCDiskXP -File combat.bin -AddAmsdosHeader 100 -AddToExistingDsk jdva6.dsk
pause