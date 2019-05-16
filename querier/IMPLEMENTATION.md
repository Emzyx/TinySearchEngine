# CS50 Querier
## Carlos Yepes, Spring 2019

### Usage

**./querier [pageDirectory][indexFilename]**

### About the Makefile

The Makefile can compile the *querier* with `make`. To clean everything you can use `make clean`, `cleanall` was created for when using all crawler, indexer and querier in sequence so that's not important since I can upload the test files.
It contains a rule `make test` which will run the testing script. You can output that into a file such as `testing.out` by running it with `make test &> testing.out`

### Modules Used

I used all of the modules archive in `common.a`, those being:
 - `index.h`
 - `word.h`
 - `pagedir.h`

Also a good amount from `libcs50.a` such as:
 - `counters.h`
 - `hashtable.h`
 - `bag.h`
 - `file.h`

All of the functions within `querier.c` can be read up within *DESIGN.md*

### Structures Used

 - *set_pair* : holds two sets which will be merged or intersected
 - *node* : a struct which contains a key, count pairing
 - *sorted_list* : a list which through a function will contain nodes sorted based on the nodes count

### Storage

The querier relies on a directory existing containing crawler created files as well as an indexeer created file from those crawled files. It cannot perform without them.