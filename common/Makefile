# Makefile for pagedir
# Initializes directories in which the tests will be stored
#
# Carlos Yepes, April 2019

PROG = pagedir
MAKE = make

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
