// input.txt
// 4 // the number of n
// 1 2 3 4
// 5 6 7 8
// 9 1 2 3
// 4 5 6 7
// 4 // the number of n
// 8 9 1 2
// 3 4 5 6
// 7 8 9 1
// 2 3 4 5

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(a, b) if(!((a) = malloc(b))){\
fprintf(stderr,"error!\n");}


int** create(int n);//
void relieve(int n, int**A);//
int** strassen(int n, int**, int**, int**);
int**m_add(int n, int**, int**);//
int**m_sub(int n, int**, int**);//
int** m_merge(int**C11, int**C12, int**C21, int**C22, int n);
int** mmult(int n, int**, int**);//초기 temp값을 가지고 이용하기 때문에 초기화 과정이 생략되면 쓰레기 값이 계산과정에 반영된다.
int**submatrix(int n, int** A, int a, int b);//

int main(void) {

	int n;
	int**A = NULL;
	int**B = NULL;
	int**C = NULL;


	FILE*f = fopen("input.txt", "rt");
	fscanf(f, "%d", &n);

	A = create(n);
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			fscanf(f, "%d", &A[i][j]);
		}
	}

	fscanf(f, "%d", &n);

	B = create(n);
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			fscanf(f, "%d", &B[i][j]);
		}
	}

	C = strassen(n, A, B, C);

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			printf("%3d ", C[i][j]);
		}
		printf("\n");
	}

	return 0;
}

int** create(int n) {
	int**A = NULL;
	MALLOC(A, n * sizeof(int));
	for (int i = 0;i < n;i++) {
		MALLOC(A[i], n * sizeof(int));
	}
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			A[i][j] = 0;
		}
	}
	return A;
}

void relieve(int n, int**A) {
	for (int i = 0;i < n;i++) {
		free(A[i]);
	}
	free(A);
}

int** strassen(int n, int**A, int**B, int**C) {

	int**A11 = NULL, **A12 = NULL, **A21 = NULL, ** A22 = NULL;
	int**B11 = NULL, **B12 = NULL, **B21 = NULL, ** B22 = NULL;
	int**C11 = NULL, **C12 = NULL, ** C21 = NULL, **C22 = NULL;
	int**X1 = NULL, **X2 = NULL, **X3 = NULL, **X4 = NULL, ** X5 = NULL, ** X6 = NULL, ** X7 = NULL, **X8 = NULL, **X9 = NULL, **X10 = NULL;
	int**M1 = NULL, ** M2 = NULL, **M3 = NULL, ** M4 = NULL, ** M5 = NULL, ** M6 = NULL, ** M7 = NULL;

	int hsize = n / 2;

	if (n <= 4) {
		C= mmult(n, A, B);
		return C;  
	}

	else {
		A11 = submatrix(n, A, 0, 0);
		A12 = submatrix(n, A, 0, hsize);
		A21 = submatrix(n, A, hsize, 0);
		A22 = submatrix(n, A, hsize, hsize);
	
		B11 = submatrix(n, B, 0, 0);
		B12 = submatrix(n, B, 0, hsize);
		B21 = submatrix(n, B, hsize, 0);
		B22 = submatrix(n, B, hsize, hsize);

		X1 = m_add(hsize, A11, A22);
		X2 = m_add(hsize, B11, B22);
		X3 = m_add(hsize, A21, A22);
		X4 = m_sub(hsize, B12, B22);
		X5 = m_sub(hsize, B21, B11);
		X6 = m_add(hsize, A11, A12);
		X7 = m_sub(hsize, A21, A11);
		X8 = m_add(hsize, B11, B12);
		X9 = m_sub(hsize, A12, A22);
		X10 = m_add(hsize, B21, B22);



		M1 = strassen(hsize, X1, X2, M1);
		M2 = strassen(hsize, X3, B11, M2);
		M3 = strassen(hsize, A11, X4, M3);
		M4 = strassen(hsize, A22, X5, M4);
		M5 = strassen(hsize, X6, B22, M5);
		M6 = strassen(hsize, X7, X8, M6);
		M7 = strassen(hsize, X9, X10, M7);


		C11 = m_add(hsize, M1, M4); C11 = m_sub(hsize, C11, M5);C11 = m_add(hsize, C11, M7);
		C12 = m_add(hsize, M3, M5);
		C21 = m_add(hsize, M2, M4);
		C22 = m_add(hsize, M1, M3);C22 = m_sub(hsize, C22, M2);C22 = m_add(hsize, C22, M6);



		C= m_merge(C11, C12, C21, C22, n);
		return C;
	}

}


int**m_add(int n, int**A, int**B) {
	int**temp = NULL;
	temp = create(n);

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			temp[i][j] = A[i][j] + B[i][j];
		}
	}
	return temp;
}

int**m_sub(int n, int**A, int**B) {

	int**temp = NULL;
	temp = create(n);

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			temp[i][j] = A[i][j] - B[i][j];
		}
	}
	return temp;

}
int** m_merge(int**C11, int**C12, int**C21, int**C22, int n) {

	int**C = NULL;
	C = create(n);
	for (int i = 0;i < n / 2;i++) {
		for (int j = 0;j < n / 2;j++) {
			C[i][j] = C11[i][j];
		}
	}
	for (int i = n / 2;i < n;i++) {
		for (int j = 0;j < n / 2;j++) {
			C[i][j] = C21[i - n/2][j];
		}
	}

	for (int i = 0;i < n / 2;i++) {
		for (int j = n / 2;j < n;j++) {
			C[i][j] = C12[i][j - n / 2];
		}
	}

	for (int i = n / 2;i < n;i++) {
		for (int j = n / 2;j < n;j++) {
			C[i][j] = C22[i - n / 2][j - n / 2];
		}
	}
	return C;
}

int** mmult(int n, int**A, int**B) {

	int **temp = NULL;
	temp = create(n);
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			for (int k = 0;k<n;k++)
				temp[i][j] += A[i][k] * B[k][j];
		}
	}
	return temp;

}

int** submatrix(int n, int** A, int m, int k) {

	int **temp = NULL;
	temp = create(n / 2);
	for (int i = 0;i < n / 2;i++) {
		for (int j = 0;j < n / 2;j++) {
			temp[i][j] = A[i + m][j + k];
		}
	}
	return temp;
}