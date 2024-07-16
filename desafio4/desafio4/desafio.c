#include <stdio.h>

int main(void)
{
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	char buff[64] = {0};

	scanf("%s", buff);
	printf(buff);
	printf("\n");

	scanf("%s", buff);
	printf(buff);
	printf("\n");
}
