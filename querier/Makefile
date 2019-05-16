# Makefile for querier
#
# Carlos Yepes, May 2019

PROG = querier
OBJS = querier.o ../common/common.a ../libcs50/libcs50.a
LIBS = 

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(LINKS)
LINKS = -I../libcs50 -I../common
MAKE = make

VAL = #valgrind

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

querier.o: querier.c common.a libcs50.a
common.a:
	$(MAKE) common.a -C ../common
libcs50.a:
	$(MAKE) -C ../libcs50


.PHONY: test clean cleanall crawl index indexed

test:
	bash -v testing.sh

############################# FOR MY TESTING ########################################
crawl:
	$(MAKE) crawl -C ../indexer

index:
	$(MAKE) indexer -C ../indexer

indexed:
	$(MAKE) testL -C ../indexer
	$(MAKE) testW -C ../indexer
	$(MAKE) testS -C ../indexer
	mkdir test
	cp ../indexer/letters.Index test/letters.Index
	cp ../indexer/wiki.Index test/wiki.Index
	cp ../indexer/scrape.Index test/scrape.Index
######################################################################

clean:
	rm -f $(PROG)
	rm -f fuzzquery
	rm -f *~ *.o
	$(MAKE) clean -C ../libcs50
	$(MAKE) clean -C ../common

cleanall:
	$(MAKE) clean
	$(MAKE) cleanall -C ../indexer
	$(MAKE) clean -C ../crawler