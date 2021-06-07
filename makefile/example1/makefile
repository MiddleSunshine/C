# 这里就是为了演示makefile的自动推导功能，就是 main.o 肯定来自 main.c，会自动执行 gcc -c -o main.o main.c，functions.c也是一样的效果
index: main.o functions.o
	gcc main.o functions.o -o main

.PHONY:
clean:
	rm -rf main.o functions.o

