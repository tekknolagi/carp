CC ?= clang
LIBS ?= 
CFLAGS ?= -c -std=c99 -Wall
LDFLAGS ?= 
INSTALL_DIR = /usr/local/bin
SRCS = carp.c
OBJS = $(SRCS:.c=.o)
BINDIR = bin/
PROG ?= $(addprefix $(BINDIR),carp.out)
EXAMPLE_SRCS = $(wildcard examples/*.c)
EXAMPLE_PROG = $(EXAMPLE_SRCS:.c=.out)

all: $(SRCS) $(PROG)

%.out: %.c
	$(CC) $^ -o $@

examples: $(EXAMPLE_PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

install:
	rm -rf /usr/local/include/carp*.h
	rm -rf /usr/local/include/carp*.c
	rm -rf /usr/local/include/carp
	mkdir /usr/local/include/carp
	cp -r . /usr/local/include/carp

js:
	emcc $(SRCS)

uninstall:
	rm -rf /usr/local/include/carp*.h
	rm -rf /usr/local/include/carp*.c
	rm -rf /usr/local/include/carp

clean:
	find . -name "*.o"	\
	-o -name "*.out"	\
	-o -name "*.js*"	\
	-o -name "*.html*"	\
	-o -name "*.bc"		\
	-o -name "*~"		\
	 | xargs rm -f
	rm -f $(PROG)
