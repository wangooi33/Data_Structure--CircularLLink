/**
  * @file name:CLLink.c
  * @brief    :The basic function of circular single linked list
  * @author   :i33akq@163.com
  * @date     :2025/06/24
  * @version  :1.0
  * @note     :tail->next = Head->next ,the tail node points to the start node.
  * @CopyRight (C)   2024-2025   i33akq@163.com   ALL Right Reseverd
*/

#include "CLLink.h"

/**
  * @function name: CLList_Create
  * @brief        : Create a circular linked list with a head node
  * @param        : None
  * @retval       : Returns pointer to head node
  * @version      : 1.0
  * @note         : Initialize as a circular structure, and the head node does not store valid data.
*/
CLNode_t* CLList_Create() {
	CLNode_t* Head = (CLNode_t*)malloc(sizeof(CLNode_t));
	if (!Head) return NULL;

	Head->next = Head;  
	return Head;
}

/**
  * @function name: CLList_NewNode
  * @brief        : Create a new node
  * @param        : 
  * 				@Data: the value to store in the new node
  * @retval       : Pointer to the newly created node
  * @version      : 1.0
  * @note         : None
*/
CLNode_t* CLList_NewNode(Elemtype_t Data) {
    CLNode_t* NewNode = (CLNode_t*)malloc(sizeof(CLNode_t));
    if(!NewNode){
		fprintf(stderr, "calloc error,errno:%d,%s\n",errno,strerror(errno));
		exit(CALLOC_FAILURE);
	}
    NewNode->data = Data;
    NewNode->next = NULL;
    return NewNode;
}

/**
  * @function name: CLList_GetTail
  * @brief        : get the tail node
  * @param        : 
  * 				@Data: the value to store in the new node
  * @retval       : Pointer to the tail node
  * @version      : 1.0
  * @note         : None
*/
CLNode_t *CLList_GetTail(CLNode_t *Head)
{
	if(!Head) return NULL;
	CLNode_t *tail = Head->next;
	while(tail->next!=Head->next)
	{
		tail=tail->next;
	}
	return tail; 
}

/**
  * @function name: CLList_Len
  * @brief        : calculate the length of the list 
  * @param        : 
  * 				@Head: the list header address
  * @retval       : the length of list
  * @version      : 1.0
  * @note         : None
*/
int CLList_Len(CLNode_t *Head)
{
	if(!Head || Head->next == Head) return 0;
	int cnt = 1;
	CLNode_t *current = Head->next;
	while(current->next != Head->next)
	{
		current = current->next;
		cnt++;
	}
	return cnt;
}

/**
  * @function name: CLList_Traverse
  * @brief        : Traverse and print the list
  * @param        : 
  * 				@Head: the list header address
  * @retval       : void
  * @version      : 1.0
  * @note         : None
*/
void CLList_Traverse(CLNode_t* Head) {
    if (IS_EMPTY_LIST(Head)) {
        printf("List is empty.\n");
        return;
    }
    CLNode_t* current = Head->next;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != Head->next); 
    printf("(%d 循环)\n",(Head->next)->data);
    return; 
}

/**
  * @function name: CLList_HeadInsert
  * @brief        : Insert node after head (head insert)
  * @param        :
  *                 @Head: the list header address
  *                 @Data: the data field of a circular linked list
  * @retval       : Insert successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_HeadInsert(CLNode_t* Head, Elemtype_t Data) {
    if (!Head) return false;
    CLNode_t* NewNode = CLList_NewNode(Data);
	
    if (Head->next == Head) {
        Head->next = NewNode;
		NewNode->next = NewNode;
		return true;
    } 
	else {
        CLNode_t *tail = CLList_GetTail(Head);
		NewNode->next = Head->next;
		Head->next = NewNode;
		tail->next = NewNode; 
		return true;
    }
}

/**
  * @function name: CLList_TailInsert
  * @brief        : Insert node at the end of the list
  * @param        :
  *                @Head: the list header address
  *                @Data: the data field of a circular linked list
  * @retval       : Insert successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_TailInsert(CLNode_t* Head, Elemtype_t Data) {
    if (!Head) return false;
    CLNode_t* NewNode = CLList_NewNode(Data);

    if (Head->next == Head) {
        Head->next = NewNode;
		NewNode->next = NewNode;
		return true;
    }
	else{
		CLNode_t *tail = CLList_GetTail(Head);
		NewNode->next = tail->next;
		tail->next = NewNode;
		return true;
	}
}

/**
  * @function name: CLList_InDest_Place
  * @brief        : Insert a node at a specific position in the circular linked list (1-based index)
  * @param        : 
  *                 @Head: the list header address
  *                 @Data: the data to insert
  *                 @Dest: the position to insert (starting from 1)
  * @retval       : true if insert successful, false otherwise
  * @version      : 1.0
  * @note         : If the list is empty, the inserted node becomes the first and loops to itself.
  *                 If inserted at position 1, Head->next and tail's next pointer will be updated.
*/
bool CLList_InDest_Place(CLNode_t* Head, Elemtype_t Data, int Dest) {
	if (!Head || Dest <= 0) return false;
    CLNode_t* NewNode = CLList_NewNode(Data);
	int len = CLList_Len(Head);
	if(Dest > len + 1) return false;

	CLNode_t *tail = CLList_GetTail(Head);

	if(Dest == 1)
	{
		NewNode->next = Head->next;
		tail->next = NewNode;
		Head->next = NewNode;
		return true;
	}
	else if(Dest == len + 1)
	{
		NewNode->next = Head->next;
		tail->next = NewNode;
		return true;
	}
	CLNode_t* prev = Head->next;
	for (int i = 1; i < Dest - 1; ++i) {
		prev = prev->next;
	}
	NewNode->next = prev->next;
	prev->next = NewNode;
	return true;
}

/**
  * @function name: CLList_InDest_BeforeValue
  * @brief        : Insert a node before the first node with the specified value
  * @param        : 
  *                 @Head: the list header address
  *                 @Data: the data to insert
  *                 @Dest: the target value to match
  * @retval       : true if insert successful, false otherwise
  * @version      : 1.0
  * @note         : If the matching node is the head node, the inserted node will become the new head (Head->next).
  *                 Tail node's next pointer will also be updated accordingly.
*/
bool CLList_InDest_BeforeValue(CLNode_t* Head, Elemtype_t Data, int Dest) {
	if (!Head || IS_EMPTY_LIST(Head)) return false;

	CLNode_t* NewNode = CLList_NewNode(Data);
	CLNode_t* prev = NULL;
    CLNode_t* current = Head->next;
    CLNode_t* tail = CLList_GetTail(Head);

    do {
        if (current->data == Dest) {
            if (prev == NULL) {
                NewNode->next = Head->next;
                Head->next = NewNode;
                tail->next = NewNode;
            } else {
                NewNode->next = current;
                prev->next = NewNode;
            }
            return true;
        }
        prev = current;
        current = current->next;
    } while (current != Head->next);
    return false; 
}

/**
  * @function name: CLList_InDest_AfterValue
  * @brief        : Insert a node after the first node with the specified value
  * @param        : 
  *                 @Head: the list header address
  *                 @Data: the data to insert
  *                 @Dest: the target value to match
  * @retval       : true if insert successful, false otherwise
  * @version      : 1.0
  * @note         : If the node with the given value is found, the new node is inserted immediately after it.
*/
bool CLList_InDest_AfterValue(CLNode_t* Head, Elemtype_t Data, int Dest) {
	if (!Head || IS_EMPTY_LIST(Head)) return false;

	CLNode_t* NewNode = CLList_NewNode(Data);
	CLNode_t* current = Head->next;

	do {
        if (current->data == Dest) {
            NewNode->next = current->next;
            current->next = NewNode;
            return true;
        }
        current = current->next;
    } while (current != Head->next);
	return false; 
}

/**
  * @function name: CLList_HeadDelete
  * @brief        : Delete the first valid node (after Head)
  * @param        : 
  * 				@Head: the list header address
  * @retval       : Delete successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_HeadDelete(CLNode_t* Head) {
	if (!Head || IS_EMPTY_LIST(Head)) return false;

  	CLNode_t* toDelete = Head->next;

	if(toDelete->next == toDelete)
	{
		Head->next = Head;
	}
	else
	{
		CLNode_t *tail = CLList_GetTail(Head);
		tail->next = toDelete->next;
		Head->next = toDelete->next;
	}
	toDelete->next = NULL;
	free(toDelete);
	return true;
}


/**
  * @function name: CLList_TailDelete
  * @brief        : Delete the last valid node (before Head)
  * @param        : 
  * 				@Head: the list header address
  * @retval       : Delete successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_TailDelete(CLNode_t* Head) {
    if (!Head || IS_EMPTY_LIST(Head)) return false;
	
	CLNode_t *toDelete = Head->next;
	CLNode_t *prev = Head;

	if (toDelete->next == toDelete) {
        Head->next = Head;
        toDelete->next = NULL;
        free(toDelete);
        return true;
    }

	while(toDelete->next != Head->next)
	{
		prev = toDelete;
		toDelete = toDelete->next;
	}
	prev->next = Head->next;
	toDelete->next = NULL;
    free(toDelete);
    return true;
}

/**
  * @function name: CLList_DelDest_Place
  * @brief        : Delete a node by its position (1-based index)
  * @param        : 
  *                 @Head: the list header address
  *                 @Dest: the position of the node to be deleted
  * @retval       : true if delete successful, false otherwise
  * @version      : 1.0
  * @note         : If dest is 1, deletes the head node (first valid node);
  *                 returns false if the position is invalid or list is empty
*/
bool CLList_DelDest_Place(CLNode_t* Head, int Dest) {
  	if (!Head || IS_EMPTY_LIST(Head) || Dest < 1)  return false;
	int len = CLList_Len(Head);
	if(Dest > len)  return false;

	CLNode_t *prev = Head;
    CLNode_t *toDelete = Head->next;

    if (Dest == 1) 
	{
        if (toDelete->next == toDelete) 
		{
            Head->next = Head;
            toDelete->next = NULL;
            free(toDelete);
            return true;
        }

        CLNode_t* tail = CLList_GetTail(Head);
        Head->next = toDelete->next;
        tail->next = Head->next;
    }
    else 
	{
        for (int i = 1; i < Dest; ++i) 
		{
            prev = toDelete;
            toDelete = toDelete->next;
        }
        prev->next = toDelete->next;
    }
	
	toDelete->next = NULL;
	free(toDelete);
	return true;
}

/**
  * @function name: CLList_DelDest_Value
  * @brief        : Delete the first node whose data field matches the specified value
  * @param        : 
  *                 @Head: the list header address
  *                 @Data: the value to be matched for deletion
  * @retval       : true if delete successful, false otherwise
  * @version      : 1.0
  * @note         : If the matched node is the head node (first valid node),
  *                 the function calls CLList_HeadDelete; returns false if not found
*/
bool CLList_DelDest_Value(CLNode_t* Head, Elemtype_t Data) {
  	if (!Head || IS_EMPTY_LIST(Head))  return false;
	
	CLNode_t *toDelete = Head->next;
	CLNode_t *prev = Head;
	CLNode_t *tail = CLList_GetTail(Head);

	if(toDelete->data == Data)
	{
		if(toDelete->next == toDelete)
		{
			Head->next = Head;
			toDelete->next = NULL;
            free(toDelete);
            return true;
		}
		
		tail->next = Head->next;
		Head->next = toDelete->next;
	}
	else
	{
		while(toDelete->next != Head->next)
		{
			if(toDelete->data == Data)  break;
			prev = toDelete;
			toDelete =toDelete->next;
		}
		if(toDelete->next == Head->next && toDelete->data != Data)  return false;
		prev->next = toDelete->next;
	}

	toDelete->next = NULL;
    free(toDelete);
    return true;
}

/**
  * @function name: CLList_Destroy
  * @brief        : Destroy the entire linked list
  * @param        : 
  *                 @Head: the list header address
  * @retval       : true if delete successful, false otherwise
  * @version      : 1.0
  * @note         : none
*/
bool  CLList_Destroy(CLNode_t* Head){
	if(!Head) return true;
	if(IS_EMPTY_LIST(Head))
	{
		free(Head);
		return true;
	}

	CLNode_t *current = Head->next;
	CLNode_t *next;
	while(current->next != Head->next)
	{
		next = current->next;
		current->next = NULL;
		free(current);
		current = next;
	}
	free(Head);
	return true;
}