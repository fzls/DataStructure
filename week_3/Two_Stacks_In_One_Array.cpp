/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 Two_Stacks_In_One_Array.cpp
* @version:
* @Time: 		 2015-10-09 20:26:47
* @Description:  Two Stacks In One Array
*：结构内的成员的使用方法。
+----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord  {
	int Capacity;       /* maximum size of the stack array */
	int Top1;           /* top pointer for Stack 1 */
	int Top2;           /* top pointer for Stack 2 */
	ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
	int N, Sn, X;
	Stack S;
	int done = 0;

	scanf("%d", &N);
	S = CreateStack(N);
	while ( !done ) {
		switch ( GetOp() ) {
		case push:
			scanf("%d %d", &Sn, &X);
			if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
			break;
		case pop:
			scanf("%d", &Sn);
			X = Top_Pop(S, Sn);
			if ( X == ERROR ) printf("Stack %d is Empty!\n", Sn);
			break;
		case end:
			PrintStack(S, 1);
			PrintStack(S, 2);
			done = 1;
			break;
		}
	}
	system("pause");

	return 0;
}

/* Your function will be put here */

Stack CreateStack( int MaxElements ) {
	Stack stack = (Stack)malloc(sizeof(StackRecord));
	stack->Capacity = MaxElements;
	stack->Top1 = 0;
	stack->Top2 = MaxElements - 1;
	stack->Array = (ElementType *)malloc(sizeof(ElementType) * MaxElements);
	return stack;
}
int IsEmpty( Stack S, int Stacknum ) {
	return Stacknum == 1 ? S->Top1 == 0 : S->Top2 == S->Capacity - 1;
}
int IsFull( Stack S ) {
	return S->Top1 == S->Top2 + 1;
}
int Push( ElementType X, Stack S, int Stacknum ) {
	if (IsFull(S))
		return 0;
	else {
		if (Stacknum == 1) {
			S->Array[S->Top1++] = X;
		}
		else {
			S->Array[S->Top2--] = X;
		}
		return 1;
	}

}
ElementType Top_Pop( Stack S, int Stacknum ) {
	if (IsEmpty(S, Stacknum)) {
		return ERROR;
	}
	else {
		if (Stacknum == 1) {
			return S->Array[--S->Top1];
		}
		else
			return S->Array[++S->Top2];
	}
}

Operation GetOp() {
	printf("0:push 1:pop 2:end\n");
	int n;
	scanf("%d", &n);
	Operation op;
	switch (n) {
	case 0 : op = push ; break;
	case 1 : op = pop ; break;
	case 2 : op = end ; break;

	}
	return op;

}  /* details omitted */
void PrintStack( Stack S, int Stacknum ) {
	int i = 0;
	if (Stacknum == 1) {
		for (i = 0; i < S->Top1; i++)
			printf("%d ", S->Array[i] );
	}
	else {
		for (i = S->Capacity - 1; i > S->Top2; i--)
			printf("%d ", S->Array[i] );
	}
	printf("\n");

} /* details omitted */

