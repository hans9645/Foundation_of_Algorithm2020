/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define heapfull(num) (heapsize == MAX-1)
#define MAX 100
#define True 1
#define False 0
#define CALLOC(p,n,s)\
 if(!((p)=calloc(n,s))){\
    fprintf(stderr,"Insufficient memory");\
    exit(EXIT_FAILURE);\
    }

#define INF 255

typedef struct {
	int level;
	int bound;
	int path[MAX];
} node;

node heap[MAX]; 
int heapsize = 0; 

int n, m, W[MAX][MAX];

int minlength, *opt;


void travel(int n, int minlength); 
int length(node v);

int bound(node v);

int contains(int path[], int vertex); 
int hasoutgoing(int path[], int vertex); 
int hasincoming(int path[], int vertex); 
int lastOf(int path[]); 
void Setinsert(int path[], int vertex);
void printPath(node u, int minlength); 

void push(node item); 

node pop(); 
int remaining(int path[]);




int main() {
	int i, j;
	int k, temp;

	FILE* f = fopen("input.txt", "r");

	fscanf(f, "%d %d", &n, &m);

	CALLOC(opt, (n + 2), sizeof(int));

	for (k = 0; k < m; k++) {
		fscanf(f, "%d %d %d", &i, &j, &temp);
		W[i][j] = temp;
	}

	travel(n, minlength);

	return 0;
}

void travel(int n, int minlength) {
	int i, j;
	node u, v;

	for (i = 0; i <= n + 1; i++) {
		u.path[i] = 0;
		v.path[i] = 0;
	}
	v.level = 0;  v.path[v.level] = 1;  v.bound = bound(v);
	minlength = INF;
	push(v);
	printPath(v, minlength);

	while (heapsize != 0) {

		v = pop(&heapsize);

		if (v.bound < minlength) {
			u.level = v.level + 1;
			for (i = 2; i <= n; i++) {
				if (contains(v.path, i)) 
					continue;
				for (j = 0; j <= n; j++) u.path[j] = v.path[j];
				Setinsert(u.path, i); 

				if (u.level == n - 2) {
					Setinsert(u.path, remaining(u.path)); 
					Setinsert(u.path, 1); 
					u.bound = 0;
					if (length(u) < minlength) {
						minlength = length(u);
						for (j = 0; j <= n; j++) opt[j] = u.path[j];
					}
					printPath(u, minlength);
				}
				else {
					u.bound = bound(u);

					if (u.bound < minlength) {

						push(u);
						printPath(u, minlength);
					}
				}
			}
		}
	}
	
	printf("[");
	for (i = 0; i <= n; i++) {
		if (opt[i + 1] == 0) {
			printf(" %d]", opt[i]);
			break;
		}
		else printf(" %d,", opt[i]);
	}
	printf(":minlength = %d\n", minlength);
}



int bound(node v) {
	int min, total = length(v);

	for (int i = 1; i <= n; i++) {
		if (hasoutgoing(v.path, i)) continue; 
		min = MAX;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (hasincoming(v.path, j)) continue;
			if (j == 1 && i == lastOf(v.path)) continue; 
			if (min > W[i][j]) min = W[i][j]; 
		}
		total += min;
	}
	return total;
}

int contains(int path[], int vertex) {
	int i;

	for (i = 0; i <= n; i++)
		if (vertex == path[i])
			return True;

	return False;
}

void Setinsert(int path[], int vertex) {
	int i;
	for (i = 0; i <= n; i++) {
		if (path[i] == 0) {
			path[i] = vertex;
			break;
		}
	}
}

int lastOf(int path[]) {
	int i;

	for (i = 0; i <= n; i++) {
		if (path[i + 1] == 0) break;
	}
	return path[i];
}
int length(node v) {
	int i = 0, j = 1, len = 0;
	while (v.path[i] != 0 && v.path[j] != 0) {
		len = len + W[v.path[i]][v.path[j]];
		i++; j++;
	}

	return len;
}
int hasoutgoing(int path[], int vertex) {
	int i;
	for (i = 0; i < n; i++) {
		if (path[i] == vertex && path[i + 1] != 0) 
			return True; 
	}

	return False;
}

int hasincoming(int path[], int vertex) {
	int i;
	for (i = 1; i <= n; i++) {
		if (path[i] == vertex && path[i - 1] != 0) 
			return True; 
	}

	return False;
}

int remaining(int path[]) { 
	int k;
	int arr[MAX];

	for (k = 1; k <= n; k++) {
		arr[k] = k;
	}
	for (k = 0; k <= n; k++) {
		arr[path[k]] = 0;
	}
	for (k = 1; k <= n; k++) {
		if (arr[k] != 0)
			break;
	}

	return k;
}


void printPath(node u, int minlength) {
	int i;

	printf("level = %d, bound = %d, path = ", u.level, u.bound);

	printf("[");
	for (i = 0; i <= n; i++) {
		if (u.path[i + 1] == 0) {
			printf(" %d ]", u.path[i]);
			break;
		}
		else printf(" %d,", u.path[i]);
	}
	printf(" (minlength = %d)\n", minlength);
}

void push(node item) {
	int i;
	if (heapfull(heapsize)) {
		fprintf(stderr, "Heap is full.\n");
		exit(EXIT_FAILURE);
	}

	i = ++(heapsize);
	while ((i != 1) && item.bound < heap[i / 2].bound) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

node pop(int* num) {
	int parent, child;
	node items, temp;

	if (!(*num)) {
		fprintf(stderr, "Heap is empty\n");
		exit(EXIT_FAILURE);
	}

	items = heap[1]; 
	temp = heap[(*num)--]; 
	parent = 1;  child = 2;
	while (child <= *num) {
	
		if ((child < *num) && (heap[child].bound > heap[child + 1].bound)) child++;
		
		if (temp.bound <= heap[child].bound)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}


	heap[parent] = temp;

	return items;
}