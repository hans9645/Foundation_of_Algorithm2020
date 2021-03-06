/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS	
#include<stdio.h>
#include<stdlib.h>
#define INF 100
#define MALLOC(a,b) a=malloc(b)

typedef int set_pointer;
typedef struct {
	int v1;
	int v2;
	int weight;
}edge;


void makeset(int i);
void init(int n);
set_pointer find(int i);
void merge(set_pointer p, set_pointer q);
int equal(set_pointer p, set_pointer q);
int equal_n2(int p,int q, set_pointer P, set_pointer Q);
void kruskal(int n, int m);


int n, m;
int U[INF] = { 0, };
edge F[INF];
edge*f_mimic;
edge e;


int main(void) {

	FILE* f = fopen("input.txt", "rt");

	fscanf(f, "%d %d", &n, &m);

	MALLOC(f_mimic, n * sizeof(edge));

	for (int i = 1;i <= m;i++) {
		fscanf(f, "%d %d %d", &e.v1, &e.v2, &e.weight);
		f_mimic[i] = e;
	}
	kruskal(n, m);



	return 0;
}

void kruskal(int n, int m) {
	int i, j,flag=1;
	int count = 1;
	set_pointer p, q; 
	init(n);

	printf("disjoint set: ");
	for (i = 1;i <= n;i++)
		printf("%4d", U[i]);
	printf("\n");


	while(count<n){

		e = f_mimic[flag++];
		i = e.v1;
		j = e.v2;
		p = find(i);
		q = find(j);
		
		if (!equal(p, q)) {
			merge(p, q);
			F[count++] = e;
			
		}
		printf("disjoint set: ");
		for (i = 1;i <= n;i++)
			printf("%4d", U[i]);
		printf("\n");
	}

	printf("\nEdge list of MST:\n");
	for (i = 1;i < n;i++) {
		printf("(%2d%2d) (W=%2d)\n", F[i].v1, F[i].v2, F[i].weight);
	}
}


void makeset(int i) {
	U[i] = i;
}
void init(int n) {
	for (int i = 1;i <= n;i++) {
		makeset(i);
	}
}
set_pointer find(int i) {
	int j = i;
	while (U[j] != j) j = U[j];

	return j;
}
void merge(set_pointer p, set_pointer q) {
	U[p] = q;
}
int equal(set_pointer p, set_pointer q) {
	if (p == q)
		return 1;
	else return 0;
}
int equal_n2(int p1, int q1, set_pointer p, set_pointer q) {
	p = find(p1);
	q = find(q1);
	return equal(p, q);
}

