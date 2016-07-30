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

typedef struct node // of a graph
{
	struct node* parent ; // in traversal (pi)
	int idx ;	
	int color ;
	int d ;	
	int f ;		
	char label ;
}node ;
typedef struct edge 
{
	char label ;
	node* v ;
}edge ;
edge* newEdge(char label , node* x)
{
	edge* ret = (edge*)malloc(sizeof(edge)) ;
	ret->label = label ;
	ret->v = x ;
	return ret ;
}
struct graph
{
	node* v[MAXNODES] ;
	int vertices ;
	struct list* adjlist[MAXNODES] ;
};

typedef struct listnode
{
	struct edge* thisnode ;
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
	ret->label = '\0' ;
	return ret ;
}
listnode* newListNode(edge* thisnode)
{
	listnode* ret = (listnode*)malloc(sizeof(listnode)) ;
	ret->thisnode = thisnode ;
	ret->next = NULL ;
	return ret ;
}

void addInList(list* nodelist,edge* thisnode)
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
bool search(graph* g,node* cur, char *str , int pos , int len)
{
	if(pos == len)
	{
		if(cur->label == '1')
		{
			return true ;	
		}
		else
		{
			return false ;
		}
	}
	listnode* it ;
	
	for(it = g->adjlist[cur->idx]->firstnode ; it != NULL ; it = it->next)
	{	
		if(it->thisnode->label == str[pos])	
		{
			if ( search(g,it->thisnode->v,str,pos+1,len)  == true) 
				return true ;
		} 
	}
	return false ;		
}
char ret[1002] ;
char* toString(int num,int digits)
{	
	int pos = digits - 1 ;
	ret[digits] = '\0' ;
	int i ;
	for(i=0 ;i<digits;i++)
	{
		ret[i] = '0' ;
	}
	while(num)
	{
		assert(pos >= 0) ;
		ret[pos--] = (char)( (num%2) + '0') ; 
		num /= 2 ;
	}
	return ret ;
}
int main()
{
	#ifndef ONLINE_JUDGE	
		freopen("input_dsa.txt" , "r" , stdin) ;
	#endif
	int vertices = 0 ;
	scanf("%d",&vertices) ;
	graph* g = newgraph(vertices) ;
	//processs input	

	int counter = 0 ;
	int digits = 0 ;
	char str[1000] ;
	int i , j , e;	
	int id ;
	int ch ;
	for(i=1 ; i<=vertices ; ++i)
	{
		scanf("%d%d%d" , &id , &ch,&e) ;
		g->v[id]->label = (char)(ch + '0') ;
		for(j = 1 ; j <= e ; ++j)
		{
			int vert ;
			scanf("%d%d" , &ch , &vert) ;
			edge* cur = newEdge( (ch + '0') , g->v[vert]) ;
			addInList(g->adjlist[id] , cur) ;
		} 		
	}
	while(counter < 10)
	{
		for(i=0 ; i< (1<<digits) ; ++i)	
		{
			strcpy(str, (toString(i,digits)) ) ;
			
			if(search(g,g->v[1],str,0,digits) == true)
			{
				if(str[0] == '\0')
				{
					str[0] = 'e' ;
					str[1] = '\0' ;
				}
				printf("%s\n",str) ;
				counter += 1; 
			}		
			if(counter == 10)
				break ;
		}
		digits += 1 ;		
	}
	assert(counter == 10) ;
	return 0;
}
