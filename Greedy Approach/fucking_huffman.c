/*
* [2015114563] [김한영] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100
#define MALLOC(a,b) a=malloc(b)

typedef struct node* nodePointer;
typedef struct node {
	char symbol;
	int freq;
	nodePointer left;
	nodePointer right;
} nodeType;
nodePointer root = NULL;
nodeType letter_R[26];
int letterIndex = 0;
typedef struct HeapType{
	nodePointer heap[MAX];
	int heap_size;
}HeapType;
HeapType h;

char letter[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char huffmanCode[26][MAX];

void push(nodePointer item);
nodePointer pop();
nodePointer huffman();
nodePointer creative(nodeType item);
void traverse(nodePointer node, int codeN);
void encode(char input[], char output[]);
void decode(nodePointer root, char input[], char output[]);//?
int isin(char symbol, nodeType letter_R[]);
int find(char input);
int sizecheck(nodeType letter_R[]);
char input[MAX] = { '\0', };
char output[MAX] = { '\0', };
char codestr[MAX];
char original[MAX];
int codeN = -1;
int tempindex = 0;

int main(void) {
	h.heap_size = 0;


	printf("Enter the words:");
	gets_s(input,MAX-1);

	encode(input, output);
	decode(root, input, output);

	return 0;
}

void encode(char input[], char output[]) {

	nodePointer temp;
	int index;
	
	for (int i = 0; input[i] != '\0';i++) {
		
		if (isin(input[i],letter_R)) {
			index = find(input[i]);
			letter_R[index].freq++;
		}
		else {
			letter_R[tempindex].symbol = input[i];
			letter_R[tempindex++].freq++;
		}
	}
	
	for (int i = 0;i < sizecheck(letter_R);i++) {
		temp = creative(letter_R[i]);
		push(temp);
	}

	root = huffman();

	printf("\nHuffman code\n");
	traverse(root, codeN);
	index = strlen(input);
	for (int i = 0; i < index; i++) {
		strcat(output, huffmanCode[input[i]-'A']);//두 문자열 붙이기
	}

	printf("\n\nResult of Encoding :\n");
	printf("%s\n\n", output);
}

void push(nodePointer item) {
	int i;
	h.heap_size++;
	i = h.heap_size;//힙의 크기를 1증가

	while ((i != 1) && (item->freq < h.heap[i / 2]->freq)) {

		h.heap[i] = h.heap[i / 2];
		i /= 2;
	}
	h.heap[i] = item;
}

nodePointer pop() {

	int parent, child;
	nodePointer item, temp;

	item = h.heap[1];
	temp = h.heap[(h.heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h.heap_size) {
		if ((child < h.heap_size) && ((h.heap[child]->freq) > h.heap[child + 1]->freq)) {
			child++;
		}
		if ((temp->freq) <= (h.heap[child]->freq)) {
			break;
		}
		h.heap[parent] = h.heap[child];
		parent = child;
		child *= 2;
	}
	h.heap[parent] = temp;

	return item;
}

nodePointer huffman() {
	nodePointer p, q, r;
	nodeType item;
	for (int i = 1;i <= sizecheck(letter_R)- 1;i++) {
		p = pop();
		q = pop();
		item.freq= p->freq + q->freq;
		r = creative(item);
		r->left = p;
		r->right = q;
		push(r);
	}
	return pop();
}

void traverse(nodePointer node,int codeN) {// 필수 복습 ;;;
	if (node) {
		codeN++;
		codestr[codeN] = '0';
		traverse(node->left, codeN);
		codestr[codeN] = '1';
		traverse(node->right, codeN);
		codestr[codeN] = '\0';
		if (node->left == NULL || node->right == NULL) {
			printf("%c : ", node->symbol);
			for (int i = 0; i < codeN; i++)
				printf("%c", codestr[i]);
			printf("\n");
			strcpy(huffmanCode[(node->symbol)-'A'], codestr);
		}
	}
}

nodePointer creative(nodeType item) {
	nodePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->freq = item.freq;
	temp->symbol = item.symbol;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int isin(char symbol, nodeType letter_R[]) {

	for (int i = 0; i <sizecheck(letter_R);i++) {
		if (letter_R[i].symbol == symbol)
			return 1;
	}
	return 0;
}

int find(char input) {
	int i;
	for (i = 0;i < sizecheck(letter_R);i++) {
		if (letter_R[i].symbol == input)
			break;

	}
	return i;
}

int sizecheck(nodeType letter_R[]) {
	int i = 0;

	while (1) {
		if (letter_R[i].freq == 0)
			break;
		i++;
	}
	return i;
}

void decode(nodePointer root, char input[], char output[]) {
	int i = 0, j = 0;
	nodePointer current;
	current = root;
	while (output[i] != '\0') {

		if (output[i] == '0')
			current = current->left;
		else if (output[i] == '1')
			current = current->right;

		if (!current->left && !current->right) {
			original[j++] = current->symbol;
			current = root;
		}
		i++;
	}
		
		printf("\nResult of Decoding: \n");
		printf("%s\n\n", original);

	
}