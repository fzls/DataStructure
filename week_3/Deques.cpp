/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 Deques.cpp
* @version:
* @Time: 		 2015-10-09 21:09:14
* @Description:暴露的问题：	1.malloc 使用方法不熟（忘记了 - -）
* 							2.C语言中 struct使用时 需要以 struct mystruct 使用
* 							3.双向链表非两端的结点的插入与删除逻辑。
*
+----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
	ElementType Element;
	PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
	PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp() {
	int n;
	scanf("%d", &n);
	Operation op;
	switch (n) {
	case 0 : op = push ; break;
	case 1 : op = pop ; break;
	case 2 : op = inject ; break;
	case 3 : op = eject ; break;
	case 4 : op = end ; break;

	}
	return op;

}  /* details omitted */

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ) {
	PtrToNode p = D->Front;
	if (p != D->Rear) {

		for (p = p->Next; p != 0; p = p->Next)
			printf("%d ", p->Element);

	}
}

int main()
{
	ElementType X;
	Deque D;
	int done = 0;

	D = CreateDeque();
	while (!done) {
		switch (GetOp()) {
		case push:
			scanf("%d", &X);
			if (!Push(X, D)) printf("Memory is Full!\n");
			break;
		case pop:
			X = Pop(D);
			if ( X == ERROR ) printf("Deque is Empty!\n");
			break;
		case inject:
			scanf("%d", &X);
			if (!Inject(X, D)) printf("Memory is Full!\n");
			break;
		case eject:
			X = Eject(D);
			if ( X == ERROR ) printf("Deque is Empty!\n");
			break;
		case end:
			PrintDeque(D);
			done = 1;
			break;
		}
	}
	system("pause");

	return 0;
}

/* Your function will be put here */



Deque CreateDeque() {
	Deque deque = (Deque)malloc(sizeof(struct DequeRecord));
	PtrToNode dummyHeader = (PtrToNode)malloc(sizeof(struct Node));
	dummyHeader->Next = dummyHeader->Last = 0;
	deque->Front = deque->Rear = dummyHeader;
	return deque;
}
int Push( ElementType X, Deque D ) {
	PtrToNode pNode;
	if (!(pNode = (PtrToNode)malloc(sizeof(struct Node))))
		return 0;
	else {
		pNode->Element = X;
		pNode->Last = D->Front;

		if ( D->Rear == D->Front ) {
			D->Rear = pNode;
			pNode->Next = NULL;
		}
		else {
			pNode->Next = D->Front->Next;
			D->Front->Next->Last = pNode;
		}
		D->Front->Next = pNode;

		// pNode->Next = D->Front->Next;

		// D->Front->Next = pNode;
		// if (pNode->Next == 0) {
		// 	D->Rear = pNode;
		// }else{
		// 	pNode->Next->Last=pNode;
		// }
		return 1;
	}

}
ElementType Pop( Deque D ) {
	if (D->Front == D->Rear)
		return ERROR;
	else {
		PtrToNode pNode = D->Front->Next;
		ElementType result = pNode->Element;
		if (!pNode->Next) {
			D->Front->Next = 0;
			D->Rear = D->Front;
		}
		else {
			pNode->Last->Next = pNode->Next;
			pNode->Next->Last = pNode->Last;
		}
		free(pNode);
		return result;
	}

}
int Inject( ElementType X, Deque D ) {
	PtrToNode pNode;
	if (!(pNode = (PtrToNode)malloc(sizeof(struct Node))))
		return 0;
	else {
		pNode->Last = D->Rear;
		pNode->Next = 0;
		pNode->Element = X;

		D->Rear->Next = pNode;

		D->Rear = pNode;
		return 1;
	}
}
ElementType Eject( Deque D ) {
	if (D->Front == D->Rear)
		return ERROR;
	else {
		PtrToNode pNode = D->Rear;
		D->Rear = D->Rear->Last;
		D->Rear->Next = 0;
		ElementType result = pNode->Element;
		free(pNode);
		return result;
	}
}