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
		int n = i / 10 + 2;
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
		int gr[n][n];
		if (i % 10 % 3 == 0) {
			for (int j = 0; j < n; ++j) {
				for (int k = j + 1; k < n; ++k) {
					gr[j][k] = gr[k][j] = rand() % 2;
				}
			}
		} else if (i % 10 % 3 == 1) {
			for (int j = 0; j < n; ++j) {
				for (int k = j + 1; k < n; ++k) {
					gr[j][k] = gr[k][j] = rand() % 4;
				}
			}
		} else {
			int m = rand() % (n * (n - 1) / 2);
			while (m) {
				int a = rand() % n;
				int b = rand() % n;
				if (a == b) {
					continue;
				}
				gr[a][b] = gr[b][a] = 1;
				--m;
			}
		}
		int m = 0;
		for (int j = 0; j < n; ++j) {
			for (int k = j + 1; k < n; ++k) {
				if (gr[j][k]) {
					++m;
				}
			}
		}
		fprintf(to, "%d %d\n", n, m);
		for (int j = 0; j < n; ++j) {
			fprintf(to, "%d", W[j]);
			if (j + 1 == n) fprintf(to, "\n");
			else fprintf(to, " ");
		}
		for (int j = 0; j < n; ++j) {
			for (int k = j + 1; k < n; ++k) {
				if (gr[j][k]) {
					fprintf(to, "%d %d\n", j + 1, k + 1);
				}
			}
		}
		fflush(to);
		free(W);
		close(fd);
	}
}