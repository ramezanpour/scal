CC=gcc
CFLAGS = -I. -Wall -g

all:
	$(CC) convertor.c main.c $(CFLAGS) -o scal

clean:
	rm -rf scal *.dSYM

install:
	chmod +x scal
	cp scal /usr/local/bin/scal


