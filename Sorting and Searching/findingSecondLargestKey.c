/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define MALLOC(a,b) a=malloc(b)
#define MIN -10

int num = 0;
int*s;//승자트리
int*check;//최대값에게 패배한 수들을 모으는 리스트
int r = 0;
int flag = 1;
int counting = 0;

double logB(double x, double base) {
	return log(x) / log(base);
}

int count() {
	int cnt = (double)num + (double)ceil((double)logB(num, 2.0)) - (double)2;
	return cnt;
}

int main(void) {

	int aid = 0;
	int number, sum = 0;
	int secondlarge = -15;
	FILE*f = fopen("text.txt", "rt");

	fscanf(f, "%d", &num);
	number = num;
	if (num % 8) {//8로 나눠지지 않으면 예외 발생하므로 무조건 8로 나눠지게 한 뒤 추가적인 노드에는 MIN으로 채움.
		aid= 8 - (num % 8);
		number = number + aid;
	}
	while (1) {//전체 승자트리의 노드 수 계산
		sum += number;
		number /= 2;
		if (number == 1 || number == 0) {
			sum += 1;
			break;
		}
	}
	MALLOC(s, (sum + 1) * sizeof(int)); 
	MALLOC(check, (num + 1) * sizeof(int)); //대충 공간 할당함.
	
	for (int i = 1;i <=sum;i++) {
		s[i]=MIN;//노드 수를 맞추기 위해 생성된 노드에는 최저의 값을 대입하여 계산용이하게 함.
	}

	for (int i = 0;i <num;i++) {
		fscanf(f, "%d", &s[sum - i]);//파일 읽어서 승자트리 leaf node에 대입
	}
	for (int i = 0;i <= num;i++) {
		check[i] = 0;//초기화
	}

	for (int i = sum;i >= 3;i = i - 2) {
		if (s[i] > s[i - 1]) {//승자트리 구성하기, 자식노드로 부터 부모노드의 값을 결정 및 대입.
			s[i / 2] = s[i];
		}
		else {
			s[i / 2] = s[i - 1];
		}
	}

	while (flag <=(sum / 2)) {//s[1] 즉, 최대값에서부터 거꾸로 따라가면서 패배한 노드를 찾아 check 배열에 대입

		if (s[2 * flag] < s[2 * flag + 1]) {
			check[r++] = s[2 * flag];
			flag = 2 * flag + 1;
		}
		else {
			check[r++] = s[2 * flag + 1];
			flag = 2 * flag;
		}
	}
	counting = count(); //yame로 해결ㅎㅎ

	printf("the largest = %d \n", s[1]);
	printf("the list of the largest = ");

	for (int i = 0;i < r;i++) {
		if (check[i] == MIN) continue;//불필요하게 넣은 값 일 경우 무시하고 다음 차례로~
		printf("%d ", check[i]);
		if (check[i] > secondlarge) {//차대키 업데이트
			secondlarge = check[i];
		}
	}
	printf("\n");
	printf("the second largest= %d\n", secondlarge);
	printf("the number of comparisons= %d\n", counting);


	return 0;
}