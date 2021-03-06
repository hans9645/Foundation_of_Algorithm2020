/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define minimum(a,b) (((a)<(b))? a : b)
#define NUM_KEYS 1000 // 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000
#define MALLOC(p,s) (((p)=malloc(s)))


int select(int n, int s[], int k);
int selection2(int s[], int low, int high, int k);
void partition2(int s[], int low, int high, int* pivotpoint);
int median(int s[], int low, int high);

int selection3(int low, int high, int k);
void partition3(int low, int high, int* pivotpoint);
void swap(int s[], int i, int j);

int num = NUM_KEYS;
int s[NUM_KEYS + 1];
int count;


int main() {
	int i, j, k, m;
	int key, result, totalcount = 0;
	clock_t start, end;
	float runtime = 0;

	srand(time(NULL));

	for (i = 1; i <= num; i++)
	{
		s[i] = i + 10;
	}

	for (m = 0; m < 100; m++) {

		key = rand() % 100 + 1;

		for (i = 0; i < 100; i++) { 
			// 재배열
			j = rand() % num;
			k = rand() % num;
			swap(s, j, k);
		}

		start = clock();
		//초기시각 지정


		//result = selection2(s, 1, num, key); // Median Algorithm 구현실행함수
		result = selection3(1, num, key); // Sherwood Algorithm 실행함수

		end = clock();
		//끝시각

		runtime += (float)(end - start) / CLOCKS_PER_SEC;//총 런타임
		totalcount += count;
		
	}
	printf("avg comparision : %d\n avg runtime : %f\n", totalcount / 100, runtime / 100);//millisec.

	return 0;
}

int select(int n, int s[], int k) {
	return selection2(s, 1, n, k);
}

int selection2(int s[], int low, int high, int k) {
	int pivotpoint;

	if (low == high)
		return s[low];
	else {
		partition2(s, low, high, &pivotpoint);
		count++;
		if (k == pivotpoint)
			return s[pivotpoint];
		else if (k < pivotpoint)
			return selection2(s, low, pivotpoint - 1, k);
		else
			return selection2(s, pivotpoint + 1, high, k);
	}
}

void partition2(int s[], int low, int high, int* pivotpoint) {
	int arraysize = high - low + 1;
	int r = (int)ceil((double)arraysize / 5); // 반올림
	int i, j, mark = 0, first, last;
	int pivotitem, *T;

	MALLOC(T, (r + 1) * sizeof(*T));
	for (i = 1; i <= r; i++) {
		first = low + 5 * i - 5;
		last = minimum(low + 5 * i - 1, high); 
		T[i] = median(s, first, last);
	}
	pivotitem = select(r, T, (int)floor((r + 1) / 2)); //median 의 median
	j = low;
	for (i = low; i <= high; i++) {
		count++;
		if (s[i] == pivotitem) {
			swap(s, i, j);
			mark = j++;
		}
		else if (s[i] < pivotitem) {
			swap(s, i, j);
			j++;
		}
	}
	*pivotpoint = j - 1;
	swap(s, mark, *pivotpoint);
}

void swap(int s[], int i, int j)
{
	int t = s[i];
	s[i] = s[j];
	s[j] = t;
}
int median(int s[], int first, int last) {
	//win,lose 함수
	int win1, win2;
	int lose1, lose2;

	if ((last - first) < 4 && (last - first) != 3) {
		count++;
		return s[(first + last) / 2];
	}
	else if ((last - first) == 3) {
		count += 4;
		return	s[first] < s[first + 1] ? (s[first] > s[first + 2] ? s[first] : (s[first + 2] < s[first + 1] ? s[first + 2] : s[first + 1])) : (s[first + 1] > s[first + 2] ? s[first + 1] : (s[first + 2] < s[first] ? s[first + 2] : s[first]));
	}

	else {
		count += 6;
		if (s[first] > s[first + 1]) {
			win1 = s[first];
			lose1 = s[first + 1];
		}
		else {
			win1 = s[first + 1];
			lose1 = s[first];
		}
		if (s[first + 2] > s[first + 3]) {
			win2 = s[first + 2];
			lose2 = s[first + 3];
		}
		else {
			win2 = s[first + 3];
			lose2 = s[first + 2];
		}
	}
	if (win1 > win2) {
		if (s[first + 4] > lose1)
			win1 = s[first + 4];
		else {
			win1 = lose1;
			lose1 = s[first + 4];
		}
	}
	else {

		if (s[first + 4] > lose2)
			win2 = s[first + 4];
		else {
			win2 = lose2;
			lose2 = s[first + 4];
		}
	}

	if (win1 > win2)
		return (win2 > lose1) ? win2 : lose1;

	else
		return (win1 > lose2) ? win1 : lose2;
}

int selection3(int low, int high, int k) {
	int pivotpoint;
	if (low == high)
		return s[low];
	else {
		partition3(low, high, &pivotpoint);
		count++;
		if (k == pivotpoint)
			return s[pivotpoint];
		else if (k < pivotpoint)
			return selection3(low, pivotpoint - 1, k);
		else
			return selection3(pivotpoint + 1, high, k);
	}
}

void partition3(int low, int high, int* pivotpoint) {
	int  pivotitem;
	int i, j, randspot, mark;
	int a = (rand() % high)+low;

	randspot = a;
	pivotitem = s[randspot];
	j = low;
	for (i = low; i <= high; i++) {
		count++;
		if (s[i] == pivotitem) {
			swap(s, i, j);
			j++;
		}
	}
	*pivotpoint = j;
	swap(s, low, *pivotpoint);
}

