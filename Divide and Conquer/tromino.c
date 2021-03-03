
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MALLOC(a,b) if(!((a)=malloc(b))){\
fprintf(stderr,"file error\n");}

int **board;
int currentNum = 1;
int flag = 0;

void initboard(int**a, int size);
void fillboard(int x,int y, int hx,int hy, int size);

int main(void) {

	FILE*f = fopen("input.txt", "r");
	int n, i, j;

	fscanf(f,"%d %d %d",&n,&i,&j);

	int size =(int) pow(2, n);  //pow �� double

	MALLOC(board, size*sizeof(int));
	for (int k = 0;k < size;k++) {
		MALLOC(board[k],size*sizeof(int));
	}

	initboard(board, size);
	fillboard(0, 0, i, j, size);
	flag++;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf(" %2d ",board[i][j] );
		}
		printf("\n");
	}

	if (flag == 1) {
		printf("������ġ �ٽ��Է��ϼ���.\n");
		scanf("%d %d", &i, &j);
	}

	initboard(board, size);

	fillboard(0, 0, i, j, size);


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf(" %2d ", board[i][j]);
		}
		printf("\n");
	}

	
	for (int k = 0;k < size;k++) {
		free(board[k]);
	}
	free(board);



	return 0;
}
void initboard(int**a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j]=-1;
		}
	}
	currentNum = 1;
}

void fillboard(int x, int y, int hx, int hy, int size) {

	int hsize = size / 2;

	board[hx][hy] = 0;


	if (size == 2) {
		for (int i = 0;i < size;i++) {
			for (int j = 0;j < size;j++) {
				if (board[x + i][y + j]!=-1) continue;
				board[x + i][y + j] = currentNum;

			}
		}
		currentNum++;
		return;
	}

	int seekX = x;
	int seekY = y;

	for (;seekX < x + size; seekX++) {
		seekY = y;
		for (;seekY < y + size;seekY++) {
			if (board[seekX][seekY] != -1)//
				goto EXIT;
		}
	}


EXIT:


	if (!(seekX < x + hsize && seekY < y + hsize)) board[x + hsize - 1][y + hsize - 1] = currentNum; // ���ϴ� ��� �簢���� hole �� ����.
	if (!(seekX >= x + hsize && seekY < y + hsize)) board[x + hsize][y + hsize - 1] = currentNum; // ���ϴ� ��� �簢���� hole �� ����.
	if (!(seekX < x + hsize && seekY >= y + hsize)) board[x + hsize - 1][y + hsize] = currentNum; // �»�� ��� �簢���� hole �� ����.
	if (!(seekX >= x + hsize && seekY >= y + hsize)) board[x + hsize][y + hsize] = currentNum; // ���� ��� �簢���� hole �� ����.
	currentNum++;


	fillboard(x,y,hx, hy, hsize);
	fillboard( x + hsize, y, hx, hy, hsize);
	fillboard( x, y + hsize, hx, hy, hsize);
	fillboard( x + hsize, y + hsize, hx, hy, hsize);


}