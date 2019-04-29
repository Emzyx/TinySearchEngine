# CS50 Lab 4
## CS50 Spring 2019

### Usage
**./crawler [seedURL][pageDirectory][maxDepth]**

To test ***VARIOUS*** URL's in succesion, using the Makefile, you can simply try _make test_
or to add the results to a file, _make test &> testing.out_

***SINCE***, _make test_ runs several tests at the same time, if you'd like to run one test at a time, run _make_ first to compile, then _make direct_ to create the directories or clear them out, and then _make test#_ where *#* is a specific number between from 1 to 4, inclusive.

Valgrind is commented out in the test files for speed purposes, to enable Valgrind, go to the Makefile and uncomment the **VAL =** part.

### Assumptions

Some assumptions one could make, is that everything works as it should (which it most likely will and has been working since Prof. Kotz provided it).
We also assume `pageDirectory` does not already contain files whos names are integers (i.e., `1`, `2`, `3`...)
We also depend on the fact that the only valid URL's are those beginning with `http://old-www.cs.dartmouth.edu`.