#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

struct QUEUE ;
typedef struct QUEUE queue ;
struct TREE ;
typedef struct TREE tree ;
struct QLIST ;
typedef struct QLIST qlist ;

bool isOperand(char ch)
{
	return ('A'<=ch && ch<='Z') ;
}

bool evaluate_qbf(char* cnf,int* x,int* cnt)
{
	int len = strlen(cnf) ;
	int i,j ;
	int r = -1 ;
	int num_ch = 0 ;
	for(i=0;i<len;i++)
	{
		if(isOperand(cnf[i]))
		{
			if(cnt[cnf[i]-'A'+1] == 0)
			{
				num_ch++ ;
			}
			cnt[cnf[i]-'A'+1]++ ;
		}
	}
	bool val = 1 , prev_val = 1 ,cur_val = 0 ;
	// printf("%d\n",num_ch) ;
	// assert(0) ;
	for(i=0;i<len;i++)
	{
		if(cnf[i] == '(')
		{
			cur_val = 0 ;
			continue ;
		}
		else if(cnf[i] == ')')
		{
			prev_val = cur_val ;
			val &= prev_val ;
			if(!val)
				break ;
		}
		else if(cnf[i] == '+' || cnf[i] == '*')
		{
			continue ;
		}
		else if(cur_val == 1)
		{
			continue ;
		}
		else if(cnf[i] == '-')
		{
			i++ ;
			cur_val |= (!x[cnf[i]-'A'+1]) ;
		}
		else if(isOperand(cnf[i]))
		{
			cur_val |= (x[cnf[i]-'A'+1]) ;
		}
	}
	return val ;	
}
struct TREE
{
	tree* lc ;
	tree* rc;
	tree* parent ;
	int id ;
	bool isLeaf ;
	int level ;
	bool res ;
};
struct QUEUE
{
	queue* next ;
	tree* node ;
};
struct QLIST
{
	queue* front ;
	queue* rear ;
	int size ;
};

void push(qlist* list,tree* node)
{
	queue* newnode = (queue* )malloc(sizeof(queue)) ;
	newnode->node = node; 
	if(list->size == 0)
	{
		list->front = list->rear = newnode ;
		if(list->front == NULL)
		{
			printf("lol max\n") ;
		}
		newnode->next = NULL ;
	}
	else
	{
		list->rear->next = newnode ;
		list->rear = newnode ;
		newnode->next = NULL ;
	}
	list->size++ ;
}
tree* pop_back(qlist* list)
{
	if(list->size == 0)
	{
		printf("UNDERFLOW\n");
		return NULL;
	}
	if(list->size == 1)
	{
		queue* temp = list->rear ;
		list->size = 0 ;
		list->front = list->rear = NULL ;
		tree* ret = temp->node ;
		free(temp) ;
		return ret;
	}
	queue* temp = list->front ;
	queue* prev = temp ;
	while(temp->next != NULL)
	{
		prev = temp ;
		temp = temp->next ;
	}
	list->rear = prev ;
	prev->next = NULL ;
	list->size-- ;
	tree* ret = temp->node ;
	free(temp) ;
	return ret ;
}
tree* pop_front(qlist* list)
{
	if(list->size == 0)
	{
		printf("UNDERFLOW\n");
		return NULL;
	}
	if(list->size == 1)
	{
		queue* temp = list->front ;
		list->size = 0 ;
		list->front = list->rear = NULL ;
		tree* ret = temp->node ;
		free(temp) ;
		return ret;
	}	
	queue* temp = list->front ;
	list->front = list->front->next ;
	tree* ret = temp->node ;
	free(temp) ;
	list->size-- ;
	return ret ;
}
bool isEmpty(qlist* list)
{
	return (list->front == NULL && list->rear == NULL) ;
}
void work(tree* root,qlist* list,char* cnf,int* cnt,int k)
{

	// make the tree
	int level = 0 ;
	push(list,root) ;
	int total = 1<<(k+1);
	total-- ;
	int count = 1 ;
	while(count < total)
	{
		tree* newnode = pop_front(list) ;
		
		tree* lft = (tree* )malloc(sizeof(tree)) ;
		tree* rgt = (tree* )malloc(sizeof(tree)) ;
		lft->parent = rgt->parent = newnode ;
		newnode->lc = lft ;
		newnode->rc = rgt ;
		lft->lc = lft->rc = rgt->lc = rgt->rc = NULL ;
		lft->level = rgt->level = newnode->level + 1 ;
		lft->res = rgt->res = 0 ;
		push(list,lft) ;
		push(list,rgt) ;
		count += 2 ;
	}
	queue* temp = list->front ;
	// printf("..size of the list is .. %d\n",list->size) ;
	int assign = 0 ;
	// printf("count = %d .. total = %d\n",count,total) ;
	if(list->front == NULL)
	{
		printf("debug more..\n") ;
	}
	while(temp != NULL)
	{
		// printf("assigner = %d\n",assign) ;
		temp->node->id = assign++ ;
		// printf("wtf..\n") ;
		temp->node->isLeaf = 1 ;
		temp = temp->next ;
	}
	// assign the values to the leaves

	int x[27] ;
	// int cnt[27] ;
	int i ;


	temp = list->front ;
		
	while(temp != NULL)
	{
		tree* cur = temp->node ;
		int v = cur->id ;
		int j = k ;
		for(i=1;i<=26;i++)
			x[i] = 0 ;
		while(v)
		{
			x[j--] = v&1 ;
			v >>= 1 ;
		}
		cur->res = evaluate_qbf(cnf,x,cnt) ;
		// printf("...## %d\n",cur->res) ;
		temp = temp->next ;
	}

	//pushup the values using reverse level order traversal 
	while(!isEmpty(list))
	{
		// printf("hello...\n") ;
		tree* cur = pop_front(list) ;
		// tree* cur = temp->node ;
		if(cur == root)
		{
			cur->res = (cur->lc->res)|(cur->rc->res) ;
			assert(list->size == 0 ) ;
			continue ;
		}
		// if(cur->parent->lc == cur)
		// {
		// 	continue ;
		// }
		// assert(cur->parent->rc == cur) ;
		if(cur->parent->lc != cur && cur->isLeaf == 1)
		{
			push(list,cur->parent) ;
			// printf("...pushing..parent whose level is .. %d\n",cur->parent->level) ;
			continue ;
		}
		if(cur->isLeaf==1 && cur->parent->lc == cur)
		{
			continue ;
		}
		// printf("merging at level .. %d\n",cur->level) ;
		if( (cur->level)&1)
		{
			// printf("");
			cur->res = (cur->lc->res)&(cur->rc->res) ;
		}
		else 
		{
			cur->res = (cur->lc->res)|(cur->rc->res) ;
		}
		if(cur->parent->lc != cur)
			push(list,cur->parent) ;
		// printf("..cur->res = %d\n",cur->res) ;
	}
	// printf("...final ev.. %d\n",root->res) ;
}
void print_preorder(tree* root)
{
	if(root == NULL)
		return ;
	printf("%d",root->res) ;
	print_preorder(root->lc) ;
	print_preorder(root->rc) ;
}
int main()
{
	int x[27] ;
	char cnf[500] ;
	int cnt[27]  ;

	scanf("%s",cnf) ;
	

	tree* root = (tree* )malloc(sizeof(tree)) ;
	root->lc = root->rc = root->parent = NULL ;
	root->id = -1 ;
	root->isLeaf = 0 ;
	root->level = 0 ;
	root->res = 0 ;


	qlist* list = (qlist* )malloc(sizeof(qlist)) ;
	list->front = list->rear = NULL ;
	list->size = 0 ;

	int num_ch = 0 ;
	int len = strlen(cnf) ;
	int i;
	for(i=1;i<=26;i++)
		cnt[i] = 0 ;
	for(i=0;i<len;i++)
	{
		if(isOperand(cnf[i]))
		{
			if(cnt[cnf[i]-'A'+1] == 0)
			{
				num_ch++ ;
			}
			cnt[cnf[i]-'A'+1]++ ;
		}
	}
	work(root,list,cnf,cnt,num_ch) ;
	print_preorder(root) ;
	printf("\n") ;
	return 0;
}
