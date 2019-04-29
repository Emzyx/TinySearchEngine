# CS50 Crawler
## CS50 Spring 2019

### Usage
**./crawler [seedURL][pageDirectory][maxDepth]**

To test the the files using the Makefile, you can simply try _make test_, which calls regular _make_ to compile and _make ctest_ from the `common` `Makefile` to create directories for the tests, then call _make test#_ on every available test *#* being the number of test.
or to add the results to a file, _make test &> testing.out_
If you want to use each test case individually just use _make test#_ where "#" is the number of test you'd like to run.

#### About the Makefile
The Makefile has several rules/components laid out:
* `direct` calls a `Makefile` rule in the `common` directory which checks if the test directories existed and creates a **tsetest** directory in the main **tse** and several subdirectories under **tsetest** to store the files created by the test cases if it didnt, and deletes them and then recreates them if they did exist.
* `test` runs the testing script `testing.sh` which runs a majority of these rules
* `test1` is the first test which crawls _http://old-www.cs.dartmouth.edu/~cs50/index.html_ at a depth of **1**
* `test2` is the second test which crawls _http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html_ at a depth of 3
* `test3` is the third test which crawls _http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html_ at a depth of 1, and took me 30 mins to finish
* `test4` is the fourth test which crawls _http://old-www.cs.dartmouth.edu/~cs50/data/tse/toscrape/index.html_ at a depth of 1
* `clean` clears the main compiling files in the `common`, `libcs50`, and `crawler` by calling `Makefile` rules in the `common` and `libcs50` directories. The files deleted include`libcs50.a`, `crawler.o`, `crawler` and `pagedir.o`. It also calls a `Makefile` rule in the `common` and directory which deletes all of the test folders (_tsetest_ and the rest)

### Modules Used

The crawler is basically made up of two modules:
 * `crawler.c`
 * `pagedir.h` (which is followed up by `pagedir.c`)

It also relies heavily on the archive file `libcs50.a`

### Functions

#### The main() function

The `main()` function is contained within **crawler.c**.

* It defines several pointers to be used with the given arguments. This was mainly done for the purpose of readability, since it'd be dumb to constantly be using args[*#*] where # refers to a specific argument.
* It then proceeds to check if the `crawler` program was given the correct amount of arguments.
* If it was given the correct number of arguments, it validates each argument using functions made and provided such as `str2int`, `validDir`, and `IsInternalURL`.
* Once validated, it creates the data structures and inserts the first webpage.
* From here it scans the webpages html for other URL's and validates those
* If they were successfully validated, it will add them to the bag and hashtable structure if they had not already existed inside of them.
* It will eventually reach all of the ones added, and save them to the given directory.
* After that it makes sure to delete the data structures to free the memory.


#### crawler.c

crawler.c uses the following functions:

```c
bool str2int(int *number, const char string[]);
char * strdup(char *string);
```
Since there is no **.h** file for crawler, I'll describe their utility here.
* `str2int` is a function which both given an `int` pointer, discerns if the input was valid by using sscanf, and if it was, gives the integer value to the pointer
* `strdup` basically the same as C's `strdup`, but that one wasnt showing up, so this one was made. It takes in a string and allocates and returns a memory pointer from the heap using malloc based on the length of the string. It's main use is so freeing the seed's URL won't give an _invalid free_

#### pagedir.h

pagedir.h contains the following functions:

```c
bool validDir(const char *dirname);
bool pagefetcher(webpage_t *page);
bool pagesaver(webpage_t *page, const char *dir, int *id);
char * pagescanner(webpage_t *page, int *pos);
```
Their descriptions can be found in `pagedir.h`

### Structs Used

The structures used include:
* `webpage_t` : this struct holds an _int_ holding the depth, a _char_ pointer holding the URL, and a _char_ pointer holding the HTML of the page
* `bag_t` : this struct holds a _void_ pointer to an item, and a *bag_t* pointer to the next node
* `hashtable_t` : this struct holds a *set_t* *array* (at least in my implementation, but I'm using Prof. Kotz's), which uses the jhash module to hash items into the array

### Storage
The crawler is contained within one directory called **crawler**. It also uses things from other directories such as the **libcs50** and **common** directory.
It also creates a directory with several subdirectories in the main _tse_ folder to store test results, and in the future, will probably be the database which the indexer and querier will use.

