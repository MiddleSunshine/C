#include <stdio.h>
#include "function.c"
#include "debug.c"

int main(int argc, char const *argv[])
{
    /**
     * 这段代码是有问题的，因为 debugNumber 定义了两次
     * 在 main 中定义一次
     * 在 debug.c 中又定义了一次
     * 可以通过运行
     * gcc main.c -o main
     * 看一下结果
     **/
    printf("%d\n",debugNumber);
    showDebugNumber();
    return 0;
}
