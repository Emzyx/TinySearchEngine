# Makefile for crawler.c
# Builds and compiles the crawler
#
# Carlos Yepes, April 2019

# program and object files
PROG = crawler
OBJS = crawler.o ../common/pagedir.o ../libcs50/libcs50.a 
LIBS =

#Uncomment to valgrind each of the tests.
VAL = #valgrind --leak-check=full -v

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50 -I../common
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Dependencies
crawler.o: crawler.c ../common/pagedir.h ../libcs50/libcs50.a
pagedir.o: ../common/pagedir.h ../libcs50/libcs50.a
../libcs50/libcs50.a: ../libcs50/libcs50-given.a
	cp ../libcs50/libcs50-given.a ../libcs50/libcs50.a

.PHONY: test clean direct

# some tests and cleanage
direct:
	$(MAKE) ctest -C ../common

# the real big test, can run without having called anything beforehand
test:
	bash -v testing.sh

test1:
	$(VAL) ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/index.html ../tsetest/index1 1

test2:
	$(VAL) ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ../tsetest/letters3 3
    
test3:
	$(VAL) ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html ../tsetest/wiki2 2

clean:
	rm -f *~ *.o
	rm -f $(PROG)
	$(MAKE) clean -C ../libcs50
	$(MAKE) clean -C ../common
	$(MAKE) dtest -C ../common
