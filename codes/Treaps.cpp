/*Implementation of treaps in cpp */
/* AKSHIT CHOPRA , BITS Pilani */
#include <bits/stdc++.h>
using namespace std ;

struct node
{
	int pr ;
	int key ;
	int sz ;
	int ht ;
	struct node* lc ;
	struct node* rc ;
	node()
	{
		lc = rc = NULL ;
	}
};
struct node* newNode(int k)
{
	struct node* ret = (struct node*)malloc(sizeof(struct node)) ;
	ret->key = k ;
	ret->pr = rand() ;
	ret->lc = ret->rc = NULL ;
	ret->ht = 1 ;
	return ret ;
}
int gt_h(struct node* t)
{
	if(t)
		return t->ht ;
	return 0 ;
}
void update_ht(struct node* t)
{
	if(t)
	{
		t->ht = max( gt_h(t->lc) , gt_h(t->rc)) + 1 ;
	}
}
int Sz(struct node* node)
{
	return (node == NULL)?0:node->sz ;
}
void update_sz(struct node* node)
{
	if(node != NULL)
		node->sz = Sz(node->lc) + Sz(node->rc) + 1 ;
}
void split(struct node* t ,int v,struct node** l ,struct node** r) // splits a treap node t , into two sepearte nodes l , r 
{
	if(t == NULL)
	{
		(*l) = (*r) = NULL ;
	}
	else if(t->key <= v)
	{
		split(t->rc , v , &(t->rc) , r);
		(*l) = t ;
	}
	else
	{
		split(t->lc , v , l , &(t->lc)) ;
		(*r) = t ;
	}
	update_sz(t) ;
	update_ht(t) ;
}
void merge(struct node** t , struct node* l , struct node* r) // merges two separate treap subtrees into one
{
	if(l==NULL || r==NULL)
	{
		(*t) = (l != NULL)?l:r ;
	}
	else if(l->pr > r->pr)
	{
		merge(&(l->rc),l->rc,r) ;
		(*t) = l ;
	}
	else
	{
		merge(&(r->lc) , l , r->lc) ;
		(*t) = r ;
	}
	update_sz(*t) ;
	update_ht(*t) ;
}
void insert(struct node** t ,struct node* newnode)
{
	if((*t) == NULL)
	{
		*t = newnode ;
	}
	else if(newnode->pr > (*t)->pr)
	{
		split(*t ,newnode->key , &( newnode->lc ),&(newnode->rc) ) ;
		*t = newnode ;
	}
	else
	{
		insert( ( ((*t)->key <= newnode->key) ? (&( (*t)->rc)): (&( (*t)->lc)) ), newnode) ;
	}
	update_sz(*t) ;
	update_ht(*t) ;
}
void erase(struct node** t,int key)
{
	if(*t == NULL)
		return ;
	else if((*t)->key == key)
	{
		struct node* tmp = *t ;
		merge(t,(*t)->lc , (*t)->rc) ;
		free(tmp) ;
	}
	else
	{
		erase( (*t)->key < key ? (&( (*t)->rc)) : (&((*t)->lc)) , key) ;
	}
	update_sz(*t) ;
	update_ht(*t) ;

}
void inOrder(struct node* root)
{
	if(root != NULL)
	{
		inOrder(root->lc) ;
		printf("%d %d\n" , root->key ,root->pr) ;
		inOrder(root->rc) ;
	}
}
void preOrder(struct node* root)
{
	if(root != NULL)
	{
		printf("%d %d\n" , root->key ,root->pr) ;
		preOrder(root->lc) ;
		preOrder(root->rc) ;
	}
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input_dsa.txt", "r", stdin);
    #endif
    struct node* t = NULL ;	
    struct node* x ;
    for(int i = 1 ; i <29 ; i++)
    {
    	x = newNode(1) ;
    	insert(&t,x) ;
    }
    inOrder(t) ;
    printf("\n\n") ;
    preOrder(t) ;
    printf("..%d..\n",t->ht) ;
	return 0 ;	
}