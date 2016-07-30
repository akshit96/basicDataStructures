#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b

struct node
{
	int i,r,c,p ;
	struct node *lc,*rc,*parent ;
};
typedef struct node node ;
struct tree
{
	node* root ;
} ;
typedef struct tree tree ;
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
void bstInsert(tree* T,node* new_node)
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
void inorder(node *root)
{
    // return ;
    if(root == NULL)
        return ;
    printf("### root = %d\n",root->i) ;
    if(root->lc != NULL)
    {
        printf("<---- lc of root = %d\n",root->lc->i) ;
    }
    else
    {
        printf("lc of root is NULL...\n") ;
    }
    if(root->rc != NULL)
    {
        printf("<---- rc of root = %d\n",root->rc->i) ;
    }
    else
    {
        printf("rc of root is NULL...\n") ;
    }

    inorder(root->lc) ;
    printf("pee ... %d " , root->i) ;
    if(root->rc != NULL)
    {
        printf(" next to pee %d\n",(root->rc)->i) ;
        
    }
    else
    {
        printf(" \n");
    }
    inorder(root->rc) ;
}
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif
	node* task[1002] ;
	int j = 0;
	int i=0,r,c,p ;

	while(~scanf("%d %d %d %d\n",&i,&r,&c,&p))
	{
		task[++j] = newnode(i,r,c,p) ;
	}
	
	int  n = j ;	

	Processor *processor = (Processor*)malloc(sizeof(Processor)) ;
	processor->currentTask = NULL ;
	
	tree* T = (tree* )malloc(sizeof(tree)) ;
	T->root = NULL ;
	
	j = 1 ;

	int max_time = task[n]->r ;
	int t = 1 ;
// 	for(t = 1 ; t <= n ;t++)
// 	{
// 		bstInsert(T,task[t]) ;
// 		printf("printing inordder..\n") ;
// 		inorder(T->root) ;
// 		printf("----\n");
// 	}
// 	printf("while poping...\n\n") ;
// 	for(t=1;t<=n;t++)
// 	{
// 		printf("printing inordder..\n") ;
// 		inorder(T->root) ;
// 		printf("----\n");
// 		treeDelete(T,task[t]) ;
// 	}
// 	return 0 ;
	while(true)
	{

// 		printf("t = %d\n" , t) ;
// 		printf("task currently on processor...\n");
// 		if(processor->currentTask == NULL)
// 		{
// 		    printf("# 0\n");
// 		}
// 		else
// 		{
// 		    printf("# %d\n",processor->currentTask->i) ;
// 		}
		if(t > max_time && processor->currentTask == NULL)
		{
			break ;
		}
		while(j <= n && (task[j]->r == t) )
		{
// 			printf("inserting ... task %d\n",task[j]->i) ;
			bstInsert(T,task[j]) ;
// 			printf("inorder after inserting.....\n") ;
// 			inorder(T->root);
// 			printf("\n");
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
				// printf("lite hi lelo tum\n");
				processor->currentTask = NULL ;
				// if(processor->currentTask == NULL)
				    // printf("all iz well\n");
			}
		}
		node* temp = treeMax(T->root) ;
		if(temp != NULL)
		{
    		if(processor->currentTask == NULL)
    		{
    		    processor->currentTask = temp ;
    		  //  printf("1 .allocating to the processor..task # %d\n",temp->i) ;
    		    treeDelete(T,temp) ;
    		    processor->currentTask->lc = processor->currentTask->rc = processor->currentTask->parent = NULL ;
    		}   
    		else
    		{
    		    if(temp->p > processor->currentTask->p)
    		    {
    		        bstInsert(T,processor->currentTask) ;
                    
    		        processor->currentTask = temp ;
    		        treeDelete(T,temp) ;
    		      //  printf("2 .allocating to the processor..task # %d\n",temp->i) ;
    		        processor->currentTask->lc = processor->currentTask->rc = processor->currentTask->rc = NULL ;
    		    }
    		}		    
		}

		t++ ;
	}
	printf("\n") ;
	return 0;
}
