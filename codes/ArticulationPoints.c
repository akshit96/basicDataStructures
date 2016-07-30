/*Tarjan's Algorithm to find articulation points in an undirected graph*/
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
typedef struct edge
{
	struct node* v ; // ending vertex of edge	
	struct edge* next ;
}edge;
struct list 
{
	edge* firstedge ;
	int sz ;	
} ;
struct node
{
	int idx ;
	int color ;
	int d , f ;
	int low ;
	bool isAp ;
	struct node* parent ;
} ;

typedef struct graph
{
	int vertices ;
	node* v[MAXNODES] ;
	struct list* adjlist[MAXNODES] ; 
}graph;
void reset_graph(graph* g)
{
	int i ;
	for(i = 1 ; i <= (g->vertices) ; ++i)
	{
		g->v[i]->d = g->v[i]->f = g->v[i]->low = g->v[i]->color = 0 ;
		g->adjlist[i]->firstedge = NULL ;
		g->adjlist[i]->sz = 0 ;
		g->v[i]->isAp = false ;
		g->v[i]->parent = NULL ;
	}
}
node* newnode(int id)
{
	node* ret = (node*)malloc(sizeof(node)) ;
	ret->idx = id ;
	ret->color = white ;
	ret->d = ret->f = 0 ;
	ret->low = 0 ;
	ret->isAp = false ;
	ret->parent = NULL ;
	return ret ;
}
graph* newgraph(int vertices)
{
	graph* g = (graph*)malloc(sizeof(graph)) ;
	g->vertices = vertices ;
	int i ;
	for(i=1 ; i<=vertices ; ++i)
	{
		g->v[i] = newnode(i) ;
		g->adjlist[i] = (struct list*)malloc(sizeof(struct list)) ;
		g->adjlist[i]->firstedge = NULL ;
		g->adjlist[i]->sz = 0 ;
	}
	return g ;
}
struct edge* newEdge(node* z)
{
	edge* ret = (edge*)malloc(sizeof(edge)) ;
	ret->v = z ;
	ret->next = NULL ;
	return ret ;
}
void addEdge(graph* g , int s ,int  d)
{
	struct edge* curedge = newEdge(g->v[d]) ;
	assert(g->adjlist[s] != NULL );
	if(g->adjlist[s]->firstedge == NULL)
	{	
		g->adjlist[s]->firstedge = curedge ;
	}
	else
	{
		edge* temp = g->adjlist[s]->firstedge ;
		while(temp->next != NULL)
		{
			temp = temp->next ;
		}
		temp->next = curedge ;
	}
	g->adjlist[s]->sz += 1 ;
}
int timer = 0 ;
void dfs_visit(graph* g,node* s)
{
	timer++ ;
	s->d = timer ;
	s->low = timer ;
	s->color = gray ;
	int children = 0 ; // stores num of children of the node in dfs-tree 
	
	edge* edg = g->adjlist[s->idx]->firstedge ;
	for( ; edg != NULL ; edg = edg->next)
	{
		if(edg->v->color == white)
		{
			edg->v->parent = s ;

			children++ ;

			dfs_visit(g,edg->v) ;
			s->low = min(s->low , edg->v->low) ; // to show on behalf of descenders

			if(s->parent == NULL && children > 1) // if s is root of dfs tree and has more than 1 tree edges
			{
				s->isAp = true ;		
			} 
 // if any of the children doesn't have back edge then s will be an articulation point.
			else if(s->parent != NULL && ((edg->v->low) >= (s->d)) )
			{
				s->isAp = true ;
			}
		
		}
		else if(edg->v != s->parent) // low time = min discovery times of proper ancesstors
		{
			s->low = min(s->low , edg->v->d) ; // back-edge
		}
	}

	timer++ ;
	s->f = timer ;
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
void printAP(graph* g)
{
	int i ;
	printf("---printing articulation points of graph----\n") ;
	for(i=1 ;i<=(g->vertices) ; ++i)
	{
		if(g->v[i]->isAp == true)
		{
			printf("%d " , i) ;
		}
	}
	printf("\n") ;
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
	printAP(g) ;
	return 0;
}
