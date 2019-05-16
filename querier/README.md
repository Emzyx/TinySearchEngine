# Carlos Yepes
## CS50 Spring 2019

## Testing

You can test using `make test`, you can compile using `make` beforehand, but the `testing.sh` will make for you as well.
You can clean using `make clean`, which will clean all the files created when compiling asides from `testing.out`

## Assumptions

Querier assumes that the arguments given are crawler and indexer created. Although it checks to see if the crawler directory was crawler created.
It assumes the index file contains files going from 1,2,3...

## Functionality

All of the functionality things were implemented
It prints the document set in decreasing order by score
It supports *and* precedence over *or*
The other two work since the above two work.