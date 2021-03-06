/*
* [2015114563] [���ѿ�] ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
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

void knapsack(int n, int w); //�迭�� ���ڷ� �޾ƿ͵� ����

int main(void) {

	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &n);
	fscanf(f, "%d", &w);
	MALLOC(value, n * sizeof(int));
	MALLOC(weight, n * sizeof(int));

	for (int i = 0;i < n;i++) {
		fscanf(f, "%d", &value[i]);
	}

	for (int i = 0;i < n;i++) {
		fscanf(f, "%d", &weight[i]);
	}

	knapsack(n, w);

	return 0;
}

void knapsack(int n, int w) {

	int sum = 0;
	for (int i = 0;i < n;i++) {
		if (w / weight[i] != 0) {
			sum += value[i];
			w -= weight[i];
		}
		
	}


	printf("The result is:");
	printf("%d\n",sum);
}