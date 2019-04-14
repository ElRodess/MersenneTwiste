#include "CrackSeed.h"

u_int32_t routine(u_int32_t val2, u_int32_t val1)
{
	//printf("V1 :  %u |V2 : %u \n",val1,val2);
	u_int32_t seed= 0;
	u_int32_t try1 = 0;
	u_int32_t try2 = 0;
	while(try1 != val1 && try2 != val2)
	{
		usleep(rand()%1000000 +40000);
		seed = time(NULL);
		seed_mt(seed);
		try1 = extract_number();
		try2 = extract_number();
		printf("seed = %u : %u et %u \n",seed,try1,try2);
	}
	return seed;
}

void crack_seed()
{
	srandom(time(NULL)+getpid());
	u_int32_t attendu = time(NULL) + 10;
	seed_mt(attendu);
	u_int32_t solution = routine(extract_number(),extract_number());
	printf("attendu : %u , solution : %u \n",attendu,solution);
}

