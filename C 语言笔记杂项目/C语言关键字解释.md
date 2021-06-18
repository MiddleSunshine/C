# C语言关键字解释

## extern

[参考视频，在最后的10分钟的时候有说明](https://www.bilibili.com/video/BV13J411X7mW?p=5)

说到这个，就要先说到C语言的编译过程，这里那[gcc举例](https://blog.csdn.net/YQXLLWY/article/details/117163379)，就是C语言编译是一个一个文件编译好，然后再链接在一起的，所以当我们使用到其他`.c`文件中的内容时，就需要提前跟编译器说好，我这个值是其他地方定义好的，这里就是使用`extern`来说明的，然后编译器就知道了。

比如这里拿`file2.c`来说明：

```c
#include<stdio.h>

extern int a;
extern short getOne(void);

int main(int argc, char const *argv[])
{
	printf("a is %d\n", a);
	printf("function result is %d",getOne());
	return 0;
}
```

然后运行`gcc -c file2.c`，这个时候编译是通过的，自动生成`file2.o`

然后我们其他文件中补上这两块的内容，这里拿`file1.c`为例：

```c
int a=1;

short getOne(void){
	return 1;
}
```

然后我们编译这个文件：`gcc -c file1.c`，也自动生成`file1.o`。

然后我们进行链接：`gcc file1.o file2.o -o main`，运行结果`./main`，输出结果为：

```bash
a is 1
function result is 1
```

然后有了上面的内容，就可以来说`static`了。

## static

