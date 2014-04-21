CFLAGS= -Wall -Werror --pedantic
LDLIBS= -lncurses -pthread
BINS= projeto ncurses

all: $(BINS)

projeto: projeto.o display.o

.PHONY: clean

clean:
	$(RM) *.o $(BINS)
