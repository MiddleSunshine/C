#include <stdio.h>

int main(int argc, char const *argv[])
{
	int a=1;
	a=!a++;
	printf("a is %d\n",a);
	return 0;
}