#include "function.h"
#include "sub.h"

int main(int argc, char const *argv[])
{
    printOne();
    return 0;
}

/**
 * 这里的内容很绕，但是解开就很简单了
 * 首先，include的作用就是把整个文件编译的时候整个包含进来
 * 这个时候如果包含的 变量的定义，那么当其他文件包含这个文件的时候，就会出现同一个变量定义两次的bug
 * 所以 .h 文件中都是定义形式
 * 然后编译的时候需要加上对应的实现文件，以上面的例子，编译的时候需要加上：
 * gcc main.c function.c -o main
 * 真正的实现函数 function.c
 * 本质上类似：
 * extern void printOne(void);
 **/