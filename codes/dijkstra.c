/* implementation of dijkstra algorithm in c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAXNODES 1002 

#define max(a,b) ((a>b) ? a:b) 
#define min(a,b) ((a<b)?a:b)

#define white 0 
#define gray 1
#define black 2

struct node ;
typedef struct node node ;
struct heap ;
typedef struct heap heap ;
struct graph ;
typedef struct graph graph ;
struct list ;
typedef struct list list ;
struct edge ;
typedef struct edge edge ;

int leftChild(int k){ return (k<<1) ; }
int rightChild(int k) { return (k<<1|1) ; }
int parent(int k){return (k>>1) ; } 

struct graph
{
	node* v[MAXNODES] ;
	list* adjlist[MAXNODES] ;
	int vertices ;
};

struct node
{
	int idx ;
	int color , d , f ;
	node* parent ;
};

struct edge
{
	int wt ; // wt of the edge
	int v ; // final vertex 	
	edge* next ;
};

struct list
{
	edge* firstedge ;
	int sz ;
};

int pos[1002] ;

typedef struct heap
{
	node* v ;
}heap ;
heap* pq[1002] ;
int n;
node* newnode(int id)
{
	node* ret = (node*)malloc(sizeof(node)) ;
	ret->idx = id ;
	ret->d = ret->f = ret->color = 0 ;
	ret->parent = NULL ;
	return ret ;
}
graph* newgraph(int vertices)
{
	graph* g = (graph*)malloc(sizeof(graph)) ;
	g->vertices = vertices ;
	int i ;
	for(i=1;i<=vertices;i++)
	{	
		g->v[i] = newnode(i) ;
		g->adjlist[i] = (list*)malloc(sizeof(list)) ;
		g->adjlist[i]->firstedge = NULL ;
		g->adjlist[i]->sz = 0 ;
	}
	return g ;
}
bool less(int i,int j)
{
	if( (pq[i]->v->d) > (pq[j]->v->d)) 
	{
		return 1 ;
	} 
	return 0  ; // can take into account order of insertion here
}
void swap_pos(int i,int j)
{
	int temp = pos[i] ;
	pos[i] = pos[j] ;
	pos[j] = temp ;	
}
void swap(int i,int j)
{
	heap temp = *pq[i] ;
	*pq[i] = *pq[j] ;
	*pq[j] = temp ;
	swap_pos(pq[i]->v->idx,pq[j]->v->idx) ;
}
void swimUp(int k)
{
	while( (k > 1) &&  less(parent(k) , k) )
	{
		swap(parent(k) , k) ;
		k = parent(k) ;
	} 
}
void sinkDown(int k)
{
	while(leftChild(k) <= n)
	{
		int j = leftChild(k) ;
		if(j<n && less(j,j+1) )
		{
			j++ ;
		}
		if(!less(k,j))
			break ;
		swap(k,j) ;
		k = j ;
	}
}
void heap_insert(heap* z)
{
	pq[++n] = z  ;
	pos[z->v->idx] = n ;
	swimUp(n) ; 
}
node* heap_delete()
{
	node* ret = pq[1]->v ;
	swap(1,n) ;
	pq[n--] = NULL ;
	sinkDown(1) ;
	return ret ;
}
edge* newEdge(int y,int wt)
{
	edge* ret = (edge*)malloc(sizeof(edge)) ;
	ret->v = y ;
	ret->wt = wt ;
	return ret ;
}
void addEdge(graph* g,int x,int y,int wt)
{
	edge* edj = newEdge(y,wt) ;
	if(g->adjlist[x]->firstedge == NULL)
	{
		g->adjlist[x]->firstedge = edj ;
	}
	else
	{
		edge* curedge = g->adjlist[x]->firstedge ;
		while(curedge->next != NULL)
			curedge = curedge->next ;
		curedge->next = edj ;
	}
	g->adjlist[x]->sz += 1 ;
}
void initialize(graph* g,node* s)
{
	int i ;
	for(i=1; i<=(g->vertices) ; ++i)
	{
		g->v[i]->d = 99999 ;
		g->v[i]->parent = NULL ;		
	}
	s->d = 0 ;
}
void relax(node* u,node* v,int wt)
{
	if(v->d > (u->d + wt))
	{
		v->d = u->d + wt ;
		swimUp(pos[v->idx]) ;
		v->parent = u ;
	}
}
heap* newheapnode(node* x)
{
	heap* z = (heap*)malloc(sizeof(heap)) ;
	z->v = x ;
	return z ;	
}
void dijkstra(graph* g,node* s)
{
	initialize(g,s) ;
	int i ;
	for(i=1; i <= (g->vertices) ; ++i)
	{
		heap_insert(newheapnode(g->v[i])) ;
	}
	while(n != 0)
	{
		node* u = heap_delete() ;
		//printf("## poped from pq--> %d ,with d value= %d\n" , u->idx , u->d) ;
		int i ;
		edge* curedge = g->adjlist[u->idx]->firstedge ;
		for( ; curedge != NULL ; curedge = curedge->next)
		{
			if(g->v[curedge->v]->color == black)
				continue ;		
			relax(u,g->v[curedge->v],curedge->wt) ;
		}
		u->color = black ;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif
	int vertices ;
	scanf("%d",&vertices) ;
	graph* g = newgraph(vertices) ;
	int edges; 
	int source =  1  ;
	scanf("%d",&source) ;
	int i,j ;
	int x,y,w ;
	for(i=1;i<=vertices;i++)
	{
		scanf("%d%d",&x,&edges) ;
		for(j=1;j<=edges;j++)
		{
			scanf("%d%d",&y,&w);
			addEdge(g,x,y,w) ;
		}
	}
	dijkstra(g,g->v[source]) ;
	for(i=1 ; i<= vertices ; ++i)
	{
		printf("%d %d\n" , i , g->v[i]->d) ;
	}

	return 0;
}
