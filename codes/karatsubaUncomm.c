#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) a>b?a:b 
#define min(a,b) a<b?a:b

struct queue ;
typedef struct queue Q ;
struct node ;
typedef struct node node ;
struct qlist ;
typedef struct qlist qlist ;
struct stack ;

typedef struct stack stack ;
struct slist ;
typedef struct slist slist ;
struct stack
{
	node* data ;
	stack* next ;
};
struct slist
{
	stack *topmost ;
	int size ;
};
void push(slist *list,node *data)
{
	stack *newnode = (stack*)malloc(sizeof(stack)) ;
	newnode->data = data ;
	newnode->next = list->topmost ;
	list->topmost = newnode ;
	list->size++ ;
}
node* top(slist *list)
{
	return (list->topmost->data) ;
}
node* pop(slist *list)
{
	assert(list->size > 0) ;
	node *ret = top(list) ;
	stack *temp = list->topmost ;
	list->topmost = list->topmost->next ;
	free(temp) ;
	list->size-- ;
	return ret ;
}
struct node
{
	int d1,d2,n ;
	int ans ;
	node *A,*B,*C ;
	node* parent ;
};
struct queue
{
	node *data ;
	Q* next ;
};
struct qlist
{
	Q *front ;
	Q *rear ;
	int size ;
};
void enque(qlist* list , node* v)
{
	if(v == NULL)
		return ;
	Q* newnode = (Q*)malloc(sizeof(Q)) ;
	newnode->data = v ;
	newnode->next = NULL ;
	if(list->front == NULL && list->rear == NULL)
	{
		list->front = list->rear = newnode ;
	}
	else
	{
		list->rear->next = newnode ;
		list->rear = newnode ;
	}
	list->size++ ;
	queue* temp = list->front ;
}
node* peekFront(qlist *list)
{
	return (list->front->data) ;
}
node* deque(qlist *list)
{
	if(list->size == 0)
	{
		printf("underflow\n");
		assert(0) ; 
	}
	node* ret = peekFront(list) ;
	Q *temp = list->front ;
	if(list->size == 1)
	{
		list->front = list->rear = NULL ;
	}	
	else
	{
		list->front = list->front->next ;
	}
	list->size-- ;
	free(temp) ;
	return ret ;
}

int countDigits(int n)
{
	int ret = 0 ;
	while(n != 0)
	{
		n /= 10;
		ret++ ;
	}
	return ret ;
}
bool isLeaf(node *cur)
{
	return (countDigits(max(cur->d1,cur->d2)) <= 1 ) ;
}
int p10[6] = {1,10,100,1000,10000,100000} ;
char x ;
void makeTree(qlist *Qlist,slist* Slist, node *root)
{
	enque(Qlist,root) ;
	while(Qlist->size != 0)
	{
		node* cur = deque(Qlist) ;
		cur->ans = 0 ;
		if(isLeaf(cur))
		{
			push(Slist,cur) ;
			continue ;
		}
		node* A = (node*)malloc(sizeof(node)) ;
		node* B = (node*)malloc(sizeof(node)) ;
		node* C = (node*)malloc(sizeof(node)) ;
		A->parent = B->parent = C->parent = cur ;
		A->A = A->B = A->C = B->A = B->B = B->C = C->A = C->B = C->C = NULL ;
		cur->A = A ;
		cur->B = B ;
		cur->C = C ;
		cur->ans = 0 ;
		int maxDigs = countDigits(max(cur->d1,cur->d2)) ;
		int n = (maxDigs + 1)>>1 ;
		cur->n = n ;
		int d1 = cur->d1 ;
		int d2 = cur->d2 ;
		int h1 = d1/p10[n] ;
		int l1 = d1%p10[n] ;
		int h2 = d2/p10[n] ;
		int l2 = d2%p10[n] ;
		A->d1 = h1 + l1 ;
		A->d2 = h2 + l2 ;
		B->d1 = h1 ;
		B->d2 = h2 ;
		C->d1 = l1 ;
		C->d2 = l2 ;
		enque(Qlist,A) ;
		enque(Qlist,B) ;
		enque(Qlist,C) ;
	}
}
void work(node *root ,qlist* Qlist, slist* Slist)
{
	if(isLeaf(root))
	{
		root->ans = (root->d1)*(root->d2) ;
		printf("%dX%d=%d\n",root->d1,root->d2,root->ans) ;
		return ;
	}
	while(Slist->size != 0)
	{
		enque(Qlist,pop(Slist)) ;
	}
	while(Qlist->size != 0)
	{
		node *cur = deque(Qlist) ;
		node *temp = cur ;

		bool f = 0 ;
		if(cur == root)
		{
			int a = cur->A->ans ;
			int b = cur->B->ans ;
			int c = cur->C->ans ;
			cur->ans = b*p10[cur->n]*p10[cur->n] + (a-b-c)*p10[cur->n] + c ;
			printf("%dX%d=%dX%dX%d+(%d-%d-%d)X%d+%d=%d\n",cur->d1,cur->d2,b,p10[cur->n],p10[cur->n],a,b,c,p10[cur->n],c,cur->ans);
			continue ;			
		}

		if(cur->parent->A == cur)
		{			
			enque(Qlist,cur->parent) ;
		}
		if(isLeaf(cur))
		{
			cur->ans = (cur->d1)*(cur->d2) ;
			printf("%dX%d=%d\n",cur->d1,cur->d2,cur->ans) ;
		}
		else
		{

			int a = cur->A->ans ;
			int b = cur->B->ans ;
			int c = cur->C->ans ;

			cur->ans = b*p10[cur->n]*p10[cur->n] + (a-b-c)*p10[cur->n] + c ;
			printf("%dX%d=%dX%dX%d+(%d-%d-%d)X%d+%d=%d\n",cur->d1,cur->d2,b,p10[cur->n],p10[cur->n],a,b,c,p10[cur->n],c,cur->ans);

		}
	}
}
int main()
{
	freopen("input_dsa.txt" , "r" , stdin) ;
	freopen("output_dsa.txt" , "w" , stdout) ;
	char s[20] ;
	scanf("%s",s) ;
	int d1,d2 ;
	sscanf(s,"%d%c%d",&d1,&x,&d2) ;
	
	node *root = (node*)malloc(sizeof(node)) ;
	root->d1 = d1 ;
	root->d2 = d2 ;
	root->parent = NULL ;
	root->A = root->B = root->C = NULL ;
	root->ans = 0 ;

	qlist* Qlist = (qlist *)malloc(sizeof(qlist)) ;
	Qlist->size = 0 ;
	Qlist->front = Qlist->rear = NULL ;

	slist* Slist =(slist*)malloc(sizeof(slist)); 
	Slist->topmost = NULL ;
	Slist->size = 0 ;

	makeTree(Qlist,Slist,root) ;
	work(root,Qlist,Slist) ;
	
	return 0;
}
