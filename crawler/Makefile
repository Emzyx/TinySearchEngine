# Makefile for crawler.c
# Builds and compiles the crawler
#
# Carlos Yepes, April 2019

PROG = crawler
OBJS = crawler.o ../common/pagedir.o ../libcs50/libcs50.a 
LIBS =

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50 -I../common
MAKE = make


$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: crawler.c ../common/pagedir.h ../libcs50/libcs50.a
pagedir.o: ../common/pagedir.h

.PHONY: test clean

test:
	./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/index.html pageDirectory 0

valgrind:
	valgrind --leak-check=full ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/index.html pageDirectory 0

clean:
	rm -f *~ *.o
	rm -f $(PROG)
