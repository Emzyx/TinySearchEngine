

#ifndef _INDEX_H
#define _INDEX_H

#include "webpage.h"
#include "hashtable.h"
#include <stdio.h>

/*
 * Builds the index hashtable
 * Goes into the specified directory and reads the files within
 * It assumes the files were made by the crawler
 */
void index_build(const char * directory, hashtable_t *index);

/*
 * Iterates through the index hashtable, and then the coounterset saving the results into the given file
 */
void index_save(FILE *fp, hashtable_t *index);

/*
 * Given a file, reads the file and creates an index hashtable
 * 
 * Credit to https://stackoverflow.com/questions/3351809/reading-file-using-fscanf-in-c
 */
void index_load(FILE *fp, hashtable_t *index);

/* Uses files to remake webpages and look for words
 * Doesnt check for NULL since while loop only passes it through if it is not NULL
 * Assumes the files are in the format the crawler left them in
 */
webpage_t * 
remakeWebpage(FILE *fp);

/*
 * A delete function to delete the counter items
 */
void hashCountersDelete(void *item);

/*
 * A function which calls counters_iterate to save the hashtable
 */
void hashCountersSave(void *arg, const char *key, void *item);

/*
 * A function that given a file through the void argument, saves the key and count to the file in a int int format
 */
void countersSave(void *arg, const int key, const int count);

#endif