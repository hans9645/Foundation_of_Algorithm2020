/*
* [2015114563] [���ѿ�] ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define MALLOC(a,b) a=malloc(b)
#define MIN -10

int num = 0;
int*s;//����Ʈ��
int*check;//�ִ밪���� �й��� ������ ������ ����Ʈ
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
	if (num % 8) {//8�� �������� ������ ���� �߻��ϹǷ� ������ 8�� �������� �� �� �߰����� ��忡�� MIN���� ä��.
		aid= 8 - (num % 8);
		number = number + aid;
	}
	while (1) {//��ü ����Ʈ���� ��� �� ���
		sum += number;
		number /= 2;
		if (number == 1 || number == 0) {
			sum += 1;
			break;
		}
	}
	MALLOC(s, (sum + 1) * sizeof(int)); 
	MALLOC(check, (num + 1) * sizeof(int)); //���� ���� �Ҵ���.
	
	for (int i = 1;i <=sum;i++) {
		s[i]=MIN;//��� ���� ���߱� ���� ������ ��忡�� ������ ���� �����Ͽ� �������ϰ� ��.
	}

	for (int i = 0;i <num;i++) {
		fscanf(f, "%d", &s[sum - i]);//���� �о ����Ʈ�� leaf node�� ����
	}
	for (int i = 0;i <= num;i++) {
		check[i] = 0;//�ʱ�ȭ
	}

	for (int i = sum;i >= 3;i = i - 2) {
		if (s[i] > s[i - 1]) {//����Ʈ�� �����ϱ�, �ڽĳ��� ���� �θ����� ���� ���� �� ����.
			s[i / 2] = s[i];
		}
		else {
			s[i / 2] = s[i - 1];
		}
	}

	while (flag <=(sum / 2)) {//s[1] ��, �ִ밪�������� �Ųٷ� ���󰡸鼭 �й��� ��带 ã�� check �迭�� ����

		if (s[2 * flag] < s[2 * flag + 1]) {
			check[r++] = s[2 * flag];
			flag = 2 * flag + 1;
		}
		else {
			check[r++] = s[2 * flag + 1];
			flag = 2 * flag;
		}
	}
	counting = count(); //yame�� �ذ᤾��

	printf("the largest = %d \n", s[1]);
	printf("the list of the largest = ");

	for (int i = 0;i < r;i++) {
		if (check[i] == MIN) continue;//���ʿ��ϰ� ���� �� �� ��� �����ϰ� ���� ���ʷ�~
		printf("%d ", check[i]);
		if (check[i] > secondlarge) {//����Ű ������Ʈ
			secondlarge = check[i];
		}
	}
	printf("\n");
	printf("the second largest= %d\n", secondlarge);
	printf("the number of comparisons= %d\n", counting);


	return 0;
}