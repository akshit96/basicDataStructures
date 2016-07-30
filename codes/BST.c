// BST implementation in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b

struct node ;
typedef struct node node ;

struct tree ;
typedef struct tree tree ;

struct node
{
	int key , val ;
	node *lc,*rc,*parent ;
};
struct tree
{
	node* root ;
};

node* newnode(node* z)
{
	node* ret = (node*)malloc(sizeof(node)) ;
	*ret = *z ;
	ret->parent  = NULL ;
	ret->lc = ret->rc = NULL ;
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
	if(x == NULL || x->key == k)
		return x ;
	if(k < x->key)
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
node* predecessor(node *x)
{
	if(x->lc != NULL)
	{
		return (treeMax(x->lc)) ;
	}
	else
	{
		node* tmp = x->parent ;
		while(tmp != NULL && tmp->lc == x)
		{
			x = tmp ;
			tmp = x->parent ;
		}
	}
}
node* treeInsertRecursive(node* root,node* x)
{
	if(root == NULL)
		return newnode(x) ;
	if(root->key < x.key)
	{
		return (treeInsertRecursive(root->lc , x)) ;
	}
	else
	{
		return (treeInsertRecursive(root->rc , x)) ;
	}
}

void treeInsert(tree* T ,node* z)
{
	node* cur = T->root ;
	if(cur == NULL) // if the tree is empty
	{
		T->root = z ;
		return ;
	}
	node *p ;
	while(cur != NULL)
	{
		p = cur ;
		if(z->key < cur->key)
		{
			cur = cur->lc ;
		}
		else
		{
			cur = cur->rc ;
		}
	}
	z->parent = p ;
	if(z->key < p->key)
	{
		p->lc = z ;
	}
	else
	{
		p->rc = z ;
	}
	z->lc = z->rc = NULL ;
}
void transplant(tree* T ,node* u,node* v) // replaces Subtree rooted at u with subtree rooted at v
{
	if(u->parent == NULL)
	{
		T->root = v ;
	}
	else if(u->parent->lc == u)
	{
		u->parent->lc = v ;
	}
	else
	{
		u->parent->rc = v ;
	}
	if(v != NULL)
	{
		v->parent = u->parent ;
	}
}
void treeDelete(tree* T,node* z)
{
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
		node* y = successor(z) ; // surely have as it has a right sub tree 
		if(y->parent != z) // if successor is not right child then adjust tree so as to make it right child
		{
			transplant(T,y,y->rc) ;
			y->rc = z->rc ;
			y->rc->parent = y ;
		}
		transplant(T,z,y) ;
		y->lc = z->lc ;
		y->lc->parent = y ;
	}
}
int main()
{
	#ifdef LOCAL	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif


	return 0;
}
