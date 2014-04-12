CFLAGS= -lncurses
BINS= projeto

all: $(BINS)

.PHONY = clean

clean:
	rm -f *.o $(BINS)
