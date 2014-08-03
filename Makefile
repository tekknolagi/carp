CC = gcc #/usr/local/bin/gcc-4.2
NDEBUG ?= 
CFLAGS = -c -std=c99 -Wall -Werror -Wno-unused-variable -Wno-format-security -O3 -static $(NDEBUG) 
SRCS = src/carp_instructions.c src/carp_lexer.c src/carp_machine.c src/carp_tokenizer.c src/lib/carp_stack.c src/lib/carp_ht.c
#$(wildcard src/*.c src/lib/*.c)
OBJS = *.o
PROG = carp

all:
	$(CC) $(CFLAGS) $(SRCS)
	ar cr libcarp.a $(OBJS)
	$(CC) src/carp.c libcarp.a -o $(PROG)
	make clean_objs

.PHONY: tests

tests:
	gcc tests/stack.c libcarp.a ../libtap/tap.c -o tests/stack

uninstall:
	rm -rf /usr/local/include/carp
	rm -f /usr/local/lib/libcarp.a
	rm -f /usr/local/bin/$(PROG)

install:
	make uninstall
	mkdir -p /usr/local/include/carp/lib
	cp src/*.h /usr/local/include/carp
	cp src/lib/*.h /usr/local/include/carp/lib
	cp libcarp.a /usr/local/lib
	mv $(PROG) /usr/local/bin

clean_libs:
	find . -name "*.a"	\
	| xargs rm -f

clean_objs:
	find . -name "*.o"	\
	-o -name "*.out"	\
	 | xargs rm -f

clean:
	make clean_objs
	rm -f $(PROG)
