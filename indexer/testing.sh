#!/bin/bash

# Test script for Indexer
# Results will be in testing.out
# There will also be files produced

# Calls rules within the crawler Makefile to compile crawler and create files for testing
#if [ -d ../tsetest ]
#then
#    echo "crawl directory exists, so files probably do too"
#else
#    make crawl
#fi
### Did not use code above since a call to Makefile probably isn't allowed, but I'll keep it since it may be useful to me later.

# Compiles indexer and indextest within the indexer directory
make

# Begin testing

# tests letters
make testL

# tests wiki
make testW

# tests scrape
make testS

# tests the indextest which tests index_save and index_load
make testT

# insufficient arguments on indexer
make insufficient

# insufficient arguments on indextest
make insufftest

# invalid directory on indexer
make invalid

# tries to read non existent file on indextest
make nread

# ceates and tries unwriteable file on indexer
make nwrite

# tries unwritable file on indextest
make nwritetest

# removes unwriteable file so it wont clutter
chmod +w nwrite.Index
rm -f nwrite.Index

# will sort to find differences in files
gawk -f indexsort.awk scrape.Index > sorted_scrape.Index
gawk -f indexsort.awk new_scrape.Index > sorted_new_scrape.Index

DIFF=$(diff --brief sorted_scrape.Index sorted_new_scrape.Index)
if [ "$DIFF" != "" ] 
then
    echo "Files differed."
else
    echo "Files matched."
fi






