/*
 * crawler.c will crawl through a given url and use dfs to retrieve more pages until it hits tthe max depth
 * 
 * Carlos Yepes, April 2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "bag.h"
#include "webpage.h"
#include "hashtable.h"
#include "pagedir.h"


#define USAGE "Usage: ./crawler [seedURL][pageDirectory][maxDepth]\n"
#define SLOTS 100

// Declarations
bool str2int(int *number, const char string[]);
bool pagefetcher(webpage_t *page);
bool pagesaver(webpage_t *page, const char *dir, int *id, int *pos);
void testprint(FILE *fp, void *item);
void testprint2(FILE *fp, const char *key, void *item);


int 
main(const int argc, const char * args[])
{
  // Variables (for readability)
  char *seed;
  const char *dir;
  int depth;
  int id = 1;
  int pos = 0;

  webpage_t *page;
  bag_t *toCrawl;
  hashtable_t *hash;

  /******************* Checking for Validity ***************************/
  if (argc < 4){
    fprintf(stderr, "Not enough arguments given.\n");
    fprintf(stderr, USAGE);
    return 1;
  }
  else if (argc > 4){
    fprintf(stderr, "Too many arguments given.\n");
    fprintf(stderr, USAGE);
    return 1;
  }
  else{
    if (!str2int(&depth, args[3])){
      fprintf(stderr, "Not a valid number\n");
      return 2;
    }
    else if(depth < 0 || depth > 10){
      fprintf(stderr, "Depth must be between [0,10]\n");
    }
    

    /************* Setting the stage ************/
    seed = (char*)args[1];

    // Checking if its a valid directory
    dir = args[2];
    if (!validDir(dir)){
      fprintf(stderr,"Not a usable directory\n");
    }
    
    page = webpage_new(seed, 0, NULL);
    toCrawl = bag_new();
    hash = hashtable_new(SLOTS);

    bag_insert(toCrawl, page);
    // hashtable_insert(hash, webpage_getURL(page), "insertion");

    while((page = bag_extract(toCrawl)) != NULL){
      if(pagefetcher(page)){
        if (pagesaver(page, dir, &id, &pos)){
          printf("success\n");
        }
        else{
          printf("save failed\n");
        }
      }
      else{
        printf("Fetch failed\n");
      }
    }

    bag_delete(toCrawl, webpage_delete);
    hashtable_delete(hash, webpage_delete);
    webpage_delete(page);

    return 0;
  }
}

/**************** Functions *****************/
bool
pagefetcher(webpage_t *page)
{
  return webpage_fetch(page);
}

bool
pagesaver(webpage_t *page, const char *dir, int *id, int *pos)
{ 
  if(dir == NULL){
    return false;
  }

  FILE *fp;
  int len = strlen(dir);
  char name[len*2];
  sprintf(name, "%s/%d", dir, *id);

  // incements id counter
  id += 1;

  fp = fopen(name, "w");
  
  if (fp != NULL){
    fprintf(fp, "%s\n%d\n%s", webpage_getNextURL(page, pos), webpage_getDepth(page), webpage_getHTML(page));
    fclose(fp);
    return true;
  }
  else{
    return false;
  }
  
}


bool 
str2int(int *number, const char string[])
{
  char next;
  return(sscanf(string, "%d%c", number, &next) == 1);
}


/**************** TEST Functions*************/

// void 
// testprint(FILE *fp, void *item)
// {
//   webpage_t *i = item;
//   char *url = webpage_getURL(i);
//   fprintf(fp, "%s", url);
// }
// void 
// testprint2(FILE *fp, const char *key, void *item)
// {
//   fprintf(fp, "%s", key);
// }




