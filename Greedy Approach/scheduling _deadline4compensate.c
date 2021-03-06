/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,b) a=malloc(b)
#define MAX 100

int J[MAX];//job list
int K[MAX];//임시 확인용
int deadline[MAX];
int profit[MAX];

int schedule(int n);
int is_feasible( int len);
void insert(int i, int len);
void copytofrom(int len,int*A,int*B);
int main(void) {

	int n,len,Total=0;

	FILE*f = fopen("input.txt", "rt");

	fscanf(f, "%d", &n);

	for (int i = 1;i <= n;i++) {
		fscanf(f, "%d", &deadline[i]);

	}

	for (int i = 1;i <= n;i++) {
		fscanf(f, "%d", &profit[i]);

	}


	len=schedule(n);

	printf("\nResult of Scheduling:\n");
	printf("[");
	for (int i = 1;i <len;i++)
	{
		printf( " %d", J[i]);
		Total += profit[J[i]];
		if (i == len-1)printf(" ");
		else printf(",");
	}
	printf("]\n");

	printf("Total Reward:%4d\n", Total);


	return 0;
}

int schedule(int n) {
	int i, len = 1;
	J[0] = K[0] = 0;//비교를 위한 초기화
	J[len++] = 1;//J가 1로 시작함
	for (i = 2;i <= n;i++) {
		copytofrom(len,J,K);//K에 J를 일단 담아봄,deadline 순서를 생각해서 담아봄,Lemma생각
		insert(i, len);//그런 뒤 K를  가지고 i를 insert해서 확인해보기 위해  
		if (is_feasible(len))//K가 feasible한 지를 따져본다
			copytofrom(len++,K,J);//feasible 하니까 J와 K를 동기화
	}
	return len;
}

int is_feasible( int len) {
	int i;
	for (i = 1;i <= len;i++) {
		if (deadline[K[i]] < i)
			return 0;
	}
	return 1;
}
void insert(int i, int len) {
	int j;
	for (j = len;j > 0;j--) {
		if (deadline[i] >= deadline[K[j - 1]])
			break;
		K[j] = K[j - 1];
	}
	K[j] = i;
}

void copytofrom(int len,int*A,int*B) {
	
	
	for (int i = 1;i <= len;i++) {
		B[i] = A[i];
	}
}