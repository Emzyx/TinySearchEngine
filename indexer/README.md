# Carlos Yepes 
# CS50 Spring 2019


## TESTING:

It's pretty easy to test everything.

**You can instantly call _make test_ and it will compile the files and test everything**

You can also redirect the output using **make test &> testing.out**
But I will be providing ***testing.out*** so you don't HAVE to do that.
You can also test using valgrind by uncommenting VAL on the indexer `Makefile`
(Although it seems to take super long in the wiki and scrap tests)

So it doesnt take forever, you could only run valgrind on the letters test which you can do by calling **make** if you havent already and then **make testL**
Although for your convenience (and running it will take some time), I'll use valgrind on all the tests and redirect them to **testing.out**

When youre done:

**You can eradicate everything that was done by the testing by calling _make cleanall_ which cleans everything within indexer, libcs50 and common.**

It just doesn't delete the testing.out
And youre done.

## Assumptions

We assume that the files in the directory given to the indexer are crawler created files.

## ALSO KNOW

There will also be some commented out lines that use crawler, but this was because I used to call crawler IN my tests, so pay them no mind now.

At the end of indexing, **IF** _make test_ wasnt redirected, it will make a notification sound after every test is complete.
Pay no attention to the name of the function `fuckMeUp` which makes the sound and sleep for a second. :)
Its kind of basically a shitpost.

