#ifndef CLLIST_H
#define CLLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype_t;

typedef struct CLNode {
    Elemtype_t data;
    struct CLNode* next;
} CLNode_t;

CLNode_t* CLList_Create();
CLNode_t* CLList_NewNode(Elemtype_t data);
int CLList_Length(CLNode_t* Head);
void CLList_Traverse(CLNode_t* Head);
bool CLList_TailInsert(CLNode_t* Head, Elemtype_t data);
bool CLList_HeadInsert(CLNode_t* Head, Elemtype_t data);
bool CLList_HeadDelete(CLNode_t* Head);
bool CLList_TailDelete(CLNode_t* Head);
bool CLList_DelDest_Place(CLNode_t* Head, int dest);
bool CLList_DelDest_Value(CLNode_t* Head, Elemtype_t data);
bool CLList_InDest_Place(CLNode_t* Head, Elemtype_t data, int dest);
bool CLList_InDest_BeforeValue(CLNode_t* Head, Elemtype_t data, int dest);
bool CLList_InDest_AfterValue(CLNode_t* Head, Elemtype_t data, int dest);

#endif 