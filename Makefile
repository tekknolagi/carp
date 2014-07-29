CC = clang
CFLAGS = -c -std=c99 -Wall -O0 -g3 -static -Wno-unused-variable
SRCS = $(wildcard *.c lib/*.c)
OBJS = *.o
PROG = carp

all:
	$(CC) $(CFLAGS) $(SRCS)
	$(CC) $(OBJS) -o $(PROG)
	make clean_objs

clean_objs:
	find . -name "*.o"	\
	-o -name "*.out"	\
	 | xargs rm -f

clean:
	make clean_objs
	rm -f $(PROG)
