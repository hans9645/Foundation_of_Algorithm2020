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
void recursive_print(int *touch,int n);
//dijkstra's algorithm : prim�� �޸� directed algorithm�̴�.
int main(void) {

	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &n);



	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			fscanf(f, "%d", &W[i][j]);
		}
	}

	prim(n);


	return 0;
}

void prim(int n) {

	int i, vnear;
	int p_min = 100;
	int min;
	edge e;
	int touch[100] = { 0, };//Y�� �ִ� vertex
	int length[100] = { 0, };
	int Total = 0;

	for (i = 2;i <= n;i++) {
		touch[i] = 1;
		length[i] = W[1][i];//���� ������ v1���κ��� �����ϴ� touch�� �ִ� vertxt������ ���°Ŷ� ���� ���� �ּ� ����
	}

	printf("touch: ");
	for (i = 2;i <= n;i++) {
		printf("%5d", touch[i]);
	}
	printf("\n");
	printf("length: ");
	for (i = 2;i <= n;i++) {
		printf("%5d", length[i]);
		if (p_min > length[i])
			p_min = length[i];
	}
	Total += p_min;



	for (int flag = 1;flag < n;flag++) {

		min = INF;
		for (i = 2;i <= n;i++) {
			if (0 <= length[i] && length[i] < min) {
				min = length[i];
				vnear = i;
			}
		}
		e.v1 = touch[vnear];
		e.v2 = vnear;
		F[flag + 1] = e;

		for (i = 2;i <= n;i++) {
			if (length[vnear]+W[vnear][i] < length[i]) {
				length[i] = W[vnear][i]+length[vnear];
				touch[i] = vnear;
				e.weight = W[vnear][i];
				Total += e.weight;
			}
		}
		length[vnear] = -1;

		printf("\n");
		printf("touch: ");
		for (i = 2;i <= n;i++) {
			printf("%5d", touch[i]);
		}
		printf("\n");
		printf("length: ");
		for (i = 2;i <= n;i++) {
			printf("%5d", length[i]);
		}

	}


	printf("\n\nEnter the destination:%d",vnear);
	printf("\nThe length of shortest path =%4d\n",Total);
	printf("The shortest path from 1 to %d:",vnear);
	recursive_print(touch, vnear);
	printf("V%d \n", vnear);
	
	



}

void recursive_print(int *touch,int n) {
	if (touch[n] == 1) {
		printf(" V%d ", touch[n]);
	}
	else {
		recursive_print(touch, touch[n]);
		printf("V%d ", touch[n]);
	}
}