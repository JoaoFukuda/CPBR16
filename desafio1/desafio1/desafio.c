#include <stdio.h>

void cumprimentar(char *nome) {
	char buffer[64];
	sprintf(buffer, "Ola, %s!\n", nome);
	printf(buffer);
	printf("Gostaria de deixar alguma mensagem?\n> ");
	scanf("%s", buffer);
}

int main(void)
{
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	char *nome = NULL;
	scanf("%ms", &nome);
	cumprimentar(nome);
}
