//
// Created by 杨庆贤 on 2021/5/3.
//

#ifndef C_STACK_H
#define C_STACK_H

#endif //C_STACK_H

#include "List.h"
/**
 * 采用顺序存储产生的栈
 */
typedef struct {
    SqlList sqlList;
    int top;
} SqlListStack;
/**
 * 插入元素
 * @param sqlListStack
 * @param data
 * @return
 */
Return PushSqlListStack(SqlListStack* sqlListStack,ElementType data){
    // 栈以满
    if (sqlListStack->top==MAX_LIST_LENGTH){
        return Error;
    }
    if(addSqlListElement(&sqlListStack->sqlList,data,sqlListStack->top+1)==Success){
        sqlListStack->top++;
    }
    return Error;
}
/**
 * 剔除数据
 * @param sqlListStack
 * @return
 */
ElementType PopSqlListStack(SqlListStack* sqlListStack){
    ElementType deleteData=sqlListStack->sqlList.data[sqlListStack->top];
    // 空队列
    if (sqlListStack->top<0){
        exit(0);
    }
    deleteSqlListElement(&sqlListStack->sqlList,sqlListStack->top);
    sqlListStack->top--;
    return deleteData;
}

void SqlListStackIndex(){
    SqlListStack sqlListStack={
            .sqlList={
                    .length=0
            },
            .top=-1
    };
    PushSqlListStack(&sqlListStack,1);
    PushSqlListStack(&sqlListStack,2);
    PushSqlListStack(&sqlListStack,3);
    PrintfSqlList(&sqlListStack.sqlList);
    PopSqlListStack(&sqlListStack);
    PopSqlListStack(&sqlListStack);
    PrintfSqlList(&sqlListStack.sqlList);
}
/**
 * 采用链表来产生栈
 */
typedef struct {
    Node* topNode;
    int top;
} NodeStack;
/**
 * 插入元素
 * @param nodeStack
 * @param data
 * @return
 */
Return PushNodeStack(NodeStack *nodeStack,ElementType data){
    // 因为C语言存储类别的关系，所以如果直接采用变量的形式，会因为内存访问限制而直接报错
    Node *newTop=malloc(sizeof(Node));
    newTop->value=data;
    newTop->next=0;
    // 防止第一个top时，一直指向自己，造成死循环
    if(nodeStack->top>0){
        newTop->next=nodeStack->topNode;
    }
    nodeStack->topNode=newTop;
    nodeStack->top++;
    return Success;
}
/**
 * 删除元素
 * @param nodeStack
 * @return
 */
ElementType PopNodeStack(NodeStack *nodeStack){
    ElementType deleteData=nodeStack->topNode->value;
    Node *topAddress=nodeStack->topNode;
    nodeStack->topNode=nodeStack->topNode->next;
    free(topAddress);
    return deleteData;
}

void NodeStackIndex(){
    NodeStack nodeStack={
            .top=0
    };
    PushNodeStack(&nodeStack,1);
    PushNodeStack(&nodeStack,2);
    PushNodeStack(&nodeStack,3);
    PrintNode(nodeStack.topNode);
    PopNodeStack(&nodeStack);
    PopNodeStack(&nodeStack);
    PrintNode(nodeStack.topNode);
}
/**
 * 共享存储空间的栈
 */
typedef struct {
    SqlList sqlList;
    int leftTop;
    int rightTop;
} DoubleSqlListStack;
/**
 * 插入元素
 * @param doubleSqlListStack
 * @param data
 * @param isLeft 插入位置
 * @return
 */
Return PopDoublerSqlListStack(DoubleSqlListStack *doubleSqlListStack,ElementType data,short int isLeft){
    // 栈已满
    if ((doubleSqlListStack->leftTop+1)==doubleSqlListStack->rightTop){
        return Error;
    }
    if (isLeft){
        doubleSqlListStack->sqlList.data[doubleSqlListStack->leftTop]=data;
        doubleSqlListStack->leftTop++;
        return Success;
    }else{
        doubleSqlListStack->sqlList.data[doubleSqlListStack->rightTop]=data;
        doubleSqlListStack->rightTop--;
        return Success;
    }
}
/**
 * 剔除元素
 * @param doubleSqlListStack
 * @param isLeft
 * @return
 */
ElementType PushDoublerSqlListStack(DoubleSqlListStack *doubleSqlListStack,short int isLeft){
    // 空队列
    if (isLeft && doubleSqlListStack->leftTop==0){
        exit(0);
    }else if(doubleSqlListStack->rightTop==(MAX_LIST_LENGTH-1)){
        exit(0);
    }
    if (isLeft){
        doubleSqlListStack->leftTop--;
        return doubleSqlListStack->sqlList.data[doubleSqlListStack->leftTop+1];
    }
    doubleSqlListStack->rightTop++;
    return doubleSqlListStack->sqlList.data[doubleSqlListStack->rightTop-1];
}
/**
 * 辅助函数，打印中间结果
 * @param doubleSqlListStack
 */
void PrintDoublerSqlList(DoubleSqlListStack *doubleSqlListStack){
    for (int i = 0; i < doubleSqlListStack->leftTop; ++i) {
        printf("Position %d's data is ",i);
        printf(ElementPrintType,doubleSqlListStack->sqlList.data[i]);
        BR;
    }
    for (int i = doubleSqlListStack->rightTop+1; i < MAX_LIST_LENGTH; ++i) {
        printf("Position %d's data is ",i);
        printf(ElementPrintType,doubleSqlListStack->sqlList.data[i]);
        BR;
    }
}

void DoubleSqlListStackIndex(){
    DoubleSqlListStack doubleSqlListStack={
            .sqlList={
                    .length=MAX_LIST_LENGTH
                    },
            .leftTop=0,
            .rightTop=MAX_LIST_LENGTH-1
    };
    PopDoublerSqlListStack(&doubleSqlListStack,1,1);
    PopDoublerSqlListStack(&doubleSqlListStack,2,0);
    PrintDoublerSqlList(&doubleSqlListStack);
    PushDoublerSqlListStack(&doubleSqlListStack,1);
    PushDoublerSqlListStack(&doubleSqlListStack,0);
    PrintDoublerSqlList(&doubleSqlListStack);
}


void StackIndex(){
    SqlListStackIndex();
    NodeStackIndex();
    DoubleSqlListStackIndex();
}


