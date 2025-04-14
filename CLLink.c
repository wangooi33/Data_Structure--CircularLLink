#include "CLLink.h"

/**
  * @function name: CLList_Create
  * @brief        : Create a circular linked list with a head node
  * @param        : None
  * @retval       : Returns pointer to head node
  * @version      : 1.0
  * @note         : None
*/
CLNode_t* CLList_Create() {
    CLNode_t* head = (CLNode_t*)malloc(sizeof(CLNode_t));
    if (!head) return NULL;
    head->next = head; // 初始化为循环结构，头结点不存储有效数据
    return head;
}

/**
  * @function name: CLList_NewNode
  * @brief        : Create a new node
  * @param        : @data: the value to store in the new node
  * @retval       : Pointer to the newly created node
  * @version      : 1.0
  * @note         : None
*/
CLNode_t* CLList_NewNode(Elemtype_t data) {
    CLNode_t* newNode = (CLNode_t*)malloc(sizeof(CLNode_t));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
  * @function name: CLList_Traverse
  * @brief        : Traverse and print the list
  * @param        : @Head: the list header address
  * @retval       : void
  * @version      : 1.0
  * @note         : None
*/
void CLList_Traverse(CLNode_t* Head) {
    if (!Head || Head->next == Head) {
        printf("List is empty.\n");
        return;
    }
    CLNode_t* current = Head->next;
    while (current != Head) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("(head)\n");
}

/**
  * @function name: CLList_HeadInsert
  * @brief        : Insert node after head (head insert)
  * @param        :
  *                @Head: the list header address
  *                @data: the data field of a circular linked list
  * @retval       : Insert successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_HeadInsert(CLNode_t* Head, Elemtype_t data) {
    if (!Head) return false;
    CLNode_t* newNode = CLList_NewNode(data);
    if (!newNode) return false;

    newNode->next = Head->next;
    Head->next = newNode;

    // 如果插入的是第一个有效节点，让它的 next 指向 Head
    if (newNode->next == Head) {
        newNode->next = Head;
    } else {
        // 找尾结点，更新其 next 指向 Head
        CLNode_t* tail = newNode->next;
        while (tail->next != Head) {
            tail = tail->next;
        }
        tail->next = Head;
    }

    return true;
}

/**
  * @function name: CLList_TailInsert
  * @brief        : Insert node at the end of the list
  * @param        :
  *                @Head: the list header address
  *                @data: the data field of a circular linked list
  * @retval       : Insert successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_TailInsert(CLNode_t* Head, Elemtype_t data) {
    if (!Head) return false;
    CLNode_t* newNode = CLList_NewNode(data);
    if (!newNode) return false;

    CLNode_t* current = Head;
    while (current->next != Head) {
        current = current->next;
    }

    current->next = newNode;
    newNode->next = Head;

    return true;
}

/**
  * @function name: CLList_InDest_Place
  * @brief        : Insert a node at a specific position in the circular linked list (1-based index)
  * @param        : 
  *                 @Head: the list header address
  *                 @data: the data to insert
  *                 @dest: the position to insert (starting from 1)
  * @retval       : true if insert successful, false otherwise
  * @version      : 1.0
  * @note         : If the list is empty, the inserted node becomes the first and loops to itself.
  *                 If inserted at position 1, Head->next and tail's next pointer will be updated.
*/
bool CLList_InDest_Place(CLNode_t* Head, Elemtype_t data, int dest) {
  if (!Head || dest < 1) return false;
  CLNode_t* newNode = CLList_NewNode(data);
  if (!newNode) return false;

  if (Head->next == NULL) {
      Head->next = newNode;
      newNode->next = newNode;
      return true;
  }

  CLNode_t* prev = Head;
  CLNode_t* current = Head->next;
  int count = 1;
  while (count < dest && current->next != Head->next) {
      prev = current;
      current = current->next;
      count++;
  }
  prev->next = newNode;
  newNode->next = current;
  if (dest == 1) { // 插入在首结点前
      // 找尾结点修复尾指针
      while (current->next != Head->next) current = current->next;
      current->next = newNode;
      Head->next = newNode;
  }
  return true;
}

/**
  * @function name: CLList_InDest_BeforeValue
  * @brief        : Insert a node before the first node with the specified value
  * @param        : 
  *                 @Head: the list header address
  *                 @data: the data to insert
  *                 @dest: the target value to match
  * @retval       : true if insert successful, false otherwise
  * @version      : 1.0
  * @note         : If the matching node is the head node, the inserted node will become the new head (Head->next).
  *                 Tail node's next pointer will also be updated accordingly.
*/
bool CLList_InDest_BeforeValue(CLNode_t* Head, Elemtype_t data, int dest) {
  if (!Head || Head->next == NULL) return false;
  CLNode_t* current = Head->next;
  CLNode_t* prev = NULL;

  do {
      if (current->data == dest) break;
      prev = current;
      current = current->next;
  } while (current != Head->next);

  if (current->data != dest) return false;

  CLNode_t* newNode = CLList_NewNode(data);
  if (!newNode) return false;

  newNode->next = current;
  if (prev == NULL) {
      // 插入到首结点前
      CLNode_t* tail = current;
      while (tail->next != Head->next) tail = tail->next;
      tail->next = newNode;
      Head->next = newNode;
  } else {
      prev->next = newNode;
  }
  return true;
}

/**
  * @function name: CLList_InDest_AfterValue
  * @brief        : Insert a node after the first node with the specified value
  * @param        : 
  *                 @Head: the list header address
  *                 @data: the data to insert
  *                 @dest: the target value to match
  * @retval       : true if insert successful, false otherwise
  * @version      : 1.0
  * @note         : If the node with the given value is found, the new node is inserted immediately after it.
*/
bool CLList_InDest_AfterValue(CLNode_t* Head, Elemtype_t data, int dest) {
  if (!Head || Head->next == NULL) return false;
  CLNode_t* current = Head->next;
  do {
      if (current->data == dest) break;
      current = current->next;
  } while (current != Head->next);

  if (current->data != dest) return false;

  CLNode_t* newNode = CLList_NewNode(data);
  if (!newNode) return false;
  newNode->next = current->next;
  current->next = newNode;
  return true;
}

/**
  * @function name: CLList_HeadDelete
  * @brief        : Delete the first valid node (after Head)
  * @param        : @Head: the list header address
  * @retval       : Delete successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_HeadDelete(CLNode_t* Head) {
  if (!Head || Head->next == Head) return false;

  CLNode_t* toDelete = Head->next;

  // 如果链表只有一个有效结点
  if (toDelete->next == Head) {
      Head->next = Head;
  } else {
      // 找尾结点
      CLNode_t* tail = Head->next;
      while (tail->next != Head) {
          tail = tail->next;
      }
      Head->next = toDelete->next;
      tail->next = Head;
  }

  free(toDelete);
  return true;
}


/**
  * @function name: CLList_TailDelete
  * @brief        : Delete the last valid node (before Head)
  * @param        : @Head: the list header address
  * @retval       : Delete successful return true otherwise return false
  * @version      : 1.0
  * @note         : None
*/
bool CLList_TailDelete(CLNode_t* Head) {
    if (!Head || Head->next == Head) return false;

    CLNode_t* prev = Head;
    CLNode_t* tail = Head->next;

    while (tail->next != Head) {
        prev = tail;
        tail = tail->next;
    }

    if (prev == Head) {
        Head->next = Head; // 删除唯一节点
    } else {
        prev->next = Head;
    }

    free(tail);
    return true;
}

/**
  * @function name: CLList_DelDest_Place
  * @brief        : Delete a node by its position (1-based index)
  * @param        : 
  *                 @Head: the list header address
  *                 @dest: the position of the node to be deleted
  * @retval       : true if delete successful, false otherwise
  * @version      : 1.0
  * @note         : If dest is 1, deletes the head node (first valid node);
  *                 returns false if the position is invalid or list is empty
*/
bool CLList_DelDest_Place(CLNode_t* Head, int dest) {
  if (!Head || Head->next == NULL || dest < 1) return false;

  CLNode_t* prev = Head;
  CLNode_t* current = Head->next;
  int count = 1;

  while (count < dest && current->next != Head->next) {
      prev = current;
      current = current->next;
      count++;
  }

  if (count != dest) return false;

  if (current == Head->next) {
      // 删除首结点
      CLList_HeadDelete(Head);
  } else {
      prev->next = current->next;
      free(current);
  }
  return true;
}

/**
  * @function name: CLList_DelDest_Value
  * @brief        : Delete the first node whose data field matches the specified value
  * @param        : 
  *                 @Head: the list header address
  *                 @data: the value to be matched for deletion
  * @retval       : true if delete successful, false otherwise
  * @version      : 1.0
  * @note         : If the matched node is the head node (first valid node),
  *                 the function calls CLList_HeadDelete; returns false if not found
*/
bool CLList_DelDest_Value(CLNode_t* Head, Elemtype_t data) {
  if (!Head || Head->next == NULL) return false;
  CLNode_t* prev = Head;
  CLNode_t* current = Head->next;
  do {
      if (current->data == data) break;
      prev = current;
      current = current->next;
  } while (current != Head->next);

  if (current->data != data) return false;

  if (current == Head->next) {
      // 删除首结点
      CLList_HeadDelete(Head);
  } else {
      prev->next = current->next;
      free(current);
  }
  return true;
}


/**
  * @function name: CLList_Length
  * @brief        : Calculate the number of valid nodes
  * @param        : @Head: the list header address
  * @retval       : Length of the list
  * @version      : 1.0
  * @note         : None
*/
int CLList_Length(CLNode_t* Head) {
    if (!Head || Head->next == Head) return 0;
    int len = 0;
    CLNode_t* current = Head->next;
    while (current != Head) {
        len++;
        current = current->next;
    }
    return len;
}