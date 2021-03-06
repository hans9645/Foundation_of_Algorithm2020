/*
* [2015114563] [���ѿ�] ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100

int n;
int W[MAX][MAX] = { 0, };//adjaceny ,���� ���� ������ 0���� ǥ��
int D[MAX][MAX] = { 0, };// 1�� ������ i���� Vertex�� subset�� A�� ���ҵ��� �ѹ��� ���� ���� �ִܱ��� ����
int P[MAX][MAX] = { 0, };//��� ���� 


int isIn(int A, int i);//A�� Vi�� �ִ��� Ȯ��
int  diff(int A, int j);//A�� Vj�� �ִ��� Ȯ��
int contains(int A, int k, int n);//A�� ����ִ� ������ ������ k����ŭ �����ϰ� �ִ��� Ȯ��
void travel(int n);//D[i][A]�� �����ϱ� ���� �Լ�
int minimum(int i, int A, int*minJ, int n);//�ּڰ� m=W[i][j]+D[j][diff(A,j)]
void tour(int i, int j);//P�� ����� ��θ� ������� �̱� ���� �Լ�

int main(void) {
	int A = 0;
	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &n);

	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			fscanf(f, "%d", &W[i][j]);
		}
	}


	travel(n);

	A = (int)pow(2, n - 1);
	printf("Total weight of optimal tour= %d\n", D[1][A-1]);
	printf("Path of optimal tour:");
	printf("V1 ");
	tour(1, A-1);

	printf("\n");
	return 0;
}


void travel(int n) {
	int i, j, k;
	int A;

	int size = (int)pow(2, n - 1);
	for (i = 2;i <= n;i++) {
		D[i][0] = W[i][1];
	}
	for (k = 1;k <= n - 2;k++) {
		for (A = 1;A < size;A++) {
			if (!contains(A, k, n)) continue;
			for (i = 2;i <= n;i++) {
				if (isIn(A, i)) continue;
				D[i][A] = minimum(i, A, &j, n);
				P[i][A] = j;
			}
		}
	}

	A = size - 1;
	D[1][A] = minimum(1, A, &j, n);
	P[1][A] = j;
}

int minimum(int i, int A, int *minJ, int n) {

	int j, m, min;
	min = 900;

	for (j = 2;j <=n;j++) {
		if (!isIn(A, j)) continue;

		m = W[i][j] + D[j][diff(A, j)];

		if (min > m) {
			min = m;
			*minJ = j;
		}
	}


	return min;
}


int isIn(int A, int i) {

	if (A & (1 << (i - 2)))
		return 1;
	else return 0;

}

int  diff(int A, int j) {
	
	return (A&~(1 << (j - 2)));
}

int contains(int A, int k, int n) {
	int count = 0;
	for (int i = 0;i < n - 1;i++) {
		if ((A&(1 << i)) != 0)  count++;
	}
	if (count == k) return 1;
	else return 0;
}

void tour(int i, int j) {

	int k;

	
	if (j== 0) {
		printf("V1");
		return ;
	}
	else
	{
		printf("V%d ", P[i][j]);
		tour(P[i][j], diff(j, P[i][j]));

	}
	

}