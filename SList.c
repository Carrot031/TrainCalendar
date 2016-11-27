#include "SList.h"

#include <stdlib.h>

SListItem* SListItem_New()
{
	SListItem* ret = malloc(sizeof(SListItem));
	ret->Data = NULL;
	ret->Next = NULL;
	ret->Dispose = SListItem_Dispose;
	return ret;
}

/* Note that this don't free Data and Next. */
void SListItem_Dispose(SListItem* this)
{
	free(this);
}

SList* SList_New()
{
	SList* ret = malloc(sizeof(SList));
	ret->First = NULL;
	ret->Add = SList_Add;
	ret->Count = SList_Count;
	ret->At = SList_At;
	ret->RemoveAt = SList_RemoveAt;
	ret->ForEach = SList_ForEach;
	ret->Dispose = SList_Dispose;
	return ret;
}

void SList_Add(SList* this, void* data)
{
	SListItem* item = SListItem_New();
	item->Data = data;

	if(!this->First){
		this->First = item;
		return;
	}

	SListItem* i = this->First;
	while(1)
	{
		/* loop until Next == NULL */
		if(i->Next){
			i = i->Next;
		}else{
			break;
		}
	}

	i->Next = item;
}

int SList_Count(SList* this)
{
	int count = 0;
	this->ForEach(this,SList_Count_ForEach_Func,&count);
	return count;
}

void SList_Count_ForEach_Func(SListItem* data,void* userdata)
{
	int* count = userdata;
	(*count)++;
}

SListItem* SList_At(SList* this,int index)
{
	if(index < 0 || index >= this->Count(this)){
		return NULL;
	}

	SListItem* i = this->First;
	int count;
	for(count = 0; count < index; count++){
		i = i->Next;
	}
	return i;
}

void SList_RemoveAt(SList* this, int index)
{
	SListItem* to_remove = this->At(this,index);
	if(!to_remove){
		return;
	}

	to_remove->Dispose(to_remove);

	SListItem* next = to_remove->Next;
	SListItem* prev = this->At(this,index - 1);

	if(!prev){
		this->First = next;
		return;
	}else{
		prev->Next = next;
	}
}

void SList_ForEach(SList* this,void(*fp)(SListItem*,void*),void* userdata)
{
	if(!fp){
		return;
	}

	if(!this->First){
		return;
	}

	SListItem* i = this->First;
	do{
		SListItem* next = i->Next;
		fp(i,userdata);
		i = next;
	}while(i);
}

void SList_Dispose(SList* this)
{
	this->ForEach(this,SList_Dispose_ForEach_Func,NULL);
	free(this);
}

void SList_Dispose_ForEach_Func(SListItem* item, void* userdata)
{
	item->Dispose(item);
}
