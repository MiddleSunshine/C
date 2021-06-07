```c
#include "stdio.h"

// 传入的值为数组的首地址，并且其中存储的值为具体的值
void printArray(int (*multiple)[3],short int firstColumn,short int secondColumn){
    printf("(%d,%d) is %d\n",firstColumn,secondColumn,multiple[firstColumn][secondColumn]);
    char stop=1;
}
// 传入的值为数组的首地址，并且其中存储的值为地址
void printArray6(int* (*multiple)[2],short int firstColumn,short int secondColumn){
    printf("(%d,%d) is %d\n",firstColumn,secondColumn,*(multiple[firstColumn])[secondColumn]);
//  这种写法是错误的，因为 multiple[firstColumn] 代表的是地址，上面指定的
//    printf("(%d,%d) is %d\n",firstColumn,secondColumn,multiple[firstColumn][secondColumn]);
    char stop=1;
}
// 传入的值为数组的首地址，并且其中存储的值为地址
void printArray7(int* (*multiple)[2],short int firstColumn,short int secondColumn){
    printf("(%d,%d) is %d\n",firstColumn,secondColumn,*(multiple[firstColumn])[secondColumn]);
//  这种写法是错误的，因为 multiple[firstColumn] 代表的是地址，上面指定的
//    printf("(%d,%d) is %d\n",firstColumn,secondColumn,multiple[firstColumn][secondColumn]);
    char stop=1;
}
// 代表其中存储的值为指针，所以允许采用多维数组的形式来获取值
void printArray2(int* multiple[],short int firstColumn,short int secondColumn){
    printf("(%d,%d) is %d\n",firstColumn,secondColumn,multiple[firstColumn][secondColumn]);
    char stop=1;
}
// 代表数组中存储的值为具体的值
void printArray3(int multiple[],short int firstColumn){
    printf("%d is %d\n",firstColumn,multiple[firstColumn]);
}

int main() {
    int multipleArray[3][2]={
            {1,2},
            {3,4},
            {5,6}
    };
    int index1Array[]={1,2};
    int index2Array[]={3,4};
    int index3Array[]={5,6};
    int *result[3];
    result[0]=index1Array;
    result[1]=index2Array;
    result[2]=index3Array;
    printArray2(result,0,1);
    printArray6(result,0,0);
    return 0;
}
```