/* implementation of kosaraju algorithm for finding SCC's in C*/
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
	st->topnode = st->topnode->next ;
	st->sz -= 1 ; 
	free(temp) ;
	return ret ;
}


struct node ;
struct listnode ;
struct list ;
struct graph ;
typedef struct graph graph ;

typedef struct node // of a graph
{
	struct node* parent ; // in traversal (pi)
	int idx ;	
	int color ;
	int d ;	
	int f ;	
	int num_of_components ;
	int scc[MAXNODES] ; // component number 	
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
int cnt ;
void dfs_search(graph* g ,node* u , stack* st)
{
	time += 1 ;
	u->d = time ;
	u->color = gray ;
	printf("%d " , u->idx) ;
	listnode* curnode ;
	
	for(curnode = g->adjlist[u->idx]->firstnode ; curnode != NULL ; curnode = curnode->next)
	{
		node* v = curnode->thisnode ;		
		if(v->color == white)
		{
			v->parent = u ;			
			dfs_search(g,v) ;
		}
	}
	push(st,u) ;
	time += 1 ;
	u->f = 	time ;
	u->color = black ;
}
void dfs2()
void dfs(graph* g,stack* st)
{
	int i ;
	time = 0 ;	
	//printf("----- dfs starts ----\n") ;	
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
			dfs_search(g , g->v[i] , st) ;
			printf("\n") ;
		}
	}
	//printf("------dfs ends----\n") ;
}
graph* transpose(graph* g)
{
	graph* gt = newgraph(g->vertices) ;
	int i ;
	for(i = 1 ; i<= (g->vertices) ; ++i)
	{
		listnode* curnode ;
		for(curnode = g->adjlist[i]->firstnode ; curnode != NULL ; curnode = curnode->next)
		{
			addInList(gt->adjlist[curnode->thisnode->idx] , gt->v[i]) ;
		}
	}
	return gt ;
}
void rePaint(graph* g)
{
	for(i=1;i<=(g->vertices) ;i++)
	{
		g->v[i]->color = white ;
	}
}
void kosaraju(graph* g)
{
	stack* st = newStack(); 
	dfs(g,st) ;
	graph* gt = transpose(g) ;
	cnt = 0 ; 	// global cnt
	while(st->isEmpty() == false)
	{
		node* cur = pop(st) ;
		node* src = gt->v[cur->idx] ;		
		if(cur->color == white)
		{
			cnt += 1 ;
			dfs_search(gt,
		}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif
	int vertices = 0 ;
	scanf("%d",&vertices) ;
	graph* g = newgraph(vertices) ;
	graph* gt = newgraph(vertices) ; // TRANSPOSE GRAPH
	int edges = 0 , i;
	scanf("%d",&edges) ;
	int v1 , v2 ;	
	for(i = 0 ; i < edges ; ++i)
	{		
		scanf("%d%d",&v1,&v2) ;			
		addInList(g->adjlist[v1] , g->v[v2]) ;// considering directed graph
		// MAKING TRANSPOSE GRAPH
		addInList(gt->adjlist[v2] , g->v[v1]) ;
	}	
	kosaraju(g) ;
	return 0;
}
