CC = gcc
CFLAGS = -Wall -w -std=c99 -Iinclude -c -o

test:
		$(CC) $(CFLAGS) bin/test.o src/test.c
		$(CC) $(CFLAGS) bin/binaryTree.o src/binaryTree.c
		$(CC) bin/binaryTree.o bin/test.o -o bin/runMe

main:
		$(CC) $(CFLAGS) bin/discuss.o src/discuss.c
		$(CC) $(CFLAGS) bin/binaryTree.o src/binaryTree.c
		$(CC) bin/binaryTree.o bin/discuss.o -o bin/runMe


clean:
		rm bin/*.o