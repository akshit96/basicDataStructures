// max-heap && heap sort 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

int pq[1002] ;
int n ;
char s[105] ;
int freq[27] = {0};
int parent(int k){return (k>>1) ;}
int leftChild(int k){return (k<<1);}
int rightChild(int k){return (k<<1|1) ;}
void swap(int *a,int *b)
{
	int temp = *a ;
	*a = *b ;
	*b = temp ;
}
bool less(int i,int j)
{
	 return (pq[i] > pq[j]) ; // logic for comparision of keys, (>) for min-heap
}
void swimUp(int k)
{
	while(k>1 && less(parent(k) , k))
	{
		swap(&pq[k],&pq[parent(k)]) ;
		k = parent(k) ;
	}
}
void insert(int val)
{
	pq[++n] = val ;
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
		swap(&pq[k],&pq[j]);
		k = j ;
	}
}
int pop()
{
	int ret = pq[1] ;
	swap(&pq[1],&pq[n]) ;
	pq[n] = -1 ;
	n-- ;
	sinkDown(1) ;
	return ret ;
}

int getHeapTop(){return pq[1];}

void makeHeapOrder()
{
	int k = n>>1 ;
	for(;k>=1;k--)
		sinkDown(k) ;
}

// in place heapSort
void heapSort()
{
	int k = n>>1 ;
	// rightmost n/2 elements are heaps of size 1 which are in heap order trivially
	// get heap order in bottom up manner
	makeHeapOrder() ;
	
	// sort
	while(n > 1)
	{
		swap(&pq[1],&pq[n]) ;
		n-- ;
		sinkDown(1) ;
	}
}

int main()
{
	freopen("inp.txt" , "r" , stdin) ;
	scanf("%s",s) ;
	int i ;
	int len = strlen(s) ;
	for(i=0;i<len;i++)
	{
		freq[s[i] - 'A' + 1]++ ;
	}
	return 0;
}
