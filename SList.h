#pragma once
typedef struct _SListItem{
	void* Data;
	struct _SListItem* Next;
	void (*Dispose)(struct _SListItem*);
} SListItem;

SListItem* SListItem_New();
void SListItem_Dispose(SListItem*);

typedef enum _SListError{
	SListError_NoError,
	SListError_IndexOutOfRange
} SListError;

typedef struct _SList{
	SListItem* First;
	void (*Add)(struct _SList*,void* data);
	int (*Count)(struct _SList*);
	SListItem* (*At)(struct _SList*,int);
	void (*RemoveAt)(struct _SList*,int);
	void (*ForEach)(struct _SList*,void(*fp)(SListItem*,void*), void* userdata);
	void (*Dispose)(struct _SList*);
} SList;

SList* SList_New();
void SList_Add(SList*,void*);
int SList_Count(SList*);
void SList_Count_ForEach_Func(SListItem*,void*);
SListItem* SList_At(SList*, int);
void SList_RemoveAt(SList*, int);
void SList_ForEach(SList*,void(*)(SListItem*,void*),void*);
void SList_Dispose(SList*);
void SList_Dispose_ForEach_Func(SListItem*,void*);
