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

int m_color, n, e;
int W[MAX][MAX] = { 0, };
int*vcolor;

void m_coloring(int i);
int promising(int i);


int main(void) {

	int a, b;
	FILE*f = fopen("input.txt", "rt");

	fscanf(f,"%d %d %d", &m_color, &n, &e);

	MALLOC(vcolor, (n + 1) * sizeof(int));

	for (int i = 1;i <= e;i++) {
		fscanf(f,"%d %d", &a, &b);
		W[a][b] = 1;
		W[b][a] = 1;
	}

	m_coloring(0);

	return 0;
}

void m_coloring(int i) {

	int color;

	if (promising(i)) {
		if (i == n) {
			for(int k = 1;k <= n;k++){
				printf("%d ", vcolor[k]);
			}
			printf("\n");
		}
	
		else {
			for (color = 1; color <= m_color; color++) {
				vcolor[i + 1] = color;
				m_coloring(i + 1);
			}
		}
	}
}


int promising(int i) {
	int j;
	int flag;
	flag = True;
	j = 1;
	while (j < i && flag) {
		if (W[i][j] && vcolor[i] == vcolor[j]) {
			flag = False;
		}
		j++;
	}
	return flag;
}
