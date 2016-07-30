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

struct node
{
	int idx ;
	int color ;
	int d , f ;
	int low ;
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
	ret->d = ret->f = ret->color = ret->low = 0 ;
	return ret ;
}
graph* newgraph(int vertices)
{
	graph* g = (graph*)malloc(sizeof(graph)) ;
	int i ;
	for(i=1 ; i<= vertices ; ++i)
	{
		g->v[i] = newnode(i) ;
		g->adjlist[i] = (list*)malloc(sizeof(list)) ;
		adjlist[i]->firstedge = NULL ;
		adjlist[i]->sz = 0;
	}
} 
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif

	return 0;
}
