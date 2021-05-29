#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

// main path, test path, count
int main(int argc, char **argv) {
	if (argc != 4) {
		return 1;
	}
	char buf[1024];
	for (int i = 0; i < 1024; ++i) {
		buf[i] = 0;
	}
	sprintf(buf, "%s/time", argv[1]);
	int fd = open(buf, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	FILE *timer = fdopen(fd, "w");
	int x = strtol(argv[3], NULL, 10);
	struct timeval now;
	for (int i = 0; i < x; ++i) {
		if (i % 10 == 0) printf("%d\n", i + 1);
		for (int i = 0; i < 1024; ++i) {
			buf[i] = 0;
		}
		sprintf(buf, "%s/test_%d", argv[2], i + 1);
		int fd1 = open(buf, O_RDONLY);
		for (int i = 0; i < 1024; ++i) {
			buf[i] = 0;
		}
		sprintf(buf, "%s/%s/out_%d", argv[1], argv[2], i + 1);
		int fd2 = open(buf, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		for (int i = 0; i < 1024; ++i) {
			buf[i] = 0;
		}
		sprintf(buf, "%s/main", argv[1]);
		gettimeofday(&now, NULL);
		long long int beg = now.tv_sec * 1000000ll + now.tv_usec;
		if (!fork()) {
			dup2(fd1, 0);
			dup2(fd2, 1);
			close(fd1);
			close(fd2);
			execlp(buf, buf, NULL);
			exit(1);
		}
		close(fd1);
		close(fd2);
		while(wait(NULL) > 0);
		gettimeofday(&now, NULL);
		long long int end = now.tv_sec * 1000000ll + now.tv_usec;
		fprintf(timer, "%lld\n", end - beg);
		fflush(timer);
	}
}