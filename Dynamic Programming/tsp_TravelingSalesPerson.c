/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100

int n;
int W[MAX][MAX] = { 0, };//adjaceny ,가는 길이 없으면 0으로 표시
int D[MAX][MAX] = { 0, };// 1을 제외한 i에서 Vertex의 subset인 A의 원소들을 한번씩 거쳐 가는 최단길이 저장
int P[MAX][MAX] = { 0, };//경로 저장 


int isIn(int A, int i);//A에 Vi가 있는지 확인
int  diff(int A, int j);//A에 Vj가 있는지 확인
int contains(int A, int k, int n);//A에 들어있는 원소의 갯수가 k개만큼 포함하고 있는지 확인
void travel(int n);//D[i][A]를 정리하기 위한 함수
int minimum(int i, int A, int*minJ, int n);//최솟값 m=W[i][j]+D[j][diff(A,j)]
void tour(int i, int j);//P에 저장된 경로를 순서대로 뽑기 위한 함수

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