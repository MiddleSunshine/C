# C语言结构体，联合，枚举类型，typedef

## 结构体

直接看代码：

```c
#include "stdio.h"
#define MAX_TITLE 30
#define MAX_AUTHOR 30
#define MAX_BOOKS 10

struct book{
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    float price;
};

struct volume{
    // 结构体的数组
    struct book books[MAX_BOOKS];
};

struct library{
    struct volume volumes[MAX_BOOKS];
    struct book books[MAX_BOOKS];
    char address[MAX_TITLE];
    char name[MAX_TITLE];
};

struct manager{
    // 结构体的指针
    struct library *library;
    char name[MAX_AUTHOR];
    char phoneNumber[10];
};

void printBookInfo(struct book books[],int length){
    for (int i = 0; i < length; ++i) {
        // 结构体的数组是如何读取其中的输入的
        printf("book title:%s,author:%s,price:%f\n",books[i].title,books[i].author,books[i].price);
    }
}

int main(){
    // 可以设置这种未定义具体 structure 名称的结构体
    struct {
        char name[MAX_AUTHOR];
        char phone[20]
    } John={
            "John",
            "110"
    };
    // 初始化结构体的时候，可以采用 .key= 这样的形式指定当前赋值的结构中的成员
    struct library CityTown={
            .address="LosAngle",
            // 如果未指定，则默认是前一个指定的成员的下一个成员
            "CityTown"
    };
    struct manager Noel={
            // 指针赋值，可以看出没有什么不同
            .library=&CityTown,
            .name="Noel",
            "911"
    };
    // 这里主要就是演示如何读取指针的值
    printf("%s is a library manager of %s.\n",Noel.name,(*Noel.library).name);
    // 但是上面的形式写起来很复杂，所以可以采用 -> 的形式读取指针中的值
    printf("%s's address is %s.\n",Noel.library->name,Noel.library->address);
}
```

## 联合

联合在语法上和结构体是类似的，只是联合是其中的所有变量都使用同一块内存来存储不同种类的数据，比如下面这个代码例子：

```c
#include "stdio.h"

union token{
    char token[20];
    char cookie[30];
};

void main() {
    union token identify = {
            .cookie="cookie"
    };
    char token[20]="tooken";
    identify.token[0]='t';
    int stop=1;
}
```

![image-20210417152925050](https://tva1.sinaimg.cn/large/008eGmZEgy1gpmrx8llgjj30p10pjwhi.jpg)

![image-20210417153008960](https://tva1.sinaimg.cn/large/008eGmZEgy1gpmrxyf3chj30nw0pttbl.jpg)

## 枚举类型

这个枚举类型是为了提高代码的可读性的，简单来说就是可以批量定义一批`int`类型的数据，比如下面的代码：

```c
#include "stdio.h"

enum rainbowColor {
    red,
    orange,
    yellow,
    green
};

void main() {
    printf("%d,%d,%d,%d\n",red,orange,yellow,green);
}
```

输出结果为：

> 0,1,2,3

也可以自己设定对应的值所对应的int型的值：

```c
#include "stdio.h"

enum rainbowColor {
    red,
    orange,
    yellow,
    green
};

enum setRainbowColor{
    Red,// 默认从0开始
    Orange=100,
    Yellow,// 如果没有没有设置对应的值，则从之前的值开始计数，比如这里就是 101
    Green // 这里是102
};

void main() {
    printf("%d,%d,%d,%d\n",red,orange,yellow,green);
    printf("%d,%d,%d,%d\n",Red,Orange,Yellow,Green);
}
```

## typedef

[预处理部分见这里](https://blog.csdn.net/YQXLLWY/article/details/115433319)

这里主要提一下typedef和`#define`之间的区别：

1. `#define`是面向预处理器的，`typedef`是面向编译器的
2. typedef只能定义类型名，但是不能定义值

这个的好处有2个：

1. 适配多种程序环境。这个就不举实际的计算机例子，而是举个生活中的例子，比如我定义：

```
typedef 豆腐脑 咸豆腐脑
```

这样的程序在北方的程序中没有问题，但是一旦到了南方，那就很麻烦了，所以我可以立刻修改成

```
typedef 豆腐脑 甜豆腐脑
```

这样在外部程序看来，使用的都是`豆腐脑`这个变量，只是我修改了其具体的值而已。

2. 定义复杂的类型，比如一些比较较真的人：

> typedef 奶茶套餐1 大杯，半糖，去冰，先加奶盖，再加芝士

这样下次你就只需要在代码中写`奶茶套餐1`，剩下的内容就交给编译器去帮你转换了。

