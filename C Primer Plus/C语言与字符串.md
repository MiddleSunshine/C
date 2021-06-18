# C语言与字符串

## 字符串本质

C语言的字符串本质上就是字符的数组。

```c
#include "stdio.h"

int main() {
    // todo 这里特意加上 const 是为了说明这个值是不可修改的
    // 更加通俗的理解就是开辟了一块只读的存储空间专门存储字符串："hello world"，然后将首地址赋值给 constString 这个指针
    const char* constString="hello world";
    // 这个值则是开辟了一块连续的地址空间，用来存储 "hello world"
  	// 这种写法编译器会自动计算数组的大小
    char changeableString[]="hello world";
    // puts 输出的时候会在后面自动加上换行符
    puts(constString);
    puts(changeableString);
}
```

[参考B站视频：小甲鱼 C语言视频教程](https://www.bilibili.com/video/BV1Ps411U7tS?p=47)

## 字符串的输入

### gets()：读取键盘输入

这个有**缓冲区溢出**的风险，即类似下面的内容：

```c
#include "stdio.h"

int main() {
    char paramStoreInput[10];
    gets(paramStoreInput);
    puts(paramStoreInput);
}
```

在编译完成时有下面的警告：

> warning: this program uses gets(), which is unsafe.

因为这个函数会将所有输入都存入`paramStoreInput`中，即使输入的字符串超过设定的大小，还是会继续占用后面的存储地址，即所谓的**缓冲区溢出**。所以编译器会有报警。

### fgets()

这个函数可以指定读取的值大小，不过问题在于它会连换行符一起带进来：

```c
#include "stdio.h"

#define STRING_LENGTH 10

int main() {
    char paramStoreInput[STRING_LENGTH];
    fgets(paramStoreInput,STRING_LENGTH,stdin);
    fputs(paramStoreInput,stdout);
}
```

`fgets()`这个参数有3个参数：

1. 变量的存储值
2. 变量所存储的字符的最大值
3. 数据来源，像上面我使用了`stdin`，即标准输入，标准输入的内容可以看这里：[标准输入/输出](https://blog.csdn.net/YQXLLWY/article/details/115149687)

由于有第二个参数，所以可以限制参数的大小，实验一下就能得到：

> hello world c
> hello wor

当我输入`hello world c`的时候，输出只有`hello wor`，输出只有9个字符串，是因为`fgets()`只能存储**所能存储的字符串的最大值-1**的大小。

但是当我输入的值比较小的时候，比如：

> hello（这里我敲一下 Enter，表示换行符）
> hello
>
> 

它会将换行符一起存储进来，而`gets()`则会忽视换行符。

### gets_s() / s_gets()

这两个我本地说没有这两个函数，所以不知道具体的情况了。

### scanf()函数

这个本质上虽然是读取字符的，但是可以配合`%s`来读取字符串，同时，也可以指定字符串的长度：

```c
#include "stdio.h"

#define STRING_LENGTH 10

int main() {
    char paramStoreInput[STRING_LENGTH];
    scanf("%10s",paramStoreInput);
    printf("%s",paramStoreInput);
}
```

这个时候分两种情况：

- 输入的字符串超过10：只读取前10个字符，存储入数组中
- 输入的字符串遇到空白内容（空行，空格，制表符，换行符）：忽略空白内容，存储前面的字符

## 字符串的输出

### puts

```c
#include "stdio.h"

int main() {
    char paramStoreInput[]="hello world";
    puts(paramStoreInput);
    // todo 这里演示如何从指定长度输出，下面3种写法是一样的
    puts(&paramStoreInput[5]);
    puts(&(paramStoreInput[5]));
    puts(paramStoreInput+5);
    // todo 这种写法是错误的
    puts((&paramStoreInput)[5]);
}
```

但是这个函数和`gets`一样都有可能会读取意外的内存数据：

```c
#include "stdio.h"

int main() {
    char paramStoreInput[]={'h','e','l','l','o'};
    puts(paramStoreInput);
}
```

输出的时候因为`paramStoreInput`中没有定义字符串的结尾，所以它会一直按照内存读下去，直到读到字符串结尾为止。

### fputs

这个函数在上面用过了，见`fgets()`。

### printf()

这个就不用讲了吧，老朋友了。

## 字符串相关函数

简单来说就是一些：

- 字符串拷贝
- 字符串黏贴
- 字符串比较
- 字符串搜索
- 字符串长度

这些类型的函数。

```c
#include "stdio.h"
#include "string.h"

void compareString(char*,char*);

int main() {
    char paramStoreInput[50]="hello world";
    printf("string length is %d\n",strlen(paramStoreInput));
    strcat(paramStoreInput," c");
    printf("%s\n",paramStoreInput);
    // todo 如果这里定义的值太小，会因为缓冲区的问题导致输出有问题，但是内容是存储下来的
    char copyString[20];
    strcpy(copyString,paramStoreInput);
    printf("%p string is %s\n",copyString,copyString);
    printf("%p string is %s\n",paramStoreInput,paramStoreInput);
    compareString(paramStoreInput,copyString);

    char limitLengthCopyString[5];
    // todo 这个函数可以采用第3个参数强制指定复制的长度
    strncpy(limitLengthCopyString,paramStoreInput, sizeof(limitLengthCopyString)-1);
    limitLengthCopyString[4]='\0';
    printf("%p string is %s\n",limitLengthCopyString,limitLengthCopyString);
    printf("%p string is %s\n",paramStoreInput,paramStoreInput);
    compareString(limitLengthCopyString,paramStoreInput);
}

void compareString(char *string1,char *string2){
    int result=strcmp(string1,string2);
    if (result==0){
        printf("two strings are same\n");
    } else if (result>0){
        printf("string one is bigger than string two\n");
    } else{
        printf("string one is smaller than string two\n");
    }
}
```

这里就是一些例子。

## 读取执行时的参数

就是执行编译后的脚本时，带上参数，编译后的文件为`C`：

```c
#include "stdio.h"

int main(int argc,char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        printf("param number is %d,input string are %s\n",argc,argv[i]);
    }
}
```

输入内容：

> ./C --param1=1 --param2=c

输出：

> param number is 3,input string are ./C
> param number is 3,input string are --param1=1
> param number is 3,input string are --param2=c

