/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
[Finding Both the Largest and Smallest Key]

Chapter 8. 선택 문제: 최대키와 최소키 동시에 찾기 (pp. 362-390.)
   Algorithm 8.4의 구현을 n이 홀수인 경우를 포함하여 완성하시오.
   단, 프로그램 내부의 비교 횟수도 함께 출력해야 함.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#define MALLOC(a,b) a=malloc(b)

int *s;
int num;
int large, small;
int count = 0;

void find(int n);

int main(void) {

	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &num);
	MALLOC(s, (num + 1) * sizeof(int));
	for (int i = 1;i <= num;i++) {
		fscanf(f, "%d", &s[i]);
	}
	find(num);

	if (!(num % 2)) {
		count = (double)3 / 2*(double)num - 2;
	}
	else {
		count = (double)3 / 2 * (double)num - (double)3 / 2;
	}
	printf("largest = %d\n", large);
	printf("smallest= %d\n", small);
	printf("the number of comparisons = %d\n", count);


	return 0;
}

void find(int n) {
	int i;

	if (s[1] < s[2]) {
		small = s[1];
		large = s[2];

	}
	else {
		small = s[2];
		large = s[1];
	
	}

	if (!(n % 2)) {
		for (i = 3;i <= n - 1;i = i + 2) {
			if (s[i] < s[i + 1]) {
			
				if (s[i] < small) {
					small = s[i];
				}
	
				if (s[i + 1] > large) {
					large = s[i + 1];
				}

			}
			else {

				if (s[i + 1] < small) {
					small = s[i + 1];
				}
		
				if (s[i] > large) {
					large = s[i];
				}
			
			}
		}
	}
	else {
		for (i = 3;i <= n - 2;i = i + 2) {
			if (s[i] < s[i + 1]) {
			
				if (s[i] < small) {
					small = s[i];
				}
			
				if (s[i + 1] > large) {
					large = s[i + 1];
				}
			
			}
			else {

				if (s[i + 1] < small) {
					small = s[i + 1];
				}

				if (s[i] > large) {
					large = s[i];
				}
			}

			if (small > s[n]) {
				small = s[n];
			}
			if (large < s[n]) {
				large = s[n];
			}
		}

	}

}