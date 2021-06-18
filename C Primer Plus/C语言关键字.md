# C语言关键字：const / volatile / restrict

## const 与指针

这一块很有意思，就是不同的写法限定的内容是不一致的，首先我们知道加上`const`后该变量就会变成只读的，但是对于指针，是限制该指针指向新的地址，还是限定指针所指向的内容变成只读的：

```c
const float * pf;
float const * pf2;
```

这两种写法是一样的。这种方式就是限定无法通过pf修改所指向的地址的内容：

```c
#include "stdio.h"

int main(){
    float constParam=1.0,constParam2=2.0;
    // 首先令 pf 指向 constParam的地址
    const float * pf=&constParam;
    // 之后修改为指向 constParam2 的地址
    pf=&constParam2;
    printf("%f\n",*pf);// 输出 2
    // 可以通过变量来修改该地址下的值
    constParam2=2.1;
    printf("%f\n",*pf);// 输出 2.1
    // 但是不能通过指针修改
    // *pf=2.2;
}
```

-------

```c
float * const pf;
```

这种写法就是限制pf指向新的地址。

```c
#include "stdio.h"

int main(){
    float constParam=1.0,constParam2=2.0;
    // 令 pf 指向 constParam 的地址
    float * const pf=&constParam;
    // 这样就不能让 pf 指向新的地址了
    // pf=&constParam2;
    *pf=1.1;// 但是可以通过 pf 修改其所指向的内容
    printf("%f\n",*pf);
    constParam=1.2;
    printf("%f\n",*pf);
}
```

## const 指针与函数

根据上面的知识，我们知道下面的变量有如下限制：

```c
void constParamFunction(const float *constParam){
    // 限制其修改其中的内容
    // *constParam=2.2;
    printf("%f\n",*constParam);
}
// 限制其将指针指向新的地址
void constParamFunction2(float * const constParam){
    // 但是可以修改其中的值
    *constParam=*constParam+1;
    printf("%f\n",*constParam);
}
```

但是有意思的是，在函数中，上面变量的限制会取消：

```c
#include "stdio.h"

void constParamFunction(const float *constParam);
void constParamFunction2(float * const constParam);

int main(){
    float constParam=1.0,constParam2=2.0;
    // 定义了两种变量
    const float *pf=&constParam;
    float * const pf2=&constParam2;
    // 首先就是两种变量函数都可以接受，即使函数已经确定了变量的种类
    constParamFunction(pf);
    constParamFunction(pf2);
    // 其次就是变量的限制在函数中不生效，例如这里，pf本身是不能修改其所指向的值的，但是在函数中却可以
    constParamFunction2(pf);
    constParamFunction2(pf2);
    // 这里可以看到修改生效
    printf("%f\n",*pf);
    printf("%f\n",*pf2);
}

void constParamFunction(const float *constParam){
    // 限制其修改其中的内容
    // *constParam=2.2;
    printf("%f\n",*constParam);
}
// 限制其将指针指向新的地址
void constParamFunction2(float * const constParam){
    // 但是可以修改其中的值
    *constParam=*constParam+1;
    printf("%f\n",*constParam);
}
```

输出：

> // constParamFunction 的输出
>
> 1.000000
> 2.000000
>
> // constParamFunction2 的输出，值都+1
>
> 2.000000
> 3.000000
>
> // 最后验证输出是否发生了修改
>
> 2.000000
> 3.000000

这就很有意思了。

## volatile

先看情况：

![image-20210412151113935](https://tva1.sinaimg.cn/large/008eGmZEgy1gpgzaricopj30s906t3yu.jpg)

这种情况下，因为x都是只读的，所以编译器会采用优化策略，将x的值保存在寄存器中，方便CPU读写，即**高速缓存**。

但是，如果在多进程，或者多线程的情况下，除非显式告诉编译器，x所代表的地址中的值不会被其他进程，线程修改，否则编译器也不敢再将x放在寄存器中，万一你这倒霉玩意在代码1中没有修改这个值，在代码2中将这个值修改了，到时候就会出现问题了。

所以`volatile`就是起这个说明的作用，但是它是告诉编译器，这个值在其他进程，线程中会发生修改。当然，也可以配合上面的const使用，而且它跟const的左右位置是没有关系的。

## restrict

这个参数就很有意思了，首先它仅仅针对指针使用，其次它表明当前指针是唯一操作该块地址的指针，比如：

```c
#include "stdio.h"
#include "stdlib.h"

void showResult(int *result,char* extraString){
    int i=0;
    printf("%s\n",extraString);
    while (i<3){
        printf("%d\n",result[i]);
        i++;
    }
}

int main(){
    int array[]={1,2,3};
    int * pointer=array;
    // 这里使用 malloc 申请到的内存
    int * restrict onlyOnePointer= malloc(3* sizeof(int));
    for (int i = 0; i < 3; ++i) {
        onlyOnePointer[i]=i;
    }
    for (int i = 0; i < 3; ++i) {
        array[i]+=i;
        pointer[i]+=1;
        array[i]*=2;
      	pointer[i]+=2;
        onlyOnePointer[i]+=1;
        onlyOnePointer[i]+=2;
    }
    showResult(array,"array");
    showResult(pointer,"pointer");
    showResult(onlyOnePointer,"onlyPointer");
}
```

[malloc的内容见这里](https://blog.csdn.net/YQXLLWY/article/details/115617091)。在上面的代码中：

```c
onlyOnePointer[i]+=1;
onlyOnePointer[i]+=2;
```

因为`restrict`关键字，所以编译器知道`onlyPointer`是唯一操作其的指针，所以可以将上面的语句优化为：

```c
onlyOnePointer[i]+=3;
```

但是同样的：

```c
pointer[i]+=1;
......
pointer[i]+=2;
```

却不能合并，因为中间还有一个`array`是操作同样的地址的参数的，如果合并了就会出现问题。

所以这个关键字就是告诉编译器，可以采取一些优化策略。同时也是告诉开发人员，当前指针是唯一操作其地址的数据。

### restrict 与函数

这个是啥意思呢？比如下面的函数形参：

```c
// 两个指针因为都要是对其地址的唯一指针，所以肯定不能是指向同一个地址
void copyString(char* restrict s1,char* restrict s2);
// 这个就没啥限制了
void copyString2(char* s1,char* s2);
```

## 奇怪的语法

在上面讲解过const与指针的关系，但是关于其还有一种很诡异的写法：

```c
// 原版
void ofMouth(int * const a1);
// 诡异版写法
void ofMounth2(int al[const]);
```

上面两种写法效果是一样的。

-------

restrict也有类似的诡异写法：

```c
// 原版
void ofMouth(int * restrict a1);
// 诡异版写法
void ofMounth2(int a1[restrict])
```


