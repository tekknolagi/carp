CC ?= gcc #/usr/local/bin/gcc-4.2
PREFIX = /usr/local
NDEBUG ?= 
CFLAGS = -g3 -std=c99 -Wall -Werror -Wno-unused-variable -Wno-format-security $(NDEBUG)
SRCS = src/carp_registers.c src/carp_instructions.c src/carp_lexer.c \
	src/carp_machine.c src/carp_tokenizer.c src/lib/carp_stack.c \
	src/lib/carp_ht.c
#$(wildcard src/*.c src/lib/*.c)
OBJS = *.o
PROG = carp
TESTS = $(wildcard tests/*.c tests/instr/*.c)
TESTS_OUTS = $(TESTS:.c=.out)

all: build clean_objs test

build:
	$(CC) -c $(CFLAGS) $(SRCS)
	ar cr libcarp.a $(OBJS)
	$(CC) $(CFLAGS) src/carp.c libcarp.a -o $(PROG)

libtap:
	cd tests/libtap && make

clean_libtap:
	cd tests/libtap && make clean

test: build libtap clean_tests $(TESTS_OUTS) run_tests

tests/%.out: tests/%.c
	$(CC) $(CFLAGS) $< libcarp.a tests/libtap/libtap.a -o $@

tests/instr/%.out: tests/instr/%.c
	$(CC) $(CFLAGS) $< libcarp.a tests/libtap/libtap.a -o $@

run_tests:
	for file in $(TESTS_OUTS); do	\
		echo $$file;	\
		./$$file; 	\
		echo; 		\
	done

clean_tests:
	rm -f $(TESTS_OUTS)

uninstall:
	rm -r $(DESTDIR)$(PREFIX)/include/carp
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
	install -pm 755 $(PROG) $(DESTDIR)$(PREFIX)/bin

clean_libs:
	find . -name "*.a"	\
	| xargs rm -f

clean_objs:
	find . -name "*.o"	\
	-o -name "*.dSYM"	\
	 | xargs rm -rf

clean_outs:
	find . -name "*.out"	\
	| xargs rm -f

clean: clean_objs clean_libtap
	rm -f $(PROG) libcarp.a
