// AUTHOR: JAMES HYLE
// PROFESSOR: BUFFENBARGER
// CLASS: CS452 OPERATING SYSTEMS
// SEMESTER: SPRING 2026

USAGE:
To use this program, cd into the folder "hw5" and invoke the "make" command at the terminal. Then invoke "make install" to install driver. Invoke "make try" to run the driver. To unistall invoke "make uninstall". To run tests in user space invoke "make tests". To clean dir's, invoke "make clean" on command line. To clean modules invoke make modules clean.


VALGRIND OUTPUT: 
==14589== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==14589== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
==14589== Command: ./TryHello
==14589== 
read() = 5 expected 5
read() = 0 expected 0
read() = -1 expected -1
==14589== 
==14589== HEAP SUMMARY:
==14589==     in use at exit: 0 bytes in 0 blocks
==14589==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==14589== 
==14589== All heap blocks were freed -- no leaks are possible
==14589== 
==14589== For lists of detected and suppressed errors, rerun with: -s
==14589== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


OUTPUT:
jameshyle@UbuntuVM:~/Documents/cs452/hw5$ make
Makefile:14: warning: overriding recipe for target 'clean'
Makefile:12: warning: ignoring old recipe for target 'clean'
make -C /lib/modules/6.17.0-22-generic/build M=/home/jameshyle/Documents/cs452/hw5 modules
make[1]: Entering directory '/usr/src/linux-headers-6.17.0-22-generic'
make[2]: Entering directory '/home/jameshyle/Documents/cs452/hw5'
warning: the compiler differs from the one used to build the kernel
  The kernel was built by: aarch64-linux-gnu-gcc (Ubuntu 15.2.0-4ubuntu4) 15.2.0
  You are using:           gcc (Ubuntu 15.2.0-4ubuntu4) 15.2.0
Makefile:14: warning: overriding recipe for target 'clean'
Makefile:12: warning: ignoring old recipe for target 'clean'
  CC [M]  Hello.o
Hello.c: In function ‘my_init’:
Hello.c:167:15: warning: unused variable ‘s’ [-Wunused-variable]
  167 |   const char *s = "Hello world!\n";
      |               ^
Makefile:14: warning: overriding recipe for target 'clean'
Makefile:12: warning: ignoring old recipe for target 'clean'
  MODPOST Module.symvers
  CC [M]  Hello.mod.o
  CC [M]  .module-common.o
  LD [M]  Hello.ko
  BTF [M] Hello.ko
Skipping BTF generation for Hello.ko due to unavailability of vmlinux
make[2]: Leaving directory '/home/jameshyle/Documents/cs452/hw5'
make[1]: Leaving directory '/usr/src/linux-headers-6.17.0-22-generic'
jameshyle@UbuntuVM:~/Documents/cs452/hw5$ make install
Makefile:14: warning: overriding recipe for target 'clean'
Makefile:12: warning: ignoring old recipe for target 'clean'
sudo rmmod Hello.ko || true
[sudo: authenticate] Password: 
rmmod: ERROR: Module Hello is not currently loaded
sudo insmod Hello.ko
sudo rm -f /dev/Hello || true
sudo mknod -m a+rw /dev/Hello c $(./getmaj Hello) 0
jameshyle@UbuntuVM:~/Documents/cs452/hw5$ make try
Makefile:14: warning: overriding recipe for target 'clean'
Makefile:12: warning: ignoring old recipe for target 'clean'
gcc -o TryHello TryHello.c -Wall -g
./TryHello
read() = 5 expected 5
read() = 0 expected 0
read() = -1 expected -1
jameshyle@UbuntuVM:~/Documents/cs452/hw5$ 
