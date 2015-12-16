/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 Add_Two_Polynomials.cpp
* @version:
* @Time: 		 2015-09-24 18:06:06
* @Description:  4-1 Add Two Polynomials   (10分)
*
+----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
	int Coefficient;
	int Exponent;
	PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );


int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);

	Polynomial a, b, s;
	a = Read();
	b = Read();
	s = Add(a, b);
	Print(s);

	// system("pause");
	return 0;
}

Polynomial Read() {
	int number, temp_coefficient, temp_exponent;
	Polynomial polynomial = (Polynomial) malloc(sizeof(struct Node));
	polynomial->Next = 0;
	PtrToNode temp_node, p;
	scanf("%d", &number);
	int i;
	for (i = 0; i < number; i++) {
		scanf("%d%d", &temp_coefficient, &temp_exponent);
		temp_node = (PtrToNode) malloc(sizeof(struct Node));
		temp_node->Coefficient = temp_coefficient;
		temp_node->Exponent = temp_exponent;
		p = polynomial;
		while (p->Next != 0) {
			if (temp_node->Exponent < p->Next->Exponent)
				p = p->Next;
			else
				break;
		}
		temp_node->Next = p->Next;
		p->Next = temp_node;
	}
	return polynomial;
}

void Print( Polynomial p ) {
	p = p->Next;
	while (p != 0) {
		printf("%d %d ", p->Coefficient, p->Exponent );
		p = p->Next;
	}
	printf("\n");
}

Polynomial Add( Polynomial a, Polynomial b ) {
	Polynomial sum = (Polynomial) malloc(sizeof(struct Node));
	Polynomial p = sum;
	p->Next = 0;
	PtrToNode temp = 0;
	a = a->Next;
	b = b->Next;
	while (a != 0 && b != 0) {
		if (a->Exponent > b->Exponent) {
			temp = (PtrToNode) malloc(sizeof(struct Node));
			temp->Coefficient = a->Coefficient;
			temp->Exponent = a->Exponent;
			temp->Next = 0;
			p->Next = temp;
			p = p->Next;
			a = a->Next;
		}
		else if (a->Exponent < b->Exponent) {
			temp = (PtrToNode) malloc(sizeof(struct Node));
			temp->Coefficient = b->Coefficient;
			temp->Exponent = b->Exponent;
			temp->Next = 0;
			p->Next = temp;
			p = p->Next;
			b = b->Next;
		}
		else {
			if (a->Coefficient + b->Coefficient != 0) {
				temp = (PtrToNode) malloc(sizeof(struct Node));
				temp->Coefficient = a->Coefficient + b->Coefficient;
				temp->Exponent = a->Exponent;
				temp->Next = 0;
				p->Next = temp;
				p = p->Next;
			}
			a = a->Next;
			b = b->Next;
		}
	}
	while (a != 0) {
		temp = (PtrToNode) malloc(sizeof(struct Node));
		temp->Coefficient = a->Coefficient;
		temp->Exponent = a->Exponent;
		temp->Next = 0;
		p->Next = temp;
		p = p->Next;
		a = a->Next;
	}
	while (b != 0) {
		temp = (PtrToNode) malloc(sizeof(struct Node));
		temp->Coefficient = b->Coefficient;
		temp->Exponent = b->Exponent;
		temp->Next = 0;
		p->Next = temp;
		p = p->Next;
		b = b->Next;
	}
	return sum;
}

