/* Querier program
 * 
 * Assumes pageDirectory contains files numbered 1, 2, 3...
 * 
 * 
 * Carlos Yepes, May 2019
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "counters.h"
#include "bag.h"
#include "pagedir.h"
#include "index.h"
#include "word.h"
#include "file.h"

typedef struct set_pair{
  counters_t *jointSet;
  counters_t *setB;
} set_pair_t;

typedef struct node{
  int key;
  int count;
  struct node *next;
} node_t;

typedef struct sorted_list{
  node_t *head;
  node_t *pointer;
  int size;
} sorted_list_t;

int fileno(FILE *stream);
void query(hashtable_t *index, const char *directory);
bool checkargs(const int argc, const char * args[]);
bool isValidQuery(char *line, char *words[], int *size);
bool hasBadChar(char * line);
void cleanLine(char *line, char *words[], int *size);
bool isComparator(char *word);
void intersectSets(void *arg, const int key, const int count);
void mergeSets(void *arg, const int key, const int count);
counters_t * combineSequences(bag_t *master_and, bag_t *master_or);
void makeAndSequence(hashtable_t *index, bag_t *master_and, char *words[], int size);
static void prompt(void);
void sortHelper(void *arg, const int key, const int count);
void findRelevantURL(counters_t *ctrs, const char *directory);

/* Global Variable
 * Indicates whether there was an "and" sequence, so it wouldnt double free a ctrs pointer
 * In combine sequences, sets are combined if theres more than one word in an "and" sequence
 */
bool intersect;

int 
main(const int argc, const char * args[])
{
  const char *directory;
  const char *filename;
  hashtable_t *index;
  FILE *fp;

  if(!checkargs(argc, args)){
    return 1;
  }
  directory = args[1];
  filename = args[2];
  fp = fopen(filename, "r");
  index = hashtable_new(lines_in_file(fp));
  index_load(fp, index);
  query(index, directory);

  hashtable_delete(index, hashCountersDelete);
  fclose(fp);
}

/************************************ FUNCTIONS **************************************/

/*
 * Brings all the other functions together
 * Calls the validation of arguments and intializes the structures
 * Also frees the structures once everything is done.
 */
void
query(hashtable_t *index, const char *directory){
  char *line;

  prompt();
  while((line = freadlinep(stdin)) != NULL){
    int size = 0;
    char *words[strlen(line)];
    counters_t *ctrs;

    isValidWord(line); // normalizes input but also checks if its greater than 3 chars, was mainly used in indexer, but it can be used here as well
    // Validate and Clean
    
    bag_t *master_and = bag_new();  
    bag_t *master_or = bag_new(); // will store the counters which will be merged

    if(isValidQuery(line, words, &size)){
      // And sequencing ///////////////////////////
      makeAndSequence(index, master_and, words, size);
      ctrs = combineSequences(master_and, master_or);
      if (ctrs && ctrs != NULL){ // do something with ctrs
        findRelevantURL(ctrs, directory);
        if (intersect == true){
          counters_delete(ctrs); // deletes ctrs pointer which was created in combineSequences when done
          ctrs = NULL;
        }
      }
    }

    prompt();
    free(line);
    bag_delete(master_and, NULL); // deletes master bag and bags inside, in case it has any  
    bag_delete(master_or, NULL);
  }
}
/*
 * Combines the "and" and "or" sequences after the bags have been made.
 * Returns a counter containing the fully intersected and merged result
 */
counters_t *
combineSequences(bag_t *master_and, bag_t *master_or)
{
  // counters_t *final = counters_new();
  bag_t *curr;      
  counters_t *setA, *setB, *jointSet;
  bool entered = false; // keeps track to see if it even entered the loop, shows if master bag is empty

  while((curr = bag_extract(master_and)) != NULL){ // extract an and sequence
    intersect = false;
    entered = true;
    // first iterate to set up and create jointSet
    if ((setA = bag_extract(curr)) == NULL){
      bag_delete(curr, NULL); // gotta delete bag here since they were extracted, although this ones for safety
      return NULL;
    }
    else if ((setB = bag_extract(curr)) == NULL){ // only had one counterset
      bag_delete(curr, NULL); // gotta delete bag here since they were extracted
      bag_insert(master_or, setA);
    }
    else{
      // if it has two counters, we intersect them, must free later since its not even in the hashtable
      jointSet = counters_new();
      intersect = true;

      //set up the struct
      set_pair_t *sets = malloc(sizeof(set_pair_t));
      sets->setB = setB;
      sets->jointSet = jointSet;
      // first intersection to construct jointSet which we will exclusively use
      counters_iterate(setA, sets, intersectSets);
      sets->setB = jointSet;

      while((setA = bag_extract(curr)) != NULL){ // combine all counters through intersection
        counters_iterate(setA, sets, intersectSets);
      }
      bag_insert(master_or, jointSet);
      free(sets); 
      bag_delete(curr, NULL); // gotta delete bags here since they were extracted
    }
  }  
  if (curr == NULL && entered == false){ // returns NULL if it had nothing to begin with and didnt enter the loop, if setA is null then there wasnt any counters
      return NULL;
  }
  // proceed to merge
  jointSet = bag_extract(master_or); // extract first, so it only enters loop if it has more than one
  while((setA = bag_extract(master_or)) != NULL){
    set_pair_t *sets = malloc(sizeof(set_pair_t));
    sets->setB = jointSet;
    sets->jointSet = jointSet;
    counters_iterate(setA, sets, mergeSets);
    free(sets);
  }
  // return final set once all combined
  return jointSet;
}

/*
 * Uses a helper function `sortHelper` and a sorted_list struct to order the documentID's in the given counter by relevancy
 * After sorting, it prints the list in order, which is ordered from most frequent to least frequent
 */
void
findRelevantURL(counters_t *ctrs, const char *directory)
{
  sorted_list_t *list= malloc(sizeof(sorted_list_t));
  list->head = NULL;
  // list->pointer = NULL;
  list->size = 0;
  counters_iterate(ctrs, list, sortHelper); // returns list in order
  FILE *fp;

  int docID;
  char document[strlen(directory) + 100];
  char *line;
  printf("Matches %d documents (ranked):\n", list->size);
  while(list->head != NULL){
    docID = list->head->key;
    sprintf(document, "%s/%d",directory, docID);
    fp = fopen(document, "r");
    line = freadlinep(fp);
    fclose(fp);
    printf("score\t%d doc %d: %s\n", list->head->count, docID, line);
    list->pointer = list->head;
    list->head = list->head->next;
    free(list->pointer);
    free(line);
  }
  free(list);
}

/*
 * Helper function which takes a list and creates a node out of given keys and counts
 * It then adds it to the sorted_list based off of the count of the node
 * Results in a sorted list of nodes which hold key, count pairs
 */
void 
sortHelper(void *arg, const int key, const int count)
{ 
  sorted_list_t *list = arg;
  list->size += 1;
  node_t *node = malloc(sizeof(node_t));
  node->key = key;
  node->count = count;
  node->next = NULL;
  if(list->head == NULL){
    list->head = node;
  }
  else if(/*node->*/count >= list->head->count){ // if new node is greater insert at head
    node->next = list->head;
    list->head = node;
  }
  else{ // new is less than head
    for (node_t *pointer = list->head; pointer != NULL; pointer = pointer->next){
      if(pointer->next == NULL || count >= pointer->next->count){ // if its greater than next or no next
        if(pointer->next != NULL){
          node->next = pointer->next;
        }
        pointer->next = node;
        break; // we inserted already so lets get out
      }
    }
  }
}

/*
 * Results in a `master_and` bag containing "and" sequences
 * if given line is empty, it leaves the `master_and` bag empty
 * Creates bags which contain sequences of words until it hits an "or" then it adds the bag to the master "and" bag
 * If it encounters a word which cannot be found it deletes the current bag and consequentially, that "and" sequence
 * It continues until it reaches the sequence
 * Takes a `master_and` bag which is a bag of bags.
 * All bags within the `master_and` will be extracted and will intersect all the counters within the sub-bags
 */
void
makeAndSequence(hashtable_t *index, bag_t *master_and, char *words[], int size)
{  
  counters_t *ctrs;
  bag_t *current; 
  for(int i = 0; i < size; i++){

    if(i == 0){ // create initial bag
      current = bag_new();
    }
    if(strcmp(words[i], "or") == 0){ // if it finds an or, add and-sequence-bag to master bag
      if (current != NULL){ // if bag doesnt exist, nothing to insert
        bag_insert(master_and, current);
      }
      current = bag_new();

    }
    else if(strcmp(words[i], "and") != 0){ // add to and-sequence-bag
      if ((ctrs = hashtable_find(index, words[i])) != NULL){ // if word exists
        bag_insert(current, ctrs);
      }
      else{
        bag_delete(current, NULL);
        current = NULL;
        while (i < size && strcmp(words[i], "or") != 0){
          i++;
        }
        i--; // subtract one so for loop can bring it back to "or"
      }
    }
    if (i == size - 1 && current != NULL){ // insert last bag if it exists
      bag_insert(master_and, current);
    }
  }
}

/*
 * Intersects the sets
 */
void 
intersectSets(void *arg, const int key, const int count)
{
  set_pair_t *counterSets = arg;
  int countB = counters_get(counterSets->setB, key); // 0 doesnt exist
  if ((countB ) > 0){ // key exists in setB if > 0
    if (countB > count){
      counters_set(counterSets->jointSet, key, count); // set the lowest one
    }
    else{
      counters_set(counterSets->jointSet, key, countB);
    }
  }
}

/*
 * Merges the given sets
 */
void
mergeSets(void *arg, const int key, const int count)
{
  set_pair_t *counterSets = arg;
  int countB = counters_get(counterSets->jointSet, key);
  // add items of first set
  if (countB > 0){ // key exists in both
    counters_set(counterSets->jointSet, key, count + countB);
  }
  else{ //key doesnt exist in joinSet, so we add it
    counters_set(counterSets->jointSet, key, count);
  }
}

/*
 * Checks the word array to see if the line given was a valid query
 */
bool
isValidQuery(char *line, char *words[], int *size){
  if(!hasBadChar(line)){ // if it does not have a bad char proceed to clean
    cleanLine(line, words, size);
    if (*size != 0){
        if (isComparator(words[0])){
          fprintf(stderr, "'%s' is a comparator\n", words[0]);
          return false;
        }
        if(isComparator(words[*size - 1])){
          fprintf(stderr, "'%s' is a comparator\n", words[*size - 1]);
          return false;
        }

      for(int i = 0; i < *size - 1; i++){
        if (isComparator(words[i]) && isComparator(words[i + 1])){
          fprintf(stderr, "Cannot have to consecutive comparators\n");
          return false;
        }
      }

      // Prints if it passes everything
      printf("Clean Query:");
      for (int i = 0; i < *size; i++){
        printf(" %s", words[i]);
      }
      printf("\n");
      return true;
    }
    // Query is empty
    return false;
  }
  // Query has bad character
  return false;
}
/*
 * checks if given word is "and" or "or"
 */
bool
isComparator(char *word)
{
  if (strcmp(word, "and") == 0 || strcmp(word, "or") == 0){
    return true;
  }
  else{
    return false;
  }
}

/*
 * Checks the arguments of given in the command line
 */
bool 
checkargs(const int argc, const char * args[])
{
  char *USAGE = "Usage: ./querier [pageDirectory][indexFilename]\n";

  if (argc != 3){ // makes sure amount of arguments is correct
    fprintf(stderr, "%s", USAGE);
    return false;
  }
  if (!validCrawlDir(args[1])){ // checks for a valid directory
    return false;
  }
  if(!validReadFile(args[2])){ // checks to see if filename is writable
    return false;
  }
  return true; // returns true if everything checks out
}

/*
 * Checks if line contained a non-space or non-alpha character
 */
bool
hasBadChar(char * line)
{
  for (int i = 0; line[i]; i++){
    if (isalpha(line[i]) || isspace(line[i])){ // if its a valid query
    }
    else{
      fprintf(stderr, "Invalid character '%c' in query.\n", line[i]);
      return true;
    }
  }
  return false;
}

/*
 * Cleans line from extra space and stuff
 */
void
cleanLine(char *line, char * words[], int *size)
{
  char *delim = " \t\n";
  char *token = strtok(line, delim);
  while (token != NULL){
    words[*size] = token;
    token = strtok(NULL, delim);
    *size += 1;
  }
}

static void
prompt(void)
{
  // print a prompt iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Query? \n");
  }
}