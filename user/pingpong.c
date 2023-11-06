#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	char received_message[4];
	int p[2];
	pipe(p);
	int pid = fork();
	if (pid == 0) {
		read(p[0], received_message, 4);
		pid = getpid();
		printf("%d: got %s\n", pid, received_message);
		write(p[1], "pong", 4);
		close(p[0]);
		close(p[1]);
	} else if (pid < 0) {
		printf("couldn't create child process :(\n");
	} else {
		write(p[1], "ping", 4);
		wait(0);
		read(p[0], received_message, 4);
		pid = getpid();
		printf("%d: got %s\n", pid, received_message);
		close(p[0]);
		close(p[1]);
	}
	exit(0);
}
