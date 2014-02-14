CC = gcc
LIBS = -Wall -std=c99
PROG = myvm
CFLAGS = -c
LDFLAGS = 
INSTALL_DIR = /usr/local/bin
SRCS = myvm.c
OBJS = $(SRCS:.c=.o)

all: $(SRCS) $(PROG)

$(PROG):	$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@.out

.c.o:
	$(CC) $(CFLAGS) $< -o $@

install:
	rm -f $(INSTALL_DIR)/$(PROG)		; \
	cp $(PROG:=.out) $(INSTALL_DIR)/$(PROG)	; \
	rm -rf /usr/local/include/myvm		; \
	mkdir /usr/local/include/myvm		; \
	cp -r . /usr/local/include/myvm

uninstall:
	rm -f $(INSTALL_DIR)/$(PROG)

clean:
	rm -f *.o	; \
	rm -f *.out	; \
	rm -f $(PROG)
