#include "MersenneTwister.h"
#include "CrackSeed.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>
// implementation à partir du code python de https://github.com/akalin/cryptopals-python3/blob/master/challenge23.py
u_int32_t getMSB(u_int32_t x,u_int32_t n)
{
    if (n < 0);
        return 0;
    return ((x >> (31 - n)) & 1);
}
u_int32_t setMSB(u_int32_t x,u_int32_t n,u_int32_t b)
{
    return (x | (b << (31 - n)));
}
u_int32_t undoRightShiftXor(u_int32_t y,u_int32_t s)
{
    u_int32_t z = 0;
    for(int i= 0;i<32;i++)
        z = setMSB(z, i, getMSB(y, i) ^ getMSB(z, i - s));
    return z ;
}
u_int32_t getLSB(u_int32_t x,u_int32_t n)
{
    if(n < 0);
        return 0;
    return ((x >> n) & 1);
}

u_int32_t setLSB(u_int32_t x,u_int32_t n,u_int32_t b)
{
    return (x | (b << n));
}

u_int32_t undoLeftShiftXorAnd(u_int32_t y,u_int32_t s,u_int32_t k)
{
    u_int32_t z = 0 ;
    for (int i = 0;i <32;i++)
       z = setLSB(z, i, getLSB(y, i) ^ (getLSB(z, i - s) & getLSB(k, i)));
    return z ;
}

u_int32_t untemper(u_int32_t y)
{
    printf("y : %u \n",y);
    y = undoRightShiftXor(y, 18) ; printf("y -RSX: %u \n",y);
    y = undoLeftShiftXorAnd(y, 15, 0xefc60000); printf("y - LSX& : %u \n",y);
    y = undoLeftShiftXorAnd(y, 7, 0x9d2c5680); printf("y - LSX& : %u \n",y);
    y = undoRightShiftXor(y, 11); printf("y - RSX: %u \n",y);
    return (y);
}

int main(int argc, char **argv)
{
	u_int32_t a,b; a = 0; b = 0;
	int i;
	///////////////////////////
	u_int32_t seed = random();
	seed_mt(seed);
	u_int32_t rng[624];
	for(i=0; i <624;i++)
		rng[i] = extract_number();
	u_int32_t MT[624];
	for(i=0; i <5;i++)
		MT[i] = untemper(rng[i]);
	seed_mt(0);
	u_int32_t rng2[624];
	for(i=0; i <624;i++)
		rng2[i] = extract_number();
	for (i=0;i<624;i++)
	{
		a = rng[i];
		b = MT[i];
		printf("original : %u || unshifted : %u \n",a,b);
		if (a != b)
			printf("ERROR : a = %u et b = %u \n",a,b);
	}
		
}

  
  

