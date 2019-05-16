
#include "counters.h"
#include "index.h"
#include "word.h"
#include "file.h"
#include "pagedir.h"

void
index_build(const char * directory, hashtable_t *index)
{ 
  webpage_t *page;
  FILE *fp; // files that will be opened
  int documentID = 1; //a counter for the number of file we're on
  char filein[20];
  char *word;
  counters_t *ctrs;

  sprintf(filein, "%s/%d", directory, documentID);

  while ((fp = fopen(filein, "r")) != NULL){
    
    page = remakeWebpage(fp);
    int pos = 0;
    while ((word = webpage_getNextWord(page, &pos)) != NULL){
      if (isValidWord(word)){ // validates individual word

        if ((ctrs = hashtable_find(index, word)) == NULL){ // makes a counter for the word if it didn't have one
          ctrs = counters_new();
          counters_set(ctrs, documentID, 1);
          hashtable_insert(index, word, ctrs);
        }
        else{ // increments the counter of the number of times the word appears in a file
          counters_add(ctrs, documentID);
        }
      }
      free(word);
    }

    // increments and changes the file to be opened
    webpage_delete(page);
    fclose(fp);

    documentID++;
    sprintf(filein, "%s/%d", directory, documentID);
  }
}

void
index_save(FILE *fp, hashtable_t *index)
{
  hashtable_iterate(index, fp, hashCountersSave);
}

void
index_load(FILE *fp, hashtable_t *index)
{ 
  char *word;
  int documentID;
  int frequency;
  int rtrn;
  counters_t *ctrs;

  while (!feof(fp)){
    word = freadwordp(fp);

    if (word != NULL){
      rtrn = fscanf(fp, "%d %d ", &documentID, &frequency);

      while(rtrn == 2){ // the amount of items scanned
        //inserts word and value into hashtable
        if ((ctrs = hashtable_find(index, word)) == NULL){
          ctrs = counters_new();
          counters_set(ctrs, documentID, frequency);
          hashtable_insert(index, word, ctrs);
        }
        else{ //found counter
          counters_set(ctrs, documentID, frequency);
        }
        //scans for the next pairing
        rtrn = fscanf(fp, "%d %d ", &documentID, &frequency);
      }
    }
    free(word);
  }
}

webpage_t * 
remakeWebpage(FILE *fp)
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

void 
hashCountersDelete(void *item)
{
  counters_t *ctrs = item;
  counters_delete(ctrs);
}

void 
hashCountersSave(void *arg, const char *key, void *item)
{
  FILE *fp = arg;
  counters_t *ctrs = item;

  fprintf(fp, "%s", key);
  counters_iterate(ctrs, fp, countersSave);
  fprintf(fp, "\n");
}

void 
countersSave(void *arg, const int key, const int count)
{
  FILE *fp = arg;
  fprintf(fp, " %d %d", key, count);
}