#!/bin/bash

#Testing script for querier
# Results will be provided in testing.out
# Only testing.out will be produced, along with the .o files which can be cleaned

# Compiles the program
make

# tests comparators at various spots, bad input and empty line, should ignore the empty line
./querier ../tsetest/letters3 test/letters.Index <<EOF
and yeehaw
yeeHAW or
yee and or haw

yee-haw
-yee to my. haw$
EOF

# tests several kinds of sequences
./querier ../tsetest/scrape2 test/scrape2.Index <<EOF
Europe travel
Europe and travel
Europe or travel
TSE
europe travel or bird scramble
EOF
