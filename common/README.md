# CS50 LAB 4
## CS50 Spring 2019

All of these files are used through the `/crawler/Makefile` which uses the `Makefile` within `common`.

The pagedir contains several functions which are described within pagedir.h

The Makefile contains 3 rules:
* `ctest` creates the test directories
* `dtest` recursively deletes the test directories
* `clean` cleans the common directory of the archive library and the .o files

These are all used within `crawler`s `Makefile`