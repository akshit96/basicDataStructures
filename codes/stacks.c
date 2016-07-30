// program to implement push and pop in stacks using singly linked list !!
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
struct node
{
	int data ;
	struct node* next ;
};
struct List
{
	int size ;
	struct node* topmost ;
};
typedef struct List myList ;
myList* list ;
void push(myList* list,int data)
{
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = data ;
	newnode->next = list->topmost ;
	list->topmost = newnode ;
	list->size++ ;
}
int top(myList* list)
{
	if(list->size == 0)
	{
		printf("the list is empty\n") ;
		return INT_MIN ;
	}
	else
	{
		return list->topmost->data ;
	}
}
void pop(myList* list)
{
	if(list->size == 0)
	{
		printf("the list is empty\n") ;
	}
	else
	{
		struct node* temp = list->topmost ;
		list->topmost = list->topmost->next ;
		temp->next = NULL ;
		printf("..poped.. %d\n",temp->data) ;
		free(temp) ;
		list->size-- ;
	}	
}
void initialize()
{
	list = (myList*)malloc(sizeof(myList)) ;
	list->size = 0 ;
	list->topmost = NULL ;
}
int main()
{
	initialize(); 
	int qt ;
	int n ;
	while(1)
	{
		scanf("%d",&qt) ;
		if(qt == -1)
			break ;

		if(qt == 0)
		{
			scanf("%d",&n) ;
			push(list,n) ;
		}
		else if(qt == 1)
		{
			pop(list) ;
		}
		else
		{
			printf("element at the top of the stack: %d\n",top(list)) ;
		}
	}
	printf("--- poping out of the stack ---\n") ;
	while(list->size != 0)
	{
		printf("%d ",top(list)) ;
		pop(list) ;
	}
	return 0;
}