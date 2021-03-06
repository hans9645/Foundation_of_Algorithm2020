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

int maxprofit;
int W,weight,profit;
int*include,*p, *w,*bestset;
int numbest;
int n;


void knapsack(int i, int profit, int weight);
int promising(int i, int profit, int weight);
int main(void) {
	
	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d %d", &n, &W);
	MALLOC(p, (n + 1) * sizeof(int));
	MALLOC(w, (n + 1) * sizeof(int));
	MALLOC(bestset, (n + 1) * sizeof(int));
	MALLOC(include, (n + 1) * sizeof(int));
	for (int i = 1;i <= n;i++) {
		w[i] = 0;
		p[i] = 0;
	}
	for (int i = 1;i <= n;i++) {
		fscanf(f, "%d", &p[i]);
		bestset[i] = 0;
		include[i] = 0;
	
	}
	for (int i = 1;i <= n;i++) {
		fscanf(f, "%d", &w[i]);
	}

	knapsack(0, 0, 0);

	printf("maxprofit= %d\n", maxprofit);

	for (int z = 1;z <= numbest;z++) {
		if(bestset[z]) printf("(%d %d) ", w[z],p[z]);
	}
	printf("\n");

	free(include);
	free(bestset);
	free(p);
	free(w);
	fclose(f);

	return 0;
}
void knapsack(int i, int profit, int weight) {

	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = i;
		for (int z = 1;z <= i;z++) {
			bestset[z] = include[z];
		}
		
	}
	if (promising(i, profit, weight)) {
		include[i + 1] = True;
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = False;
		knapsack(i + 1, profit, weight);
	}
}

int promising(int i, int profit, int weight) {
	int j, k;
	int totweight;
	float bound;

	if (weight >= W) {
		return False;
	}
	else {
		j = i + 1;
		bound = (float)profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			bound += p[j];
			j++;
		}
		k = j;
		if (k <= n) {
			bound = bound + (W - totweight)*(p[k] / w[k]);
		}
		return bound > maxprofit;
	}
}