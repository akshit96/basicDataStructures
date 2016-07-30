// binary tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
struct tree ;
typedef struct tree node ;
node
{
	int data ;
	node* parent; 
	node* left_child ;
	node* right_child ;
};
void inOrder(node* root)
{
	if(root == NULL)
		return ;
	inOrder(root->left_child) ;
	printf("%d " , root->data) ;
	inOrder(root->right_child) ;
}
void postOrder(node* root)
{
	if(root == NULL)
		return ;
	postOrder(root->left_child) ;
	postOrder(root->right_child) ;
	printf("%d ", root->data);
}
void preOrder(node* root)
{
	if(root == NULL)
		return ;
	printf("%d ",root->data) ;
	preOrder(root->left_child) ;
	preOrder(root->right_child) ;
}
int main()
{
	// node* root = (node* )malloc(sizeof(node)) ;

	return 0;
}
