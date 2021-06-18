# C语言之函数指针

[参考B站视频：小甲鱼C语言视频教程](https://www.bilibili.com/video/BV1Ps411U7tS?p=47&spm_id_from=pageDriver)

在开始前，问一个问题，函数是否是类似`int a=1;`这样的变量？

答案如果是是的。那么是否可以定义一个函数类型的变量呢？

答案如果也是是的，那么怎么定义呢？

```c
int bigger(int,int);
```

类似这样，就定义了一个函数类型的变量，其接受两个`int`类型的输入作为参数。

具体看下面的例子：

```c
#include "stdio.h"

int main() {
    int bigger(int,int);
    int smaller(int,int);
    int a=3,b=4;
    printf("%d is bigger than %d\n",bigger(a,b),smaller(a,b));
}

int bigger(int a,int b){
    return a>b?a:b;
}

int smaller(int a,int b){
    return bigger(a,b)==a?b:a;
}
```

这样乍看定义一个函数变量是多余的，但是如果加上指针会如何？可以定义一个指针指向这个函数变量吗？

```c
#include "stdio.h"

int main() {
    int bigger(int,int);
    int smaller(int,int);
    int a=3,b=4;
    printf("%d is bigger than %d\n",bigger(a,b),smaller(a,b));
    // 如何定义一个函数类型的指针
    int (*pointerBigger)(),(*pointerSmaller)();
    // 如何对这个函数类型的指针赋值
    pointerBigger=bigger;
    pointerSmaller=smaller;
    // 如何调用这个函数指针所对应的函数
    printf("%d is bigger than %d\n",(*pointerBigger)(a,b),(*pointerSmaller)(a,b));
}

int bigger(int a,int b){
    return a>b?a:b;
}

int smaller(int a,int b){
    return bigger(a,b)==a?b:a;
}
```

这里采用了函数类型的指针来调用对应的函数。重点在于如何定义一个函数类型的指针，如何对这个函数类型的指针赋值，如何调用这个函数指针所对应的函数。

这里再举一个例子，模拟实现一个计算器：

```c
#include "stdio.h"

int add(int a,int b){
    return a+b;
};
int delete(int a,int b){
    return a-b;
};
int multiplication(int a,int b){
    return a*b;
};
int division(int a,int b){
    if (b==0){
        return 0;
    }
    return a/b;
};

int Calculator(int a,int b,int (*function)()){
    return (*function)(a,b);
}

int main() {
    int a=1,b=2;
    printf("%d+%d=%d\n",a,b,Calculator(a,b,add));
    printf("%d-%d=%d\n",a,b,Calculator(a,b,delete));
    printf("%d*%d=%d\n",a,b,Calculator(a,b,multiplication));
    // todo 这里是有问题的，因为统一了返回类型为 int，但是实际上返回的类型应该是 float
    printf("%d/%d=%d\n",a,b,Calculator(a,b,division));
    return 0;
}
```



