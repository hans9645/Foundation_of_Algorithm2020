/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s)\
 if(!((p)=malloc(s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }
#define MAX 100
#define heap_check(num) (num==MAX-1)?1:0
#define false 0
#define true 1

typedef struct node {
	int level;
	int profit;
	int weight;
	float bound;
	int items[MAX];
}node;

node heap_PQ[MAX];//priority queue
int heap_size = 0;//heap 크기
int n, W;
int *p, *w;
int maxprofit;
int *bestitems;

void knapsack3(int n, int W, int p[], int w[]);
float bound(node v);
void insert(node v);
node pop();


int main(void) {


	FILE*f = fopen("input.txt", "rt");
	fscanf(f, "%d %d", &n, &W);

	MALLOC(p, (n+1) * sizeof(int));
	MALLOC(w, (n+1) * sizeof(int));
	MALLOC(bestitems, (n + 1) * sizeof(*bestitems));
	for (int i = 1; i <= n; i++) {
		fscanf(f, "%d", &p[i]);
		
	}
	for (int i = 1; i <= n; i++) {
		fscanf(f, "%d", &w[i]);
	}

	knapsack3(n, W, p, w );



	return 0;
}

void knapsack3(int n, int W, int profit[], int weight[]) {
	
	node u, v;
	v.level = 0; v.profit = 0; v.weight = 0; maxprofit = 0;
	v.bound = bound(v);
	for (int i = 0;i <= n;i++) {
		u.items[i] = false;
		v.items[i] = false;
	}
	insert(v);

	while (heap_size != 0) {
		v = pop();
		printf("level : %d (%3d %3d %7.2f) maxprofit = %d \n", v.level, v.profit, v.weight, v.bound, maxprofit);

		if (v.bound > maxprofit) {
			u.level = v.level + 1;
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			for (int i = 1;i <= n;i++) {
				u.items[i] = v.items[i];//복사
			}
			u.items[u.level] = true;
			u.bound = bound(u);
			if (u.weight <= W&&u.profit > maxprofit) {
			maxprofit = u.profit;
				for (int i = 1;i <= n;i++) 
					bestitems[i] = u.items[i];
			}
			if (u.bound > maxprofit) {//담은 경우
				insert(u);
			}
			u.level = v.level + 1;
			u.weight = v.weight;
			u.profit = v.profit;
			for (int i = 1;i <= n;i++) {
				u.items[i] = v.items[i];//복사
			}

			u.items[u.level] = false;
			u.bound = bound(u);
			if (u.bound > maxprofit) {//담지 않은 경우
				insert(u);
			}

		}
	}
	printf("maxprofit = %d\n", maxprofit);
	printf("bestitems : ");
	for (int i = 1; i <= n; i++)
		if (bestitems[i] == true)
			printf("(%d, %d) ", w[i], p[i]);
}


float bound(node v) {

	int j, k;
	int totweight;
	float result;

	if (v.weight >= W) 
		return 0;
	else {
		result = (float)v.profit;
		j = v.level + 1;
		totweight = v.weight;
		while (j <= n &&totweight + w[j] <= W) {
			totweight = totweight + w[j];
			result = result + p[j];
			j++;
		}
		k = j;
		if (k <= n) {
			result = result + (W - totweight)*(p[k] / w[k]);
		}
		return result;
	}


}

void insert(node v) {

	int child, parent,i;
	node temp;
	if (heap_check(heap_size)) {
		fprintf(stderr, "Heap is full.\n");
		exit(EXIT_FAILURE);
	}
	heap_size++;
	i = heap_size;
	/*child = i;
	parent = i / 2;
	heap_PQ[i] = v;
	while (child > 1 && v.bound > heap_PQ[parent].bound) {
		temp = heap_PQ[child];
		heap_PQ[child] = heap_PQ[parent];
		heap_PQ[parent] = temp;
		parent=child/ 2;
	}*/
	while ((i != 1) && v.bound > heap_PQ[i / 2].bound) {
		heap_PQ[i] = heap_PQ[i / 2];
		i /= 2;
	}
	heap_PQ[i] = v;
}

node pop() {
	
	/*
	int parent, child;
	node result;
	node temp;

	if (!(heap_size)) {
		fprintf(stderr, "Heap is empty\n");
		exit(EXIT_FAILURE);
	}

	result = heap_PQ[1];
	heap_size--;

	parent = 1;
	child = parent * 2;
	if (child + 1 <= heap_size) {
		child = (heap_PQ[child].bound > heap_PQ[child + 1].bound) ? child : child + 1;
	}

	while (child <= heap_size && heap_PQ[parent].bound < heap_PQ[child].bound) {
		temp = heap_PQ[parent];
		heap_PQ[parent] = heap_PQ[child];
		heap_PQ[child] = temp;

		parent = child;
		child = child * 2;
		if (child + 1 <= heap_size) {
			child = (heap_PQ[child].bound > heap_PQ[child + 1].bound) ? child : child + 1;
		}
	}
	return result;
	*/

	int parent, child;
	node result, temp;

	if (!(heap_size)) {
		fprintf(stderr, "Heap is empty\n");
		exit(EXIT_FAILURE);
	}

	result = heap_PQ[1]; // 우선순위가 제일 높은 요소

	temp = heap_PQ[(heap_size--)]; // 우선순위가 제일 낮은 요소
	parent = 1; 
	child = parent*2;
	while (child <= heap_size) {
		// 자식 중에서 값이 더 큰 자식을 찾는다.
		if ((child < heap_size) && (heap_PQ[child].bound < heap_PQ[child + 1].bound)) {
			child++;
		}
		if (temp.bound >= heap_PQ[child].bound) {// 레벨을 따라 temp가 들어갈 위치를 지정
			break;
		}
		heap_PQ[parent] = heap_PQ[child];
		parent = child;
		child *= 2;
	}
	heap_PQ[parent] = temp;

	return result;
}