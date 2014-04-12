CFLAGS= -lncurses -lpthread
BINS= projeto

all: $(BINS)

.PHONY = clean

clean:
	rm -f *.o $(BINS)
