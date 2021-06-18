# C语言之预处理

这个本来没啥讲的，就是我发现了一个很有意思的东西：

```c
#include "stdio.h"

#define PI 3
#define S PI*r*r

int main() {
    int r=3;
    printf("%d\n",S);
    return 0;
}
```

注意这里看到定义预处理的时候：`#define S PI*r*r`，有一个`r`的值是没有定义的，但是这样是没有问题的，真的有意思。

至于为什么可以这么写，是因为这里只是预处理，在真正编译的时候，会被替换成具体的值，即会被替换成下面的形式：

```c
#include "stdio.h"

int main() {
    int r=3;
    printf("%d\n",3*r*r);
    return 0;
}
```

所以代码不会有问题。

