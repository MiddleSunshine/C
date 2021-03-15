//
// Created by 杨庆贤 on 2021/3/13.
//

#ifndef C_3_H
#define C_3_H

#endif //C_3_H

#include "stdint.h"

// ====================== int部分的代码 ======================
/**
 * 知识点：单纯说明设置变量的方式
 */
void setIntParam() {
    short int year, month;
    year = 2020;
    month = 3;
    short int day = 15;
    printf("今天是 %d-%d-%d\n", year, month, day);
}

/**
 * 知识点：可以采用八进制，十六进制的方式来定义int类型的数据
 */
void setIntWithOtherBaseSystem() {
    short int yearDays = 0555;// 八进制的 365表示
    short int monthAmount = 0xc;// 十六进制的 12
    // todo 在输出前加上 # 可以展示编码前的符号，而不仅仅是数字
    printf("一年有%d天，采用八进制表示为%#o / %o\n", yearDays, yearDays, yearDays);
    printf("一年有%d个月，采用十六进制表示为%#x / %x\n", monthAmount, monthAmount, monthAmount);
}

void wrongPrintf() {
    int minusInt = -10;
    printf("采用%%u输出负数时，得到的结果为：%u\n", minusInt);// 结果为其补码
    int maxInt = INT32_MAX;
    printf("当采用%%hd输出shor int的数据时，原本的%d的值会变成%hd\n", maxInt, maxInt);
    // 当采用%hd输出shor int的数据时，原本的2147483647的值会变成-1
    // todo 因为short int产生了溢出，所以就变成了-1
}

// ====================== char部分的代码 ======================
void setChar() {
    char word = 'W';
    char string = "W";
    printf("'单引号'中的内容为字母：%c，\"双引号\"中的内容为字符串：%c\n", word, string);
}

// ====================== float & doubler 部分的代码 ======================
void defaultFloat(){
    float pi=3.1415926;
    double width=3.1;
    // todo 这里显示为小数点后3位小数
    printf("这个圆的宽为：%.3f\n",2*pi*width);
}

/**
 * 知识点：确定当前运行的计算机上存储各个类型的数据需要多少位存储数据
 */
void getParamSize() {
    // int
    printf("short int有%zd位字节存储\n", sizeof(short int));
    printf("int有%zd位字节存储\n", sizeof(int));
    printf("long int有%zd位字节存储\n", sizeof(long int));
    printf("long long int有%zd位字节存储\n", sizeof(long long int));
    printf("unsigned int有%zd位字节存储\n", sizeof(unsigned int));
    // char
    printf("char有%zd位字节存储\n",sizeof(char));
    // float & doubler
    printf("float有%zd位字节存储\n",sizeof(float));
    printf("doubler有%zd位字节存储\n",sizeof(double));
}

/**
 * 代码入口，方便外部调用
 */
void Page3Index() {
    setIntParam();
    setIntWithOtherBaseSystem();
    wrongPrintf();
    setChar();
    defaultFloat();
    getParamSize();
}