/* implementation of bfs in C*/
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
struct qnode ;
struct qlist ;
struct list ;
struct graph ;
typedef struct graph graph ;

typedef struct node // of a graph
{
	struct node* parent ; // in traversal (pi)
	int idx ;	
	int color ;
	int d ;			
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

typedef struct qnode
{
	struct node* thisnode ;
	struct qnode*	next ;
}qnode ;

typedef struct qlist
{
	struct qnode* front ;
	struct qnode* rear ;
	int sz ;
}qlist ;

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
	ret->color = white ;
	return ret ;
}

qlist* newQlist()
{
	qlist* newqlist = (qlist*)malloc(sizeof(qlist)) ;
	newqlist->front = newqlist->rear = NULL ;
	newqlist->sz = 0 ;
	return newqlist ;
}

listnode* newListNode(node* thisnode)
{
	listnode* ret = (listnode*)malloc(sizeof(listnode)) ;
	ret->thisnode = thisnode ;
	ret->next = NULL ;
	return ret ;
}

qnode* newQnode(node* thisnode)
{
	qnode* ret = (qnode*)malloc(sizeof(qnode)) ;
	ret->next = NULL ;
	ret->thisnode = thisnode ;
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
void enque(qlist* que_list,node* newnode)
{
	qnode* new_qnode = newQnode(newnode) ;
	if(que_list->front == NULL && que_list->rear == NULL)
	{
		que_list->front = que_list->rear = new_qnode; 
	}
	else
	{
		que_list->rear->next = new_qnode ;
		que_list->rear = new_qnode ;
		new_qnode->next = NULL ; 
	}
	que_list->sz += 1 ;	
} 
qnode* deque(qlist* que_list)
{
	if(que_list->sz == 0)
	{
		printf("queue is empty\n") ;
		return NULL ;
	}
	qnode* temp ;	
	if(que_list->sz == 1)
	{
		temp = que_list->front ;
		que_list->front = que_list->rear = NULL ;
		temp->next = NULL ;		
		
	}
	else
	{
		temp = que_list->front ;
		que_list->front = que_list->front->next ;
		temp->next = NULL ;		
	}
	que_list->sz -= 1 ;
	return temp ;
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
bool empty(qlist* que_list)
{
	return (que_list->sz == 0) ;
}

void bfs(graph* g , node* source)
{
	int i ;
	for(i = 1 ; i <= (g->vertices) ; i++)
	{
		
		g->v[i]->parent = NULL ;
		g->v[i]->d = inf ;
		g->v[i]->color = white ;
	}	
	g->v[source->idx]->d = 0 ;
	qlist* que_list = newQlist() ;
	enque(que_list , source) ;
	//assert(0);	
	source->parent = NULL ;
	while(!empty(que_list))
	{
		qnode* topnode = deque(que_list) ;
		node* s = topnode->thisnode ;
		printf("%d ",s->idx) ;
		assert(s != NULL) ;
		list* nodelist = g->adjlist[s->idx] ;
		listnode* cur = nodelist->firstnode ;
		while(cur != NULL)
		{	
			node* curnode = cur->thisnode ;			
			if(curnode->color == white)
			{
				curnode->color = gray ;
				curnode->d = s->d + 1 ;
				curnode->parent = s ;
				enque(que_list , curnode) ;
			} 
			cur = cur->next ;
		}
		s->color = black ;								
	}
	printf("\n") ;
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
	bfs(g,g->v[1]) ;	
	return 0;
}
