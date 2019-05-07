
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "word.h"

bool 
validWord(char * word)
{
  // normalizes the word
  // Credit to: https://stackoverflow.com/questions/2661766/how-do-i-lowercase-a-string-in-c
  for (int i = 0; word[i]; i++){
    word[i] = tolower(word[i]);
  }

  // checks to see if its greater than 3 characters
  if (strlen(word) >= 3){
    return true;
  }
  else{
    return false;
  }
}

