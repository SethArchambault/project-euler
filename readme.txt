# Project Euler

I'm attempting to do this while practicing Mike Acton's technique illustrated here:
https://www.youtube.com/watch?v=GPpD4BBtA1Y

# Project 1

Tags: c programming, data oriented development, performance

Using data oriented principles outlined by Mike Acton, I've made this as efficient as I can.

The way I arrived upon this, was by looking at the standard solution (n % 5 == 0 || n % 3 == 0) and then creating integers "match" and "no_match".

You'll get these results:
match: 467
no_match: 533

Meaning, the standard solution is only 46.7% efficient. 
This becomes even more easy to understand if you print "1" every time you match, and "0" every time you don't match. Very low data density.

But what also becomes evident is that there is a pattern! If you count how often the 0's repeat you'll find this pattern:

3,2,1,3,1,2,3,3,2,1,3,1,2,3,3 etc..

So instead of incrementing by 1 and throwing away 52.3% of the results (basically doing nothing productive most of the time) You can increment by the next number in the cycle, and just iterate through that, yeilding 100% efficiency.  Which is not to say this couldn't be optimized more using data oriented techniques, but that's as far as I was able to take it.

The result is 4 times faster. (.0027 ms as compared to .0113 ms)

````
#include<stdio.h>
int main() {
  int sum 
  int cycle[] = {3,2,1,3,1,2,3}; 
  int cycle_i = -1;
  int cycle_len = sizeof (cycle) / sizeof (int);
  for (int n = 0; n < num; n += cycle[cycle_i])
  {
    sum += n;
    ++cycle_i;
    if (cycle_i >= cycle_len) cycle_i = 0;
  }
  printf("sum: %d", sum);
return 0;
}
````
