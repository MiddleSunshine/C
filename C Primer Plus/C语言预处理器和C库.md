# C语言预处理器和C库

## C语言编译前工作

下面的步骤发生在程序交给预处理器前，由编译器处理。

1. 字符映射，即将代码中出现的字符映射到源字符集。啥叫源字符集呢？就是程序理解的字符集。
2. 搜索`\`以及后面有个换行符的代码，将其整合成一行，比如：

```c
printf("hello \
       world\n");
```

会被转换成：

```c
printf("hello world\n");
```

3. 将代码文本中的：
   - 序列
   - 空白序列
   - 注视序列

替换成一个空格，简单来说就是将代码中的非代码部分去掉。

## #define详细内容

首先就是在[C语言预处理器](https://blog.csdn.net/YQXLLWY/article/details/115433319)中说过，可以在其中使用参数，本质是对其中的值在代码开始编译前由预处理器进行替换，但是如果情况复杂一点，比如下面这样时：

```c
#include "stdio.h"
// 在这里定义了 x
#define DOUBLE(x) x*x

void main() {
    // 但是在下面直接使用了原本的值
    printf("%d\n", DOUBLE(2));// 这里还有，2替换X，变成 2*2，结果为4
    printf("%d\n", DOUBLE(2+3));// 这里很有意思，结果是11，我不知道是怎么替换的，只是说明这种情况下要注意
}
```

或者是这个例子：

```c
#include "stdio.h"

#define StringISize(x) printf("x is %s\n",x)

void main() {
    char *string="hello world";
    StringISize(string);
}
```

输出：`x is hello world`。

但是如果我把代码修改成这个样子：

```c
#include "stdio.h"
// 这里我在第一个 x 前面加上了 # 的符号
#define StringISize(x) printf(#x" is %s\n",x)

void main() {
    char *string="hello world";
    StringISize(string);
}
```

结果输出：`string is hello world`，`#x`直接替换成了变量名，迷之操作。。。。。。

接下来还有一种迷之操作：

```c
#include "stdio.h"
// 这里的 ## 是粘合剂的效果，指定替换的部分
#define X(n) x##n

void main() {
    int X(1)=12;// 这里等于是 int x1=12;
    int X(2)=13;// int x2=13;
    printf("x1 is %d,x2 is %d\n", X(1), X(2));
}
```

## #include

这里就是：`<>`和`""`这两种方式的区别：

```c
#include <stdio.h>//在系统目录中
#include "3.h"// 在当前目录中寻找

void main() {

}
```

## #undef

顾名思义，就是取消掉`#define`设置的值，比如下面的代码：

```c
#include <stdio.h>//在系统目录中

#define PI 3.1415926
#undef PI

void main() {
    printf("PI is %f",PI);// 这里的PI是不存在的
}
```

## # if #else 等

这个就是顾名思义，设定条件，比如下面的代码：

```c
#include <stdio.h>

#define SYSTEM_OPERATION_WINDOWS 1

#if SYSTEM_OPERATION_WINDOWS==1
    #include "3.h"
#else
    #include "4.h"
#endif

#ifdef SYSTEM_OPERATION_WINDOWS
    #include "5.h"
#endif

void main() {

}
```

## 预定义宏

下面就是举了一些例子而已。

```c
#include <stdio.h>

void main() {
    printf("The date of today is %s and the time is %s and datetime is %s\n",__DATE__,__TIME__,__TIMESTAMP__);
    printf("File Path is %s and the file is %s\n",__FILE__,__FILE_NAME__);
    printf("This line is %d\n",__LINE__);
}
```

## #error

这个就是告诉编译器，这里有问题：

```c
#include <stdio.h>

#ifdef DEBUG_MODE
// 在 error 后面可以跟一个字符串，而且不需要“”
#error this file is wrong
#endif

void main() {

}
```

## 范型选择

比如下面这个代码：

```c
#include <stdio.h>
// _Generic 简单来说就是根据 x 的参数类型返回不同的值，default 指定一个默认值，跟switch很像
#define MESSAGE(x) _Generic(x,int:1,float:2.2,char*:"error",default:"with out setting")

void main() {
    int i;
    printf("default i is %d\n", MESSAGE(i));
    char* s;
    printf("default s is %s\n", MESSAGE(s));
}
```

## 内联函数：inline

首先说一下啥是内联函数，就是编译器可能会采用代码替换的方式，而不是函数调用的方式来实现内联函数，比如：

```c
#include <stdio.h>

void showAge(int age){
    printf("your age is %d\n",age);
}

void main() {
    showAge(1);
    showAge(20);
}
```

这种传统的方式就是函数调用，而如果：

```c
#include <stdio.h>

inline void showAge(int age){
    printf("your age is %d\n",age);
}

void main() {
    showAge(1);// 这里就是会编译器替换成 printf("your age is %d\n",1);
    showAge(20);// 这里也是 printf("your age is %d\n",20);
}
```

接下来就是内联函数的一些特性了：

1. 内联函数是没有地址的，也对，毕竟就是拿来替换的
2. 内联函数必须和调用的函数在同一个文件中，否则编译器找不到，所以如果需要共用，可以放在头文件中

## _Noreturn

```c
#include <stdio.h>

_Noreturn error(char *string){
    printf("This File Stop @%s\n",__FILE__);
    printf("%s\n",string);
}

void main() {
    error("stop here");
    printf("这部分代码不会执行了\n");
}
```

首先，这个参数表示当前函数执行后不会返回`main`函数，类似`exit()`的效果。