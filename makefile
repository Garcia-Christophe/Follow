CC=gcc
CFLAGS=-Wall
LDLIBS=-lm
DEPS=list.h testListHelpers.h strhash.h
OBJ=main.o list.o testListHelpers.o strhash.o
OBJ_TESTS=tests.o list.o testListHelpers.o strhash.o
EXEC=main
EXEC_TEST=test

clean :
	rm -f *.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compile : $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(LDLIBS)

compileTest : $(OBJ_TESTS)
	$(CC) -o $(EXEC_TEST) $^ $(CFLAGS) $(LDLIBS)

run : clean compile
	./$(EXEC)

tests : clean compile compileTest
	./$(EXEC_TEST)
