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

// test set, names
int main(int argc, char **argv) {
	char buf[1024];
	for (int i = 0; i < 1024; ++i) {buf[i] = 0;}
	sprintf(buf, "%s_ans", argv[1]);
	int fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	FILE *to = fdopen(fd, "w");
	for (int j = 2; j < argc; ++j) {
		fprintf(to, "%s", argv[j]);
		if (j + 1 == argc) fprintf(to, "\n");
		if (j + 1 != argc) fprintf(to, " ");
	}
	for (int i = 0; i < 100; ++i) {
		fprintf(to, "%d: ", i + 1);
		for (int j = 2; j < argc; ++j) {
			for (int i = 0; i < 1024; ++i) {buf[i] = 0;}
			sprintf(buf, "%s/%s/out_%d", argv[j], argv[1], i + 1);
			int fd = open(buf, O_RDONLY);
			FILE *fr = fdopen(fd, "r");
			long long x;
			fscanf(fr, "%lld", &x);
			close(fd);
			fprintf(to, "%lld", x);
			if (j + 1 == argc) fprintf(to, "\n");
			if (j + 1 != argc) fprintf(to, " ");
		}
	}
	fflush(to);
	close(fd);
}