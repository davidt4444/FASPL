#include <stdio.h>
int main()
{
	FILE * test;
	char c;
	test = fopen("test/string.faspl", "r");
	
	while(1)
	{
		c = getc(test);
		printf("%c", c);
	}
	
	fprintf(stdin, "hello world!");
}