# Makefile for pagedir
# Initializes directories in which the tests will be stored
#
# Carlos Yepes, April 2019

PROG = pagedir
MAKE = make

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(LINKS)
LINKS = -I../libcs50

pagedir.o: pagedir.h libcs50.a
word.o: word.h
index.o: index.h
libcs50.a:
	$(MAKE) -C ../libcs50
common.a: pagedir.o word.o index.o
	ar cr $@ $^

.PHONY: dtest ctest clean

# creates several directories which will hold the test results
ctest:
	mkdir ../tsetest
	mkdir ../tsetest/index1
	mkdir ../tsetest/letters3
	mkdir ../tsetest/wiki1
	mkdir ../tsetest/scrape1

# deletes all the directories created by ctest
dtest:
	rm -rf ../tsetest

# deletes all the .o files within and if a /pagedir exists that too
clean:
	rm -f *~ *.o
	rm -f *.a
	rm -f $(PROG)
