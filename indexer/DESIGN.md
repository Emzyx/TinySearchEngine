# CS50 Indexer
## CS50 Spring 2019

### Files

The indexer will only have a `indexer.c` file.

#### indexer.c

The `indexer` is going to implement a **hashtable** of **counters**.
The *key* to the **hashtable** is going to be a "word" which is read from the document and the *item* is going to be a **counter** structure.
Each **counter** *key* within the **hashtable** will use an `int` which will be based off of the `document IDs` from the results of `crawler`, since it names files starting from 1. The *count* within the **counter** will represent the amount of times the word appeared in that specific `document`.

##### Pseudocode

Might have to remake a webpage data structure using the URL written in the second line of the document, and then fetch the html again
Or try to find a way offline to just add only the html from the rest of the document

Ignore words fewer than 3 characters or *chars < 3*

> It will go into the given `pageDirectory`and open one document at a time for reading
> It will retrieve a word, and while it has not passed through every word in the document
>> It will get a word from the document 


