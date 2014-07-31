CC = /usr/local/bin/gcc-4.2
#clang
CFLAGS = -c -std=c99 -Wall -O0 -g3 -static -Wno-unused-variable
SRCS = $(wildcard *.c lib/*.c)
OBJS = *.o
PROG = carp

# all:
# 	$(CC) $(CFLAGS) $(SRCS)
# 	$(CC) $(OBJS) -o $(PROG)
# 	make clean_objs

all:
	make objs

objs:
	$(CC) $(CFLAGS) $(SRCS)
	ar cr libcarp.a $(OBJS)
	make clean_objs

uninstall:
	rm -rf /usr/local/include/carp

install:
	make uninstall
	mkdir /usr/local/include/carp
	cp -r . /usr/local/include/carp

clean_objs:
	find . -name "*.o"	\
	-o -name "*.out"	\
	-o -name "*.a"		\
	 | xargs rm -f

clean:
	make clean_objs
	rm -f $(PROG)
