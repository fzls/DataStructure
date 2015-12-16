/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 PercolateUpAndDown.cpp
* @version:
* @Time: 		 2015-11-05 17:38:26
* @Description:  Write the routines to do a "percolate up" and a "percolate down" in a binary min-heap.
*
+----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
	ElementType  *Elements;
	int Capacity;
	int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H ) {
	while (H->Elements[p] < H->Elements[p / 2]) {
		ElementType tmp = H->Elements[p];
		H->Elements[p] = H->Elements[p / 2];
		H->Elements[p / 2] = tmp;
		p /= 2;
	}
}
void PercolateDown( int p, PriorityQueue H ) {
	ElementType littleChild = p * 2;
	while (littleChild <= H->Size) {
		if (littleChild < H->Size && H->Elements[littleChild + 1] < H->Elements[littleChild])
			littleChild++;
		if (H->Elements[littleChild] < H->Elements[p]) {
			ElementType tmp = H->Elements[p];
			H->Elements[p] = H->Elements[littleChild];
			H->Elements[littleChild] = tmp;
			p = littleChild;
			littleChild = p * 2;
		}
		else
			break;
	}
}

void Insert( ElementType X, PriorityQueue H )
{
	int p = ++H->Size;
	H->Elements[p] = X;
	PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H )
{
	ElementType MinElement;
	MinElement = H->Elements[1];
	H->Elements[1] = H->Elements[H->Size--];
	PercolateDown( 1, H );
	return MinElement;
}

int main()
{
	int n, i, op, X;
	PriorityQueue H;

	scanf("%d", &n);
	H = Initialize(n);
	for ( i = 0; i < n; i++ ) {
		scanf("%d", &op);
		switch ( op ) {
		case 1:
			scanf("%d", &X);
			Insert(X, H);
			break;
		case 0:
			printf("%d ", DeleteMin(H));
			break;
		}
	}
	printf("\nInside H:");
	for ( i = 1; i <= H->Size; i++ )
		printf(" %d", H->Elements[i]);
	return 0;
}

/* Your function will be put here */
