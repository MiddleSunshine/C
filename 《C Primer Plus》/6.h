//
// Created by 杨庆贤 on 2021/3/21.
//

#ifndef C_6_H
#define C_6_H

#endif //C_6_H

#include "stdio.h"

void pointArray(){
    short int arrayLength=5;
    int password[arrayLength];
    for (int i = 0; i < arrayLength; ++i) {
        printf("The %d Password is \n",i+1);
        scanf("%d",&password[i]);
    }
    for (int i = 0; i < arrayLength; ++i) {
        switch (i) {
            case 0:
                printf("The Password is\n");
            default:
                printf("%d",password[i]);
                break;
        }
    }
}

void Page6Index(){
    pointArray();
}