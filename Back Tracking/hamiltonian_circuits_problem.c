/*
[2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(a,b) a=malloc(b)
#define MAX 50
#define True 1
#define False 0

int n, e;
int W[MAX][MAX];
int*vindex;

void hamiltonian(int i);
int promising(int i);

int main(void) {

	int a, b;
	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d %d", &n, &e);
	MALLOC(vindex, (n + 1) * sizeof(int));

	for (int i = 1;i <= 6;i++) {
		fscanf(f, "%d %d", &a, &b);
		W[a][b] = 1;
		W[b][a] = 1;
	}
	vindex[0] = 1;
	hamiltonian(0);

	return 0;
}

void hamiltonian(int i) {
	int j;

	if (promising(i)) {
		if (i == n - 1) {
			for (int k = 0;k < n;k++)
				printf("%d ", vindex[k]);
			printf("1\n");
		}
		else {
			for (j = 2;j <= n;j++) {
				vindex[i + 1] = j;
				hamiltonian(i + 1);
			}
		}
	}
}

int promising(int i) {
	int j;
	int flag;

	if (i == n - 1 && !W[vindex[n - 1]][vindex[0]])
		flag = False;
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
		flag = False;
	else {
		flag = True;
		j = 1;
		while (j < i&&flag) {
			if (vindex[i] == vindex[j])
				flag = False;
			j++;
		}
	}
	return flag;

}