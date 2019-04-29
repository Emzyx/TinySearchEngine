

#include <stdbool.h>
#include "pagedir.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "webpage.h"

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

bool
pagefetcher(webpage_t *page)
{
  return webpage_fetch(page);
}


bool
pagesaver(webpage_t *page, const char *dir, int *id)
{ 
  if(dir == NULL){
    return false;
  }

  FILE *fp;
  int len = strlen(dir);
  char name[len*2];
  sprintf(name, "%s/%d", dir, *id);

  // incements id counter.
  *id += 1;

  fp = fopen(name, "w");
  
  if (fp != NULL){
    fprintf(fp, "%s\n%d\n%s", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
    fclose(fp);
    return true;
  }
  else{
    return false;
  }
}

char *
pagescanner(webpage_t *page, int *pos)
{ 
  return webpage_getNextURL(page, pos);
}

