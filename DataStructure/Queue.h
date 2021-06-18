//
// Created by 杨庆贤 on 2021/5/4.
//

#ifndef C_QUEUE_H
#define C_QUEUE_H

#endif //C_QUEUE_H

#include "List.h"
/**
 * 采用顺序存储实现队列
 */
typedef struct {
    SqlList sqlList;
} SqlListQueue;
/**
 * 添加元素进入队列
 * @param sqlListQueue
 * @param data
 * @return
 */
Return InSqlListQueue(SqlListQueue* sqlListQueue,ElementType data){
    // 队列已满
    if (sqlListQueue->sqlList.length==MAX_LIST_LENGTH){
        return Error;
    }
    addSqlListElement(&sqlListQueue->sqlList,data,sqlListQueue->sqlList.length);
    return Success;
}
/**
 * 将元素退出队列
 * @param sqlListQueue
 * @return
 */
ElementType OutSqlListQueue(SqlListQueue* sqlListQueue){
    ElementType outData=sqlListQueue->sqlList.data[0];
    if(deleteSqlListElement(&sqlListQueue->sqlList,0)==Success){
        return outData;
    }
    exit(0);
}
/**
 * 演示代码
 */
void SqlListQueueIndex(){
    SqlListQueue sqlListQueue={
            .sqlList={
                    .length=0
                    }
    };
    InSqlListQueue(&sqlListQueue,1);
    InSqlListQueue(&sqlListQueue,2);
    InSqlListQueue(&sqlListQueue,3);
    PrintfSqlList(&sqlListQueue.sqlList);
    OutSqlListQueue(&sqlListQueue);
    OutSqlListQueue(&sqlListQueue);
    PrintfSqlList(&sqlListQueue.sqlList);
}
// todo 写到这里
typedef struct {
    Node* indexNode;
} NodeQueue;

Return InNodeQueue(NodeQueue* nodeQueue,ElementType data){

}

Return OutNodeQueue(NodeQueue* nodeQueue){

}

void NodeQueueIndex(){
    NodeQueue nodeQueue;
    InNodeQueue(&nodeQueue,1);
    InNodeQueue(&nodeQueue,2);
    InNodeQueue(&nodeQueue,3);
    PrintNode(nodeQueue.node);
}

void QueueIndex(){
//    SqlListQueueIndex();
    NodeQueueIndex();
}