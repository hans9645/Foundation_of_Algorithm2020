#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,n) a=malloc(n)
#define MIN(x,y) (x)>(y)?(y):(x)


int bin2(int n, int k);
int *B;
int a;

int main(void) {

	int n, k;


	printf("Enter the number of n : ");
	scanf("%d", &n);
	printf("Enter th number of k : ");
	scanf("%d", &k);
	MALLOC(B, k+1 * sizeof(int));
	


	for (int j = 0;j < k + 1;j++)
		B[j] = 0;
	

	printf("binomial coefficient of(%d,%d) =  %d", n, k, bin2(n,k));


	return 0;
}

int bin2(int n, int k) {
	int i, j, min;

	for (i = 0;i < n + 1;i++) {
		min = MIN(i, k);
		
		for (j = min;j >= 0;j--) {
			
			if (j == 0 || j ==i) {
				B[j] = 1;
				
				printf("%d", B[j]);
			}
			else
			{
				
				B[j] = B[j] +B[j-1];

				printf("%d", B[j]);
				
			}
			
		}
		printf("\n");
	}

	return B[k];
}