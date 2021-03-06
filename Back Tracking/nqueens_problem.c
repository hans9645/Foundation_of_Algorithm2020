/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,b) a=malloc(b)
#define true 1
#define false 0

int n;
int *col;

void queens(int index);
int prominsing(int index);
int abs(int num);

int main(void) {

	
	printf("Enter the number of n =");
	scanf("%d", &n);
	MALLOC(col, (n+1) * sizeof(int));
	
	queens(0);

	return 0;
}


void queens(int index) {
	int j;
	if (prominsing(index)) {
		if (index == n) {
			for (int i = 1;i <= n;i++) {
				printf("(%d,%d) ", i, col[i]);
			}
			printf("\n");
		}
		else {
			for (j = 1;j <= n;j++) {
				col[index + 1] = j;
				queens(index + 1);
			}
		}
	}
}
int prominsing(int index) {
	int k;
	int flag;
	k = 1;
	flag = true;
	while (k < index && flag) {
		if (col[index] == col[k] || abs(col[index] - col[k]) == (index - k)) {
			flag = false;
		}
		k++;
	}
	return flag;
}

int abs(int num) {
	int result;
	result = num > 0 ? num : -num;

	return result;
}