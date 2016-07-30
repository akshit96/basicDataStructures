//sab moh maya
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b

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
node* treeSearch(node* x,int k)
{
	if(x == NULL || x->p == k)
		return x ;
	if(k < x->p)
		return (treeSearch(x->lc , k)) ;
	else
		return (treeSearch(x->rc , k)) ;
}
node* successor(node* x)// next node that appears in the inorder traversal of BST
{
	if(x == NULL)
		return x ;
	if(x->rc != NULL) // if x has right sub tree
	{
		return (treeMin(x->rc)) ;
	}
	else // visualize inorder traversal and get the idea (if x doesnt have a right subtree )
	{
		node* temp = x->parent ;
		while(temp != NULL && temp->rc == x)
		{
			x = temp ;
			temp = temp->parent ;
		}
		return temp ;
	}
}
void treeInsert(tree* T,node* new_node)
{
	if(T->root == NULL) // empty tree
	{
		T->root = new_node ;
		return ;
	}
	node* cur = T->root ;
	node* par = NULL;
	while(cur != NULL)
	{
		par = cur ;
		if(new_node->p < cur->p)
		{
			cur = cur->lc ;
		}
		else
		{
			cur = cur->rc ;
		}
	}
	
	if(new_node->p < par->p)
	{
		par->lc = new_node ;
		new_node->parent = par ;
	}
	else
	{
		par->rc = new_node ;
		new_node->parent = par ;
	}
}
void transplant(tree* T ,node* u,node* v) // replaces Subtree rooted at u with subtree rooted at v
{
	if(u->parent == NULL)
	{
		T->root = v ;
	}
	else if( (u->parent)->lc == u)
	{
		(u->parent)->lc = v ;
	}
	else
	{
		(u->parent)->rc = v ;
	}
	if(v != NULL)
	{
		v->parent = u->parent ;
	}
}
void treeDelete(tree* T,node* z)
{
    if(z == NULL)
        return ;
	node* root = T->root ;
	if(z->lc == NULL)
	{
		transplant(T,z,z->rc) ;
	}
	else if(z->rc == NULL)
	{
		transplant(T,z,z->lc) ;
	}
	else // z has 2 children
	{
		node* y = successor(z) ; // surely have it as treemin(z->rc) as it has a right sub tree 
		if(y->parent != z) // if successor is not right child then adjust tree so as to make it right child
		{
			transplant(T,y,y->rc) ;
			y->rc = z->rc ;
			(y->rc)->parent = y ;
		}
		transplant(T,z,y) ;
		y->lc = z->lc ;
		(y->lc)->parent = y ;
	}
}
typedef struct Processor
{
	node* currentTask ;
}Processor ;
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif
	node* task[1002] ;
	int j = 0;
	int i=0,r,c,p ;
	
	tree* T = (tree* )malloc(sizeof(tree)) ;
	T->root = NULL ;
	while(~scanf("%d%d%d%d\n",&i,&r,&c,&p))
	{
		task[++j] = newnode(i,r,c,p) ;
		if(r == 0)
		{
			treeInsert(T,task[j]) ;
		}
	}
	
	int  n = j ;	

	Processor *processor = (Processor*)malloc(sizeof(Processor)) ;
	processor->currentTask = treeMax(T->root) ;
	treeDelete(T,processor->currentTask) ;
	processor->currentTask->lc = processor->currentTask->rc = processor->currentTask->parent = NULL ;
	
	j = 1 ;

	int max_time = task[n]->r ;
	int t = 1 ;
	while(t <= max_time || processor->currentTask != NULL)
	{
		while(j <= n && (task[j]->r == t) )
		{
			treeInsert(T,task[j]) ;
			j++ ;
		}

		if(processor->currentTask == NULL)
		{
			printf("0 ") ;
		}
		else
		{
			printf("%d ",processor->currentTask->i) ;
			processor->currentTask->c -= 1 ;
			if(processor->currentTask->c == 0)
			{
				processor->currentTask = NULL ;
			}
		}
		node* temp = treeMax(T->root) ;
		if(temp != NULL)
		{
	    		if(processor->currentTask == NULL)
	    		{
	    		    processor->currentTask = temp ;
	    		    treeDelete(T,temp) ;
	    		    processor->currentTask->lc = processor->currentTask->rc = processor->currentTask->parent = NULL ;
	    		}   
	    		else
	    		{
	    		    if(temp->p > processor->currentTask->p)
	    		    {
	    		        treeInsert(T,processor->currentTask) ;
		            
	    		        processor->currentTask = temp ;
	    		        treeDelete(T,temp) ;
	    		        processor->currentTask->lc = processor->currentTask->rc = processor->currentTask->parent = NULL ;
	    		    }
	    		}		    
		}
		t++ ;
	}
	printf("\n") ;
	return 0;
}
