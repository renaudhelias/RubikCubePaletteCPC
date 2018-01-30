@echo off
rem set path=%path%;\sdcc\bin
sdasz80 -o crt0_cpc.s
sdasz80 -o putchar_cpc.s
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_basic.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_frame.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_keyb.c
sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_sync.c
rem sdcc -mz80 -c --std-c99 --opt-code-speed --oldralloc jdvapi_floppy.c
sdcc -mz80 -c --std-c99 --opt-code-speed poisson.c
sdcc -mz80 -c --std-c99 --opt-code-speed bluegirl.c
sdcc -mz80 -c --std-c99 --opt-code-speed joueurs.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel poisson.rel main.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel bluegirl.rel puzzmem.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel joueurs.rel combat.c
sdcc -mz80 --code-loc 0x0138 --data-loc 0 --fno-omit-frame-pointer --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel jdvapi_basic.rel jdvapi_frame.rel jdvapi_keyb.rel jdvapi_sync.rel combat2.c
sdcc -mz80 --code-loc 0x04038 --data-loc 0 --fno-omit-frame-pointer --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel Load01.c
sdcc -mz80 --code-loc 0x04038 --data-loc 0 --fno-omit-frame-pointer --oldralloc --no-std-crt0 crt0_cpc.rel putchar_cpc.rel Load02.c
hex2bin main.ihx
hex2bin puzzmem.ihx
hex2bin combat.ihx
hex2bin combat2.ihx
hex2bin Load01.ihx
hex2bin Load02.ihx
CPCDiskXP -File main.bin -AddAmsdosHeader 100 -AddToNewDsk jdva6.dsk
CPCDiskXP -File puzzmem.bin -AddAmsdosHeader 100 -AddToExistingDsk jdva6.dsk
CPCDiskXP -File combat.bin -AddAmsdosHeader 100 -AddToExistingDsk jdva6.dsk
CPCDiskXP -File combat2.bin -AddAmsdosHeader 100 -AddToNewDsk jdva6_combat2.dsk
CPCDiskXP -File J1A.scr -AddToExistingDsk jdva6_combat2.dsk
CPCDiskXP -File J1R.scr -AddToExistingDsk jdva6_combat2.dsk
CPCDiskXP -File J2A.scr -AddToExistingDsk jdva6_combat2.dsk
CPCDiskXP -File J2R.scr -AddToExistingDsk jdva6_combat2.dsk
CPCDiskXP -File Load01.bin -AddAmsdosHeader 100 -AddToExistingDsk jdva6_combat2.dsk
CPCDiskXP -File 01.scr -AddToExistingDsk jdva6_combat2.dsk
CPCDiskXP -File Load02.bin -AddAmsdosHeader 100 -AddToNewDsk jdva6_Load02.dsk
CPCDiskXP -File 01.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 02.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 03.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 04.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 05.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 06.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 07.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 08.scr -AddToExistingDsk jdva6_Load02.dsk
CPCDiskXP -File 09.scr -AddToExistingDsk jdva6_Load02.dsk

pause