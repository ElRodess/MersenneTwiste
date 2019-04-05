#include "MersenneTwister.h"
// Create a length n array to store the state of the generator

 // Initialize the generator from a seed
 u_int32_t MT[624] = {0};
u_int32_t indx = 0;
  // Generate the next n values from the series x_i 
 void twist() {
     for(int i=0;i<624;i++){
         u_int32_t x = (MT[i] & UPPER_MASK) + (MT[(i+1) % 624] & LOWER_MASK);
         MT[i] = MT[(i + 397) % 624] ^ (x >> 1);
         if( (x % 2) != 0 ){ // lowest bit of x is 1
			MT[i] ^= 0x9908b0df;
		}
     }
 } 
 
 void seed_mt(int seed) {
     int i;
     indx = 0 ;
     MT[0] = seed & 0xffffffff;
     for(i=1;i<624;i++) { // loop over each element
         MT[i] = (0x6c078965 * (MT[i-1] ^ (MT[i-1] >> (32-2))) + i) & 0xffffffff;
     }
 }
 
 // Extract a tempered value based on MT[indx]
 // calling twist() every n numbers
 u_int32_t extract_number() {
     if (indx == 0){
         twist();
     }
       u_int32_t y = MT[indx];
     y ^= ((y >> 11) /*& 0xffffffff*/);
     y ^= ((y << 7) & TEMPERING_MASK_B);
     y ^= ((y << 15) & TEMPERING_MASK_C);
     y ^= (y >> 18);
 
     indx = (indx + 1 )%624;
     return (y) ; 
 }
 
