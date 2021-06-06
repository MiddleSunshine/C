//
// Created by 杨庆贤 on 2021/3/23.
//

#ifndef C_8_H
#define C_8_H

#endif //C_8_H
#include "stdio.h"

void withoutInputCache(){
    char inputChar;
    // 这里的输入内容被存放在缓存区中
    while ((inputChar=getchar())!='#')
        putchar(inputChar);
}

void Page8Index(){
    withoutInputCache();
}