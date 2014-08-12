CC ?= gcc #/usr/local/bin/gcc-4.2
PREFIX = /usr/local
NDEBUG ?= 
CFLAGS = -c -g3 -std=c99 -Wall -Werror -Wno-unused-variable -Wno-format-security -static $(NDEBUG)
SRCS = src/carp_instructions.c src/carp_lexer.c src/carp_machine.c src/carp_tokenizer.c src/lib/carp_stack.c src/lib/carp_ht.c
#$(wildcard src/*.c src/lib/*.c)
OBJS = *.o
PROG = carp.out
TESTS=$(wildcard tests/*.c)
TESTS_OUTS=$(TESTS:.c=.out)

all: build clean_objs

build:
	$(CC) $(CFLAGS) $(SRCS)
	ar cr libcarp.a $(OBJS)
	$(CC) -g -std=c99 src/carp.c libcarp.a -o $(PROG)

libtap:
	cd tests/libtap && make

clean_libtap:
	cd tests/libtap && make clean

test: libtap $(TESTS_OUTS) runtests

tests/%.out: tests/%.c
	$(CC) $< libcarp.a tests/libtap/libtap.a -o $@

runtests:
	for file in tests/*.out; do	\
		echo $$file;		\
		./$$file; 		\
		echo; 			\
	done

cleantests:
	rm tests/*.out

#tests:
#	gcc tests/stack.c libcarp.a ../libtap/tap.c -o tests/stack

uninstall:
	rm $(DESTDIR)$(PREFIX)/include/carp
	rm $(DESTDIR)$(PREFIX)/lib/libcarp.a
	rm $(DESTDIR)$(PREFIX)/bin/$(PROG)

install:
	test -d ${DESTDIR}${PREFIX}/bin || mkdir -p ${DESTDIR}${PREFIX}/bin
	test -d ${DESTDIR}${PREFIX}/lib || mkdir -p ${DESTDIR}${PREFIX}/lib
	test -d ${DESTDIR}${PREFIX}/include/carp || mkdir -p ${DESTDIR}${PREFIX}/carp
	test -d ${DESTDIR}${PREFIX}/include/carp/lib || mkdir -p $(DESTDIR)$(PREFIX)/include/carp/lib
	cp src/*.h $(DESTDIR)$(PREFIX)/include/carp
	cp src/lib/*.h $(DESTDIR)$(PREFIX)/include/carp/lib
	cp libcarp.a $(DESTDIR)$(PREFIX)/lib
	install -pm 755 $(PROG) $(DESTDIR)$(PREFIX)/bin/carp

clean_libs:
	find . -name "*.a"	\
	| xargs rm -f

clean_objs:
	find . -name "*.o"	\
	 | xargs rm -f

clean: clean_objs clean_libtap
	rm -f $(PROG)
