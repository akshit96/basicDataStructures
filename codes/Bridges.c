/*code to find Bridges in an undirected graph*/
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

#define MAXNODES 1100

struct node ;
typedef struct node node ;
struct graph ;
typedef struct graph graph ;
struct list ;
typedef struct list list ;
struct edge ;
typedef struct edge edge ;

struct list
{
	edge* firstedge ;
	int sz ;
};

struct edge
{	
	node* v ;
	edge* next ;
};
edge* newEdge(node* n)
{
	edge* ret = (edge*)malloc(sizeof(edge)) ;
	ret->v = n ;
	ret->next = NULL ;
	return ret ;
}
struct node
{
	int idx ;
	int color ;
	int d , f ;
	int low ;
	struct node* parent ;
} ;

struct graph
{
	node* v[MAXNODES] ;
	list* adjlist[MAXNODES] ;
	int vertices ;		
};

node* newnode(int id)
{
	node* ret = (node*)malloc(sizeof(node)) ;
	ret->idx = id ;
	ret->parent = NULL ;
	ret->d = ret->f = ret->color = ret->low = 0 ;
	return ret ;
}
int timer = 0 ;
void dfs_visit(graph* g,node* s)
{
	s->d = ++timer ;
	s->low = s->d ;
	s->color = gray ;
	edge* curedge = g->adjlist[s->idx]->firstedge ;
	for( ; curedge != NULL ; curedge = curedge->next)
	{
		node* cur = curedge->v ;	
		if(cur->color == white)
		{
			cur->parent = s ;
			dfs_visit(g,cur) ;

			s->low = min(s->low , cur->low) ;
			if( (cur->low)  > (s->d) )	
			{
				printf("%d %d\n" , s->idx , cur->idx) ;
			}		
		}
		else if(cur != s->parent)
		{
			s->low = min(s->low , cur->d) ;
		}
	} 
	s->f = ++timer ;
	s->color = black ;
}
void dfs(graph* g)
{
	int i ;
	timer = 0 ;
	for(i=1; i<= (g->vertices) ; ++i)
	{
		if(g->v[i]->color == white)	
		{
			dfs_visit(g,g->v[i]) ;
		}
	}
}
graph* newgraph(int vertices)
{
	graph* g = (graph*)malloc(sizeof(graph)) ;
	int i ;
	g->vertices = vertices ;
	for(i=1 ; i<= vertices ; ++i)
	{
		g->v[i] = newnode(i) ;
		g->adjlist[i] = (list*)malloc(sizeof(list)) ;
		g->adjlist[i]->firstedge = NULL ;
		g->adjlist[i]->sz = 0;
	}
	return g ;
} 

void addEdge(graph* g , int i , int y)
{
	edge* temp = g->adjlist[i]->firstedge ;
	edge* edg = newEdge(g->v[y]) ;
	if(temp == NULL)
	{
		g->adjlist[i]->firstedge = edg ; 
	}
	else
	{
		while(temp->next != NULL)
			temp = temp->next ;
		
		temp->next = edg ;
	}
	g->adjlist[i]->sz +=1 ;
}	
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif
	int vertices ;
	scanf("%d",&vertices) ;
	int edges ;
	scanf("%d",&edges) ;
	int i ;
	graph* g = newgraph(vertices) ;
	int x,y ;

	for(i=1 ; i<= edges ; ++i)
	{
		scanf("%d%d",&x,&y) ;
		addEdge(g,x,y) ;
		addEdge(g,y,x) ;		
	}
	dfs(g) ;	
	
	return 0;
}
