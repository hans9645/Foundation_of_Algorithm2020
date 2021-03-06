/*
* [2015114563] [���ѿ�] ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
*/
#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,b) a=malloc(b)
#define MAX 100

int J[MAX];//job list
int K[MAX];//�ӽ� Ȯ�ο�
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
	J[0] = K[0] = 0;//�񱳸� ���� �ʱ�ȭ
	J[len++] = 1;//J�� 1�� ������
	for (i = 2;i <= n;i++) {
		copytofrom(len,J,K);//K�� J�� �ϴ� ��ƺ�,deadline ������ �����ؼ� ��ƺ�,Lemma����
		insert(i, len);//�׷� �� K��  ������ i�� insert�ؼ� Ȯ���غ��� ����  
		if (is_feasible(len))//K�� feasible�� ���� ��������
			copytofrom(len++,K,J);//feasible �ϴϱ� J�� K�� ����ȭ
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