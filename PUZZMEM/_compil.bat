@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_basic.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_frame.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_keyb.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_sync.c
sdcc -mz80 -c --std-c99 --opt-code-speed --fno-omit-frame-pointer --oldralloc jdvapi_floppy.c
sdcc -mz80 -c --std-c99 --opt-code-speed bluegirl.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel bluegirl.rel puzzmem.c
hex2bin puzzmem.ihx
CPCDiskXP -File puzzmem.bin -AddAmsdosHeader 100 -AddToNewDsk puzzmem.dsk
pause