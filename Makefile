
radix-serv:
	gcc -o radix-serv src/main.c -I.

build-tests:
	gcc -g -o tests tests.c -I.

test:
	gcc -g -o tests tests.c -I. && sudo gdb -quiet ./tests

.PHONY: all test radix-serv
