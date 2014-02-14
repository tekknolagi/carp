CC = gcc
LIBS = -Wall -std=c99
PROG = carp
CFLAGS = -c
LDFLAGS = 
INSTALL_DIR = /usr/local/bin
SRCS = carp.c
OBJS = $(SRCS:.c=.o)

all: $(SRCS) $(PROG)

$(PROG):	$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@.out

.c.o:
	$(CC) $(CFLAGS) $< -o $@

#	rm -f $(INSTALL_DIR)/$(PROG)		; \
	cp $(PROG:=.out) $(INSTALL_DIR)/$(PROG)	; \

install:
	rm -rf /usr/local/include/carp		; \
	mkdir /usr/local/include/carp		; \
	cp -r . /usr/local/include/carp

uninstall:
	rm -f $(INSTALL_DIR)/$(PROG)		; \
	rm -r /usr/local/include/carp

clean:
	rm -f *.o	; \
	rm -f *.out	; \
	rm -f $(PROG)
