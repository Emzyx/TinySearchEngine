# CS50 Indexer
## CS50 Spring 2019

### Files

The indexer will only have a `indexer.c` file.
But it will also make use of the `index.c` within the common

#### indexer.c

The `indexer` is going to implement a **hashtable** of **counters**.
The *key* to the **hashtable** is going to be a "word" which is read from the document and the *item* is going to be a **counter** structure.
Each **counter** *key* within the **hashtable** will use an `int` which will be based off of the `document IDs` from the results of `crawler`, since it names files starting from 1. The *count* within the **counter** will represent the amount of times the word appeared in that specific `document`.

##### Pseudocode
- It will validate all the arguments
- It will go into the given `pageDirectory` and while there are documents remaining, it will open one document at a time for reading
  - It will retrieve a *word* from the document, and while more *words* remain
    - It will get another *word* from the document
    - If the *word* doesnt exist within the ***index hashtable***
      - It will create a ***counter set*** for the *word* and initialize a counter corresponding to a *documentID*
    - Else if the word does exist within the ***index hashtable***
      - It will increment the count for the counter of the current *documentID* of the word
- Once thats done, it will iterate through the index hashtable
- It will save one word in a line, and after the word it will iterate through each counter belonging to that word
- It will save every key and count within the counter in the format [documentID count] with key corresponding to documentID
- Then it will finally clean up the data structures and close the files.
- Done

### Interface

The only interface with the user would be on the command-line.
It must always be given 2 arguments:
```
indexer directory filename
```
With the directory being one which holds crawler created files

For example:
```
./indexer ../tsetest/wiki2 wikiIndex
```

### Inputs and Outputs

The only inputs are the ones shown above in the *Interface* section

The output is a file named after the 2nd argument given in the inputs
It is formatted:
 - word documentID count documentID count ...

### Decomposition into Modules

The following modules and functions were used:
1. `indexer`, puts all of the components together.
  > **Houses these Functions**
   - _main_ which uses `checkargs` to validate arguments, `index_build` to build the index hashtable, `index_save` to save the index hashtables contents into a file. It also uses the `fuckMeUp` function, which plays the notification sound.
   - _checkargs_ validates the arguments given to the _main_. Makes sure they exist can be written into
   - _fuckMeUp_ makes the notification sound. #shitpost (please don't take points off for this :-))
2. `index` within the common directory
  > **Houses these Functions**
   - *index_build* which given an initialized hashtable, and a directory it goes through every document within and builds the hashtable based on the frequency of each word in each document. It assumes the directory given contains crawler made files.
   - *index_save* given a hashtable and a file opened for writing, it iterates through the hashtable and saves the contents as formatted above.
   - *index_load* given the name of an existing indexer created file, loads the file contents into a hashtable
   - *remakeWebpage* given a crawler created file, it returns a webpage structure containing the files url, depth, and html
   - *hashCountersDelete* operates within a `hashtable_delete` call to delete the individual counters
   - *hashCountersSave* operates within the index_save call, this saves the word obtained and calls `counters_iterate`
   - *countersSave* is called by counters_iterate and saves the key and count of each counter into the file which corresponds to the documentID and the word frequency in that document
3. `pagedir` within the common directory
  > **We used:**
   - *validDir* which checks to see if the directory given can be opened/is valid.
   - *validWriteFile* checks and opens the filename given to see if it is writeable.
   - *str2int* given a string, it extracts an integer and writes it into a given pointer if it is a valid integer, else it returns false
4. `word` within the common directory
  > **Houses**
   - *validWord* which normalizes a word by making it lowercase and checks to see if the words length is at least 3 characters

Made use of the structures:
 - counters
 - hashtable

### Testing Plan

We plan on testing this by:

 - Test the program with insufficient arguments
 - Provide a nonexisting directory
 - Alter the permissions of a file to restrict all access, feed the file to the indexer, should fail
 - Give parameters to a file which holds crawler results and a writeable filename, which should succeed
 - Compare test results of a successful index to the indextest by sorting and then looking for differences