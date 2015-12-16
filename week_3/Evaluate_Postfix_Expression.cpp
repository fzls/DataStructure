/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 Evaluate_Postfix_Expression.cpp
* @version:
* @Time: 		 2015-10-09 19:10:13
* @Description:  Evaluate Postfix Expression
*暴露的问题：1.考虑问题应全面，注意每种情况应如何处理。
+----------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
	ElementType v;
	char expr[Max_Expr];
	gets(expr);
	v = EvalPostfix( expr );
	if ( v < Infinity )
		printf("%f\n", v);
	else
		printf("ERROR\n");
	system("pause");

	return 0;
}

/* Your function will be put here */


ElementType EvalPostfix( char *expr ) {
	ElementType integer = 0.0, fraction = 0.0, factor = 0.1, sign = 1;
	int  flag = 0, count = 0;
	ElementType stack[Max_Expr];
	int curr = 0;
	while (expr) {
		if (*expr == '-' && expr + 1 && (*(expr + 1) >= '0' && *(expr + 1) <= '9')) {
			sign = -1;
			expr++;
		}
		else if (*expr >= '0' && *expr <= '9')
			integer = 10 * integer + (*expr++ - '0') ;
		else if (*expr == '.') {
			expr++;
			while (*expr != ' ') {
				fraction += (*expr++ - '0') * factor;
				factor /= 10;
			}
			factor = 0.1;
		}
		else if (*expr == ' ') {
			if (!flag) {
				count++;
				stack[curr++] = sign * (integer + fraction);
				integer = fraction = 0.0;
				sign = 1;
			}
			else
				flag = 0;
			expr++;
		}
		else {
			if (count == 0) {
				return sign * (integer + fraction);
			}
			if (curr < 2 && expr != 0) {
				return Infinity;
			}
			if (curr >= 2) {
				switch (*expr) {
				case '+' : stack[curr - 2] += stack[curr - 1] ; break;
				case '-' : stack[curr - 2] -= stack[curr - 1] ; break;
				case '*' : stack[curr - 2] *= stack[curr - 1] ; break;
				case '/' : if (stack[curr - 1] >= -1e-6 && stack[curr - 1] <= 1e-6)
						return Infinity ;
					else stack[curr - 2] /= stack[curr - 1];
					break;

				}
				curr--;
				expr++;
				flag = 1;

			}

			if (*expr == 0) {
				if (curr == 1)
					return stack[0];
				else {
					return Infinity;
				}
			}
		}
	}
}