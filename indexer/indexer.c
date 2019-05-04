/*
 * 
 * Carlos Yepes, April 2019
 */

#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "pagedir.h"
#include "file.h"
#include "hashtable.h"
#include "counters.h"
#include "word.h"
#include "index.h"

#define USAGE "Usage: ./indexer [pageDirectory][indexFilename]\n"

void fuckMeUp(void);
bool checkargs(const int argc, const char * args[]);
webpage_t * remakeWebpage(FILE *fp);

int
main(const int argc, const char * args[])
{
  const char * directory;
  const char * filename;
  webpage_t *page;
  FILE *fp; // files that will be opened
  FILE *fpwrite; // file that will be written in
  int documentID = 1; //a counter for the number of file we're on
  char filein[20];

  hashtable_t *indextable = hashtable_new(900);

  if(!checkargs(argc, args)){
    return 1;
  }
  
  directory = args[1];
  filename = args[2];

  sprintf(filein, "%s/%d", directory, documentID);
  fpwrite = fopen(filename, "w"); // will overwrite whatevers inside it if it exists, create it if id doesnt
  
  char *word;
  counters_t *ctrs;

  while ((fp = fopen(filein, "r")) != NULL){
    // fuckMeUp(); //turn volume up

    page = remakeWebpage(fp);
    int pos = 0;
    while ((word = webpage_getNextWord(page, &pos)) != NULL){
      if (validWord(word)){ // validates individual word

        if ((ctrs = hashtable_find(indextable, word)) == NULL){ // makes a counter for the word if it didn't have one
          ctrs = counters_new();
          counters_set(ctrs, documentID, 1);
          hashtable_insert(indextable, word, ctrs);
        }
        else{ // increments the counter of the number of times the word appears in a file
          counters_add(ctrs, documentID);
        }
        printf("%s\n", word);
      }
      free(word);
    }

    // increments and changes the file to be opened
    webpage_delete(page);
    fclose(fp);

    documentID++;
    sprintf(filein, "%s/%d", directory, documentID);
  }

  // saves the counter pairs to a file
  hashtable_iterate(indextable, fpwrite, hashCountersSave);
  hashtable_delete(indextable, hashCountersDelete); 
  fclose(fpwrite);
  return 0;

}

/***************** FUNCTIONS ******************/

/*
 * Checks arguments and validates them.
 * Only returns true if all of them are valid
 */
bool checkargs(const int argc, const char * args[])
{

  if (argc != 3){ // makes sure amount of arguments is correct
    fprintf(stderr, "%s", USAGE);
    return false;
  }

  if(!validWriteFile(args[2])){ // checks to see if filename is writable
    remove(args[2]); // remove file so it doesnt clutter if its not valid
    return false;
  }

  if (!validDir(args[1])){ // checks for a valid directory
    remove(args[2]);// remove file so it doesnt clutter if its not valid
    return false;
  }

  return true; // returns true if everything checks out
}

/* Uses files to remake webpages and look for words
 * Doesnt check for NULL since while loop only passes it through if it is not NULL
 * Assumes the files are in the format the crawler left them in
 */
webpage_t * remakeWebpage(FILE *fp)
{
  webpage_t *page;
  char * url;
  int depth;
  char * strdepth;
  char * html;

  url = freadlinep(fp);

  strdepth = freadlinep(fp);
  str2int(&depth, strdepth);
  free(strdepth);

  html = freadfilep(fp);

  page = webpage_new(url, depth, html);
  return page;
}

/*
 * Ay fuck it up
 */
void fuckMeUp(void)
{
  printf("\a");
  sleep(1);
}