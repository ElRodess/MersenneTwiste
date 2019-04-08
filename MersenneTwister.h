#ifndef __include_MersenneTwister_h__
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define __include_MersenneTwister_h__
#define UPPER_MASK		0x80000000
#define LOWER_MASK		0x7fffffff
#define TEMPERING_MASK_B	0x9d2c5680 
#define TEMPERING_MASK_C	0xefc60000


void twist();
void seed_mt(int seed);
u_int32_t extract_number();
#endif 
