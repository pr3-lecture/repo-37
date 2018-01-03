.PHONY: all clean
all: encrypt decrypt test

clean:
	rm -f encrypt decrypt test main.o crypto.o test.o

main.o: main.c
	gcc -Wall -c main.c

crypto.o: crypto.c
	gcc -Wall -c crypto.c

test.o: test.c
	gcc -Wall -c test.c

encrypt: main.o crypto.o
	gcc -o encrypt main.o crypto.o

decrypt: main.o crypto.o
	gcc -o decrypt main.o crypto.o

test: test.o crypto.o
	gcc -o test test.o crypto.o
	./test