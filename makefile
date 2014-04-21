CFLAGS= -Wall --pedantic -g -Og
LDLIBS= -lncurses -pthread
BINS= projeto

all: $(BINS)

projeto: projeto.o display.o

display.o: sprites.h

.PHONY: clean

clean:
	$(RM) *.o $(BINS)
