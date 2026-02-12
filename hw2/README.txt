// AUTHOR: JAMES HYLE
// PROFESSOR: BUFFENBARGER
// CLASS: CS452 OPERATING SYSTEMS
// SEMESTER: SPRING 2026

USAGE:
To use this program, cd into the subfolder "hw2" and invoke the make command at the terminal. The program will compile and then invoke "./main" on the terminal. To check the program with valgrind invoke "valgrind --leak-check=full ./main". Valgrind output is shown in the corresponding section. To clean dir, invoke "make clean" on command line. 

MAIN OUTPUT WITH VALGRIND:
valgrind ./main
==3312== Memcheck, a memory error detector
==3312== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3312== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3312== Command: ./main
==3312== 
bmt before: FF
bmt before: 255
bmt after bitclr: 7F
bmt after bitclr: 127

bmt before: FF
bmt before: 255
bmt after bitinv: FD
bmt before: 253
e2size(t): 4
size2e: 3
                BUDDY TEST

Initial State: Pool created (1024 bytes)
NULL pool
---allocator State---
Pool address:    0x4029000
Memory address:  0x402a000
Pool size:       1024 bytes
lower:  4 (2^4 = 16 bytes)
upper:  10 (2^10 = 1024 bytes)

--- free Lists ---
Free Lists (orders 4 to 10):
  Order 4 (size 16): empty
  Order 5 (size 32): empty
  Order 6 (size 64): empty
  Order 7 (size 128): empty
  Order 8 (size 256): empty
  Order 9 (size 512): empty
  Order 10 (size 1024): 0x402a000 -> NULL

--- bitmaps ---
(1 = allocated, 0 = free)
bbmprt:
00 00 00 00
00 00
00
00
00
00
00
===========================================


--- basic allocations (64B, 32B, 32B) ---
allocated p1 (64B), p2 (32B), p3 (32B)
NULL pool
---allocator State---
Pool address:    0x4029000
Memory address:  0x402a000
Pool size:       1024 bytes
lower:  4 (2^4 = 16 bytes)
upper:  10 (2^10 = 1024 bytes)

--- free Lists ---
Free Lists (orders 4 to 10):
  Order 4 (size 16): empty
  Order 5 (size 32): empty
  Order 6 (size 64): empty
  Order 7 (size 128): 0x402a080 -> NULL
  Order 8 (size 256): 0x402a100 -> NULL
  Order 9 (size 512): 0x402a200 -> NULL
  Order 10 (size 1024): empty

--- bitmaps ---
(1 = allocated, 0 = free)
bbmprt:
00 00 00 00
00 02
01
00
00
00
00
===========================================


--- large allocations (128B, 256B) ---
allocated p4 (128B), p5 (256B)
NULL pool
---allocator State---
Pool address:    0x4029000
Memory address:  0x402a000
Pool size:       1024 bytes
lower:  4 (2^4 = 16 bytes)
upper:  10 (2^10 = 1024 bytes)

--- free Lists ---
Free Lists (orders 4 to 10):
  Order 4 (size 16): empty
  Order 5 (size 32): empty
  Order 6 (size 64): empty
  Order 7 (size 128): empty
  Order 8 (size 256): empty
  Order 9 (size 512): 0x402a200 -> NULL
  Order 10 (size 1024): empty

--- bitmaps ---
(1 = allocated, 0 = free)
bbmprt:
00 00 00 00
00 02
01
01
01
00
00
===========================================


--- free & coalesce ---
Freeing p3 (32B)...
Freeing p1 (64B)...
Freeing p2 (32B) -> Should merge p2+p3 (64B), then merge with p1 (128B)
NULL pool
---allocator State---
Pool address:    0x4029000
Memory address:  0x402a000
Pool size:       1024 bytes
lower:  4 (2^4 = 16 bytes)
upper:  10 (2^10 = 1024 bytes)

--- free Lists ---
Free Lists (orders 4 to 10):
  Order 4 (size 16): empty
  Order 5 (size 32): empty
  Order 6 (size 64): empty
  Order 7 (size 128): 0x402a000 -> NULL
  Order 8 (size 256): empty
  Order 9 (size 512): 0x402a200 -> NULL
  Order 10 (size 1024): empty

--- bitmaps ---
(1 = allocated, 0 = free)
bbmprt:
00 00 00 00
00 00
00
00
01
00
00
===========================================


--- final cleanup ---
Freeing p4 (128B)...
Freeing p5 (256B)...

---final---
NULL pool
---allocator State---
Pool address:    0x4029000
Memory address:  0x402a000
Pool size:       1024 bytes
lower:  4 (2^4 = 16 bytes)
upper:  10 (2^10 = 1024 bytes)

--- free Lists ---
Free Lists (orders 4 to 10):
  Order 4 (size 16): empty
  Order 5 (size 32): empty
  Order 6 (size 64): empty
  Order 7 (size 128): empty
  Order 8 (size 256): empty
  Order 9 (size 512): empty
  Order 10 (size 1024): 0x402a000 -> NULL

--- bitmaps ---
(1 = allocated, 0 = free)
bbmprt:
00 00 00 00
00 00
00
00
00
00
00
===========================================

buddy allocator deleted.
==3312== 
==3312== HEAP SUMMARY:
==3312==     in use at exit: 0 bytes in 0 blocks
==3312==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==3312== 
==3312== All heap blocks were freed -- no leaks are possible
==3312== 
==3312== For lists of detected and suppressed errors, rerun with: -s
==3312== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

