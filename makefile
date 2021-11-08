CC=gcc
CFLAGS=-Wall
LDLIBS=-lm
DEPS=list.h testListHelpers.h
OBJ=main.o list.o testListHelpers.o
EXEC=main

clean :
	rm -f *.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compile: $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(LDLIBS)

run : clean compile
	./$(EXEC)
