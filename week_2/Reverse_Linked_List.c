/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 Reverse_Linked_List.c
* @version:
* @Time: 		 2015-09-24 19:38:46
* @Description:  4-2 Reverse Linked List   (10分)
*
+----------------------------------------------------------
*/
List Reverse( List L ) {
	if (L->Next != 0) {
		Position prior, curr, next;
		prior = 0;
		curr =	L->Next;
		next = curr->Next;
		while (next != 0) {
			curr->Next = prior;
			prior = curr;
			curr = next;
			next = next->Next;
		}
		curr->Next = prior;
		L->Next = curr;
	}
	return L;
}


typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
	ElementType Element;
	Position Next;
};
