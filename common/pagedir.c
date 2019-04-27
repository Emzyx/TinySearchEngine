

#include <stdbool.h>
#include "pagedir.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool
validDir(const char *dirname)
{ 
  if (dirname == NULL){
      fprintf(stderr, "Null or empty directory name\n");
      return false;
  }

  FILE *fp;
  int len = strlen(dirname);
  char filename[len*2];
    
  sprintf(filename, "%s/.crawler", dirname);
  if((fp = fopen(filename, "w")) != NULL){
      fclose(fp);
      return true;
  }
  else{
      fprintf(stderr, "directory doesnt appear to be accessible\n");
      return false;
  }
}


