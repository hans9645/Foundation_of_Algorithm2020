#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,n) a=malloc(n)
#define MIN(x,y) (x)>(y)?(y):(x)
#define MAX 100

int** floyd2(int n, int**W, int**P);


int **D, **W;
int**P;

void path(int q, int r) {
	if (P[q][r] != 0) {
		path(q, P[q][r]);
		printf(" %d", P[q][r]);
		path(P[q][r], r);
	}
}

int main(void) {
	int v, e;
	int v1, v2, size;
	int departure, arrival;
	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &v);
	fscanf(f, "%d", &e);

	MALLOC(P, (v + 1) * sizeof(int));
	for (int m = 0;m < v + 1;m++) {
		MALLOC(P[m], (v + 1) * sizeof(int));
	}

	MALLOC(W, (v + 1) * sizeof(int));
	for (int j = 0;j < v + 1;j++) {
		MALLOC(W[j], (v + 1) * sizeof(int));
	}

	for (int i = 0;i<v + 1;i++) {
		for (int j = 0;j < v + 1;j++) {
			W[i][j] = MAX;
			if (i == j) {
				W[i][j] = 0;
			}
		}
	}

	for (int i = 0;i < e;i++) {
		fscanf(f, "%d %d %d", &v1, &v2, &size);
		W[v1][v2] = size;
	}

	printf("Enter the source node : ");
	scanf("%d", &departure);
	printf("Enter the destination node : ");

	scanf("%d", &arrival);


	D = floyd2(v, W,P);


	printf("Path from %d to %d is: %d",departure,arrival,departure);
	path(departure, arrival);
	printf(" %d\n", arrival);

	

	return 0;
}

int** floyd2(int n, int**W,int**P) {

	int**temp;
	int i, j, k;

	for (i = 0;i <= n;i++) {
		for (j = 0;j <= n;j++) {
			P[i][j] = 0;
		}
	}

	temp = W;
	for (k = 1;k <= n;k++) {
		for (i = 1;i <= n;i++) {
			for (j = 1;j <= n;j++) {
				if (temp[i][j] > temp[i][k] + temp[k][j]) {
					P[i][j] = k;
					temp[i][j] = temp[i][k] + temp[k][j];
				}
		
			}
		}
	}
	return temp;
}