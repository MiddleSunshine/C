//
// Created by 杨庆贤 on 2021/3/21.
//

#ifndef C_5_H
#define C_5_H

#endif //C_5_H
#include "stdio.h"

// 用这个可以给参数种类设置别名
typedef short int monthLength;

void paramAlias(){
    monthLength m=12;
    printf("A year has %d month\n",m);
}

void plus(){
    short int a=1,b=1;
    printf("a is %d\n++a is %d\na++ is %d\n",a,++a,b++);
}

void withParamFunction(short int age){
    printf("You are %d years old\n",age);
}

void Page5Index(){
//    paramAlias();
//    plus();
    withParamFunction(10);
}