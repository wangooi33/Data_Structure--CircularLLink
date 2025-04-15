/**
  * @file name:CircularLLink.c
  * @brief    :functional test
  * @author   :i33akq@163.com
  * @date     :2025/04/14
  * @version  :1.0
  * @note     :None
  * @CopyRight (C)   2024-2025   i33akq@163.com   ALL Right Reseverd
*/
#include "CLLink.h"

int main()
{
    CLNode_t* list = CLList_Create();

    CLList_TailInsert(list, 10);
    CLList_TailInsert(list, 20);
    CLList_TailInsert(list, 30);
    CLList_Traverse(list);

    CLList_HeadInsert(list, 5);
    CLList_Traverse(list);

    //CLList_InDest_Place(list,100,4);
    //CLList_Traverse(list);

    //CLList_InDest_BeforeValue(list,100,5);
    //CLList_Traverse(list);

    //CLList_InDest_AfterValue(list,100,5);
    //CLList_Traverse(list);

    //CLList_HeadDelete(list);
    //CLList_Traverse(list);

    //CLList_TailDelete(list);
    //CLList_Traverse(list);

    //CLList_DelDest_Place(list,1);
    //CLList_Traverse(list);

    CLList_DelDest_Value(list,5);
    CLList_Traverse(list);

    printf("Length: %d\n", CLList_Length(list));

    return 0;
}
