//Akshit Chopra
/*sab-moh-maya*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
 
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)

typedef struct node
{
	char key[30] ;
	int ht ;
	struct node *lc , *rc ;
 
}node ;
 
typedef struct tree 
{
	node * root ;
}tree ;
int z_cnt = 0 ;
node* newnode(char *key)
{
	node* ret = (node*)malloc(sizeof (node) ) ;
	strcpy(ret->key , key) ;
	ret->lc = ret->rc = NULL ;
	ret->ht = 1 ;
	return ret ;
}
int getHeight(node* root)
{
	if(root == NULL)
		return 0 ;
	else
	{
		return (root->ht) ;
	}
}
int getBalance(node* root)
{
	if(root == NULL)
		return 0 ;
	int lft = getHeight(root->lc) ;
	int rgt = getHeight(root->rc) ;
	return (lft - rgt) ;
}
bool less(char *a,char *b)
{
	if(strcmp(a,b) < 0)
		return 1 ;
	else
		return  0 ;
}
bool isBalanced(node* root)
{
	int h_dif = (getHeight(root->lc)) - (getHeight(root->rc)) ;
	return((-1<=h_dif && h_dif<=1)) ;
}
node* rotateLeft(node* root)
{
	node* newroot = root->rc ;
	node* temp = newroot->lc ;
 
	newroot->lc = root ;
	root->rc = temp ;
 
	root->ht = max(getHeight(root->lc) , getHeight(root->rc)) + 1 ;
	newroot->ht = max(getHeight(newroot->lc) , getHeight(newroot->rc)) + 1 ;
 
	return newroot ;	
}
node* rotateRight(node* root)
{
	node* newroot = root->lc ;
	node* temp = newroot->rc ;
 
	newroot->rc = root ;
	root->lc = temp ;
 
	root->ht = max(getHeight(root->lc) , getHeight(root->rc)) + 1 ;
	newroot->ht = max(getHeight(newroot->lc) , getHeight(newroot->rc)) + 1 ;
 
	return newroot ;	
}
node* balancedTreeInsert(node* root , node* newnode)
{
	if(root == NULL)
	{
		return newnode ;
	}
	if(less(newnode->key,root->key))
	{
		root->lc = balancedTreeInsert(root->lc , newnode) ;
	}
	else
	{
		root->rc = balancedTreeInsert(root->rc , newnode) ;
	}
 
	root->ht = max(getHeight(root->lc) , getHeight(root->rc)) + 1 ;
 
	if(isBalanced(root))
		return root ;
 	z_cnt++ ;
	int balance = getBalance(root) ;
	node* ret = NULL ;
	if(balance > 1)
	{
		if(!less(newnode->key , root->lc->key))
		{
			root->lc = rotateLeft(root->lc) ;
		}
		ret = rotateRight(root) ;
	}
	if(balance < -1)
	{		
		if(less(newnode->key , root->rc->key))
		{
			root->rc = rotateRight(root->rc) ;
		}
		ret = rotateLeft(root) ;
	}
	return ret ;
}
void inOrder(node* root)
{
	if(root == NULL)
		return ;
	inOrder(root->lc) ;
	printf("%s %d %d\n" , root->key , root->ht , getBalance(root)) ;
	inOrder(root->rc) ;
}
void preOrder(node* root)
{
	if(root == NULL)
		return ;
	printf("%s %d %d\n" , root->key , root->ht , getBalance(root)) ;
	preOrder(root->lc) ;
	preOrder(root->rc) ;
}
void processData(tree* T)
{
	char s[30] ;
	int cnt = 0 ;
	while(scanf("%s\n",s) != EOF) 
	{
		node* temp = newnode(s) ;
		assert(temp != NULL);
		z_cnt = 0 ;
		T->root = balancedTreeInsert(T->root , temp) ;
		assert(z_cnt <= 1) ;
		cnt++;
	}
	assert(cnt > 0);	
}
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin);
	#endif
	tree* T = (tree*)malloc(sizeof(tree)) ;
	T->root = NULL ;
	processData(T);

	inOrder(T->root) ;
	preOrder(T->root) ;
	
	return 0;
}