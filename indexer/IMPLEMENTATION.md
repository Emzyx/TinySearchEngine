# CS50 Indexer
## CS50 Spring 2019

### Usage

**./indexer [pageDirectory][filename]**

To test the files using the `Makefile`, you can use _make test_, which will call the bash script and run the tests

### About the Makefile

The `Makefile` will house most if not all of the tests which will be called in the test script. This is so that if you would like to try out any tests alone you can call the individual test which will be described below. It is also so that if you would like to run _Valgrind_ you can uncomment it from the top of the `Makefile`

To test we will provide a *make* rule that will crawl and create webpages for the use of the tests. It will create a directory and perform the crawl. They should all be deleted within the **crawler** `Makefile`, which we will probably include in the **indexer** `Makefile`

#### Testing in the Makefile

The tests are:
 - `test` the main test which will call most to all of the others by running the test script: `testing.sh`
 - `insufficient` to test the program with insufficient arguments
 - `insufftest` which tests indextest with insufficient arguments
 - `invalid` which tests a non-existing directory
 - `nwrite` which creates a file, and makes it unwriteable (nwrite = not writeable)
 - `nwritetest` which tests the same unwriteable file on the *indextest*
 - `nread` which tries to open a nonexisting file for reading
 - `testL` which will test the files created by **crawler** when it crawled "letters" at a depth of 3
 - `testW` which will test the files created by **crawler** when it crawled wiki at a depth of 1
 - `testT` which uses the `indextest` to test the *index_load* and the *index_save* using the index of letters

 It also includes a nifty *clean*, which cleans the common directory, the libcs50 directory and the indexer directory from the *.o*'s and binary files.

 If you want utter and complete extermination use *make cleanall* which cleans the indexer, common, and libcs50 file of all *.o* files, binary files and test results aside from *testing.out*

 ### Modules Used

 Initially we only used `pagedir` and `indexer` but after reading the instructions and going further, we used `word` and `index` which house a lot more functions which are used in multiple *.c* files

 More on these can be read within the ***DESIGN.md***

### Structs Used

We used the structures:

 - `webpage_t` : a struct which holds a URL, the URL's depth from the seed, and the URL's HTML
 - `hashtable_t` : intended to hold a char key and a void item. We used it to hold a word and a `counters_t` as the *void* item
 - `counters_t` : holds 2 integers, a key and a counter. Used the *documentID* as the key, and the frequency of a word within that document as the count

### Storage

THe **indexer** relies heavily on the fact that the directory given has **crawler** created files. This is because the **crawler** created files have names that are integers, which allow for easy reading/loading.

