/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,b) a=malloc(b)
#define true 1
#define false 0

int n, W,total;
int*w,*including;
int weight;

void sum_of_subsets(int i, int weight, int total);
int promising(int i);

int main(void) {

	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d %d", &n, &W);

	MALLOC(w, (n+1) * sizeof(int));
	MALLOC(including, (n + 1) * sizeof(int));
	
	for (int i = 1;i <= n;i++) {
		fscanf(f, "%d", &w[i]);
		total += w[i];
	}
	for (int i = 1;i <= n;i++) {
		including[i] = false;
	}
	printf("The subsets are: \n");
	sum_of_subsets(0, 0, 0);



	return 0;
}

void sum_of_subsets(int i, int weight, int total) {

	if (promising(i)) {
		if (weight == W) {
			for (int k = 1;k <= n;k++) {
				if (including[k]==true) {
					printf("%d ", w[k]);
				}
			}
			printf("\n");
		}
		else {
			including[i + 1] = true;
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			including[i + 1] = false;
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}
	}

}

int promising(int i) {

	int num= (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
	return num;

}