#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int A, M, E, R, Y, X, S, T, O, L;
int* alpha[10] = { &A, &M, &E, &R, &Y, &X, &S, &T, &O, &L };

int check() {
	int flag = 0;
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 10;j++) {
			if (*alpha[i] == *alpha[j]) {
				flag++;
			}
		}
	}
	if (flag == 10) {
		return 1;
	}
	else {
		return 0;
	}
}

int square(int num) {
	int temp = sqrt((double)num);
	return ((temp * temp) == num);
}


int main(void) {
	
	char in ;
	FILE*f = fopen("input1.txt", "rt");
	while (!feof(f)) {
		fscanf(f, "%c", &in);
		printf("%c", in);
		if (feof(f)) {
			break;
		}
	}
	printf("\n");

	int ary[3] = { 1,4,9 };
	int ary_TO[5] = { 16,25,36,49,81 };
	int num;

	for (int i = 0;i < 3;i++) {
		A = ary[i];
		for (int i = 10;i*i < 1000;i++) {
			if (i*i / 100 == A) {
				if ((i*i / 10) % 10 == i*i % 10) {
					L = i*i%10;	
					for (int i = 31;i*i< 10000;i++) {
						num = i*i;
						if((num/10)%10==A){
							X = num / 1000;
							M = (num / 100) % 10;
							S = num % 10;
							for (int i = 100;i*i < 100000;i++) {
								num =i*i;
								if (num / 10000 == M) {
									if ((num / 100) % 10 == (num / 10) % 10) {
										R = (num / 100) % 10;
										Y = num % 10;
										E = (num / 1000) % 10;
										for (int i = 0;i <=5;i++) {
											if (ary_TO[i] / 10!=A) {
												if (ary_TO[i] / 10 != M) {
													if (ary_TO[i] / 10 != E) {
														if (ary_TO[i] / 10 != R) {
															if (ary_TO[i] / 10 != Y) {
																if (ary_TO[i] / 10 != X) {
																	if (ary_TO[i] / 10 != S) {
																		if (ary_TO[i] / 10 != L) {
																			T = ary_TO[i] / 10;
																			O = ary_TO[i] % 10;
																			if (check()) {
																				if(square(X+M+A+S))
																				//printf("%2d %2d %2d %2d %2d %2d %2d %2d %2d %2d\n", A, M, E, R, Y, X, S, T, O, L);
																				printf("A  M E R R Y  X M A S  T O  A L L\n%d %2d%2d%2d%2d%2d %2d%2d%2d%2d %2d%2d %2d%2d%2d\n", A, M, E, R, R, Y, X, M, A, S, T, O, A, L, L);
																			}
																			}
																	}

																}

															}
														}
													}
												}

											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


	return 0;
}