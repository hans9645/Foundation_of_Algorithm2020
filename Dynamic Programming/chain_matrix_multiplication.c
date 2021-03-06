
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,b) a=malloc(b)

int** minmult(int n);
void order(int i, int j);
int minimum(int i,int j,int*k,int**temp);
int**P, **M;
int*d;

int main(void) {
	int n;


	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &n);

	MALLOC(d, (n + 1) * sizeof(int));

	MALLOC(P, (n + 1) * sizeof(int));
	for (int i = 0;i <= n;i++) {
		MALLOC(P[i], (n + 1) * sizeof(int));
	}

	for (int i = 0;i <= n;i++) {//0으로 초기화
		for (int j = 0;j <= n;j++) {
			P[i][j] = 0;
		}
	}


	MALLOC(M, (n + 1) * sizeof(int));
	for (int i = 0;i <= n;i++) {
		MALLOC(M[i], (n + 1) * sizeof(int));
	}

	for (int i = 0;i <= n;i++) {//0으로 초기화
		for (int j = 0;j <= n;j++) {
			M[i][j] = 0;
		}
	}

	for (int i = 0;i <= n;i++) {// an array of d (from d0 to dn)
		fscanf(f, "%d", &d[i]);
	}


	printf("the result of M:\n");
	M = minmult(n);
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			if (i <= j) {
				printf("%3d ", M[i][j]);
			}
			else
				printf("    ");
		}
		printf("\n");
	}

	printf("optimal value is %d\n\n",M[1][n]);

	printf("The result of P:\n");

	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			if (i <j) {
				printf("%3d ", P[i][j]);
			}
			else
				printf("    ");
		}
		printf("\n");
	}

	


	return 0;
}

int** minmult(int n) {
	int i, j, k, diagonal;
	int **temp;
	MALLOC(temp, (n + 1) * sizeof(int));
	for (i = 0;i <= n;i++) {
		MALLOC(temp[i], (n + 1) * sizeof(int));
	}

	for (i = 0;i <= n;i++) {//0으로 초기화
		for (j = 0;j <= n;j++) {
			temp[i][j] = 0;
		}
	}


	for (i = 1;i <= n;i++) {//행렬의 자기곱셈은 계산불가.
		temp[i][i] = 0;
	}

	for (diagonal = 1;diagonal <= n - 1;diagonal++) {
		for (i = 1; i <= n - diagonal;i++) {
			j = i + diagonal;
			temp[i][j] = minimum(i,j,&k,temp);
			P[i][j] = k;
		}
	}
	return temp;
}
void order(int i, int j) {

	int k;
	if (i == j) {
		printf("A%d", i);
	}
	else {
		k = P[i][j];
		printf("(");
		order(i, k);
		order(k + 1, j);
		printf(")");
	}
}

int minimum(int i, int j, int*k,int**temp) {

	int n, m, min;
	min = 1000;

	for (n = i;n < j;n++) {
		m = temp[i][n] + temp[n + 1][j] + d[i - 1] * d[n] * d[j];// 전역배열에 아직 저장안되어있었는데 전역배열을 사용해서재귀함수구현해서 diagonal 2 부터 에러떴음.

		if (min > m) {
			min = m;
			*k = n;
		}
	}
	return min;
}