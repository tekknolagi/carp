CC = gcc
LIBS = -Wall
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
	cp $(PROG:=.out) $(INSTALL_DIR)/$(PROG)	;

uninstall:
	rm -f $(INSTALL_DIR)/$(PROG)

clean:
	rm -f *.o	; \
	rm -f *.out	; \
	rm -f $(PROG)
