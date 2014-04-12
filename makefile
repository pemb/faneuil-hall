CFLAGS= -lncurses -lpthread
BINS= projeto

all: $(BINS)

projeto: display.o

.PHONY: clean

clean:
	rm -f *.o $(BINS)
