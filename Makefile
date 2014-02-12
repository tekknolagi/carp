CC = gcc
LIBS = -Wall
PROG = myvm
CFLAGS = -c
LDFLAGS = 
INSTALL_DIR = /usr/bin
SRCS = myvm.c
OBJS = $(SRCS:.c=.o)

all: $(SRCS) $(PROG)

$(PROG):	$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@.out

.c.o:
	$(CC) $(CFLAGS) $< -o $@

#install:
#	rm -f $(INSTALL_DIR)/$(PROG)	; \
#	cp $(PROG) $(INSTALL_DIR)	;

clean:
	rm -f *.o	; \
	rm -f *.out	; \
	rm -f $(PROG)
