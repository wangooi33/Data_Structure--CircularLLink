/**
  * @file name:CLLink.h
  * @brief    :Functional interface design
  * @author   :i33akq@163.com
  * @date     :2025/06/24
  * @version  :1.0
  * @note     :none
  * @CopyRight (C)   2024-2025   i33akq@163.com   ALL Right Reseverd
*/

#ifndef CLLIST_H
#define CLLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define IS_EMPTY_LIST(Head) ((Head) == NULL || (Head)->next == (Head))
#define CALLOC_FAILURE 1

typedef int Elemtype_t;

typedef struct CLNode {
    Elemtype_t data;
    struct CLNode* next;
} CLNode_t;

/**
  * @function name: CLList_Create
  * @brief        : Create a circular linked list with a head node
  * @param        : None
  * @retval       : Returns pointer to head node
  * @version      : 1.0
  * @note         : Initialize as a circular structure, and the head node does not store valid data.
*/
CLNode_t* CLList_Create();

/**
  * @function name: CLList_NewNode
  * @brief        : Create a new node
  * @param        : 
  * 				@Data: the value to store in the new node
  * @retval       : Pointer to the newly created node
  * @version      : 1.0
  * @note         : None
*/
CLNode_t* CLList_NewNode(Elemtype_t Data);

/**
  * @function name: CLList_GetTail
  * @brief        : get the tail node
  * @param        : 
  * 				@Data: the value to store in the new node
  * @retval       : Pointer to the tail node
  * @version      : 1.0
  * @note         : None
*/
CLNode_t *CLList_GetTail(CLNode_t *Head);

/**
  * @function name: CLList_Len
  * @brief        : calculate the length of the list 
  * @param        : 
  * 				@Head: the list header address
  * @retval       : the length of list
  * @version      : 1.0
  * @note         : None
*/
int CLList_Len(CLNode_t *Head);

/**
  * @function name: CLList_Traverse
  * @brief        : Traverse and print the list
  * @param        : 
  * 				@Head: the list header address
  * @retval       : void
  * @version      : 1.0
  * @note         : None
*/
void CLList_Traverse(CLNode_t* Head);

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
bool CLList_HeadInsert(CLNode_t* Head, Elemtype_t Data);

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
bool CLList_TailInsert(CLNode_t* Head, Elemtype_t Data);

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
bool CLList_InDest_Place(CLNode_t* Head, Elemtype_t Data, int Dest);

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
bool CLList_InDest_BeforeValue(CLNode_t* Head, Elemtype_t Data, int Dest);

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
bool CLList_InDest_AfterValue(CLNode_t* Head, Elemtype_t Data, int Dest);

/**
  * @function name: CLList_HeadDelete
  * @brief        : Delete the first valid node (after Head)
  * @param        : 
  * 				@Head: the list header address
  * @retval       : Delete successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_HeadDelete(CLNode_t* Head);

/**
  * @function name: CLList_TailDelete
  * @brief        : Delete the last valid node (before Head)
  * @param        : 
  * 				@Head: the list header address
  * @retval       : Delete successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_TailDelete(CLNode_t* Head);

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
bool CLList_DelDest_Place(CLNode_t* Head, int Dest);

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
bool CLList_DelDest_Value(CLNode_t* Head, Elemtype_t Data);

/**
  * @function name: CLList_Destroy
  * @brief        : Destroy the entire linked list
  * @param        : 
  *                 @Head: the list header address
  * @retval       : true if delete successful, false otherwise
  * @version      : 1.0
  * @note         : none
*/
bool  CLList_Destroy(CLNode_t* Head);

#endif 
