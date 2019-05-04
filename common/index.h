

#ifndef _INDEX_H
#define _INDEX_H

/*
 * A delete function to delete the counter items
 */
void hashCountersDelete(void *item);

void hashCountersSave(void *arg, const char *key, void *item);

void countersSave(void *arg, const int key, const int count);

#endif