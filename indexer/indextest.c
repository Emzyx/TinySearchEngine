
#include "index.h"
#include "pagedir.h"

bool checkargs(const int argc, const char * args[]);

int
main(const int argc, const char * args[])
{ 

  if (!checkargs(argc, args)){
    return 1;
  }

  // variabless for readability
  const char * oldfile;
  const char * newfile;
  FILE *fpold;
  FILE *fpnew; // file that will be written in

  hashtable_t *indextable = hashtable_new(900);

  oldfile = args[1];
  newfile = args[2];

  fpold = fopen(oldfile, "r");
  fpnew = fopen(newfile, "w"); // will overwrite whatevers inside it if it exists, create it if id doesnt

  index_load(fpold, indextable);

  // saves the counter pairs to a file
  index_save(fpnew, indextable);
  hashtable_delete(indextable, hashCountersDelete); 
  fclose(fpnew);
  fclose(fpold);
  return 0;
}

bool 
checkargs(const int argc, const char * args[])
{
  char *USAGE = "Usage: ./indexer [oldFilename][newFilename]\n";

  if (argc != 3){ // makes sure amount of arguments is correct
    fprintf(stderr, "%s", USAGE);
    return false;
  }

  if(!validReadFile(args[1])){ // checks to see if filename is readable
    return false;
  }

  if (!validWriteFile(args[2])){ // checks to see if given write file name ir writable
    return false;
  }

  return true; // returns true if everything checks out
}