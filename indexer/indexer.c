/*
 * indexer.c will go through the files created by the crawler
 * (It ASSUMES that the files were made by the crawler)
 * It then proceeds to save the words which appeared (if they are greater than 3 characters) and the frequency in which they appeared in
 * Format of file is: word [documentID frequency] [documentID frequency]...
 * 
 * Carlos Yepes, April 2019
 */

#include "pagedir.h"
#include <stdlib.h>
#include "index.h"
#include <unistd.h>
#include <string.h>

void fuckMeUp(void);
bool checkargs(const int argc, const char * args[]);

int
main(const int argc, const char * args[])
{
  // variabless for readability
  const char * directory;
  const char * filename;

  FILE *fpwrite; // file that will be written in

  hashtable_t *indextable = hashtable_new(900);

  if(!checkargs(argc, args)){
    return 1;
  }
  directory = args[1];
  filename = args[2];
  fpwrite = fopen(filename, "w"); // will overwrite whatevers inside it if it exists, create it if id doesnt

  // builds the hashtable index
  index_build(directory, indextable);

  // saves the counter pairs to a file
  index_save(fpwrite, indextable);
  hashtable_delete(indextable, hashCountersDelete); 
  fclose(fpwrite);
  fuckMeUp(); //turn volume up
  return 0;
}

/***************** FUNCTIONS ******************/

/*
 * Checks arguments and validates them.
 * Only returns true if all of them are valid
 */
bool 
checkargs(const int argc, const char * args[])
{
  char *USAGE = "Usage: ./indexer [pageDirectory][indexFilename]\n";

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

/*
 * Ay fuck it up
 */
void 
fuckMeUp(void)
{
  printf("\a");
  sleep(1);
}