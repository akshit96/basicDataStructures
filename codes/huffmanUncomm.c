// heap && heap sort && huffman_Coding
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
int cnt = 0 ;
int idx(char ch){return ( ('A'<=ch && ch<='Z')?(ch-'A'+1):(ch-'a'+26) ) ;}
struct Key ;
typedef struct Key Key ;
struct Key
{
	int frq ;
	char data;
	Key *lc,*rc ;
	int order ;
};
char code[256][10] ;
int arr[10] ;
Key *pq[1002] ;
int n ;
char s[1005] ;
int freq[256] = {0};
int parent(int k){return (k>>1) ;}
int leftChild(int k){return (k<<1);}
int rightChild(int k){return (k<<1|1) ;}
void swap(Key *a,Key *b)
{
	Key temp = *a ;
	*a = *b ;
	*b = temp ;
}
bool less(int i,int j)// logic for comparision of keys, (>) for min-heap
{
	if(pq[i]->frq > pq[j]->frq)
	{
	 	return 1 ;
	}
	else if(pq[i]->frq == pq[j]->frq)
	{
		if(pq[i]->order < pq[j]->order)
			return 0 ;
		else
			return 1 ;
	}
	else
	{
	 	return 0 ;
	}
}
void swimUp(int k)
{
	while(k>1 && less(parent(k) , k))
	{
		swap(pq[k],pq[parent(k)]) ;
		k >>= 1 ;
	}
}
void insert(Key *key)
{
	pq[++n] = key ;
	swimUp(n) ;
}
void sinkDown(int k)
{
	while(leftChild(k)<=n)
	{
		int j = leftChild(k) ;
		if(j<n && less(j,j+1))
			j++;
		if(!(less(k,j)))
			break ;
		swap(pq[k],pq[j]);
		k = j ;
	}
}
Key* pop()
{
	Key *ret = pq[1] ;
	swap(pq[1],pq[n]) ;
	pq[n] = NULL ;
	n-- ;
	sinkDown(1) ;
	return ret ;
}

Key getHeapTop(){return (*pq[1]);}

void makeHeapOrder()
{
	int k = n>>1 ;
	// rightmost n/2 elements are heaps of size 1 which are in heap order trivially
	// get heap order in bottom up manner
	for(;k>=1;k--)
		sinkDown(k) ;
}

// in place heapSort
void heapSort()
{

	makeHeapOrder() ;	
	// sort
	while(n > 1)
	{
		swap(pq[1],pq[n]) ;
		n-- ;
		sinkDown(1) ;
	}
}
int numNodes ;
void printPQ()
{
	int i;
	printf("print pq..\n");
	for(i=1;i<=n;i++)
	{
		printf("%c %d\n",pq[i]->data , pq[i]->frq) ;
	}
	printf("\n") ;
}
Key* makeTree()
{
	while(n > 1)
	{
		Key one = getHeapTop() ;
		pop();
		Key two = getHeapTop() ;
		pop();
		Key* lft = (Key* )malloc(sizeof(Key)) ;
		Key* rgt = (Key* )malloc(sizeof(Key)) ;

		*lft = one ;
		*rgt = two ;
		//if(lft->order > rgt->order )
		//	swap(lft,rgt);
		Key* newkey = (Key* )malloc(sizeof(Key)) ;
		numNodes++ ;
		newkey->lc = lft ;
		newkey->rc = rgt ;
		newkey->data = '0' ;
		newkey->frq = lft->frq + rgt->frq ;
		newkey->order = cnt++ ;
		insert(newkey) ;
	}
	assert(n == 1) ;
	return pq[n] ;
}
void postOrder(Key* root)
{
	if(root == NULL)
		return ;
	postOrder(root->lc) ;
	postOrder(root->rc);
	printf("%c",root->data) ; 
}
void inOrder(Key* root)
{
	if(root == NULL)
		return ;

	inOrder(root->lc) ;
	printf("%c",root->data) ;
	inOrder(root->rc); 
}
bool isLeaf(Key* node)
{
	return (node->lc == NULL && node->rc == NULL);
}
bool taken[256] ;
void getCodes(Key* root,int top)
{
	if(root->lc)
	{
		arr[top] = 0 ;
		getCodes(root->lc,top+1) ;
	}
	if(root->rc)
	{
		arr[top] = 1 ;
		getCodes(root->rc,top+1) ;
	}
	if(isLeaf(root))
	{
		int i ;
		for(i=0;i<top;i++)
		{
			code[idx(root->data)][i] = arr[i] + '0' ;
		}
		code[idx(root->data)][i] = '\0'; 
	}
}

int main()
{
	freopen("input_dsa.txt" , "r" , stdin) ;
	int i ;
	int numChars = 0 ;
	scanf("%s",s) ;
	int len = strlen(s) ;
	for(i=0;i<len;i++)
	{
		if(freq[idx(s[i])] == 0)
			numChars++ ;
		freq[idx(s[i])]++ ;
	}
	for(i=0;i<len;i++)
	{
		if(!taken[idx(s[i])])
		{
			Key *newkey = (Key*)malloc(sizeof(Key)) ;
			newkey->data = s[i] ;
			newkey->frq = freq[idx(s[i])] ;
			newkey->lc = NULL ;
			newkey->rc = NULL ;
			Key* temp = newkey ;
			taken[idx(s[i])] = 1 ;	
			newkey->order = cnt++ ;	
			insert(newkey) ;
			assert(newkey == temp);
		}
	}

	numNodes = numChars ;
	Key* root = makeTree() ;
	printf("%d\n",numNodes) ;
	if(numChars == 1)
	{
		printf("0%c\n0%c\n",s[0],s[0]) ;
		for(i=0;i<len;i++)
		{
			printf("0");
		}
		printf("\n");
		return 0 ;
	}
	postOrder(root);
	printf("\n") ;
	inOrder(root) ;
	printf("\n") ;
	getCodes(root,0);
	for(i=0;i<len;i++)
		printf("%s",code[idx(s[i])]) ;
	
	printf("\n");
	return 0;
}
