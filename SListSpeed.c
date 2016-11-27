#include "SList.h"
#include <time.h>
#include <stdio.h>
const int nloop = 1024;
int main()
{
	SList* list = SList_New();
	int array[nloop];
	{
		int i;
		clock_t t = clock();
		for(i = 0;i < nloop;i++){
			int data = 255;
			list->Add(list,&data);
		}
		printf("SList: %f sec.\n",(clock() - t)/(double)CLOCKS_PER_SEC);
	}

	{
		int i;
		clock_t t = clock();
		for(i = 0;i < nloop;i++){
			int data = 255;
			array[i] = data;
		}
		printf("Array: %f sec.\n",(clock() - t)/(double)CLOCKS_PER_SEC);

	}
	return 0;
}
