/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 Level-order_Traversal.cpp
* @version:
* @Time: 		 2015-10-15 16:32:06 ~2015-10-15 17:07:52
* @Description:  4-1 Level-order Traversal   (8分)
*test gits in this program
*well this is really fun, so next time or more precisely, after i read the algorithms, i will learn to use it.
+----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10 /* maximum number of nodes in a tree */
typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
	ElementType Element;
	Tree  Left;
	Tree  Right;
};

Tree BuildTree(); /* details omitted */
void d( Tree NodePtr )
{
	printf(" %d", NodePtr->Element);
}

void Level_order ( Tree T, void (*visit)(Tree ThisNode) );

int main()
{
	Tree T = BuildTree();
	printf("Level-order:");
	Level_order(T, PrintNode);
	system("pause");

	return 0;
}

/* Your function will be put here */

// #define MaxTree 10 /* maximum number of nodes in a tree */
// typedef int ElementType;

// typedef struct TreeNode *Tree;
// struct TreeNode {
// 	ElementType Element;
// 	Tree  Left;
// 	Tree  Right;
// };

void Level_order ( Tree T, void (*visit)(Tree ThisNode) ) {
	if (T) {
		Tree queue[MaxTree], temp;

		int front = -1, rear = -1;
		queue[++rear] = T;
		while (front != rear) {
			temp = queue[++front];
			visit(temp);
			if (temp->Left)//not T, but the current node, namely the temp;
				queue[++rear] = temp->Left;
			if (temp->Right)
				queue[++rear] = temp->Right;

		}
	}



}