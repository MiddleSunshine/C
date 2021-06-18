#include <stdio.h>

int main(int argc, char const *argv[])
{
	int b=0;
	int a=b++;
	printf("a is %d\n", a);
	printf("b is %d\n",b);
	return 0;
}