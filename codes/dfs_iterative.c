/* implementation of dfs in C without recursion*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
 
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)

#define white 0 
#define gray 1
#define black 2

#define MAXNODES 1001
#define inf 2000000000

struct node ;
struct listnode ;
struct list ;
struct graph ;
typedef struct graph graph ;

struct stack ;
typedef struct stack stack ;
struct stacknode ;
typedef struct stacknode ;
struct stacknode
{
	struct node* thisnode ;
	struct stacknode* next ;
} ;
struct stacknode* newStackNode(struct node* newnode)
{
	struct stacknode* ret = (struct stacknode*)malloc(sizeof(struct stacknode)) ;
	stacknode->thisnode = newnode ;
	stacknode->next = NULL ;
}
struct stack
{
	struct stacknode* topnode ;
	struct stack* next ;	
	int sz ;
	bool isEmpty()
	{
		return (sz == 0) ;
	}
} ;
stack* newStack()
{
	stack* st = (stack*)malloc(sizeof(stack)) ;
	st->sz = 0 ;
	st->topnode = NULL ;
	st->next = NULL ;
}
void push(stack* st ,node* newnode)
{

	struct stacknode* temp = newStackNode(newnode) ;	
	temp->next = st->topnode ;
	st->topnode = temp ;
	st->sz += 1 ;
} 
node* pop(stack* st)
{
	if(sz == 0)
	{
		return NULL ;
	}
	node* ret = st->topnode->thisnode ;
	stacknode* temp = st->topnode ;
	free(temp) ;
	return ret ;
}
typedef struct node // of a graph
{
	struct node* parent ; // in traversal (pi)
	int idx ;	
	int color ;
	int d ;	
	int f ;		
}node ;

struct graph
{
	node* v[MAXNODES] ;
	int vertices ;
	struct list* adjlist[MAXNODES] ;
};

typedef struct listnode
{
	struct node* thisnode ;
	struct listnode* next ;
}listnode;

typedef struct list
{
	struct listnode* firstnode ;
	int sz ;	
}list ;

node* newnode(int idx)
{
	node* ret = (node*)malloc(sizeof(node)) ;
	ret->idx = idx ;
	ret->parent = NULL ;
	ret->d = 0 ;
	ret->f = 0 ;
	ret->color = white ;
	return ret ;
}
listnode* newListNode(node* thisnode)
{
	listnode* ret = (listnode*)malloc(sizeof(listnode)) ;
	ret->thisnode = thisnode ;
	ret->next = NULL ;
	return ret ;
}

void addInList(list* nodelist,node* thisnode)
{
	listnode* newnode = newListNode(thisnode) ;
	if(nodelist->firstnode == NULL)
	{
		nodelist->firstnode = newnode ;	
	}
	else
	{
		listnode* temp = nodelist->firstnode ;
		while(temp->next != NULL)
		{
			temp = temp->next ;
		}
		temp->next = newnode ;	
	}
	nodelist->sz += 1 ;
}
graph* newgraph(int vertices)
{
	graph* ret = (graph*)malloc(sizeof(graph)) ;
	int i ;
	for(i=1;i<=vertices;++i)
	{
		ret->v[i] = newnode(i) ;
		ret->adjlist[i] = (list*)malloc(sizeof(list)) ;
		ret->adjlist[i]->firstnode = NULL ;
		ret->adjlist[i]->sz = 0 ; 
	}
	ret->vertices = vertices ;
	return ret ;
}
int time ;
void dfs_search_iterative(graph* g ,node* u)
{
	stack* st = newStack() ;
	push(st , u) ;
	while(st->isEmpty() == false)
	{
		u->color = gray ;
		time += 1 ;
		u->d = time ;	
		node * s = pop(st) ;
		listnode* curnode ;
		for(curnode = g->adjlist[s->idx]->firstnode ; curnode != NULL  ; cur = cur->next)
		{
			node* v = curnode->thisnode ;
			if(v->color == white)
			{
				v->parent = s ;	
				push(st,v) ;
			}
		} 
		time = time +
		s->color = black ;
	}	
}
void dfs(graph* g)
{
	int i ;
	time = 0 ;	
	printf("----- dfs starts ----\n") ;	
	for(i=1;i<= g->vertices ;i++)
	{
		g->v[i]->color = white ;
		g->v[i]->d = g->v[i]->f = 0 ;		
	}	
	for(i=1;i<= g->vertices ; i++)
	{
		if(g->v[i]->color == white)
		{
			g->v[i]->parent = NULL ;			
			dfs_search_iterative(g , g->v[i]) ;
			printf("\n") ;
		}
	}
	printf("------dfs ends----\n") ;
}
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif
	int vertices = 0 ;
	scanf("%d",&vertices) ;
	graph* g = newgraph(vertices) ;
	int edges = 0 , i;
	scanf("%d",&edges) ;
	int v1 , v2 ;	
	for(i = 0 ; i < edges ; ++i)
	{		
		scanf("%d%d",&v1,&v2) ;			
		addInList(g->adjlist[v1] , g->v[v2]) ;// considering directed graph
	}
	dfs(g) ;
	
	return 0;
}
