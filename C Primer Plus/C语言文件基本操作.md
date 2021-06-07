# C语言文件基本操作

基本例子：

```c
#include "stdio.h"

int main(){
    // 获取文件地址指针，或者叫句柄
    FILE *fileHandler= fopen("这里写一个文件的绝对路径","r");
    int ch;
    // 读取内容
    while ((ch= getc(fileHandler))!=EOF){
        // 输出内容到标准输出
        putc(ch,stdout);
    }
    // 释放句柄
    fclose(fileHandler);
    return 0;
}
```

[getc和putc的内容见这里](https://blog.csdn.net/YQXLLWY/article/details/115441863)

在开始介绍前，还有一些基础只是，首先就是文件的分类：

- 文本文件：简单来说就是采用各种编码保存的文本内容，比如中文是GBK编码，或者更加广泛的UTF-8编码
- 二进制文件：比如图片，音频等，就是二进制文件

当然，所有计算机上的内容都是采用二进制来保存的，上面的更加像是我们对文件的一种抽象的分类，与之对应的就是文本内容，二进制内容。文本文件格式，二进制文件格式。

-----

接下来还有一个概念就是I/O的级别。有底层I/O，即操作系统提供的I/O服务。标准高级I/O，即C库提供的I/O。这就类似于将底层I/O进行封装，封装好了给你使用一样，下面介绍的都是标准I/O。

## 文件的打开模式

- r：打开一个只读的文件
- w：打开一个只写的文件，文件内容会被置空
- a：打开只写的文件，但是是在后面追加内容的形式，不会删除老的内容，append
- r+：打开可读写的文件
- w+：打开可读写的文件，同样会将文件内容置空
- a+：打开可读写的文件，以追加文件内容的形式
- rb,wb,ab,ab+,a+b,wb+,w+b,rb+,r+b：上面操作对二进制文件的的操作
- wx,wbx,w+x,wb+x,w+bx......：关键字在x上，这个关键点在于独占性，即打开后就会独占该文件，如果不能做到独占，就打开失败。

## fprintf、fscanf

这个其实用起来比较别扭，但是最主要的就是要搞懂什么是标准输入输出，什么是输出到文件。[标准输入输出的内容，即stdin的内容见这里](https://blog.csdn.net/YQXLLWY/article/details/115149687)

```c
#include "stdio.h"

int main(){
    FILE *fileHandler= fopen("一个本地文件的绝对路径","a+");
    char inputString[10];
    int stopPrint=0;
    while (!stopPrint){
        // 标准输入，即键盘
        fscanf(stdin,"%10s",inputString);
        // 输入的第一个字母为q时停止输入
        if(inputString[0]=='q'){
            stopPrint=1;
        }else{
            // 输出到文件
            fprintf(fileHandler,"%s\n",inputString);
        }
    }
    fclose(fileHandler);
}
```

上面的代码会一直读取输入，以追加内容的形式，将其输出到开始制定的文件中去。

## fseek和ftell：文件的随机访问

说是随机访问，本质就是可以指定文件的偏移量，一个偏移量等于1个字符。比如下面的代码：

```c
#include "stdio.h"

int main(){
    FILE *fileHandler= fopen("一个文件的路径","r+");
    // ftell 获取文件的位置
    printf("Position is %ld\n", ftell(fileHandler));
    // 设置2个偏移量，SEEK_SET设置开始计算的位置为开头，2L则是设定偏移量为2个字符
    fseek(fileHandler,2L,SEEK_SET);
    printf("Position is %ld\n", ftell(fileHandler));
    char inputString[50];
    fscanf(fileHandler,"%50s",inputString);
    fprintf(stdout,"%s\n",inputString);
    fclose(fileHandler);
}
```

这里详细解释一下fseek的3个参数：

- 第一个参数，文件的句柄
- 第二个参数，偏移量，如果是正数就从第三个参数开始往后数，如果是负数，就从第三个参数标明的位置往前数，参数类型为`long`。
- 第三个参数，指定开始计算的位置，有3个参数：
  - SEEK_SET：文件开始处
  - SEEK_CUR：当前位置
  - SEEK_END：文件的结尾

比如说：`fseek(fileHandler,-10,SEEK_END)`就是从文件结尾处开始，读取10个字符的长度。

------

这样已经可以处理长度为`long`的文件了，但是如果是长度超过`long`所能表示的范围，就需要用到下面两个参数了：

### fgetpos和fsetpos

首先说`fsetpos`支持两个参数，第一个同样是文件句柄，但是第二个就不是long类型的数据了，而是`fpos_t`类型的数据，这个数据可以使用`fgetpos`来获得，比如下面的代码：

```c
#include "stdio.h"

int main(){
    FILE *fileHandler= fopen("/Users/yangqingxian/Desktop/github/C/README2.md","r+");
    fpos_t pos;
    char storeData[50];
    fscanf(fileHandler,"%s",storeData);
    printf("%s\n",storeData);
    // 获取当前位置的值
    fgetpos(fileHandler,&pos);
    pos+=3LL;
    // 修改偏移量
    fsetpos(fileHandler,&pos);
    fscanf(fileHandler,"%s",storeData);
    printf("%s\n",storeData);
    fclose(fileHandler);
}


```

这里逐层找进去，就能发现`fpos_t`的本质就是`long long`，所以这里使用`3LL`。

但是这里很奇怪，偏移量不是一个字符一个偏移量的。





