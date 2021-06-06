//
// Created by 杨庆贤 on 2021/3/14.
//

#ifndef C_4_H
#define C_4_H

#endif //C_4_H

#include "stdio.h"
#include "string.h"

// 注意，这里是没有 = 号的
#define MONTH_NOTE "一年有"
// 注意，这里是有 = 的，并且还需要标注数据类型
const short int MONTH_LENGTH=12;

void setString(){
    short int stringLength=10;
    char string[stringLength];
    for (int i = 0; i < stringLength; ++i) {
        string[i]='a';
    }
    for (int i = 0; i < stringLength; ++i) {
        printf("Index is %d,Data is %c\n",i,string[i]);
    }
}

void setStringDefault(){
    short int stringLength=10;
    char string[stringLength];
    printf("Print the string under %d words\n",stringLength);
    scanf("%s",string);
    for (int i = 0; i < stringLength; ++i) {
        printf("Index:%d,Data:%c\n",i,string[i]);
    }
    printf("string length is %d\n",strlen(string));// 字符串结尾的 \0 是不会纳入计算范畴中的
    printf("string memory size is %zd bytes",sizeof(string));// 注意，一个字符占1个字节，所以数组多长就是占多少个字节
}

void setConstAndDefine(){
    printf("%s %d 个月\n",MONTH_NOTE,MONTH_LENGTH);
    printf("define 设定的字符串长度为：%d，使用%zd个字节存储\n",strlen(MONTH_NOTE),sizeof(MONTH_NOTE));
    // define 设定的字符串长度为：9，使用10个字节存储
    // 多出来的那一个字节就是 \0，表示字符串结尾
}

void Page4Index(){
//    setString();
//    setStringDefault();
    setConstAndDefine();
}