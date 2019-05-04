
#include "counters.h"
#include "index.h"

void hashCountersDelete(void *item)
{
  counters_t *ctrs = item;
  counters_delete(ctrs);
}

void hashCountersSave(void *arg, const char *key, void *item)
{
  FILE *fp = arg;
  counters_t *ctrs = item;

  fprintf(fp, "%s", key);
  counters_iterate(ctrs, fp, countersSave);
  fprintf(fp, "\n");
}

void countersSave(void *arg, const int key, const int count)
{
  FILE *fp = arg;
  fprintf(fp, " [%d %d]", key, count);
}