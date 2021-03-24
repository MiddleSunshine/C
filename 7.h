//
// Created by 杨庆贤 on 2021/3/21.
//

#ifndef C_7_H
#define C_7_H

#endif //C_7_H
#include "stdio.h"
#include "ctype.h"

char simpleChar(){
    char inputChar=getchar();
    // getchar 类似 scanf('%c',&charParam);
    printf("Your Input Is %c\n Or You Can Output likes That ",inputChar);
    putchar(inputChar);
    // putchar 类似 printf("%c",charParam);
    return inputChar;
}

void stringFunction(){
    char inputChar='a';
    printf("Your low case is %c.And Up case is %c\n",tolower(inputChar),toupper(inputChar));
    if (isalpha(inputChar)){
        printf("Your input is word\n");
    }else if (isalnum(inputChar)){
        printf("Your input is number\n");
    }else{
        printf("Can't parse the input\n");
    }
}

void Page7Index(){
//    simpleChar();
    stringFunction();
}