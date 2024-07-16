#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/fcntl.h>

#define FILENAME "motd"

int main(void)
{
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	struct stat s;
	if (stat(FILENAME, &s) == -1) {
		printf("Error getting file stat\n");
		return 1;
	}

	if (s.st_uid == 0) {
		printf("This is the wrong file motd\n");
		return 1;
	}

	int fd = 0;
	if ((fd = open(FILENAME, O_RDONLY)) == -1) {
		printf("Error opening file\n");
		return 1;
	}
	char buffer[4096];
	size_t rdsz = 0;

	while ((rdsz = read(fd, buffer, 4096)) != 0) {
		fwrite(buffer, 1, rdsz, stdout);
	}

	close(fd);
}
