#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b

int counter = 1 ;
typedef struct node
{
	int i,r,c,p ;
	struct node *lc,*rc,*parent ;
}node ;
typedef struct tree
{
	node* root ;
}tree ;
node* newnode(int i,int r,int c,int p)
{
	node* ret = (node*)malloc(sizeof(node)) ;
	ret->i = i ;
	ret->r = r ;
	ret->c = c ;
	ret->p = p ;
	ret->lc = ret->rc = ret->parent = NULL ;
	return ret ;
}
node* treeMax(node* x)
{
	node *temp = x ;
	if(temp == NULL)
		return NULL ;
	while(temp->rc != NULL)
	{
		temp = temp->rc ;
	}
	return temp ;
}
node* treeMin(node* x)
{
	node *temp = x ;
	if(temp == NULL)
		return NULL ;
	while(temp->lc != NULL)
	{
		temp = temp->lc ;
	}
	return temp ;
}
node* treeInsert(node* root,node* new_node)
{
	if(root == NULL || new_node == NULL)
	{
		return new_node; 
	}
	if(new_node->p < root->p)
	{
		root->lc = treeInsert(root->lc , new_node) ;
	}
	else
	{
		root->rc = treeInsert(root->rc , new_node) ; 
	}
	return root ;
}
node* treeDelete(node* root,node* z)
{
	if(root == NULL || z==NULL)
		return root ;
	if(z->p < root->p)
	{
		root->lc = treeDelete(root->lc , z) ;
	}
	else if(z->p > root->p)
	{
		root->rc = treeDelete(root->rc , z) ;
	}
	else
	{
		node* ret ;
		if(root->lc == NULL)
		{
			ret = root->rc ;
			return ret ;
		}
		else if(root->rc == NULL)
		{
			ret = root->lc ;
			return ret ;
		}
		else
		{
			ret = treeMin(root->rc) ;
			root->p = ret->p ;
			root->i = ret->i ;
			root->r = ret->r ;
			root->c = ret->c ;
			root->rc = treeDelete(root->rc , ret) ;
		}
	}
	return root ;
}
typedef struct Processor
{
	node* currentTask ;
}Processor ;
node* task[1002] ;
void printInput()
{
	int i = 0 ;
	while(task[++i] != NULL)
	{
		printf("%d %d %d %d\n",task[i]->i , task[i]->r , task[i]->c , task[i]->p) ;
	}
}
int main()
{
	// #ifndef ONLINE_JUDGE	
	// 	freopen("input_dsa.txt" , "r" , stdin) ;
	// #endif

	int j = 0;
	int i=0,r,c,p ;
	int max_time = 0 ;
	while(scanf("%d%d%d%d\n",&i,&r,&c,&p) != EOF)
	{		
		task[++j] = newnode(i,r,c,p) ;
		assert(c > 0) ;
	}
//	printInput() ;
//	return 0 ;
	
	int  n = j ;
	max_time = task[n]->r ;
	Processor *processor = (Processor*)malloc(sizeof(Processor)) ;
	processor->currentTask = NULL ;
	
	tree* T = (tree* )malloc(sizeof(tree)) ;
	T->root = NULL ;
	j = 1 ;
	int t = 1 ;
	int processed = 0 ;
	while(processed < n)
	{
	
		while(j <= n && task[j]->r == t)
		{
			T->root = treeInsert(T->root , task[j]) ;
			j++ ;
		}
		if(processor->currentTask == NULL)
		{
			printf("0\n") ;
		}
		else
		{
			printf("%d\n",processor->currentTask->i) ;
			processor->currentTask->c -= 1 ;
			if(processor->currentTask->c == 0)
			{
				processed += 1 ;
				processor->currentTask = NULL ;
			}
			
		}
		// printf("t = %d\n",t) ;

		if(processor->currentTask != NULL)
			T->root = treeInsert(T->root , processor->currentTask) ;

		node* newTask = treeMax(T->root) ;
		if(newTask != NULL)
		{
			T->root = treeDelete(T->root , newTask) ;
			newTask->lc = newTask->rc = NULL ;
		}
		// if(t > 4)
		// 	assert(0) ;	
		processor->currentTask = newTask ;

		t++ ;
	}
	return 0;
}
