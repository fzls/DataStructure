/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 IterativeMergesort.cpp
* @version:
* @Time: 		 2015-11-05 17:57:18
* @Description:  How would you implement mergesort without using recursion?
The idea of iterative mergesort is to start from N sorted sublists of length 1, and each time to merge a pair of adjacent sublists until one sorted list is obtained. You are supposed to implement the key function of merging.
*
+----------------------------------------------------------
*/
#include <stdio.h>

#define ElementType int
#define MAXN 100
void merge(ElementType list[], ElementType sorted[], int left, int left_bound, int right, int right_bound) {
	int t = left;
	while (left <= left_bound && right <= right_bound)
		if (list[left] <= list[right])
			sorted[t++] = list[left++];
		else
			sorted[t++] = list[right++];
	while (left <= left_bound)
		sorted[t++] = list[left++];
	while (right <= right_bound)
		sorted[t++] = list[right++];
}

void merge_pass( ElementType list[], ElementType sorted[], int N, int length ) {
	int i;
	for (i = 0; i <= N - 2 * length; i += 2 * length)
		merge(list, sorted, i, i + length - 1, i + length, i + 2 * length - 1);
	if (i >= N - length)
		while (i < N) {
			sorted[i] = list[i];
			++i;
		}
	else
		merge(list, sorted, i, i + length - 1, i + length, N - 1);
}

void output( ElementType list[], int N )
{
	int i;
	for (i = 0; i < N; i++) printf("%d ", list[i]);
	printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
	ElementType extra[MAXN];  /* the extra space required */
	int  length = 1;  /* current length of sublist being merged */
	while ( length < N ) {
		merge_pass( list, extra, N, length ); /* merge list into extra */
		output( extra, N );
		length *= 2;
		merge_pass( extra, list, N, length ); /* merge extra back to list */
		output( list, N );
		length *= 2;
	}
}


int main()
{
	int N, i;
	ElementType A[MAXN];

	scanf("%d", &N);
	for (i = 0; i < N; i++) scanf("%d", &A[i]);
	merge_sort(A, N);
	output(A, N);

	return 0;
}

/* Your function will be put here */
