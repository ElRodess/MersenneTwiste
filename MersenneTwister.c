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
#define a	0x9908B0DF
#define s	17
#define t	37 
#define u	11
#define d	0xffffffff
#define l	18
#define f	1812433253

int MT[n];
int indx = n+1;
 // Initialize the generator from a seed
 
  // Generate the next n values from the series x_i 
 void twist() {
     for(int i=0;i<=n-1;i++){
         int x = (MT[i] & UPPER_MASK)
                   + (MT[(i+1) % n] & LOWER_MASK) ;
         int xA = x >> 1 ;
         if( (x % 2) != 0 ){ // lowest bit of x is 1
             xA = xA ^ a;
         }
         MT[i] = MT[(i + m) % n] ^ xA ;
     }
     indx = 0 ;
 } 
 
 void seed_mt(int seed) {
     int i;
     indx = n ;
     MT[0] = seed;
     for(i=1;i<=n-1;i++) { // loop over each element
         MT[i] = (f * (MT[i-1] ^ (MT[i-1] >> (w-2))) + i) & d;
     }
 }
 
 // Extract a tempered value based on MT[indx]
 // calling twist() every n numbers
int extract_number() {
     if (indx >= n ){
         if(indx > n ){
           printf("error : Generator was never seeded \n");
           // Alternatively, seed with constant value; 5489 is used in reference C code[46]
         }
         twist();
     }
 
     int y = MT[indx];
     y ^= ((y >> u));
     y ^= ((y << s) & TEMPERING_MASK_B);
     y ^= ((y << t) & TEMPERING_MASK_C);
     y ^= (y >> l);
 
     indx = indx + 1 ;
     return (y) ; 
 }
 


int main(int argc, char **argv)
{
	seed_mt(1337);
	for(int i=0; i<100; i++) {
    printf("%f\n", extract_number());
  }
}
