#include <stdio.h>
#include "SList.h"

void foreach(SListItem* item,void* userdata)
{
	printf("%d\n",*((int*)(item->Data)));
}

int main()
{
	printf("Checking SList.\n");

	SList* slist = SList_New();
	int a,b,c;
	a = 123;
	b = 456;
	c = 789;
	printf("Allocated *slist at %p\n",slist);

	slist->Add(slist,&a);
	printf("Added int a to slist.\n");
	printf("slist->First is %p\n",slist->First);

	slist->Add(slist,&b);
	slist->Add(slist,&c);
	printf("Added two other pointers to slist.\n");

	printf("Iterating:\n");
	slist->ForEach(slist,foreach,NULL);

	int i;
	for(i = 0; i < 3; i++){
		printf("At(%d):%d\n",i,*((int*)slist->At(slist,i)->Data));
	}

	printf("Length is %d.\n",slist->Count(slist));

	slist->RemoveAt(slist,0);
	printf("Removed index 0.\n");
	printf("Iterating:\n");
	slist->ForEach(slist,foreach,NULL);

	slist->RemoveAt(slist,0);
	printf("Removed index 0.\n");
	printf("Iterating:\n");
	int d = 114514;
	slist->Add(slist,&d);
	slist->ForEach(slist,foreach,NULL);

	slist->Dispose(slist);
	printf("Disposed.\n");

	return 0;
}
