#include "../const.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_LIST_LENGTH 100

#define Error 0
#define Success 1

typedef int Return;
/**
 * 顺序存储部分
 */
typedef struct {
    ElementType data[MAX_LIST_LENGTH];
    int length;
} SqlList;
/**
 * 添加元素
 * @param sqlList
 * @param newData
 * @param position
 * @return
 */
Return addSqlListElement(SqlList *sqlList,ElementType newData,int position){
    if(position<0 || position>sqlList->length || position>MAX_LIST_LENGTH){
        return Error;
    }
    if (position!=sqlList->length){
        ElementType lastData=sqlList->data[position],temp;
        for (int i = position; i <MAX_LIST_LENGTH; ++i) {
            temp=sqlList->data[i];
            sqlList->data[i]=lastData;
            lastData=temp;
        }
    }
    sqlList->data[position]=newData;
    sqlList->length++;
    return Success;
}
/**
 * 删除元素
 * @param sqlList
 * @param position
 * @return
 */
Return deleteSqlListElement(SqlList *sqlList,int position){
    if(position<0 || position>sqlList->length || position>MAX_LIST_LENGTH){
        return Error;
    }
    for (int i = position; i < MAX_LIST_LENGTH; ++i) {
        sqlList->data[i]=sqlList->data[i+1];
    }
    sqlList->data[sqlList->length]=0;
    sqlList->length--;
    return Success;
}
/**
 * 搜索元素
 * @param sqlList
 * @param search
 * @return
 */
Return searchSqlList(SqlList *sqlList,ElementType search){
    for (int i = 0; i < sqlList->length; ++i) {
        if(sqlList->data[i]==search){
            return Success;
        }
    }
    return Error;
}
/**
 * 辅助函数，打印函数
 * @param sqlList
 */
void PrintfSqlList(SqlList* sqlList){
    printf("the length is %d\n",sqlList->length);
    for (int i = 0; i < sqlList->length; ++i) {
        printf("Position %d's data is ",i);
        printf(ElementPrintType,sqlList->data[i]);
        BR;
    }
}
/**
 * 效果展示
 */
void sqlListIndex(){
    SqlList sqlList={
            .length=0
    };
    addSqlListElement(&sqlList,0,0);
    addSqlListElement(&sqlList,1,1);
    addSqlListElement(&sqlList,1,0);
    PrintfSqlList(&sqlList);
    addSqlListElement(&sqlList,3,3);
    PrintfSqlList(&sqlList);
    addSqlListElement(&sqlList,2,2);
    PrintfSqlList(&sqlList);
    deleteSqlListElement(&sqlList,0);
    PrintfSqlList(&sqlList);
    deleteSqlListElement(&sqlList,3);
    PrintfSqlList(&sqlList);
    deleteSqlListElement(&sqlList,1);
    PrintfSqlList(&sqlList);
    if(searchSqlList(&sqlList,1)==Success){
        printf("%d in the list\n",1);
    }else{
        printf("%d not in the list\n",1);
    }
}
/**
 * 线性表链式存储结构
 */
typedef struct {
    ElementType value;
    struct Node *next;
} Node;
/**
 * 添加元素
 * @param addPosition
 * @param newNode
 * @return
 */
Return addNode(Node *addPosition,Node *newNode){
    newNode->next=addPosition->next;
    addPosition->next=newNode;
    return Success;
}

/**
 * 删除元素
 * @param indexNode
 * @param removeValue
 * @return
 */
Return deleteNode(Node *indexNode,ElementType removeValue){
    Node *nextNode=indexNode;
    if (indexNode->value==removeValue){
        printf("Can't delete the index value\n");
        exit(0);
    }
    Node *lastNode;
    do {
        lastNode=nextNode;
        nextNode=nextNode->next;
        if (nextNode->value==removeValue){
            lastNode->next=nextNode->next;
            free(nextNode);
            return Success;
        }
    } while (nextNode->next);
    return Error;
}
/**
 * 辅助函数，打印值
 * @param indexNode
 */
void PrintNode(Node *indexNode){
    Node *nextNode=indexNode;
    printf(ElementPrintType,nextNode->value);
    BR;
    do {
        nextNode=nextNode->next;
        printf(ElementPrintType,nextNode->value);
        BR;
    } while (nextNode->next);
}
/**
 * 搜索链表
 * @param indexNode
 * @param searchValue
 * @return
 */
Return searchNode(Node *indexNode,ElementType searchValue){
    Node *nextNode=indexNode;
    if (indexNode->value==searchValue){
        return Success;
    }
    do {
        nextNode=nextNode->next;
        if (nextNode->value==searchValue){
            return Success;
        }
    } while (nextNode->next);
    return Error;
}
/**
 * 效果演示
 */
void nodeIndex(){
    Node indexNode={
            .value=0
    };
    Node *n,*last;
    last=&indexNode;
    for (int i = 1; i <10; ++i) {
        n= malloc(sizeof(Node));
        n->value=i;
        addNode(last,n);
        last=n;
    }
    PrintNode(&indexNode);
    printf("Remove the node\n");
    deleteNode(&indexNode,1);
    PrintNode(&indexNode);
    if (searchNode(&indexNode,1)==Success){
        printf("1 is in the node list\n");
    }else{
        printf("1 is not in the node list\n");
    }
    if (searchNode(&indexNode,8)==Success){
        printf("8 is in the node list\n");
    }else{
        printf("8 is not in the node list\n");
    }
}

/**
* 静态存储
*/

typedef struct {
    ElementType data;
    int cur;
} StaticLinkList;

void emptyStaticLinkList(StaticLinkList staticLinkList[]){
    for (int i = 0; i < MAX_LIST_LENGTH; ++i) {
        staticLinkList[i].cur=0;
    }
}
/**
 * 获取静态列表的最后一个值的下标
 * @param staticLinkList
 * @param position
 * @return
 */
int getStaticLinkListEndIndex(StaticLinkList staticLinkList[],int position){
    if (staticLinkList[position].cur){
        return getStaticLinkListEndIndex(staticLinkList,staticLinkList[position].cur);
    }
    return position;
}
/**
 * 获取静态列表中的一个空位置的值
 * @param staticLinkList
 * @param position
 * @return
 */
int getEmptyStaticLinkListIndex(StaticLinkList staticLinkList[],int position){
    if (position==0){
        position++;
    }
    // 超过设定值
    if (position>MAX_LIST_LENGTH){
        exit(0);
    }
    if (staticLinkList[position].cur){
        return getEmptyStaticLinkListIndex(staticLinkList,position+1);
    }
    return position;
}
/**
 * 添加一个元素
 * @param staticLinkList
 * @param newData
 * @param position
 * @return
 */
Return addStaticLinkList(StaticLinkList staticLinkList[],ElementType newData,int position){
    if (position==0){
        staticLinkList[position].data=newData;
        return Success;
    }
    if (staticLinkList[position].cur){
        // 当前该位置有数据占据该位置
        // 将当前位置的数据拷贝至一个空的数组位置
        int emptyStaticLinkListIndex= getEmptyStaticLinkListIndex(staticLinkList,1);
        staticLinkList[emptyStaticLinkListIndex].data=staticLinkList[position].data;
        staticLinkList[emptyStaticLinkListIndex].cur=staticLinkList[position].cur;
        // 将新的值存储进当前位置中
        staticLinkList[position].data=newData;
        staticLinkList[position].cur=emptyStaticLinkListIndex;
    }else{
        // 搜索静态表的最后一个值
        int staticListLinkEndIndex= getStaticLinkListEndIndex(staticLinkList,0);
        // 将新的值存储进空的数组下标中
        staticLinkList[position].data=newData;
        // 并将静态表的最后一个数组下标指向那里
        staticLinkList[staticListLinkEndIndex].cur=position;
    }
    return Success;
}
/**
 * 删除静态表的值
 * @param staticLinkList
 * @param position
 * @return
 */
Return deleteStaticLinkList(StaticLinkList staticLinkList[],int position){
    // 不允许抹除整个数组
    if (position==0){
        exit(0);
    }
    if (position>MAX_LIST_LENGTH){
        return Error;
    }
    int nextPosition=0;
    // 寻找被删除元素的上级
    while (staticLinkList[nextPosition].cur!=position){
        nextPosition=staticLinkList[nextPosition].cur;
    }
    if (staticLinkList[nextPosition].cur){
        // 将当前被删除的元素的下一个元素交给它的上级
        staticLinkList[nextPosition].cur=staticLinkList[position].cur;
        staticLinkList[position].cur=0;
    }
    // 即使这里没有找到该元素的上级也没有关系，说明当前位置不在数组之中
    return Success;
}
/**
 * 搜索静态表中的一个值
 * @param staticLinkList
 * @param data
 * @return
 */
Return searchStaticLinkList(StaticLinkList staticLinkList[],ElementType data){
    if (staticLinkList[0].data==data){
        return Success;
    }
    int position=0;
    do {
        if (staticLinkList[position].data==data && staticLinkList[position].cur){
            break;
        }
        position=staticLinkList[position].cur;
    } while (staticLinkList[position].cur);
    return staticLinkList[position].data==data?Success:Error;
}
/**
 * 辅助函数，打印输出的
 * @param staticLinkList
 */
void printStaticLinkList(StaticLinkList staticLinkList[]){
    int position=0;
    do {
        printf("Index:%d & data:",position);
        printf(ElementPrintType,staticLinkList[position].data);
        BR;
        position=staticLinkList[position].cur;
    } while (position);
}
/**
 * 演示代码
 */
void staticLinkListIndex(){
    StaticLinkList staticLinkList[MAX_LIST_LENGTH];
    emptyStaticLinkList(staticLinkList);
    addStaticLinkList(staticLinkList,1,0);
    addStaticLinkList(staticLinkList,2,3);
    addStaticLinkList(staticLinkList,3,10);
    printStaticLinkList(staticLinkList);
    printf("Try to delete some indexes\n");
    deleteStaticLinkList(staticLinkList,3);
    printStaticLinkList(staticLinkList);
    if(searchStaticLinkList(staticLinkList,2)==Error){
        printf("2 is not in static link list\n");
    }else{
        printf("2 is in static link list\n");
    }
    if(searchStaticLinkList(staticLinkList,3)==Error){
        printf("3 is not in static link list\n");
    }else{
        printf("3 is in static link list\n");
    }
}