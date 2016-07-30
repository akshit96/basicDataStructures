#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
struct Stack ;
typedef struct Stack stack ;
struct Stack
{
	char val ;
	int reg ;
	stack* next ;
};
struct Header
{
	stack* topmost ;
	int size ;
};
typedef struct Header header ;
stack* top(header* head)
{
	return head->topmost ;
}
void push(header* head,char v,int r)
{
	stack* newnode = (stack*)malloc(sizeof(stack)) ;
	newnode->val = v ;
	newnode->reg = r ;
	newnode->next = head->topmost ;
	head->topmost = newnode ;
	head->size++ ;
}
void pop(header* head)
{
	if(head == NULL)
	{
		printf("stack is empty...\n") ;
		return ;
	}
	stack* temp_node = head->topmost ;
	head->topmost = head->topmost->next ;
	char ret = temp_node->val ;
	head->size-- ;
	free(temp_node) ;
}
bool isEmpty(header* head)
{
	return (head->size == 0) ;
}
bool isOperand(char ch)
{
	return (('a'<=ch && ch<='z')||('A'<=ch && ch<='Z'));
}
bool isOperator(char ch)
{
	return (ch=='+' || ch=='-' || ch=='*' || ch=='/') ;
}
int precedence(char op)
{
	if(op == '+' || op=='-')
	{
		return 1 ;
	}
	else if(op == '*' || op=='/') 
	{
		return 2 ;
	}
	return -1 ;
}

void infix_to_postfix(char* infix,char* postfix,header* head)
{
	int i,len ;
	len = strlen(infix) ;
	int j = 0 ;
	for(i=0;i<len;i++)
	{
		// printf("handling... %c\n",infix[i]) ;
		if(isOperand(infix[i]))
		{
			postfix[j++] = infix[i] ;
		}
		else if(infix[i] == '(')
		{
			push(head,'(',0) ;
		}
		else if(infix[i] == ')')
		{
			while(!isEmpty(head) && (top(head)->val) != '(')
			{
				stack* topnode = top(head) ;
				postfix[j++] = topnode->val ;
				pop(head); 
			}
			pop(head) ; // pop the corresponding '('
		}
		else // operator case
		{

			while(!isEmpty(head) && precedence(infix[i]) <= precedence(( top(head))->val ))
			{	
				stack* topnode = top(head) ;
				postfix[j++] = topnode->val ;
				pop(head) ;
			}
			
			push(head,infix[i],0) ;
		}
	}
	while(!isEmpty(head))
	{
		stack* topnode = top(head) ;
		postfix[j++] = topnode->val ;
		pop(head) ;
	}
	postfix[j] = '\0' ;
}
void getInstr(char* infix,char* postfix,header* head)
{
	int i,j ;
	int len = strlen(postfix) ;
	int r = 1 ;
	i = 0 ;
	for(i=0;i<len;i++)
	{
		while(isOperand(postfix[i]) )
		{
			push(head,postfix[i],0) ;
			i++ ;		
		}
		// operator encountered
		// pop the last two elements in the stack
		stack* n1 = head->topmost ;
		int r1 = n1->reg ;char c1 = n1->val ;
		pop(head);
		stack* n2 = head->topmost ;
		int r2 = n2->reg ; char c2 = n2->val ;
		pop(head);
		char op = postfix[i] ;
		if(r2 != 0)
		{
			printf("LD TEMP%d\n",r2) ;
		}
		else
		{
			printf("LD %c\n",c2) ;
		}
		if(op == '+')
			printf("AD ") ;
		else if(op == '-')
			printf("SB ") ;
		else if(op == '*')
			printf("ML ") ;
		else if(op == '/')
			printf("DV ") ;

		if(r1 != 0)
		{
			printf("TEMP%d\n",r1) ;
		}
		else
		{
			printf("%c\n",c1) ;
		}
		printf("ST TEMP%d\n",r) ;
		push(head,'\0',r) ;
		r++ ;
	}

}
int main()
{
	char infix[109] ;
	char postfix[109] ;
	header* head = (header*)malloc(sizeof(header)) ;
	head->topmost = NULL ;
	head->size = 0 ;	
	scanf("%s",infix) ;
	int f = 0 ;char ch ;
	int i ;
	int len = strlen(infix) ;
	for(i=0;i<len;i++)
	{
		if(isOperator(infix[i]))
		{
			f = 1 ;
			break ;
		}
		else if(isOperand(infix[i]))
		{
			ch = infix[i] ;
		}

	}
	if(f == 0)
	{
		printf("%c\n",ch) ;
	}
	else
	{
		infix_to_postfix(infix,postfix,head) ;
		printf("%s\n",postfix);
		getInstr(infix,postfix,head);		
	}

	return 0;
}