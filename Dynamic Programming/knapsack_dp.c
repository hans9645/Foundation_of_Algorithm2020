/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100
#define MALLOC(a,b) a=malloc(b)
int n;
int w;
int *value;
int *weight;
int **P; //이 때 P[0][w]와 P[n][0] 은 0으로 설정.

void knapsack(int n, int w); //변수명 변경 가능
int maximum(int a, int b);

int main(void) {

	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &n);
	fscanf(f, "%d", &w);
	MALLOC(value, (n + 1) * sizeof(int));
	MALLOC(weight, (n + 1) * sizeof(int));

	for (int i = 1;i <= n;i++) {
		fscanf(f, "%d", &value[i]);
	}

	for (int i = 1;i <= n;i++) {
		fscanf(f, "%d", &weight[i]);
	}

	MALLOC(P, (n + 1) * sizeof(int));
	for (int i = 0;i < (n + 1);i++) {
		MALLOC(P[i], (w + 1) * sizeof(int));
	}

	for (int i = 0;i < w + 1;i++) {
		P[0][i] = 0;
	}

	for (int i = 0;i < n + 1;i++) {
		P[i][0] = 0;
	}


	knapsack(n, w);

	return 0;
}

void knapsack(int n, int w) {

	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= w;j++) {
			if (j >= weight[i]) {
				P[i][j] = maximum(P[i - 1][j], value[i] + P[i - 1][j - weight[i]]);
			}
			else {
				P[i][j] = P[i - 1][j];
			}
		}
	}

	printf("The result is : %d\n", P[n][w]);

}

int maximum(int a, int b) {
	if (a <= b)
		return b;

	return a;
}