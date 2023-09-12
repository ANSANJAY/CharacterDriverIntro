#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE	"/dev/msg"

int main()
{
	int fd;
	int retval;
	char buffer[10];
	int i;

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();

	for (i = 0; i < 250; i++) {
		retval = write(fd, "hello", 5);
		printf("Write retval:%d\n", retval);
		if (retval != 5)
			break;
	}
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
