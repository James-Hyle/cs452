PATH=/usr/bin:/bin:/sbin

name:=Hello
module:=$(name).ko

obj-m:=$(name).o
KDIR :=/lib/modules/$(shell uname -r)/build
PWD  :=$(shell pwd)

KBUILD_CFLAGS+=-DDEVNAME='"$(name)"'

modules clean: ; $(MAKE) -C $(KDIR) M=$(PWD) $@

clean: ; rm -f $(prog) *.o *.d *.i test/single_char test/read_empty test/single_token test/multiple_token test/default_seps test/consecutive_seps test/large_token test/leading_trailing test/custom_sep test/null_sep

install: $(module)
	sudo rmmod $(module) || true
	sudo insmod $(module)
	sudo rm -f /dev/$(name) || true
	sudo mknod -m a+rw /dev/$(name) c $$(./getmaj $(name)) 0

uninstall:
	sudo rmmod $(module) || true
	sudo rm -f /dev/$(name) || true

tests:
	gcc -o test/single_char test/single_char.c -I test -Wall -g
	gcc -o test/read_empty test/read_empty.c -I test -Wall -g
	gcc -o test/single_token test/single_token.c -I test -Wall -g
	gcc -o test/multiple_token test/multiple_token.c -I test -Wall -g
	gcc -o test/default_seps test/default_seps.c -I test -Wall -g
	gcc -o test/consecutive_seps test/consecutive_seps.c -I test -Wall -g
	gcc -o test/large_token test/large_token.c -I test -Wall -g	
	gcc -o test/leading_trailing test/leading_trailing.c -I test -Wall -g
	gcc -o test/custom_sep test/custom_sep.c -I test -Wall -g
	gcc -o test/null_sep test/null_sep.c -I test -Wall -g
	
	@echo Test String: a
	@test/single_char

	@echo Test String: 
	@test/read_empty

	@echo Test String: hello
	@test/single_token

	@echo Test String: foo bar baz
	@test/multiple_token

	@echo Test String: 3 spaces
	@test/default_seps

	@echo Test String: "foo   bar"
	@test/consecutive_seps

	@echo Test String: hello Buffer Size = 3!
	@test/large_token

	@echo Test String: "  hello  "
	@test/leading_trailing

	@echo Test String: a,b,c with comma separator
	@test/custom_sep

	@echo Test String: ab NULL cd with NULL char separator
	@test/null_sep


TryHello: TryHello.c
	gcc -o $@ $< -Wall -g

Hello: Hello.c
	gcc -o $@ $< -Wall -g

try: TryHello
	./$<
