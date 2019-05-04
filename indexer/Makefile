# Makefile for indexer
# Builds and compiles indexer
#
# Carlos Yepes, April 2019

# program and object files
PROG = indexer
OBJS = indexer.o ../common/common.a ../libcs50/libcs50.a
LIBS = 

# uncomment for valgrind testing
VAL = valgrind --leak-check=full -v

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(LINKS)
LINKS = -I../libcs50 -I../common
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# dependencies
indexer.o: indexer.c common.a libcs50.a
libcs50.a:
	$(MAKE) -C ../libcs50
common.a:
	$(MAKE) common.a -C ../common

.PHONY: clean test

testL:
	$(VAL) ./$(PROG) ../tsetest/letters3 nut

clean:
	rm -f *~ *.o
	rm -f $(PROG)
	$(MAKE) clean -C ../libcs50
	$(MAKE) clean -C ../common

