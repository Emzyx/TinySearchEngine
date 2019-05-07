
#ifndef PAGE_DIR
#define PAGE_DIR

#include <stdbool.h>
#include "webpage.h"


/*
 * Retrieves the html from the url of a given webpage struct 
 * 
 * Directly uses the webpage_fetch to retreive the html
 * 
 * Returns false if webpage_fetch returns NULL
 * Returns true if webpage_fetch succeeded
 */
bool pagefetcher(webpage_t *page);

/*
 * Saves the page into the given directory using an id.
 * 
 * Saves the page into the given test directory if it exists
 * Assigns each file a name based on the "id" number
 * 
 * returns false if save failed
 * returns true if save succeeded
 */
bool pagesaver(webpage_t *page, const char *dir, int *id);

/*
 * Scans the given page for the next URL
 * 
 * Directly uses webpage_getNextURL
 * Returns a char pointer to a malloc'd webpage URL
 */
char * pagescanner(webpage_t *page, int *pos);

/*
 * Checks the validity of a given directory name
 * 
 * It attempts to open a file to write using the
 * given directory name.
 * 
 * Returns false if it could not be opened, since directory didn't exist
 * Returns true and creates a .crawler file in directory.
 */
bool validDir(const char *dirname);

/*
 *  Checks to see if the write file is valid by attempting to open it.
 * 
 * Returns false if it failed to open the file
 * Returns true if it successfully opened the file for writing
 * 
 */
bool validWriteFile(const char * name);

/*
 * Checks to see if the read file is valid by attempting to open it.
 * 
 * Returns false if name was invalid or failed to open for reading
 * Returns true if it successfuly opened for reading
 */
bool validReadFile(const char * name);

/* 
 * Given a pointer to an integer, converts a valid char string into an integer
 * 
 * Returns true if valid int
 * Returns false if failed
 * 
 * Thanks Prof. Kotz
 */
bool str2int(int *number, const char string[]);

#endif