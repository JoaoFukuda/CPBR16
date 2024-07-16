#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *password = "eachintheshell";

void win()
{
	system("cat ./flag");
	exit(0);
}

int main(void)
{
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	srand(time(0));

	char buffer[strlen(password) + 1];
	fgets(buffer, strlen(password) + 1, stdin);

	if (strlen(buffer) != strlen(password))
		goto errado;

	for (int i = 0; i < strlen(password); i++) {
		char c = password[i] ^ rand();
		if (c != buffer[i])
			goto errado;
	}

	win();

errado:
	printf("Errado, tente novamente!\n");
}
