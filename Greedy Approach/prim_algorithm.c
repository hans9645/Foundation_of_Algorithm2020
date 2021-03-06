/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
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
		nearest[i] = 1;//현재 f에 속하지 않는 마디들은 각각 v1에 제일 가까워지고 싶어함,그래야 f에 들어가니깐
		distance[i] = W[1][i];//각각 마디들과 v1과의 거리를 초기화
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