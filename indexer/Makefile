# Makefile for indexer
# Builds and compiles indexer
#
# Carlos Yepes, April 2019

# indexer program and object files
PROG = indexer 
OBJS = indexer.o ../common/common.a ../libcs50/libcs50.a
LIBS = 

# indextest program and object files
PROGTEST = indextest
OBJSTEST = indextest.o ../common/common.a ../libcs50/libcs50.a

# uncomment for valgrind testing
VAL = #valgrind

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(LINKS)
LINKS = -I../libcs50 -I../common
MAKE = make

all: indexer indextest

# rule for indexer
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# rule for indextest
$(PROGTEST): $(OBJSTEST)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


# dependencies
indexer.o: indexer.c common.a libcs50.a
indextest.o: indextest.c common.a libcs50.a
libcs50.a:
	$(MAKE) -C ../libcs50
common.a:
	$(MAKE) common.a -C ../common

.PHONY: clean cleanall crawl test testL testT testW testS insufficient insufftest invalid nwrite nwritetest nread

################TESTS#############

# master test, runs the script
test:
	bash -v testing.sh

# tests the letters
testL:
	$(VAL) ./$(PROG) ../tsetest/letters3 letters.Index

# tests the wiki
testW:
	$(VAL) ./$(PROG) ../tsetest/wiki1 wiki.Index

# tests the scrape
testS:
	$(VAL) ./$(PROG) ../tsetest/scrape1 scrape.Index

# tests test (indextest)
testT:
	$(VAL) ./$(PROGTEST) scrape.Index new_scrape.Index

# insufficient arguments
insufficient:
	./$(PROG) ../tsetest/index1

#insufficient aruments on indextest
insufftest:
	./$(PROGTEST) scrape.Index

# invalid directory
invalid:
	./$(PROG) ../tsefake/letters3 fake_letters.Index

# tests non existent read file for indextest
nread:
	./$(PROGTEST) non_existent nread.Index

# removes the writeability of a file then feeds it to indexer, should fail
# testing script will remove the file to not clutter AFTER it fails
nwrite:
	touch nwrite.Index
	chmod a-rwx nwrite.Index
	ls -l nwrite.Index
	./$(PROG) ../tsetest/index1 nwrite.Index

# same as nwrite, but on the indextest
nwritetest:
	./$(PROGTEST) scrape.Index nwrite.Index

################### END OF TESTS #######################

# creates crawler files, not tooo much depth, so should be quick
# didn't use due since it Prof said I should change my testing.sh, but I'll keep it since I may use it some other time
crawl:
	$(MAKE) test -C ../crawler

# doesnt delete newly created .Index files since I thought you may want to remove the
# .o files so you can find the created .Index files without the clutter of the .o files
clean:
	rm -f *~ *.o
	rm -f $(PROG)
	rm -f $(PROGTEST)
	$(MAKE) clean -C ../libcs50
	$(MAKE) clean -C ../common
#$(MAKE) clean -C ../crawler

# delete everything created except testing.out
cleanall:
	$(MAKE) clean
	rm -f *~ *.Index
#$(MAKE) cleanall -C ../crawler
	

