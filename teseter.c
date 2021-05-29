#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
	if (argv != 4) {
		return 1;
	}
	char buf[1024];
	for (int i = 0; i < 1024; ++i) {
		buf[i] = 0;
	}
	sprintf("%s/time", argv[1]);
	int fd = open(buf, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	FILE *timer = fdopen(fd, "w");
	int x = strtol(argv[3], NULL, 10);
	for (int i = 0; i < x; ++i) {
		printf("%d\n", i + 1);
		for (int i = 0; i < 1024; ++i) {
			buf[i] = 0;
		}
		sprintf("%s/test_%d", argv[2], i + 1);
		int fd1 = open(buf, O_RDONLY);
		for (int i = 0; i < 1024; ++i) {
			buf[i] = 0;
		}
		sprintf("%s/%s/out_%d", argv[1], argv[2], i + 1);
		int fd2 = open(buf, O_RDONLY);
		for (int i = 0; i < 1024; ++i) {
			buf[i] = 0;
		}
		sprintf("%s/main", argv[1]);
		int beg = time();
		if (!fork()) {
			dup2(1, fd1);
			dup2(0, fd2);
			close(fd1);
			close(fd2);
			execlp(buf, buf, NULL);
			exit(1);
		}
		close(fd1);
		close(fd2);
		while(wait(NULL) > 0);
		int end = time();
		fprintf(timer, "%d\n", end - beg);
		fflush(timer);
	}
}