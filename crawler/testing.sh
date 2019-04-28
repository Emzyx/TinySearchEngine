#!/bin/bash

# TEST SCRIPT FOR CRAWLER
# RESULTS WILL BE IN /tse-Emzyx/tsetest

# Compiles the files
make

# makes the directories for the tests
make direct

# runs test1
# Uses http://old-www.cs.dartmouth.edu/~cs50/index.html with a depth of 1
make test1

# test2
# uses http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html with a depth of 3
make test2

# test3
# uses http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html with a depth of 2
make test3
