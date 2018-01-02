.PHONY: all clean
all: encrypt decrypt runtest

clean:
	rm -f encrypt decrypt test crypto.o test.o

crypto.o: crypto.c
	cc -Wall -c crypto.c

test.o: test.c
	cc -Wall -c test.c

encrypt: crypto.o
	cc -o encrypt crypto.o

decrypt: crypto.o
	cc -o decrypt crypto.o

runtest: test.o crypto.o
	cc -o test test.o crypto.o
	./test
