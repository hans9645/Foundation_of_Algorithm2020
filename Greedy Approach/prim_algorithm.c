/*
* [2015114563] [���ѿ�] ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
*/
#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<stdlib.h>
#define INF 999

typedef struct {
	int v1;
	int v2;
	int weight;
}edge;


int W[100][100] = { 0, };
int n = 0;
edge F[100];

void prim(int n);

//prim's algorithm 
int main(void) {
	
	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &n);
	
	

	for (int i = 1;i <=n;i++) {
		for (int j = 1;j <=n;j++) {
			fscanf(f, "%d", &W[i][j]);
		}
	}

	prim(n);


	return 0;
}

void prim(int n) {

	int i, vnear;
	int min;
	edge e;
	int nearest[100] = { 0, };
	int distance[100] = { 0, };
	int Total = 0;

	for (i = 2;i <= n;i++) {
		nearest[i] = 1;//���� f�� ������ �ʴ� ������� ���� v1�� ���� ��������� �;���,�׷��� f�� ���ϱ�
		distance[i] = W[1][i];//���� ������ v1���� �Ÿ��� �ʱ�ȭ
	}


	printf("distance: ");
	for (i = 2;i <= n;i++) {
		printf("%5d", distance[i]);
	}
	printf("\n");
	printf("nearest: ");
	for (i = 2;i <= n;i++) {
		printf("%5d", nearest[i]);
	}
	printf("\n");




	for (int flag = 1;flag < n;flag++) {

		min = INF;
		for (i = 2;i <= n;i++) {
			if (0 <= distance[i] && distance[i] < min) {
				min = distance[i];
				vnear = i;
			}
		}
		e.v1 = nearest[vnear];
		e.v2 = vnear;
		e.weight = W[nearest[vnear]][vnear];
		Total += e.weight;
		F[flag + 1] = e;

		distance[vnear] = -1;

		for (i = 2;i <= n;i++) {
			if (W[i][vnear] < distance[i]) {
				distance[i] = W[i][vnear];
				nearest[i] = vnear;
			}
		}
		printf("distance: ");
		for (i = 2;i <= n;i++) {
			printf("%5d", distance[i]);
		}
		printf("\n");
		printf("nearest: ");
		for (i = 2;i <= n;i++) {
			printf("%5d", nearest[i]);
		}
		printf("\n");

	}
	printf("\nEdge list of MST:\n");
	for (i = 2;i <= n;i++) {
		printf("      (%d %d) (W=%d)\n", F[i].v1, F[i].v2, F[i].weight);
	}
	printf("\nTotal cost of MST:%4d\n\n", Total);



}