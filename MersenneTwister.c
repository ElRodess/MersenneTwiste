#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Create a length n array to store the state of the generator

#define UPPER_MASK		0x80000000
#define LOWER_MASK		0x7fffffff
#define TEMPERING_MASK_B	0x9d2c5680 
#define TEMPERING_MASK_C	0xefc60000
#define w	32 
#define n	624
#define m	397
#define r	31
#define a	0x9908b0df
#define s	7
#define t	15
#define u	11
#define d	0xffffffff
#define l	18
#define f	0x6c078965

u_int32_t MT[n] = {0};
u_int32_t indx = 0;
 // Initialize the generator from a seed
 
  // Generate the next n values from the series x_i 
 void twist() {
     for(int i=0;i<n;i++){
         u_int32_t x = (MT[i] & UPPER_MASK) + (MT[(i+1) % n] & LOWER_MASK);
         MT[i] = MT[(i + m) % n] ^ (x >> 1);
         if( (x % 2) != 0 ){ // lowest bit of x is 1
			MT[i] ^= 0x9908b0df;
		}
     }
 } 
 
 void seed_mt(int seed) {
     int i;
     indx = 0 ;
     MT[0] = seed & d;
     for(i=1;i<n;i++) { // loop over each element
         MT[i] = (f * (MT[i-1] ^ (MT[i-1] >> (w-2))) + i) & d;
     }
 }
 
 // Extract a tempered value based on MT[indx]
 // calling twist() every n numbers
 u_int32_t extract_number() {
     if (indx == 0){
         twist();
     }
       u_int32_t y = MT[indx];
     y ^= ((y >> u) /*& d*/);
     y ^= ((y << s) & TEMPERING_MASK_B);
     y ^= ((y << t) & TEMPERING_MASK_C);
     y ^= (y >> l);
 
     indx = (indx + 1 )%n;
     return (y) ; 
 }
 


int main(int argc, char **argv)
{
	int i = 0;
	seed_mt(1337);
	for( i=0; i<10; i++) {
    printf("%u\n", extract_number());
}
    printf(" \n \n");
    seed_mt(1338);
	for(i=0; i<10; i++) {
    printf("%u\n", extract_number());
  }
  
  printf(" \n \n");
    seed_mt(1337);
	for(i=0; i<10; i++) {
    printf("%u\n", extract_number());
  }
}
