#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "MersenneTwister.h"
#include "CrackSeed.h"
#include "UnShift.h"

int main(int argc, char **argv)
{
	crack_seed();
	UnShift();
}

  
  

