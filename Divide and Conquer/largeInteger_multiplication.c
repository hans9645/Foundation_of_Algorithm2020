#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include<malloc.h>
#define CALLOC(p,n,s)\
    if(!((p) = calloc(n,s))){\
        fprintf(stderr, "memory error\n"); \
        exit(EXIT_FAILURE);\
    }

// ? ?? ??? ????

int* prod(int* u, int* v); // ? ?? ???
int* arrayAdd(int* a, int* b); // ?? ???
int* arrayMult(int* a, int* b); // ?? ??? (?? ????)
int sizeofArray(int* a); //??? ?? ??
int* divideArray(int* a, int m); //???? ??? ??
int* remArray(int* a, int m); // ???? ??? ??
int* ArrayPow(int* a, int m); // 10^m ??
int* manageSize(int* a); // ??? ??? ??
void carry(int* a); // ??? ?? ??
int* changeToint(char* a); // ???? ??? ??? ??

int* mul;


int main() {
    char a[40], b[40];
    int* u, * v;
    int i;
  
    printf("Enter the number of u : "); gets_s(a, 40);
    printf("Enter the number of v : "); gets_s(b, 40);

    u = changeToint(a);
    v = changeToint(b);

    mul = prod(u, v);
    mul = manageSize(mul);

    printf("Result of multiplication :\n");
    for (i = sizeofArray(mul)-1; i > 0; i--) {
        if (((i - 1) % 3) == 0 && i != 1) printf("%d,", mul[i]);
        else printf("%d", mul[i]);
    }
    printf("\n");

    free(u);
    free(v);
    free(mul);
    
    return 0;
}

// ? ?? ???
int* prod(int* u, int* v) {
    int* x, * y, * w, * z;
    int* temp;
    int n, m, min_n;
    int* zero;
    n = sizeofArray(u) >= sizeofArray(v) ? sizeofArray(u) : sizeofArray(v);
    min_n= sizeofArray(u) >= sizeofArray(v) ? sizeofArray(v) : sizeofArray(u);

    if (_msize(u) == 0 || _msize(v) == 0) {
        zero = (int*)calloc(2, sizeof(int));
        return zero;
    }

    if (n <= 2 || min_n <= n / 2) {
        return arrayMult(u, v);
    }

    else {
        m = n / 2;
        x = divideArray(u, m);    y = remArray(u, m);
        w = divideArray(v, m);    z = remArray(v, m); 

        temp = arrayAdd(ArrayPow(prod(x, w), 2 * m), ArrayPow(arrayAdd(prod(x, z), prod(w, y)), m));
        temp = arrayAdd(temp, prod(y, z));
       
        return temp;
    }
}

// ?? ???
int* arrayAdd(int* a, int* b) {
    int i, a_n, b_n, c_n;
    int* c;

    a_n = sizeofArray(a);
    b_n = sizeofArray(b);
    c_n = (a_n >= b_n) ? a_n + 1 : b_n + 1;

    CALLOC(c, c_n, sizeof(int));

    for (i = 1; i < a_n; i++) c[i] += a[i];
    for (i = 1; i < b_n; i++) c[i] += b[i];

    carry(c);
    
    
    return c;
}

// ?? ??? (?? ????)
int* arrayMult(int* a, int* b) {
    int i, j, a_n, b_n, c_n;
    int* c;

    a_n = sizeofArray(a);
    b_n = sizeofArray(b);
    c_n = sizeofArray(a) >= sizeofArray(b) ? sizeofArray(a) : sizeofArray(b);

    CALLOC(c, c_n + 1, sizeof(int));

    for (i = 1; i < a_n; i++)
        for (j = 1; j < b_n; j++)
            c[i + j - 1] += a[i] * b[j];

    carry(c);
  
    return c;
}

//??? ?? ??
int sizeofArray(int* a) {
    int n;

    n = _msize(a) / sizeof(int);

    return n;
}

// ??? ?? ??
void carry(int* a) {
    int n, i, carry;
    n = sizeofArray(a);
    
    for (i = 1; i < n; i++) {
        if (a[i] != 0 && a[i] >= 10) {
            carry = a[i] / 10;
            a[i] = a[i] % 10;
            a[i + 1] += carry;
        }
    }
}

// ???? ??? ?? (??)
int* divideArray(int* a, int m) {
    int n, i;
    int* c;
    n = sizeofArray(a) - m;

    if (n == 1) {
        CALLOC(c, n , sizeof(int)); // n+1
        return c;
    }

    CALLOC(c, n, sizeof(int));

    for (i = 1; i < n; i++) {
        c[i] = a[m + i];
    }

    return c;
}

// ???? ??? ?? (??)
int* remArray(int* a, int m) {
    int i;
    int* c;
    CALLOC(c, m + 1, sizeof(int));

    for (i = 1; i <= m; i++) c[i] = a[i];

    return c;
}

// 10^m ??
int* ArrayPow(int* a, int m) {
    int n, i;
    int* c;

    n = sizeofArray(a) + m;
    CALLOC(c, n, sizeof(int));

    for (i = 1; i < sizeofArray(a); i++) {
        c[m + i] = a[i];
    }
    
    return c;
}

// ??? ??? ??
int* manageSize(int* a) {
    int i, n, check=0;
    int* c;

    n = sizeofArray(a);
    for (i = n - 1; i > 0; i--) {
        if (a[i] != 0) {
            check = i;
            break;
        }
    }
    CALLOC(c, check + 1, sizeof(int));
    
    for (i = 1; i <= check; i++) {
        c[i] = a[i];
    }

    return c;
}

// ???? ??? ??? ??
int* changeToint(char* a) {
    int i = 0, check = 0;
    int* c;

    while (1) {
        if (a[i] == '\0') break;
        i++;
    }

    check = i;

    CALLOC(c, check + 1, sizeof(int));

    for (i = 0; i < check; i++) {
        c[i + 1] = a[check - 1 - i] - '0';
    }
    return c;
}