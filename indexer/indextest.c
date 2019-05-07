
#include "index.h"

int
main(const int argc, const char * args[])
{
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

