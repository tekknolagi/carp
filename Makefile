PREFIX ?= /usr/local

BIN = carp
LIB = libcarp.a

CFLAGS  += -std=c99 -pedantic -Wall -W -Werror -Wextra \
	   -Wwrite-strings -Wpointer-arith -Wbad-function-cast
LDFLAGS += -lm

MAIN_SRCS = src/main.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

# We use carp_* to avoid including carp.c (main)
LIB_SRCS = $(shell echo src/*.c src/lib/*.c)
LIB_HDRS = $(shell echo src/*.h src/lib/*.h)
LIB_OBJS = $(LIB_SRCS:.c=.o)

TEST_SRCS = $(shell echo tests/*.c tests/instr/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_BINS = $(TEST_SRCS:.c=.out)
TEST_LIBS = $(LIB) tests/libtap/libtap.a

ifeq ($(RELEASE),yes)
	CFLAGS += -O2
	CFLAGS += -DNDEBUG
else
	CFLAGS  += -g3
	LDFLAGS += -g
endif

ifeq ($(CDEBUG),yes)
	CFLAGS += -DCDEBUG
endif

.PHONY: all clean libtap libtap_clean test install uninstall
all: $(BIN)

$(BIN): $(MAIN_OBJS) $(LIB)
	$(CC) $(LDFLAGS) $^ -o $@

$(LIB): $(LIB_OBJS)
	ar crs $@ $^

src/lib/%.o: src/lib/%.c $(LIB_HDRS)
src/%.o: src/%.c $(LIB_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean: libtap_clean
	rm -rf $(MAIN_OBJS) $(BIN) $(LIB_OBJS) $(LIB) $(TEST_BINS) $(TEST_OBJS)

libtap:
	cd tests/libtap && make

libtap_clean:
	cd tests/libtap && make clean

tests/instr/%.o: tests/instr/%.c
tests/%.o: tests/%.c $(LIB_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

tests/instr/%.out: tests/instr/%.o
tests/%.out: tests/%.o $(LIB) libtap
	$(CC) $(LDFLAGS) $< $(TEST_LIBS) -o $@

# To avoid rm tests.o, not really necessary but consistent
$(TEST_BINS): $(TEST_OBJS)

test: $(LIB) libtap $(TEST_BINS)
	@for file in $(TEST_BINS); do \
		echo;                 \
		echo $$file;          \
		./$$file;             \
	done

install:
	test -d ${DESTDIR}${PREFIX}/bin || mkdir -p ${DESTDIR}${PREFIX}/bin
	test -d ${DESTDIR}${PREFIX}/lib || mkdir -p ${DESTDIR}${PREFIX}/lib
	test -d ${DESTDIR}${PREFIX}/include/carp || \
		mkdir -p ${DESTDIR}${PREFIX}/carp
	test -d ${DESTDIR}${PREFIX}/include/carp/lib || \
		mkdir -p $(DESTDIR)$(PREFIX)/include/carp/lib
	cp src/*.h $(DESTDIR)$(PREFIX)/include/carp
	cp src/lib/*.h $(DESTDIR)$(PREFIX)/include/carp/lib
	cp $(LIB) $(DESTDIR)$(PREFIX)/lib
	install -pm 755 $(BIN) $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm -r $(DESTDIR)$(PREFIX)/include/carp
	rm $(DESTDIR)$(PREFIX)/lib/$(LIB)
	rm $(DESTDIR)$(PREFIX)/bin/$(BIN)
