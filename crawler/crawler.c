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
char * strdup(char *string);

int 
main(const int argc, const char * args[])
{
  // Variables (for readability)
  char *seed;
  const char *dir;
  int depth;
  
  int id = 1;

  /******************* Checking for Validity ***************************/
  if (argc < 4){
    fprintf(stderr, "Not enough arguments given.\n");
    fprintf(stderr, "%s\n", USAGE);
    return 1;
  }
  else if (argc > 4){
    fprintf(stderr, "Too many arguments given.\n");
    fprintf(stderr, "%s\n", USAGE);
    return 1;
  }
  else{
    if (!str2int(&depth, args[3])){
      fprintf(stderr, "Not a valid number\n");
      return 2;
    }
    else if(depth < 0 || depth > 10){
      fprintf(stderr, "Depth must be between [0,10]\n");
      return 2;
    }
    

    /************* Setting the stage ************/

    // Checks if its a valid URL
    seed = (char*)args[1];
    if (!IsInternalURL(seed)){
      fprintf(stderr, "Not an internal URL\n");
      return 3;
    }
    
    // to prevent it from giving an invalid free due to the seed
    seed = strdup(seed);

    // Checking if its a valid directory
    dir = args[2];
    if (!validDir(dir)){
      fprintf(stderr,"Not a usable directory\n");
      return 4;
    }
    
    // Creates the data structures
    char *extractedURL;
    webpage_t *page = webpage_new(seed, 0, NULL);
    bag_t *toCrawl = bag_new();
    hashtable_t *hash = hashtable_new(SLOTS);

    bag_insert(toCrawl, page);
    hashtable_insert(hash, args[1], "");
    
    // The big boi loop that does the work
    while((page = bag_extract(toCrawl)) != NULL){
      int pos = 0;
      
      // fetches the html
      if(pagefetcher(page)){

        // saves the page if it successfully retrieved html
        if (pagesaver(page, dir, &id)){
          printf("%d\tSaved:\t%s\n",webpage_getDepth(page), webpage_getURL(page));

          // if it isnt balls deep itll go deeper
          if (webpage_getDepth(page) < depth){

            // begins the extraction of URL's and adding them to the hashtable and bags
            while((extractedURL = pagescanner(page, &pos)) != NULL){
              printf("%d\tFound:\t%s\n",webpage_getDepth(page) + 1, extractedURL);

              if(NormalizeURL(extractedURL)){
                if (IsInternalURL(extractedURL)){ // normalizes the url and proceeds only if its internal
                  if (hashtable_insert(hash, extractedURL, "")){
                    webpage_t *new =  webpage_new(extractedURL, webpage_getDepth(page) + 1, NULL);
                    bag_insert(toCrawl, new);
                    printf("%d\tAdded:\t%s\n",webpage_getDepth(page) + 1, extractedURL);
                  }
                  else{ //frees memory allocated to already existing url
                    printf("%d\tIgDup:\t%s\n", webpage_getDepth(page) + 1, extractedURL);
                    free(extractedURL);
                  }
                }
                else{ // frees extractedURL if its not internal
                  printf("%d\tIgExt:\t%s\n", webpage_getDepth(page) + 1, extractedURL);
                  free(extractedURL);
                }
              }
            }
          }
        }
        else{
          fprintf(stderr, "Save failed\n");
        }
      }
      else{
        fprintf(stderr, "Fetch failed\n");
      }
    // didnt use webpage delete because it gave an invalid free because of the char portion
    webpage_delete(page);
    }
    // Deletes the structures once the job is complete
    bag_delete(toCrawl, webpage_delete);
    hashtable_delete(hash, NULL);
    
    return 0;
  }
}

/**************** Functions *****************/
// Thanks Prof. Kotz
bool 
str2int(int *number, const char string[])
{
  char next;
  return(sscanf(string, "%d%c", number, &next) == 1);
}

// Props to https://stackoverflow.com/questions/252782/strdup-what-does-it-do-in-c
char *
strdup(char *string)
{
  char *new = malloc(strlen(string) + 1);
  if (new == NULL) return NULL;
  strcpy(new, string);
  return new;
}
