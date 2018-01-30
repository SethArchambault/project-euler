#include <stdio.h>
#include <time.h>
#include <assert.h>

#define LIMIT 4000000
#define NUM 430 

typedef struct {
	int sum;
	int cnt;
	int hit;
	int miss;
	int debug_i;
	int debug[NUM];
} result;

result fib()
{
	result r;
	r.sum = 0;
	long int val_1 = 1;
	long int val_2 = 2;
	long int val_3 = 0;
	r.debug[0] = 1;
	r.debug[1] = 2;
	r.debug_i = 2;
	r.sum = 2;
	r.cnt = 0;
	r.hit = 0;
	r.miss = 0;
	while(1)
	{
		++r.cnt;
		val_3 = val_1 + val_2;
		if (val_3 >= LIMIT) break;
		assert(r.debug_i < NUM);
		if (val_3 % 2 == 0)
		{
			r.sum += val_3;
			r.debug[r.debug_i] = val_3;
			++r.hit;
		}
		else
		{
			r.debug[r.debug_i] = -1;
			++r.miss;
		}
		val_1 = val_2;
		val_2 = val_3;
		++r.debug_i;
	}
	return r;
}


/* SKIP the first two results of each result, get the third */
result fib_skip()
{
	result r;
	r.sum = 0;
	long int val_1 = 1;
	long int val_2 = 2;
	long int val_3 = 0;
	r.debug[0] = 1;
	r.debug[1] = 2;
	r.debug_i = 2;
	r.sum = 2;
	r.cnt = 0;
	r.hit = 0;
	r.miss = 0;
	while(1)
	{
		++r.cnt;
		val_3 = val_1 + val_2; // skip
		val_1 = val_2;
		val_2 = val_3;
		val_3 = val_1 + val_2; // skip
		val_1 = val_2;
		val_2 = val_3;
		val_3 = val_1 + val_2; // get
		if (val_3 >= LIMIT) break;

		r.sum += val_3;
		assert(r.debug_i < NUM);
		r.debug[r.debug_i] = val_3;
		++r.hit;
		val_1 = val_2;
		val_2 = val_3;
		++r.debug_i;
	}
	return r;
}

/* the original thing but with arrays */
result fib_array()
{
	result r;
	r.sum = 0;
	r.debug[0] = 1;
	r.debug[1] = 2;
	r.debug_i = 2;
	r.sum = 2;
	r.cnt = 0;
	r.hit = 0;
	r.miss = 0;
	long int v[NUM];
	v[0] = 1;
	v[1] = 2;
	int v_i = 2;
	while(1)
	{
		++r.cnt;
		v[v_i] = v[v_i - 1] + v[v_i -2];
		if (v[v_i]>= LIMIT) break;
		assert(v_i < NUM);
		assert(r.debug_i < NUM);
		if (v[v_i] % 2 == 0)
		{
			r.debug[r.debug_i] = v[v_i];
			r.sum += v[v_i];
			++r.hit;
		}
		else
		{
			r.debug[r.debug_i] = -1;
			++r.miss;
		}
		++v_i;
		++r.debug_i;
	}
	return r;
}

result fib_array_skip()
{
	result r;
	r.sum = 0;
	r.debug[0] = 1;
	r.debug[1] = 2;
	r.debug_i = 2;
	r.sum = 2;
	r.cnt = 0;
	r.hit = 0;
	r.miss = 0;
	int v[NUM];
	v[0] = 1;
	v[1] = 2;
	int v_i = 1;
	while(1)
	{
		++r.cnt;
		v_i += 3;
		v[v_i-1] = v[v_i - 3] + v[v_i -4] + v[v_i -3];
		v[v_i] = v[v_i - 1] + v[v_i - 3] + v[v_i -4];
		if (v[v_i]>= LIMIT) break;
		assert(v_i < NUM);
		assert(r.debug_i < NUM);
		r.debug[r.debug_i] = v[v_i];
		r.sum += v[v_i];
		++r.hit;
		++r.debug_i;
	}
	return r;
}


int main()
{
	clock_t time_1 = clock();
	//result r = fib();
	result r = fib_array_skip();
	clock_t time_2 = clock();
	double time_spent = (double)(time_2 - time_1) / CLOCKS_PER_SEC;
	printf("\n%f ms\n", time_spent);
	printf("hit: %d, miss: %d, efficiency: %f\n", r.hit, r.miss, (double)r.hit / (r.hit + r.miss));
	printf("correct: 4613732 actual: %d, cnt: %d\n", r.sum, r.cnt);
	for (int n = 0; n < r.debug_i; ++n)
	{
		printf("%d ", r.debug[n]);
	}
}
