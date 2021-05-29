#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
n, m
W
gr
*/

int main() {
	srand(time(NULL));
	for (int i = 0; i < 100; ++i) {
		if (i % 10 == 0) {
			printf("%d\n", i + 1);
		}
		char name[100];
		for (int j = 0; j < 100; ++j) {
			name[j] = 0;
		}
		sprintf(name, "test_%d", i+1);
		int fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		FILE* to = fdopen(fd, "w");
		int n = i * 50 + 50;
		int* W = malloc(n * sizeof(int));
		if (i % 10 < 3) {
			for (int j = 0; j < n; ++j) {
				W[j] = rand() % 10 + 1;
			}
		} else if (i % 10 < 6) {
			for (int j = 0; j < n; ++j) {
				W[j] = rand() % 100 + 1;
			}
		} else {
			for (int j = 0; j < n; ++j) {
				W[j] = rand() % 1000000 + 1;
			}
		}
		int m = rand() % (n * (n - 1) / 2);
		printf("%d %d\n", n, m);
		for (int j = 0; j < n; ++j) {
			fprintf(to, "%d", W[j]);
			if (j + 1 == n) fprintf(to, "\n");
			else fprintf(to, " ");
		}
		fprintf(to, "%d %d\n", n, m);
		while (m) {
			int a = rand() % n;
			int b = rand() % n;
			if (a == b) {
				continue;
			}
			fprintf(to, "%d %d\n", a + 1, b + 1);
			--m;
		}
		fflush(to);
		free(W);
		close(fd);
	}
}