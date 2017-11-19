nolist
read "firmware.asm"
read "keys.asm"
read "inks.asm"

run start,break
org #8000
limit #9fff

.start
call KL_L_ROM_ENABLE
ld a,2
call SCR_SET_MODE
ld bc,#0202
call SCR_SET_BORDER
ld bc,#0f0f
ld a,14
call SCR_SET_INK
ld bc,#1919
ld a,15
call SCR_SET_INK

;ld sp,#c000
di
ld hl,(#39)
ld (hl),#c9
ld hl,0
ld de,store40
ld bc,#40
ldir
ld hl,unlock
ld bc,#bc11
.unlocklp
ld a,(hl)
inc hl
out (c),a
dec c
jr nz,unlocklp

.menu
call reset
ld de,#c002
call prints
db "Select a test to run",0
ld e,#a2
call prints
db "1. ASIC Sprite test",0
ld e,#f2
call prints
db "2. Monitor HSYNC test",0
ld de,#c142
call prints
db "3. Horizontal Split and Soft-Scroll test",0
ld e,#92
call prints
db "4. Interrupt, VSync and R52 timing test",0
ld e,#e2
call prints
db "5. Instruction Timing test",0
ld de,#c232
call prints
db "6. Register 0 test",0
ld e,#82
call prints
db "7. Register 4 test",0
ld e,#d2
call prints
db "8. Register 9 test",0
ld de,#c322
call prints
db "9. Interrupt Wait test",0
ld de,#c782
call prints
db "Soft Scroll (Z, X): ",0
ld e,20
call waite
.lpmenu
call waitffb
ld bc,#7fb8
out (c),c
ld a,(defssc)
ld (#6804),a
ld bc,#7fa0
out (c),c
ld bc,#7f8a
out (c),c
ld de,#c796
call hexa
ei
halt
ld hl,tkm
dec (hl)
jr nz,lpmenu
ld (hl),4
call scan
ld a,KEY_1
call tkey
jr z,runtest1
ld a,KEY_2
call tkey
jp z,runtest2
ld a,KEY_3
call tkey
jp z,runtest3
ld a,KEY_4
call tkey
jp z,runtest4
ld a,KEY_5
call tkey
jp z,runtest5
ld a,KEY_6
call tkey
jp z,runtest6
ld a,KEY_7
call tkey
jp z,runtest7
ld a,KEY_8
call tkey
jp z,runtest8
ld a,KEY_9
call tkey
jp z,runtest9
ld hl,defssc
ld a,KEY_Z
call tkey
jr nz,mnoz
dec (hl)
.mnoz
ld a,KEY_X
call tkey
jr nz,mnox
inc (hl)
.mnox
jp lpmenu

.tkm
db 3

.defssc
db 0

.runtest1
call reset
di
ld bc,#7f10
out (c),c
ld bc,#7f00 + INK_3
out (c),c
ld bc,#bc01
out (c),c
ld bc,#bd3f
out (c),c
ld bc,#bc06
out (c),c
ld bc,#bd10
out (c),c
ei

ld de,#c000
call prints
db "ASIC Sprite Test (Cursors, A, S, Z, X, <, > and T)",0
ld e,#7e
call prints
db "X:     Y:     Scale:   R2:   R9:",0

.loop
ld e,3
call waite
call scan
call setvals
ld de,#c080
ld hl,(sprx)
call hexhl
ld e,#87
ld hl,(spry)
call hexhl
ld e,#92
ld a,(sprsz)
call hexa
ld e,#98
ld a,(r2)
call hexa
ld e,#9e
ld a,(r9)
call hexa
ld a,KEY_LEFT
call tkey
jr nz,noleft
ld hl,(sprx)
dec hl
ld (sprx),hl
.noleft
ld a,KEY_RIGHT
call tkey
jr nz,noright
ld hl,(sprx)
inc hl
ld (sprx),hl
.noright
ld a,KEY_UP
call tkey
jr nz,noup
ld hl,(spry)
dec hl
ld (spry),hl
.noup
ld a,KEY_DOWN
call tkey
jr nz,nodown
ld hl,(spry)
inc hl
ld (spry),hl
.nodown
ld a,KEY_COMMA
call tkey
jr nz,nocomma
ld a,(r2)
dec a
and #3f
ld (r2),a
.nocomma
ld a,KEY_POINT
call tkey
jr nz,nopoint
ld a,(r2)
inc a
and #3f
ld (r2),a
.nopoint
ld a,KEY_Z
call tkey
jr nz,noz
ld hl,sprsz
dec (hl)
.noz
ld a,KEY_X
call tkey
jr nz,nox
ld hl,sprsz
inc (hl)
.nox
ld a,KEY_A
call tkey
jr nz,noa
ld hl,r9
dec (hl)
.noa
ld a,KEY_S
call tkey
jr nz,nob
ld hl,r9
inc (hl)
.nob
ld a,KEY_T
call tkey
jr nz,not
ld a,(dbl)
xor 1
ld (dbl),a
ld de,#3f3f
jr z,notdbl
ld de,#7f7e
.notdbl
ld bc,#bc00
out (c),c
inc b
out (c),d
dec b
inc c
out (c),c
inc b
out (c),e
.not
ld a,KEY_SPACE
call tkey
jp z,menu
jp loop

.sprx
dw 0

.spry
dw 0

.sprsz
db 5

.r2
db 46

.r9
db 7

.dbl
db 0

.runtest2
call reset
ld de,#c000
call prints
db "HSYNC Test (Cursors, Z, X, <, >)",0
ld de,#c050
call prints
db "R2:00 Height:00 R3:00 R0:00",0
.test2
call waitffb
call scan
ld a,KEY_SPACE
call tkey
jp z,menu
ei
halt
ld de,#c053
ld a,(hspos)
call hexa
ld e,#5d
ld a,(hswid)
call hexa
ld e,#63
ld a,(r3)
call hexa
ld e,#69
ld a,(r0)
call hexa
ei
halt
ld e,33
call waitrowe
ld bc,#bc02
out (c),c
ld a,(hspos)
inc b
out (c),a
dec b
inc c
out (c),c
ld a,(r3)
inc b
out (c),a
ld bc,#bc00
out (c),c
ld a,(r0)
inc b
out (c),a
ld bc,#7f10
out (c),c
ld c,#4c
out (c),c
ld a,(hswid)
ld e,a
call waitrowe
ld bc,#7f5c
out (c),c
ld bc,#bc02
out (c),c
ld bc,#bd2e
out (c),c
ld bc,#bc00
out (c),c
ld bc,#bd3f
out (c),c
ld bc,#bc03
out (c),c
ld bc,#bd8e
out (c),c
ld hl,key
dec (hl)
jp nz,test2
ld (hl),2
ld hl,hspos
ld a,KEY_LEFT
call tkey
jr nz,nleft2
ld a,(hl)
cp 63
jr z,nleft2
inc (hl)
.nleft2
ld a,KEY_RIGHT
call tkey
jr nz,nright2
ld a,(hl)
or a
jr z,nright2
dec (hl)
.nright2
ld hl,hswid
ld a,KEY_UP
call tkey
jr nz,nup2
ld a,(hl)
cp 1
jr z,nup2
dec (hl)
.nup2
ld a,KEY_DOWN
call tkey
jr nz,ndown2
ld a,(hl)
cp #b8
jr z,ndown2
inc (hl)
.ndown2
ld hl,r3
ld a,KEY_Z
call tkey
jr nz,nz2
ld a,(hl)
cp #80
jr z,nz2
dec (hl)
.nz2
ld a,KEY_X
call tkey
jr nz,nx2
ld a,(hl)
cp #8f
jr z,nx2
inc (hl)
.nx2
ld hl,r0
ld a,KEY_COMMA
call tkey
jr nz,ncomma2
ld a,(hl)
cp #30
jr z,ncomma2
dec (hl)
.ncomma2
ld a,KEY_POINT
call tkey
jr nz,npoint2
ld a,(hl)
cp #7f
jr z,npoint2
inc (hl)
.npoint2
jp test2

.hspos
db 46

.hswid
db 48

.r3
db #8e

.r0
db #3f

.runtest3
call reset
ld de,#c000
call prints
db "Horizontal Split Test (Left, Right Cursors)",0
ld e,#50
call prints
db "Soft Scroll:",0
ld e,#a0
ld b,10
.pmore
call prints
db "01234567890123456789012345678901234567890123456789012345678901234567890123456789"
db "00000000001111111111222222222233333333334444444444555555555566666666667777777777",0
dec b
jp nz,pmore
ld bc,#7fb8
out (c),c
ld a,#f
ld (#6004),a
ld hl,#80
ld (#6000),hl
ld hl,48
ld (#6002),hl
.test3
call waitffb
call scan
ld a,KEY_SPACE
call tkey
jp z,menu
ld a,(ssc + 1)
ld (#6804),a
ei
halt
ld de,#c05c
ld a,(ssc + 1)
call hexa
ei
halt
ld e,41
call waitrowe
ld b,5
djnz $-1
ld bc,#7fb8
out (c),c
ld e,16
.test3lp
ld hl,0
ld (#6400),hl
nop
nop
nop
nop
nop
nop
nop
nop
ld bc,#7f00
out (c),c
ld c,#4b
out (c),c
ld hl,0
ld (#6400),hl
ld hl,#fff
ld (#6400),hl
ld c,#44
out (c),c
nop
nop
nop
nop
nop
nop
nop
nop
nop
dec e
jr nz,test3lp
ld e,16
call waitrowe
ld e,48
.test3lp2
ld b,3
djnz $-1
ld a,#e0
ld (#6000),a
nop
nop
nop
nop
nop
nop
ld a,#80
ld (#6000),a
ld b,6
djnz $-1
nop
nop
nop
nop
dec e
jr nz,test3lp2
ld e,15
call waitrowe
ld b,13
djnz $-1
ld e,48
.test3lp3
ld b,3
djnz $-1
nop
ld a,0
ld (#6804),a
nop
nop
nop
nop
nop
nop
.ssc
ld a,0
ld (#6804),a
ld b,6
djnz $-1
nop
nop
nop
dec e
jr nz,test3lp3
ld hl,key
dec (hl)
jp nz,test3
ld (hl),2
ld hl,ssc + 1
ld a,KEY_LEFT
call tkey
jr nz,noleft3
dec (hl)
.noleft3
ld a,KEY_RIGHT
call tkey
jr nz,noright3
inc (hl)
.noright3
jp test3

.runtest4
call reset
ld a,2
ld (key),a
ld bc,#bc03
out (c),c
ld bc,#bd8e
out (c),c
ld de,#c000
call prints
db "Vertical Sync and Raster 52 Timing Test :",0
ld de,#c140
call prints
db "012345678901234567890123456789012345678 :",0
ld de,#c1e0
call prints
db "NOPs to SYNC: ",0
ld de,#c410
call prints
db "012345678 :",0
ld de,#c460
call prints
db "012345678 :",0
ld de,#c4b0
call prints
db "012345678 :",0
ld de,#c500
call prints
db "012345678 :",0
ld de,#c550
call prints
db "012345678 :",0
ld de,#c5a0
call prints
db "012345678 :",0
ld de,#c690
call prints
db "012345678 :",0
ld bc,#7f01
out (c),c
ld c,INK_0
out (c),c
.test4
di
call waitffb
ld bc,#7f00
out (c),c
ld c,INK_18
out (c),c
ld e,77
call waitrowe
ld b,10
djnz $-1
nop:nop:nop
ld bc,#7f00 + INK_1
out (c),c
ld b,8
djnz $-1
nop
nop
ei
halt
nop
nop
nop
nop
nop
nop
nop
nop
nop
ld bc,#7f00 + INK_6
out (c),c
ld c,#01
out (c),c
ld c,INK_26
out (c),c
ld c,#00
out (c),c
ei
halt
nop
nop
nop
nop
nop
nop
nop
ld bc,#7f00 + INK_4
out (c),c
ld hl,key
dec (hl)
jr nz,nor4
ld (hl),2
ld a,KEY_SPACE
call tkey
jp z,menu
ld hl,numnops
ld a,KEY_LEFT
call tkey
jr nz,nol4
ld a,(hl)
dec a
and 7
ld (hl),a
.nol4
ld a,KEY_RIGHT
call tkey
jr nz,nor4
ld a,(hl)
inc a
and 7
ld (hl),a
.nor4
ld de,#c1ee
ld a,(numnops)
call hexa
ei
halt
ld e,24
call waitrowe
ld b,15
djnz $-1
nop
ld a,(numnops)
ld c,a
ld a,8
sub c
ld c,a
ld b,0
ld hl,nops
add hl,bc
call KL_PCHL
ld bc,#bc07
out (c),c
ld bc,#bd0e
out (c),c
ld b,#f5
in a,(c)
rra
ld d,INK_10
jr nc,use10
ld d,INK_13
.use10
in a,(c)
rra
jr nc,use10
.inffb2
in a,(c)
rra
jr c,inffb2
ld bc,#7f9a
out (c),c
ld e,17
call waitrowe
ld b,8
djnz $-1
nop
ld bc,#7f00
out (c),c
out (c),d
ei
halt
ld bc,#bd1e
out (c),c
ld b,10
djnz $-1
nop
nop
ld bc,#7f00
out (c),c
ld c,INK_24
out (c),c
ld c,1
out (c),c
ld bc,#7f00 + INK_0
out (c),c
call scan
nop
nop
nop
nop
nop
nop
nop
jp test4

.numnops
db 0

.inittime
ld e,1
call waite
call resetextra
ld hl,nops
ld bc,1
call runit
inc hl ;Assuming NOP time is OK
ld (reftime + 1),hl
call resetextra
ld de,#c0a0

ld hl,gettimes
ld (times + 1),hl
ret

.runtest5
ex af,af'
push af
ex af,af'
exx
push hl
push de
push bc
exx
call reset
di
ld de,#c000
call prints
db "Instruction Timing Test (Assumes NOP, HALT and Interrupt timing Ok)",0
ld hl,instruction
ld (pruntest + 1),hl
ld hl,1
ld (bcpause + 1),hl
.dotest5
call inittime
call stdinst
call newline2
call printsnl
db "CB Codes",0
call newline2
ld hl,gettimescb
ld (times + 1),hl
xor a
ld b,a
call testcb
call newline2
call printsnl
db "DD Codes",0
call newline2
ld hl,gettimesdd
ld (times + 1),hl
ld a,#fd
ld (testdjnz + 2),a
ld hl,startextradd
ld bc,endextraddfd
call setextra
call stdinst
ld a,#fe
ld (testdjnz + 2),a
call newline2
call printsnl
db "ED Codes",0
call newline2
ld hl,gettimesed
ld (times + 1),hl
call tested
call newline2
call printsnl
db "FD Codes",0
call newline2
ld hl,gettimesdd
ld (times + 1),hl
ld a,#fd
ld (testdjnz + 2),a
ld hl,startextrafd
ld bc,endextraddfd
call setextra
call stdinst
ld a,#fe
ld (testdjnz + 2),a
call newline2
call printsnl
db "DD CB Codes",0
call newline2
ld hl,gettimesddcb
ld (times + 1),hl
ld hl,startextraddcb
ld bc,noextra
call setextra
xor a
ld b,a
call looptest1
call newline2
call printsnl
db "FD CB Codes",0
call newline2
ld hl,gettimesddcb
ld (times + 1),hl
ld hl,startextrafdcb
ld bc,noextra
call setextra
xor a
ld b,a
call looptest1
exx
pop bc
pop de
pop hl
exx
ex af,af'
pop af
ex af,af'
call space
jp menu

.tested
ld hl,startextraed
ld bc,noextra
.tested2
call setextra
ld b,#43
xor a
call looptest1
xor a
ld hl,#fffe
call setmodshl
ld hl,testsed1
call normtest
ld b,52
ld a,#7c
call looptest1
ld b,2
ld a,#b0
call testirdr1
ld b,2
call testirdr2
ld b,4
call looptest1
ld b,2
ld a,#b8
call testirdr1
ld b,2
call testirdr2
ld a,#bc
ld b,#44
call looptest1
call newline2
call printsnl
db "CPIR, CPDR with match",0
call newline2
ld a,#ff
ld (testcpir),a
xor a
ld (modmoda + 1),a
ld a,#b1
ld b,1
call testirdr1
ld a,#b9
ld b,1
call testirdr1
xor a
ld (testcpir),a
ld a,#ff
ld (modmoda + 1),a
call resetmods
jp resetextra

.testirdr1
push af
push bc
ld b,a
ld a,(moda + 1)
push af
.modmoda
ld a,#ff
ld (moda + 1),a
ld a,b
push de
ld hl,2  ;Do first for a count of 2
ld (modbc + 1),hl
ld (tests3 + 1),a
call testitcl
push bc
ld hl,1  ;Then for a count of 1
ld (modbc + 1),hl
call testitcl
pop hl
ld a,(modmoda + 1)
or a
ld a,h
jr z,nosub
sub b
.nosub
ld c,b
ld b,a
ld a,(tests3 + 1)
pop de
call showinst
pop af
ld (moda + 1),a
pop bc
pop af
inc a
djnz testirdr1
ret

.testirdr2
push af
push bc
push de
ld hl,#200  ;Do first for a count of 2
ld (modbc + 1),hl
ld (tests3 + 1),a
call testitcl
push bc
ld hl,#100  ;Then for a count of 1
ld (modbc + 1),hl
call testitcl
pop hl
ld a,h
sub b
ld c,b
ld b,a
ld a,(tests3 + 1)
pop de
call showinst
pop bc
pop af
inc a
djnz testirdr2
ret

.testitcl
ld hl,0
ld (#fffe),hl
ld (#fffc),hl
ld hl,tests3
ld e,0
jp testit

.stdinst
ld hl,tests1
call normtest
push de
ld hl,(modbc + 1)
push hl
ld hl,#100
ld (modbc + 1),hl
ld hl,testdjnz
ld e,0
call testit
push bc
ld a,#02
ld (modbc + 2),a
ld hl,testdjnz
ld e,0
call testit
ld a,b
pop bc
sub b
ld c,b
ld b,a
pop hl
ld (modbc + 1),hl
pop de
ld a,#10
call showinst
ld hl,tests2
call normtest
ld b,#37
ld a,#3f
call looptest1
ld bc,#101
call showinst
ld b,#4b
ld a,#77
call looptest1
ld hl,tests4
call normtest
ld a,#c7
call rsttest
ld hl,tests5
call normtest
ld a,#cf
call rsttest
ld hl,tests6
call normtest
ld a,#ff
ld (moda + 1),a
ld hl,testoutn
call testboth
call showinst
xor a
ld (moda + 1),a
ld hl,tests7
call normtest
ld a,#d7
call rsttest
ld hl,tests8
call normtest
ld a,#ff
ld (moda + 1),a
ld hl,testinn
call testboth
call showinst
xor a
ld (moda + 1),a
ld hl,tests9
call normtest
ld a,#df
call rsttest
ld hl,tests10
call normtest
ld a,#e7
call rsttest
ld hl,instruction + 1
xor a
call setmodshl
ld hl,tests11
call normtest
call resetmods
ld a,#ef
call rsttest
ld hl,tests12
call normtest
ld a,#f7
call rsttest
ld hl,tests13
call normtest
ld a,#ff
jp rsttest

.testcb
push bc
push af
ld (testscb1 + 2),a
ld hl,testscb1
call testboth
pop af
push af
call showinst
pop af
pop bc
inc a
djnz testcb
ret

.testa
ld (tests3 + 1),a
ld hl,tests3
call testboth
ret

.rsttest
call testa
dec b:dec b:dec b
dec c:dec c:dec c
jp showinst

.clear
ld hl,#c050
ld b,8
.clrlp
push bc
push hl
ld d,h
ld e,l
inc de
ld bc,#7ff - #50
ld (hl),0
ldir
pop hl
ld a,h
add 8
ld h,a
pop bc
djnz clrlp
ret

.space
ld de,#c780
call prints
db "Press Space to continue",0
.wtspc
call scan
ld a,KEY_SPACE
call tkey
jr nz,wtspc
ret

.looptest1
ld hl,tests3
ld c,1

.looptest ; B = count, C = instruction offset, A = first instruction,
          ; HL = buffer
push bc
push af
push hl
ld b,0
add hl,bc
ld (hl),a
pop hl
push hl
call testboth
call showinst
pop hl
pop af
inc a
pop bc
djnz looptest
ret

.normtest
ld b,(hl)
inc hl
.t5lp2
push bc
call testboth
call showinst
pop bc
djnz t5lp2
ret

.newline  ;DE = current position
ld hl,#c000
ld bc,#50
.newlnlp
call cphlde
jr nc,usehl
add hl,bc
jr newlnlp
.usehl
ret

.newline2
call newline
add hl,bc
ex de,hl
ret

.cphlde
ld a,h
cp d
ret nz
ld a,l
cp e
ret

.printsnl
call checknl
jp prints

.checknl
push af
push bc
push hl
push de
ld hl,#c730
call cphlde
jr z,newscr
jr nc,nonew
.newscr
call space
call clear
pop de
ld de,#c0a0
push de
.nonew
pop de
pop hl
pop bc
pop af
ret

.showinst  ;A = Instruction, B,C = time
push hl
push bc
push af
call checknl
push bc
call hexa
call prints
db ":",0
pop bc
push bc
ld a,b
call bithex
pop bc
ld a,c
cp b
jr z,nosec
push bc
call prints
db "/",0
pop bc
ld a,c
call bithex
jr endins
.nosec
call prints
db "  ",0
.endins
pop af
.times
call gettimes
pop bc
ld a,(bcpause + 1)
dec a
call nz,modwaittime
ld a,h
cp b
jr nz,badtime
ld a,l
cp c
jr nz,badtime
call prints
db 06," ",0
pop hl
ret

.badtime
call prints
db #cb," ",0
pop hl
ret

.gettimes
ld c,a
ld b,0
ld hl,times1
add hl,bc
ld a,(hl)
.modtime
ld h,a
and #f
ld l,a
ld a,h
rra
rra
rra
rra
and #f
ld h,a
ret

.gettimescb
ld b,a
ld c,#22
and 7
cp 6
jr nz,gottimecb
ld c,#44
bit 7,b
jr nz,gottimecb
bit 6,b
jr z,gottimecb
ld c,#33
.gottimecb
ld a,c
jr modtime

.gettimesdd
push af
call gettimes
inc h
inc l
pop af
cp #34
jr c,gottimedd
cp #37
jr c,longdd
cp #46
jr c,gottimedd
cp #bf
jr nc,gottimedd
cp #70
jr c,not7077
cp #78
jr nc,not7077
cp #76
jr nz,longdd
ld hl,#101
jr gottimedd
.not7077
and 7
cp 6
jr nz,gottimedd
.longdd
inc h
inc l
inc h
inc l
.gottimedd
ret

.gettimesed
push af
ld a,(modmoda + 1)
or a
jr nz,normtimes
pop af
ld c,#44
jr gottimecb

.normtimes
pop af
ld c,#22
cp #bc
jr nc,gottimecb
sub #40
jr c,gottimecb
ld c,a
ld b,0
ld hl,times2
add hl,bc
ld a,(hl)
jr modtime

.gettimesddcb
ld c,#77
cp #40
jr c,gottimecb
cp #80
jr nc,gottimecb
ld a,#66
jp modtime

.storesp2
dw 0

.storesp
dw 0

.instend
dw 0

.store
ds 4

.testboth ; HL = address of size + data
          ; Returns A = instruction, HL = end of data, B = time1, C = time2
push de
ld e,0
push hl
call testit
ld d,b
pop hl
dec e
call testit
ld c,d
pop de
ret

.testit ; HL = address of size + data, E = flags
        ; Returns A = instruction, HL = end of data, B = time
push de
ld c,(hl)
ld b,0
inc hl
push bc
push hl
call runit
.reftime
ld de,0
ex de,hl
or a
sbc hl,de
ld b,l
pop hl
pop de
ld a,(hl)
add hl,de
pop de
ret

.noextra
ret

.resetextra
ld hl,noextra
ld b,h
ld c,l
.setextra ; HL = start routine, BC = end routine
ld (startextra + 1),hl
ld (endextra + 1),bc
ret

.startextraed
ld a,#ed
ld (de),a
inc de
ret

.startextradd
push af
ld a,#dd
jr setextrafd

.startextrafd
push af
ld a,#fd
.setextrafd
ld (de),a
inc de
pop af
cp #e9  ; jp (ix), jp (iy)
ret nz
push hl
ld hl,instruction + 2
ld (modix + 2),hl
ld (modiy + 2),hl
pop hl
ret

.startextraddcb
push af
ld a,#dd
jr setextrafdcb

.startextrafdcb
push af
ld a,#fd
.setextrafdcb
ld (de),a
inc de
ld a,#cb
ld (de),a
inc de
ld a,0
ld (de),a
inc de
pop af
ret

.endextraddfd
cp #34
jr c,nosetdd
cp #37
jr c,setdd
cp #46
jr c,nosetdd
cp #bf
jr nc,nosetdd
cp #76
jr z,nosetdd
cp #70
jr c,less70
cp #78
jr c,setdd
.less70
and 7
cp 6
jr nz,nosetdd
.setdd
xor a
ld (de),a
inc de
.nosetdd
ret


.runit  ;HL = address of instruction data to run, BC = size, DE = Flags
        ;Returns
di
push bc
push de
ld (flags + 1),de
ld (storesp),sp
push bc
push hl
ld bc,#7f8e  ;Disable lower ROM
out (c),c
call waitffb
ld de,0
call setint
ld bc,#bc0f    ;Ensure writing to reg 15
out (c),c
ei
halt
ld de,instruction
pop hl
ld a,(hl)
.startextra
call noextra
pop bc
ld a,(hl)
ldir
.endextra
call noextra
ld (instend),de
ld h,d
ld l,e
dec hl
ld a,(hl)
cp hi3
jr nz,nohi3
dec hl
ld a,(hl)
cp lo3
jr nz,nohi3
ld (hl),e
inc hl
ld (hl),d
.nohi3
push de   ; For RET tests
ld b,8
xor a
.clrlp2
ld (de),a
inc de
djnz clrlp2
ld (storesp2),sp
ld hl,#38
ld (#be86),hl
ld (#beff),hl
ld a,#be
ld i,a
ei
halt
ld de,getins
call setint
ld e,47
call waitrowe
.flags
ld hl,0
push hl
ld a,#c9
ld (#0000),a
ld (#0008),a
ld (#0010),a
ld (#0018),a
ld (#0020),a
ld (#0028),a
ld (#0030),a
ld (#0038),a
pop af
.modhl
ld hl,store
.modde
ld de,store
.modbc
ld bc,store
.modix
ld ix,store
.modiy
ld iy,store
.moda
ld a,0
ei
.pruntest
jp instruction
.instruction
ds 18
di
im 1
ei
nop
nop
ld a,#c3
ld (#38),a
ld sp,(storesp)
.bcpause
ld bc,1
.lpbc1
dec bc
ld a,b
or c
jr nz,lpbc1
ei
ds 256
.getins
ld de,0
call setint
pop hl
ld bc,(instend)
or a
sbc hl,bc
ld sp,(storesp)
ld bc,#7f8a
out (c),c
pop de
pop bc
ret

.resetmods
xor a
ld hl,store
.setmodshl
ld (modhl + 1),hl
ld (modde + 1),hl
ld (modbc + 1),hl
ld (modix + 2),hl
ld (modiy + 2),hl
ld (moda + 1),a
ret

.puta
push hl
ld (hl),a
inc hl
ld (hl),a
inc hl
ld (hl),a
inc hl
ld (hl),a
inc hl
pop hl
ld a,h
add 8
ld h,a
ret

.runtest6
call reset
ld de,#c000
call prints
db "Register 0 Test",0
ld de,#c050
call prints
db "R9:   R4:   R5:   R0:",0
ld de,#c0a0
call prints
db "Addr:",0
ld de,#c1e0
call prints
db "ABCDEFGHIJKLMNOPQRSTUVWXYZ",0
ld hl,#c190
ld a,3
call puta
ld a,#c
call puta
ld a,#f
call puta
ld a,#30
call puta
ld a,#33
call puta
ld a,#3c
call puta
ld a,#3f
call puta
ld a,#ff
call puta
call waitffb
ei
halt
ei
halt
ld hl,#bfff
ld (bytead),hl
.test6
call waitffb
ld bc,#bc07
out (c),c
ld bc,#bd1e
out (c),c
ld bc,#bc06
out (c),c
ld bc,#bd05
out (c),c
ld b,22
djnz $-1
ld bc,#7f9e
out (c),c
call scan
ld a,(tkey6)
dec a
jr nz,nos6
ld hl,t6r4
ld a,KEY_Z
call tkey
jr nz,noz6
ld (hl),0
ld de,(outca)
ld (t6r4set),de
.noz6
ld a,KEY_X
call tkey
jr nz,nox6
ld (hl),1
ld de,(outcd)
ld (t6r4set),de
.nox6
ld hl,t6r5
ld a,KEY_A
call tkey
jr nz,noa6
dec (hl)
.noa6
ld a,KEY_S
call tkey
jr nz,nos6
inc (hl)
.nos6
ei
halt
ld bc,#bc06
out (c),c
ld bc,#bd05
out (c),c
ld hl,tkey6
dec (hl)
jr nz,nodown6
ld (hl),3
ld hl,t6r9
ld a,KEY_UP
call tkey
jr nz,noup6
dec (hl)
.noup6
ld a,KEY_DOWN
call tkey
jr nz,nodown6
inc (hl)
.nodown6
ld bc,#7f8a
out (c),c
ld a,(t6r9)
ld de,#c053
call hexa
ld hl,(bytead)
ld de,#c0a5
call hexhl
ld a,(t6r4)
ld de,#c059
call hexa
ld a,(t6r5)
ld bc,#bc05
out (c),c
inc b
out (c),a
ld de,#c05f
call hexa
ld a,(t6r0)
ld de,#c065
call hexa
ld bc,#7f8e
out (c),c
ei
halt
ld bc,#7f8c
out (c),c
ld b,72
djnz $-1
ld de,#0102
ld bc,#bc04
out (c),c
inc b
out (c),c
ld bc,#bc0d
out (c),c
ld bc,#bdc9
out (c),c
ld bc,#bc09
out (c),c
ld a,(t6r9)
inc b
out (c),a
xor a
dec b
out (c),d
.t6r1
ld bc,#bd01
out (c),d
ld bc,#bc02
out (c),c
ld bc,#bd08
out (c),c
dec b
out (c),a
inc b
out (c),d
ld bc,#bc04
out (c),c
inc b
.t6r4set
out (c),a
nop:nop:nop:nop:nop:nop:nop:nop
nop:nop:nop:nop:nop:nop
dec b
out (c),a
ld bc,#bd13
out (c),c
ld hl,#0520
nop
.test6lp
nop:nop:nop:nop:nop:nop:nop:nop
nop:nop:nop:nop
out (c),h
nop:nop
out (c),d
nop:nop:nop:nop:nop:nop:nop:nop
nop:nop:nop:nop:nop:nop:nop:nop
nop:nop:nop:nop:nop:nop:nop:nop
nop:nop:nop:nop:nop:nop:nop:nop
nop:nop
out (c),c
dec l
jp nz,test6lp
ld h,#19
out (c),h
dec b
out (c),d
inc b
out (c),a
dec b
out (c),e
ld bc,#bd2e
out (c),c
dec b
out (c),a
ld bc,#bd3f
out (c),c
ld bc,#bc09
out (c),c
ld bc,#bd00
out (c),c
ld bc,#bc05
out (c),c
ld bc,#bd00
out (c),c
ld e,#a0
call waitrowe
ld bc,#bc09
out (c),c
ld bc,#bd07
out (c),c
ld bc,#bc04
out (c),c
ld bc,#bd09
out (c),c
ld bc,#bc07
out (c),c
ld bc,#bd01
out (c),c
ld bc,#7f8e
out (c),c
ld bc,#bc01
out (c),c
ld bc,#bd28
out (c),c
ld bc,#bc0d
out (c),c
inc b
xor a
out (c),a
ld bc,#bc05
out (c),c
inc b
out (c),a
ld a,KEY_RIGHT
call tkey
jr nz,noright6
ld hl,(bytead)
inc hl
set 7,h
set 6,h
ld (bytead),hl
ld (hl),#cc
.noright6
ld a,KEY_SPACE
call tkey
jp z,menu
jp test6

.bytead
dw #bfff

.t6r9
db 6
.t6r4
db 0
.t6r5
db 0
.t6r0
db 2
.tkey6
db 2

.outca
out (c),a

.outcd
out (c),d

.runtest7
call reset
ld de,#c000
call prints
db "Register 4 Test",0
ld e,#a0
call prints
db "NOPS1:",0
ld e,#f0
call prints
db "NOPS2:",0
ld de,#c140
call prints
db "R5:",0
ld de,#c190
call prints
db "Line 5",0
ld de,#c1e0
call prints
db "Line 6",0
ld de,#c230
call prints
db "Line 7",0
ld de,#c280
call prints
db "NOPS3:",0
ld bc,#7f8e
out (c),c
ld hl,#2000
ld de,#2001
ld bc,#1fff
ld (hl),0
ldir
call waitffb
ei
halt
ei
halt
.test7
call waitffb
ld b,30
djnz $-1
ld bc,#7f9e
out (c),c
call scan
ei
halt
ld bc,#7f8a
out (c),c
ld hl,(t7nops)
ld de,#c0a7
call hexhl
ld hl,(t7nops2)
ld de,#c0f7
call hexhl
ld de,#c144
ld a,(t7r5)
call hexa
ld de,#c287
ld hl,(t7nops3)
call hexhl
ld bc,#7f8e
out (c),c
ld hl,(t7nops)
ld bc,#2000
add hl,bc
ld (hl),#c9
ld a,(t7r5)
ld bc,#bc05
out (c),c
inc b
out (c),a
ei
halt
ld e,4
call waitrowe
ld b,2
djnz $-1
call #2000
ld (hl),0
ld hl,(t7nops2)
ld bc,#2000
add hl,bc
ld (hl),#c9
ld bc,#bc04
out (c),c
ld bc,#bd05
out (c),c
call #2000
ld (hl),0
ld c,7
out (c),c
ld hl,(t7nops3)
ld bc,#2000
add hl,bc
ld (hl),#c9
call #2000
ld (hl),0
ld bc,#bd20
out (c),c
ld bc,#bc07
out (c),c
ld bc,#bd18
out (c),c
ld bc,#bc05
out (c),c
ld bc,#bd00
out (c),c
ld bc,#7f00
out (c),c
ld bc,#7f4c
out (c),c
ld b,20
djnz $-1
ld bc,#7f44
out (c),c
ld hl,t7key
ld a,(hl)
dec a
ld (hl),a
jp nz,noleft7
ld (hl),3
ld a,KEY_A
call tkey
jr nz,noa7
ld hl,(t7nops3)
dec hl
ld a,h
and #1f
ld h,a
ld (t7nops3),hl
.noa7
ld a,KEY_S
call tkey
jr nz,nos7
ld hl,(t7nops3)
inc hl
ld a,h
and #1f
ld h,a
ld (t7nops3),hl
.nos7
ld hl,t7r5
ld a,KEY_Z
call tkey
jr nz,noz7
dec (hl)
.noz7
ld a,KEY_X
call tkey
jr nz,nox7
inc (hl)
.nox7
ld a,KEY_UP
call tkey
jr nz,noup7
ld hl,(t7nops2)
dec hl
ld a,h
and #1f
ld h,a
ld (t7nops2),hl
.noup7
ld a,KEY_DOWN
call tkey
jr nz,nodown7
ld hl,(t7nops2)
inc hl
ld a,h
and #1f
ld h,a
ld (t7nops2),hl
.nodown7
ld a,KEY_RIGHT
call tkey
jr nz,noright7
ld hl,(t7nops)
inc hl
ld a,h
and #1f
ld h,a
ld (t7nops),hl
.noright7
ld a,KEY_LEFT
call tkey
jr nz,noleft7
ld hl,(t7nops)
dec hl
ld a,h
and #1f
ld h,a
ld (t7nops),hl
.noleft7
ld a,KEY_SPACE
call tkey
jp z,menu
jp test7

.t7nops
dw #1ef
.t7nops2
dw 0
.t7nops3
dw #78c
.t7r5
db 0
.t7key
db 2

.runtest8
call reset
ld de,#c000
call prints
db "Register 9 Test",0
ld e,#a0
call prints
db "NOPS1:",0
ld e,#f0
call prints
db "NOPS2:",0
ld de,#c140
call prints
db "R9 (1):",0
ld de,#c190
call prints
db "R9 (2):",0
ld de,#c1e0
call prints
db "Line 6",0
ld de,#c230
call prints
db "Line 7",0
ld de,#c028
ld a,1
ld b,16
.lpt61
push af
push bc
push de
ld b,a
.lpt62
push bc
ld a,#95
call fchar
pop bc
djnz lpt62
pop hl
ld de,#50
add hl,de
ex de,hl
pop bc
pop af
inc a
djnz lpt61
ld bc,#7f8e
out (c),c
ld hl,#2000
ld de,#2001
ld bc,#1fff
ld (hl),0
ldir
call waitffb
ei
halt
ei
halt
.test8
call waitffb
ld b,30
djnz $-1
ld bc,#7f9e
out (c),c
call scan
ei
halt
ld bc,#7f8a
out (c),c
ld hl,(t8nops1)
ld de,#c0a7
call hexhl
ld hl,(t8nops2)
ld de,#c0f7
call hexhl
ld de,#c148
ld a,(t8r9a)
call hexa
ld de,#c198
ld a,(t8r9b)
call hexa
ld bc,#7f8e
out (c),c
ld hl,(t8nops1)
ld bc,#2000
add hl,bc
ld (hl),#c9
ei
halt
ld e,13
call waitrowe
call #2000
ld (hl),0
ld hl,(t8nops2)
ld bc,#2000
add hl,bc
ld (hl),#c9
ld bc,#bc09
out (c),c
ld a,(t8r9a)
inc b
out (c),a
call #2000
ld (hl),0
ld a,(t8r9b)
out (c),a
ld e,2
call waitrowe
ld bc,#bd07
out (c),c
ld hl,t8key
dec (hl)
jr nz,nodown8
ld (hl),3
ld a,KEY_A
call tkey
jr nz,noa8
ld hl,(t8nops1)
dec hl
ld a,h
and #1f
ld h,a
ld (t8nops1),hl
.noa8
ld a,KEY_S
call tkey
jr nz,nos8
ld hl,(t8nops1)
inc hl
ld a,h
and #1f
ld h,a
ld (t8nops1),hl
.nos8
ld a,KEY_Z
call tkey
jr nz,noz8
ld hl,(t8nops2)
dec hl
ld a,h
and #1f
ld h,a
ld (t8nops2),hl
.noz8
ld a,KEY_X
call tkey
jr nz,nox8
ld hl,(t8nops2)
inc hl
ld a,h
and #1f
ld h,a
ld (t8nops2),hl
.nox8
ld hl,t8r9a
ld a,KEY_LEFT
call tkey
jr nz,noleft8
dec (hl)
.noleft8
ld a,KEY_RIGHT
call tkey
jr nz,noright8
inc (hl)
.noright8
ld hl,t8r9b
ld a,KEY_UP
call tkey
jr nz,noup8
dec (hl)
.noup8
ld a,KEY_DOWN
call tkey
jr nz,nodown8
inc (hl)
.nodown8
ld a,KEY_SPACE
call tkey
jp z,menu
jp test8

.t8nops1
dw 0

.t8nops2
dw 0

.t8r9a
db 7

.t8r9b
db 7

.t8key
db 2

.key
db 2

.runtest9
ex af,af'
push af
ex af,af'
exx
push hl
push de
push bc
exx
call reset
di
ld de,#c000
call prints
db "Interrupt Wait state timing test",0
ld hl,waittest
ld (pruntest + 1),hl
ld hl,450
ld (bcpause + 1),hl
xor a
ld (testcpir),a
jp dotest5

.waittest
;Insert exact number of wait states to cause interrupt generate
push bc
push af
ld b,45
djnz $-1
pop af
pop bc
nop
nop
jp instruction

.modwaittime
push af
ld a,b
and #f
ld b,a
ld a,c
and #f
ld c,a
push bc
push de
push hl
ld hl,adjtable
ld de,#0000
ld a,(instruction)
cp #dd
jr z,waitddfd
cp #fd
jr nz,twaited
.waitddfd
ld de,#0101
ld a,(instruction + 1)
jr testwait
.twaited
cp #ed
jr nz,testwait
ld a,(instruction + 1)
cp #b1
jr z,isb1
cp #b9
jr nz,notb1
.isb1
ld b,a
ld a,(testcpir)
or a
jr nz,nomatch
ld a,b
.notb1
cp #46
jr z,is46
cp #4e
jr z,is46
cp #66
jr z,is46
cp #6e
jr nz,not46
.is46
.break
ld a,(plus)
ld a,#dd
jr nz,newtimea
ld a,#22
jr newtimea
.not46
ld hl,adjtableed
.testwait
ld b,(hl)
.testwait1
inc hl
cp (hl)
jr z,newtime
inc hl
djnz testwait1
.nomatch
pop hl
.retshow
pop de
pop bc
pop af
ret

.newtime
inc hl
ld a,(hl)
.newtimea
ld l,a
and #f0
rrca
rrca
rrca
rrca
add d
ld h,a
ld a,l
and #0f
add e
ld l,a
pop de
jr retshow

.testcpir
db 0

;opcodes, times
.adjtable
db 18
db #03,#11, #0b,#11, #13,#11, #1b,#11, #23,#11, #2b,#11, #33,#11, #3b,#11
db #c0,#14, #c8,#41, #d0,#14, #d8,#41, #e0,#14, #e3,#55, #e8,#41, #f0,#14
db #f8,#41, #f9,#11

.adjtableed
db 12
db #47,#22, #4f,#22, #57,#22, #5e,#44, #5f,#22, #7e,#44, #a0,#44, #a8,#44
db #b0,#64, #b1,#54, #b8,#64, #b9,#54

.waitrowe
ld b,14
.lpwtrow
djnz lpwtrow
nop
nop
nop
dec e
jr nz,waitrowe
ret

.setvals
di
ld bc,#7fb8
out (c),c
ld hl,(sprx)
ld (#6000),hl
ld hl,(#6000)
ld (sprx),hl
ld hl,(spry)
ld (#6002),hl
ld hl,(#6002)
ld (spry),hl
ld a,(sprsz)
ld (#6004),a
ld a,(r2)
ld bc,#bc02
out (c),c
inc b
out (c),a
ld a,(r9)
ld bc,#bc09
out (c),c
inc b
and #1f
out (c),a
ld bc,#bc04
out (c),c
ld l,a
ld h,0
inc hl
ld e,l
ld d,h
or a
ld c,#71
jr z,isbig
ld c,#54
dec a
jr z,isbig
ld c,0
.lpbig
ld a,h
cp #01
jr nz,notbig
ld a,l
cp #38
jr nc,isbig
.notbig
inc c
add hl,de
jr lpbig
.isbig
inc b
out (c),c
dec b
ld a,6
out (c),a
inc b
dec c
out (c),c
ld a,e
dec a
jr nz,not1
ld a,20
jr set7
.not1
dec a
jr nz,not2
ld a,20
jr set7
.not2
ld a,c
srl a
.set7
ld bc,#bc07
out (c),c
inc b
out (c),a
ld bc,#7fa0
out (c),c
ld bc,#7f8a
out (c),c
ei
ret

.prints
ex (sp),hl
call printhl
ex (sp),hl
ret

.printhl
ld a,(hl)
inc hl
or a
ret z
call fchar
jr printhl

.hexhl
ld a,h
call hexa
ld a,l
.hexa
push af
rra
rra
rra
rra
call bithex
pop af
.bithex
and #f
cp 10
jr c,less10
add 7
.less10
add 48
jp fchar

.waitffb
ld b,#f5
.waitffblp
in a,(c)
rra
jr nc,waitffblp
ret

.waite
call waitffb
ei
halt
ei
halt
dec e
jr nz,waite
ret

.plus
db 0

.reset
di
ld hl,store40
ld de,0
ld bc,#40
ldir
ld e,10
call waite
ld hl,defvals
ld bc,#bc00
.lpcrtc
ld a,(hl)
inc hl
out (c),c
inc b
out (c),a
dec b
inc c
ld a,c
cp 14
jr nz,lpcrtc
di
ld bc,#7fb8
out (c),c
xor a
ld (#6004),a
ld a,(defssc)
ld (#6804),a
ld a,#81        ;Should cause IM0 instruction to use #86
ld (#6805),a

ld hl,#fff
ld (#6422),hl

ld a,#ff
ld (#4000),a
ld a,(#4000)
and #f0
ld (plus),a

ld hl,spr
ld de,#4000
ld bc,#100
ldir

ld e,10
call waite
ld a,2
jp SCR_SET_MODE

.scan       ;Scans the keyboard to ktab, called on interrupt
            ;Only flags corrupt
ld l,0
ld bc,#f40e
out (c),c
ld bc,#f6c0
out (c),c
out (c),l
ld bc,#f792
out (c),c
ld c,#49
ld hl,ktab+9
.sclp
ld b,#f6
out (c),c
ld b,#f4
ind
dec c
bit 6,c
jp nz,sclp
ld bc,#f782
out (c),c
ret

.tkey       ;Tests key A, returns Z if pressed
push hl
rrca
rrca
rrca
ld h,a
and #1f
ld l,a
ld a,h
ld h,0
ld bc,ktab
add hl,bc
rra
rra
and #38
or #46
ld (gmsk+1),a
.gmsk
bit 0,(hl)
pop hl
ret

.fchar  ;Output the character A at DE
push bc
push hl
ld l,a
ld h,7
add hl,hl
add hl,hl
add hl,hl
ld c,d
ld b,8
.chlp
ld a,(hl)
inc l
ld (de),a
ld a,d
add 8
ld d,a
djnz chlp
ld d,c
pop hl
pop bc
inc de
ret

.setint  ; Sets the interrupt address to DE
di
ld hl,(#39)
ld a,d
or e
jr z,setc9
ld (hl),#c3
inc hl
ld (hl),e
inc hl
ld (hl),d
ret
.setc9
ld (hl),#c9
ret

.nops
nop
nop
nop
nop
nop
nop
nop
nop
ret

.unlock
db #FF,#00,#FF,#77,#B3,#51,#A8,#D4,#62,#39,#9C,#46,#2B,#15,#8A,#CD,#EE

.defvals
db #3F,#28,#2E,#0E,#26,#00,#19,#1E,#00,#07,#00,#00,#30,#00

.spr
db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
db 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1
db 1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1
db 1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1
db 1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1
db 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1
db 1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1
db 1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1
db 1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1
db 1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1
db 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1
db 1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1
db 1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1
db 1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1
db 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1
db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

.tests1
db 16
db 1,#00, 3,#01,0,0, 1,#02, 1,#03, 1,#04, 1,#05, 2,#06,0, 1,#07
db 1,#08, 1,#09, 1,#0a, 1,#0b, 1,#0c, 1,#0d, 2,#0e,0, 1,#0f

.testdjnz
db 2,#10,#fe

.tests2
db 46
db 3,#11,0,0, 1,#12, 1,#13, 1,#14, 1,#15, 2,#16,0, 1,#17
db 2,#18,0, 1,#19, 1,#1a, 1,#1b, 1,#1c, 1,#1d, 2,#1e,0, 1,#1f
db 2,#20,0, 3,#21,0,0, 3,#22,0,0, 1,#23, 1,#24, 1,#25, 2,#26,0
db 1,#27, 2,#28,0, 1,#29, 3,#2a,0,0, 1,#2b, 1,#2c, 1,#2d
db 2,#2e,0, 1,#2f, 2,#30,0, 3,#31,0,0, 3,#32,0,0, 1,#33, 1,#34
db 1,#35, 2,#36,0, 1,#37, 2,#38,0, 1,#39, 3,#3a,0,0, 1,#3b
db 1,#3c, 1,#3d, 2,#3e,0

.tests3
db 1,0

.instruction3 equ instruction + 3

.lo3 equ instruction3 and #ff
.hi3 equ instruction3 / 256;

.tests4
db 5
db 3,#c2,lo3,hi3, 3,#c3,lo3,hi3, 3,#c4,lo3,hi3, 1,#c5, 2,#c6,0 

.tests5
db 6
db 1,#c8, 1,#c9, 3,#ca,lo3,hi3, 3,#cc,lo3,hi3, 3,#cd,lo3,hi3, 2,#ce,0

.tests6
db 3
db 1,#d0, 1,#d1, 3,#d2,lo3,hi3

.testoutn
db 2,#d3,#ff

.tests7
db 3
db 3,#d4,lo3,hi3, 1,#d5, 2,#d6,0

.tests8
db 3
db 1,#d8, 1,#d9, 3,#da,lo3,hi3

.testinn
db 2,#db,#ff

.tests9
db 2
db 3,#dc,lo3,hi3, 2,#de,0

.tests10
db 7
db 1,#e0, 1,#e1, 3,#e2,lo3,hi3, 1,#e3, 3,#e4,lo3,hi3, 1,#e5
db 2,#e6,0

.tests11
db 6
db 1,#e8, 1,#e9, 3,#ea,lo3,hi3, 1,#eb, 3,#ec,lo3,hi3, 2,#ee,0

.tests12
db 7
db 1,#f0, 1,#f1, 3,#f2,lo3,hi3, 1,#f3, 3,#f4,lo3,hi3, 1,#f5, 2,#f6,0

.tests13
db 6
db 1,#f8, 1,#f9, 3,#fa,lo3,hi3, 1,#fb, 3,#fc,lo3,hi3, 2,#fe,0

.testscb1
db 2,#cb,0

.losp equ storesp2 and #ff
.hisp equ storesp2 / 256;

.testsed1
db 57
db 3,#43,0,0, 1,#44, 1,#45, 1,#46, 1,#47, 1,#48, 1,#49, 1,#4a, 3,#4b,0,0
db 1,#4c, 1,#4d, 1,#4e, 1,#4f, 1,#50, 1,#51, 1,#52, 3,#53,0,0, 1,#54
db 1,#55, 1,#56, 1,#57, 1,#58, 1,#59, 1,#5a, 3,#5b,0,0, 1,#5c, 1,#5d
db 1,#5e, 1,#5f, 1,#60, 1,#61, 1,#62, 3,#63,0,0, 1,#64, 1,#65, 1,#66
db 1,#67, 1,#68, 1,#69, 1,#6a, 3,#6b,0,0, 1,#6c, 1,#6d, 1,#6e, 1,#6f
db 1,#70, 1,#71, 1,#72, 3,#73,0,0, 1,#74, 1,#75, 1,#76, 1,#77, 1,#78
db 1,#79, 1,#7a, 3,#7b,losp,hisp

.times1
db #11,#33,#22,#22,#11,#11,#22,#11,#11,#33,#22,#22,#11,#11,#22,#11
db #43,#33,#22,#22,#11,#11,#22,#11,#33,#33,#22,#22,#11,#11,#22,#11
db #23,#33,#55,#22,#11,#11,#22,#11,#32,#33,#55,#22,#11,#11,#22,#11
db #23,#33,#44,#22,#33,#33,#33,#11,#32,#33,#44,#22,#11,#11,#22,#11
db #11,#11,#11,#11,#11,#11,#22,#11,#11,#11,#11,#11,#11,#11,#22,#11
db #11,#11,#11,#11,#11,#11,#22,#11,#11,#11,#11,#11,#11,#11,#22,#11
db #11,#11,#11,#11,#11,#11,#22,#11,#11,#11,#11,#11,#11,#11,#22,#11
db #22,#22,#22,#22,#22,#22,#11,#22,#11,#11,#11,#11,#11,#11,#22,#11
db #11,#11,#11,#11,#11,#11,#22,#11,#11,#11,#11,#11,#11,#11,#22,#11
db #11,#11,#11,#11,#11,#11,#22,#11,#11,#11,#11,#11,#11,#11,#22,#11
db #11,#11,#11,#11,#11,#11,#22,#11,#11,#11,#11,#11,#11,#11,#22,#11
db #11,#11,#11,#11,#11,#11,#22,#11,#11,#11,#11,#11,#11,#11,#22,#11
db #24,#33,#33,#33,#35,#44,#22,#44,#42,#33,#33,#00,#53,#55,#22,#44
db #24,#33,#33,#33,#35,#44,#22,#44,#42,#11,#33,#33,#53,#00,#22,#44
db #24,#33,#33,#66,#35,#44,#22,#44,#42,#11,#33,#11,#53,#00,#22,#44
db #24,#33,#33,#11,#35,#44,#22,#44,#42,#22,#33,#11,#53,#00,#22,#44

.times2
db #44,#44,#44,#66,#22,#44,#22,#33,#44,#44,#44,#66,#22,#44,#22,#33
db #44,#44,#44,#66,#22,#44,#22,#33,#44,#44,#44,#66,#22,#44,#22,#33
db #44,#44,#44,#66,#22,#44,#22,#55,#44,#44,#44,#66,#22,#44,#22,#55
db #44,#44,#44,#66,#22,#44,#22,#22,#44,#44,#44,#66,#22,#44,#22,#22
db #22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22
db #22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22,#22
db #55,#44,#55,#55,#22,#22,#22,#22,#55,#44,#55,#55,#22,#22,#22,#22
db #65,#64,#65,#65,#22,#22,#22,#22,#65,#64,#65,#65

list
.ktab
ds 10

.store40
ds #40

.end
