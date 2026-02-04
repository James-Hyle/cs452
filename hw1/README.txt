// AUTHOR: JAMES HYLE
// PROFESSOR: BUFFENBARGER
// CLASS: CS452 OPERATING SYSTEMS
// SEMESTER: SPRING 2026

USAGE:
To use this program, cd into the subfolder "hw1" and invoke the make command at the terminal. The program will compile and then invoke "./deq" on the terminal. To check the program with valgrind invoke "valgrind --leak-check=full ./deq". Valgrind output is shown in the corresponding section. To clean dir, invoke "make clean" on command line. 

vscode ➜ /workspaces/cs452/hw1 (main) $ make
gcc -o deq.o -c deq.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o main.o -c main.c -g -Wall -MMD -D_GNU_SOURCE
gcc -o deq deq.o main.o -g
vscode ➜ /workspaces/cs452/hw1 (main) $ ./deq
Test: putting 5, 10, 20 into list
  PASS: list length is 3!
Test: checking index 0 from head of list
  PASS: got 5!
Test: removing 10 from Head search
  PASS: removed 10, length now 2
Test: getting from tail
  PASS: got 20!
PASS: Deque is empty and returns NULL safely


VALGRIND OUTPUT:

vscode ➜ /workspaces/cs452/hw1 (main) $ valgrind --leak-check=full ./deq
==9057== Memcheck, a memory error detector
==9057== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==9057== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==9057== Command: ./deq
==9057== 
Test: putting 5, 10, 20 into list
  PASS: Length is 3!
Test: Checking index 0 from Head
  PASS: got 5!
Test: removing 10 from Head search
  PASS: removed 10, length now 2
Test: getting from tail
  PASS: got 20!
PASS: Deque is empty and returns NULL safely
==9057== 
==9057== HEAP SUMMARY:
==9057==     in use at exit: 0 bytes in 0 blocks
==9057==   total heap usage: 5 allocs, 5 frees, 1,120 bytes allocated
==9057== 
==9057== All heap blocks were freed -- no leaks are possible
==9057== 
==9057== For lists of detected and suppressed errors, rerun with: -s
==9057== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
