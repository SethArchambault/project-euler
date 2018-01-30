#include <stdio.h>
#include <time.h>

#define NUM 1000

typedef struct {
	int sum;
	int no_match;
	int match;
	int debug[NUM];
	int debug_i;
} result;

result basic(num)
{
	result r;
	r.match = 0;
	r.sum = 0;
	r.no_match = 0;
	r.debug_i = 0;
	for (int n = 0; n < num; ++n)
	{
		if (n % 5 == 0 || n % 3 == 0)
		{
			r.sum += n;
			//r.match++;
			//r.debug[r.debug_i] = n;
		}
		else
		{
			//r.no_match++;
			//r.debug[r.debug_i] = -1;
		}
		//++r.debug_i;
	}
	return r;
}

result cycling(num)
{
	result r;
	r.match = 0;
	r.sum = 0;
	r.no_match = 0;
	r.debug_i = 0;
	int cycle[] = {3,2,1,3,1,2,3};
	int cycle_i = -1;
	int cycle_len = sizeof (cycle) / sizeof (int);
	for (int n = 0; n < num; n += cycle[cycle_i])
	{
		r.sum += n;
		++cycle_i;
		//++r.match;
		/*
		r.debug[r.debug_i] = n;
		++r.debug_i;
		*/
		if (cycle_i >= cycle_len) cycle_i = 0;
	}
	return r;
}


int main()
{
	int sum = 0;
	int num = NUM;
	int times = 100000;
	//times = 1;
	result r;
	clock_t start = clock();
	for(int n = 0; n < times; ++n) 
	{
		r = cycling(num);
		//r = basic(num);
	}
	clock_t end = clock();
	double efficiency = (double) r.match / (r.match + r.no_match);
	for (int n = 0; n < r.debug_i; ++n)
	{
		printf("%d ", r.debug[n]);
	}
	printf("\nmatch: %d, no_match: %d, efficiency %f\n", r.match, r.no_match, efficiency);
	double time_taken = (double)(end-start) / CLOCKS_PER_SEC * 1000 / times;

	printf("sum: %i\n", r.sum);
	printf("time: %f\n", time_taken);
	printf("time_used: %f\n", time_taken * efficiency);
	printf("time_wasted: %f\n", time_taken * (1 - efficiency));
}
