// AUTHOR: JAMES HYLE
// PROFESSOR: BUFFENBARGER
// CLASS: CS452 OPERATING SYSTEMS
// SEMESTER: SPRING 2026

USAGE:
To use this program, cd into the folder "hw4" and invoke the "make" 
command at the terminal. The program will compile and then invoke ./wam 
<capacity> on the terminal to run the application. To verify the 
program with valgrind invoke "./vg". To clean dir, invoke "make clean" 
on command line.


VALGRIND OUTPUT: 
vscode ➜ /workspaces/ubuntu/cs452/hw4 (main) $ ./vg
+ valgrind --leak-check=full --show-leak-kinds=all --suppressions=fltk.supp ./wam
==34065== Memcheck, a memory error detector
==34065== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==34065== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==34065== Command: ./wam
==34065== 
main.c:32: error: usage: ./wam <nThreads>

==34065== 
==34065== HEAP SUMMARY:
==34065==     in use at exit: 1,760 bytes in 2 blocks
==34065==   total heap usage: 13 allocs, 11 frees, 76,271 bytes allocated
==34065== 
==34065== LEAK SUMMARY:
==34065==    definitely lost: 0 bytes in 0 blocks
==34065==    indirectly lost: 0 bytes in 0 blocks
==34065==      possibly lost: 0 bytes in 0 blocks
==34065==    still reachable: 0 bytes in 0 blocks
==34065==         suppressed: 1,760 bytes in 2 blocks
==34065== 
==34065== For lists of detected and suppressed errors, rerun with: -s
==34065== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
