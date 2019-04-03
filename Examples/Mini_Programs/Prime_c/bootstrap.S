.globl _start
.globl main
.globl _store_internals
.equ _memEnd, 0x10000

_start:
li sp, _memEnd
jal main
nop
nop
nop
nop

_end:
	ebreak
nop
nop
nop
nop

#define STORE    sw
#define REGBYTES 4

_store_internals:
addi    sp, sp, -REGBYTES * 32

STORE	x1, 0x0(sp)
STORE	x2, 1 * REGBYTES(sp)
STORE	x3, 2 * REGBYTES(sp)
STORE	x4, 3 * REGBYTES(sp)
STORE	x5, 4 * REGBYTES(sp)
STORE	x6, 5 * REGBYTES(sp)
STORE	x7, 6 * REGBYTES(sp)
STORE	x8, 7 * REGBYTES(sp)
STORE	x9, 8 * REGBYTES(sp)
STORE	x10, 9 * REGBYTES(sp)
STORE	x11, 10 * REGBYTES(sp)
STORE	x12, 11 * REGBYTES(sp)
STORE	x13, 12 * REGBYTES(sp)
STORE	x14, 13 * REGBYTES(sp)
STORE	x15, 14 * REGBYTES(sp)
STORE	x16, 15 * REGBYTES(sp)
STORE	x17, 16 * REGBYTES(sp)
STORE	x18, 17 * REGBYTES(sp)
STORE	x19, 18 * REGBYTES(sp)
STORE	x20, 19 * REGBYTES(sp)
STORE	x21, 20 * REGBYTES(sp)
STORE	x22, 21 * REGBYTES(sp)
STORE	x23, 22 * REGBYTES(sp)
STORE	x24, 23 * REGBYTES(sp)
STORE	x25, 24 * REGBYTES(sp)
STORE	x26, 25 * REGBYTES(sp)
STORE	x27, 26 * REGBYTES(sp)
STORE	x28, 27 * REGBYTES(sp)
STORE	x29, 28 * REGBYTES(sp)
STORE	x30, 29 * REGBYTES(sp)
STORE	x31, 30 * REGBYTES(sp)

addi	sp, sp, REGBYTES * 32
ret