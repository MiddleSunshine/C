# C语言分配内存

首先说基础：

- malloc：申请内存
  - 参数：申请内存所需要的**字节**数
  - 返回参数：`void*`类型的指针，如果申请内存失败，就会返回空指针
- free：释放内存
  - 参数：申请到的地址，即上面返回的指针
  - 返回参数：无
- calloc：作用和 malloc 类似，就是参数不同

下面就是借用这个内存分配演示一下生成动态数组：

```c
#include "stdio.h"
#include "stdlib.h"

int main(){
    int arrayLength;
    if (scanf("%d",&arrayLength)!=1){
        printf("Wrong Input\n");
        exit(EXIT_FAILURE);
    }
    char* inputString;
    // 申请内存
    inputString=(char*)malloc(arrayLength* sizeof(char));
    for (int i = 0; i <= arrayLength; ++i) {
        scanf("%c",&inputString[i]);
    }
    for (int i = 0; i <= arrayLength; ++i) {
        printf("%c\n",inputString[i]);
    }
    // 释放内存
    free(inputString);
}
```

## 内存泄漏 / memory leak

简单点来说就是在一直申请内存但是没有释放，直到所有内存都被占用：

```c
#include "stdio.h"
#include "stdlib.h"

char* createArray(unsigned int arrayLength);

int main(){
    char* addresses[100];
    for (int i = 0; i < 100; ++i) {
        // 这里一直在申请内存
        addresses[i]= createArray(100);
    }
    /**
     * 下面的代码就是在释放内存了
    for (int i = 0; i < 100; ++i) {
        free(addresses[i]);
    }
    **/
}

char* createArray(unsigned int arrayLength){
    return malloc(arrayLength*sizeof(char));
}
```

## 存储类别

### 静态存储类别

类似于[静态存储期](https://blog.csdn.net/YQXLLWY/article/details/115579286)一样的效果。

### 自动存储类别

类似于[自动存储期](https://blog.csdn.net/YQXLLWY/article/details/115579286)一样的效果。

### 动态分配内存

这个就是上面讲的。这部分的好处就是可以跳出[存储期](https://blog.csdn.net/YQXLLWY/article/details/115579286)的概念，比如这部分在某个函数中生成，再到某个函数中去释放，比如：

```c
#include "stdio.h"
#include "stdlib.h"

char* createArray(unsigned int arrayLength);
void freeArray(char* address[]);

int main(){
    char* addresses[100];
    for (int i = 0; i < 100; ++i) {
        // 这里一直在申请内存
        addresses[i]= createArray(100);
    }
    freeArray(addresses);
}

char* createArray(unsigned int arrayLength){
    // 像这种变量就会在函数执行完之后被自动销毁
    int temp=arrayLength;
    return malloc(arrayLength*sizeof(char));
}

void freeArray(char* address[]){
    int i=0;
    while (address[i]){
        free(*address[i]);
        i++;
    }
}
```

但是这样导致的结果后果也有，就是内存地址会变成一块一块不连贯的存在。比如你在函数A中申请了1-100的内存，在函数2中申请了101-130的内存，之后你释放掉了1-100的内存，再重新申请了1-30的内存，于是你的内存块就变成了：

- 1-30：在使用
- 31-100:闲置
- 101-130：在使用

这样当你要申请80的内存块时，就必须不断往后去申请。