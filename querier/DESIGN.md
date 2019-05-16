#CS50 Querier
## CS50 Spring 2019

### Files

The querier will only have the `querier.c` file.
Aside from that it will make use of the `index.h`, `pagedir.h` and the `word.h` files.

#### querier.c

The `querier` implements a **hashtable** of **counters**, as well as a  _master_ **bag** of **bags** of **counters**. The _master_ **bag** containing bags, with the amount of bags equaling the number of _and_ sequences separated by an "or". The **counters** within the *sub-bags* equal the number of words searched for.

For example, if the user were to query for:
 > ***search first and home***

Then the result would be a **master bag** containing a single **bag** which would contain the **counters** for each searched word if they exist. If a single word does not exist, since it is an _and_ sequence the **bag** will be deleted and the **master bag** would be empty.

Another example:
 > ***search first or home***

Would result in a **master bag** containing two **bags** which would contain their respective **counters**.

#### Pseudocode

The following modules were used:
1. `querier` which houses the main and many helper functions:
 > **Houses**
  - _fileno_ : no real clue as to what this does, provided by Prof. Kotz to work with the _prompt_. Says it does something with streams.
  - _query_ : reads the stdin and calls all the other functions to parse the inputs, normalize the line, check to make sure its a valid query, then it proceeds to process the *and* and *or* sequences of the line by calling `combineSequences` which prioritizes *and* sequences and returns the pointer to a `counters` struct. It then calls `findRelevantURL` to sort the `counters` struct into a `sorted_list` struct and prints the result of the sort, with the greatest score on top.
  - _checkargs_ : parses the initial arguments given from the command line and checks if they are valid.
  - _isValidQuery_ : checks the input from stdin, calls `hasBadChar`, and `isComparator` to see if it is valid, in other words, if it has an *and* or *or* at the start or end, or an *and* and *or* consecutively
  - _hasBadChar_ : Checks the line given by seeing if the line contains any non space or alpha characters
  -  _cleanLine_ : Cleans the line of whitespace and such by tokenizing it and adding to a array of strings
  - _isComparator_ : checks to see if the given word matches to an *and* or *or*
  - _intersectSets_ : a function which can be called by `counter_iterator` which takes in a `set_pair` and intersects every set passed through with each other to obtain one `counters` struct which contains the result of all the intersections. It passes this into a `master_or` bag which will merge all of the *and* sequences separated by an *or*
  - _mergeSets_ : merges every counter passed through.
  - _combineSequences_ : takes in `master` bags for the *and* and *or* sequences. Calls `counters_iterate`, `mergeSets` and `intersectSets` to combine all of the counters from the words into one resultant `counter` which I called `jointSet`
  - _makeAndSequence_ : Takes in the `hashtable` index, the `master_and` bag, the `array` of words created by `cleanLine`, and an int of the size of the `array` of words. It creates sub-*bags* of words until it either hits a word which does not exist in the hashtable and proceeds to destroy that bag and consequently the *and* sequence, or until it reaches an *or*, and it will add the bag to the `master_and` bag.
  - _prompt_ : prints a prompt for an interactive user
  - _sortHelper_ : is called by a `counter_set` in `findRelevantURL`. It takes in a `counter` struct and a `sorted_list` struct. It creates a node struct for the *key* and *count* passed through and adds them to the `sorted_list` struct. It adds them to the "list" based off of the value of the *count* in each node. Resulting in a "sorted list".
  - _findRelevantURL_ : takes in a `counter` and the name of the `directory` to search for crawled files. It creates a `sorted_list` struct which it passes down to `sort_helper` through `counters_iterate`. Once the iterating stops, we have a sorted list, and we go through each node in the list and retrieve the URL from the crawler created files. It then prints the score or the "relevancy" (if i may) and the documentID as well as the URL of the document.

I recognize I probably couldve split it up into more functions. Such as *findRelevantURL* I could have made a function which takes the `sorted_list` and prints the results rather than integrating it into *findRelevantURL*. I also couldve separated some others.

### Testing Plan

We will be conducting several tests, these include:
 - With comparators at the beginning and end as well as multiple comparators placed one after the other.
 - With words that do not exist within the indexed files.
 - Empty lines/no input
 - One *and* sequence
 - 2 words separated by an *or*
 - Two *and* sequences
 - A fuzz query test.

