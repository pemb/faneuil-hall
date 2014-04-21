CFLAGS= -Wall -Werror --pedantic
LDLIBS= -lncurses -pthread
BINS= projeto ncurses

all: $(BINS)

projeto: display.o

.PHONY: clean

clean:
	rm -f *.o $(BINS)
