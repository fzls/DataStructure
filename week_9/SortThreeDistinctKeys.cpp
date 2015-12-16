/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 SortThreeDistinctKeys.cpp
* @version:
* @Time: 		 2015-11-19 16:12:17
* @Description:
*
+----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

typedef enum { true, false, maybe } Keys;
typedef Keys ElementType;

void Read( ElementType A[], int N ); /* details omitted */

void MySort( ElementType A[], int N );

void PrintA( ElementType A[], int N )
{
	int i, k;

	k = i = 0;
	for ( ; i < N && A[i] == false; i++ );
	if ( i > k )
		printf("false in A[%d]-A[%d]\n", k, i - 1);
	k = i;
	for ( ; i < N && A[i] == maybe; i++ );
	if ( i > k )
		printf("maybe in A[%d]-A[%d]\n", k, i - 1);
	k = i;
	for ( ; i < N && A[i] == true; i++ );
	if ( i > k )
		printf("true in A[%d]-A[%d]\n", k, i - 1);
	if ( i < N )
		printf("Wrong Answer\n");
}

int main()
{
	int N;
	ElementType *A;

	scanf("%d", &N);
	A = (ElementType *)malloc(N * sizeof(ElementType));
	Read( A, N );
	MySort( A, N );
	PrintA( A, N );
	return 0;
}

/* Your function will be put here */
inline void swap(ElementType *a, ElementType *b) {
	if (*a == *b)
		return;
	ElementType temp = *a;
	*a = *b;
	*b = temp;
}
int sort( ElementType A[], int left, int right, int key) {
	for ( int curr = left;;) {
		for (; curr <= right && A[curr] != key; ++curr)
			;
		if (curr <= right)
			swap(&A[left++], &A[curr++]);
		else
			break;
	}
	return left;
}
void MySort( ElementType A[], int N ) {
	int EndOfFalseAreaByOne = sort(A, 0, N - 1, false);
	sort(A, EndOfFalseAreaByOne, N - 1, maybe );
}
