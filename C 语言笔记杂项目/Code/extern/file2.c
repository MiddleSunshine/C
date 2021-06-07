#include<stdio.h>

extern int a;
extern short getOne(void);

int main(int argc, char const *argv[])
{
	printf("a is %d\n", a);
	printf("function result is %d",getOne());
	return 0;
}