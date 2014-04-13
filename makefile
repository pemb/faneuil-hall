CFLAGS= -lncurses -pthread -Wall -Werror --pedantic
BINS= projeto ncurses

all: $(BINS)

projeto: display.o

.PHONY: clean

clean:
	rm -f *.o $(BINS)
