/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a,b) a=malloc(b)
#define MAX 100

typedef struct nodeType* nodePointer;
typedef struct nodeType {
	int key;
	nodePointer left;
	nodePointer right;
}nodeType;

void  optsearchtree(int n);
int  minimum(int i, int j, int*k);
void input(nodePointer *root, int a);
nodePointer tree(int i, int j);
void inorder(nodePointer ptr);
void preorder(nodePointer ptr);

int*K, *P;
int M[MAX][MAX],R[MAX][MAX];



int main(void) {

	FILE*f = fopen("input.txt", "rt");
	int n;
	nodePointer root = NULL;


	fscanf(f, "%d", &n);
	MALLOC(K, (n + 1) * sizeof(int));
	MALLOC(P, (n + 1) * sizeof(int));
	for (int i = 0;i < n+1;i++) {
		fscanf(f, "%d", &K[i]);
	}
	for (int i = 0;i < n + 1;i++) {
		fscanf(f, "%d", &P[i]);
	}

	optsearchtree(n);

	printf("The result of M:\n");
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			if (i <= j) {
				printf("%3d", M[i][j]);
			}
			else printf("   ");
		}
		printf("\n");
	}

	printf("The optimal value is %d\n", M[1][n]);

	printf("The result of R:\n");

	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			if (i <= j) {
				printf("%3d", R[i][j]);
			}
			else printf("   ");
		}
		printf("\n");
	}
	root = tree(1, n);
	printf("The optimal BST is :\n");
	printf("preorder : ");
	preorder(root);
	printf("\n");
	printf("inorder : ");
	inorder(root);

	return 0;
}

void  optsearchtree(int n) {
	int i, j, k, diagonal;
	for (int i = 1;i <= n;i++) {
		M[i][i - 1] = 0;
		M[i][i] = P[i];
		R[i][i - 1] = 0;
		R[i][i] = i;
	}
	M[n + 1][n] = 0;
	R[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1;i <= n - diagonal;i++) {
			j = i + diagonal;
			M[i][j] = minimum(i, j, &k);
			R[i][j] = k;
		}
	}
}


int  minimum(int i, int j, int*mink) {

	int k, m, min,sum=0;
	min = 1000;
	for (int l = i;l <= j;l++) {
		sum += P[l];
	}

	for (k = i;k < j;k++) {

		m = M[i][k - 1] + M[k + 1][j] + sum;
		if (m < min) {
			min = m;
			*mink = k;
		}
	}
	return min;

}

nodePointer tree(int i, int j) {
	int k;
	nodePointer ptr;

	k = R[i][j];
	if (k == 0) {
		return NULL;
	}
	else {
		MALLOC(ptr, sizeof(nodeType));
		ptr->key = K[k];
		ptr->left = tree(i, k - 1);
		ptr->right = tree(k + 1, j);
		return ptr;
	}
}

void inorder(nodePointer ptr) {
	if (ptr) {
		inorder(ptr->left);
		printf("%d ", ptr->key);
		inorder(ptr->right);
	}

}
void preorder(nodePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->key);
		inorder(ptr->left);
		inorder(ptr->right);
	}

}