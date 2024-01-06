CC=gcc
CFLAGS=-Wall

all: main.o interpreter.o machine.o program.o
	$(CC) $(CFLAGS) -o brainfuck main.o interpreter.o machine.o program.o

interpreter.o: interpreter.c
	$(CC) $(CFLAGS) -c interpreter.c

machine.o: machine.c 
	$(CC) $(CFLAGS) -c machine.c

program.o: program.c 
	$(CC) $(CFLAGS) -c program.c

main.o: main.c 
	$(CC) $(CLFAGS) -c main.c

test: all
	./brainfuck ../brainfuck-programs/helloworld.b

clean:
	rm *.o brainfuck