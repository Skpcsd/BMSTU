CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: build

build: main.o list.o
	$(CC) $(CFLAGS) main.o list.o -o app.exe

main.o: main.c list.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

run: build
	./app.exe

clean:
	rm -f *.o app.exe

