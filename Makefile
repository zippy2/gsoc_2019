CFLAGS=-O0 -ggdb -std=c99 -pedantic -Wall -Werror -D_XOPEN_SOURCE=500 -D_GNU_SOURCE
BIN=exercise
OBJS=exercise.o filemap.o

exercise: $(OBJS)

clean:
	rm -f $(OBJS) $(BIN)
