#include "Random.h"
#include <time.h>
#include <stdlib.h>
int GetRandom(int min,int max)
{
	static int initialized = 0;
	if(initialized == 0){
		initialized = 1;
		srand((unsigned int)time(NULL));
	}
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}
