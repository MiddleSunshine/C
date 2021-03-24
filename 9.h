//
// Created by 杨庆贤 on 2021/3/24.
//

#ifndef C_9_H
#define C_9_H

#endif //C_9_H
#include "stdio.h"

// 函数部分代码
void printName(short int age,short int weight);
short int withoutParamName(char,char);
void withoutParam(void);

void printName(short int age,short int weight){
    printf("I'm %d years old and %d pounds\n",age,weight);
}

short int withoutParamName(char a,char b){
    return 0;
}

void withoutParam(void){
    printf("To do nothing\n");
}

void address(){
    int store=666;
    // &store 获取地址，*(&store) 打开对应的地址并对其进行操作
    // 比 store_data=store 这样直接获取值，&store 只有一个地址的大小
    int store_data=*(&store);
    printf("address is %p and the data in that store is %d\n",&store,store_data);
}

void setAddress(){
    int store=666;
    // int * 定义为当前数据类型为地址
    int * address=&store;
    // *address 打开对应的地址并对其进行操作
    int value=*address;
    printf("address is %p,and the store data is %d\n",address,value);
}
/**
 *
 * @param param1Address *param1Address，表明当前值的数据类型为指针
 * @param param2Address
 */
void setPointerFunction(int *param1Address,int *param2Address){
    // 打开对应的地址获取值
    int temp=*param1Address;
    // *param1Address 打开对应的地址，将新的值存储进去
    // *param2Address 打开对应的地址，将值取出来
    *param1Address=*param2Address;
    *param2Address=temp;
}

void showResult(){
    int p1,p2;
    p1=1;
    p2=2;
    printf("First P1 is %d,P2 is %d\n",p1,p2);
    setPointerFunction(&p1,&p2);
    printf("After the function.P1 is %d,P2 is %d\n",p1,p2);
}

void Page9Index(){
    showResult();
}