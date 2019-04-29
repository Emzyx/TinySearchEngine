# Makefile for crawler.c
# Builds and compiles the crawler
#
# Carlos Yepes, April 2019

# program and object files
PROG = crawler
OBJS = crawler.o ../common/common.a ../libcs50/libcs50.a 
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
../common/common.a: ../common/pagedir.o
	ar cr $@ $^

.PHONY: direct test test1 test2 test3 clean

# checks if directory exists, if it did recursively clear their contents by deleting them and making them
direct:
	if [ -d "../tsetest" ]; then $(MAKE) dtest -C ../common; fi; $(MAKE) ctest -C ../common

# the real big test, can run without having called anything beforehand
test:
	bash -v testing.sh

test1:
	$(VAL) ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/index.html ../tsetest/index1 1

test2:
	$(VAL) ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html ../tsetest/letters3 3
    
test3:
	$(VAL) ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html ../tsetest/wiki1 1

test4:
	$(VAL) ./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/data/tse/toscrape/index.html ../tsetest/scrape1 1

clean:
	rm -f *~ *.o
	rm -f $(PROG)
	$(MAKE) clean -C ../libcs50
	$(MAKE) clean -C ../common
	$(MAKE) dtest -C ../common
