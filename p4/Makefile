CC = gcc
CFLAGS = -g -O0 -Wall
LDFLAGS = -lm

default: all

all: build run

build: tfidf.c testes.c
	$(CC) tfidf.c testes.c $(CFLAGS) $(LDFLAGS) -o executavel

run: executavel
	./executavel

test: tfidf.c
	$(CC) tfidf.c $(CFLAGS) $(LDFLAGS) -o executavel

clean:
	rm -rf ._* executavel executavel.dSYM
