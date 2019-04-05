#include "MersenneTwister.h"

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
