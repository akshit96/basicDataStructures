#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b

bool less(int i,int j)
{
	return (i<j) ;
}
void swapArrayElements(int *a,int i,int j)
{
	int tmp = a[i] ;
	a[j] = a[i] ;
	a[i] =  tmp ;
}
int partitionIndex(int *a,int lo,int hi)
{
	// consider the pivot to be 'hi'
	// for random shuffling select any number in [lo...hi] and swap(a[number] , a[hi])
	// take it lite here
	int i,j ;
	int x = a[hi] ;
	j = lo - 1 ;
	for(i=lo;i<=hi;i++)
	{
		if(a[i] <= x)
		{
			j++ ;
		}
		swapArrayElements(a[i] , a[j]) ;
	}
	swapArrayElements(a , j+1 , hi) ;
	return (j+1);
}
void QuickSort(int *a,int lo,int hi)
{
	if(hi <= lo)
	{
		return ;
	}
	int idx = partitionIndex(a,lo,hi);
	QuickSort(a,lo,idx-1) ;
	QuickSort(a,idx+1,hi) ;
}
int main()
{
	freopen("input_dsa.txt" , "r" , stdin) ;
	int n,i ;
	int a[1002] ;
	scanf("%d",&n) ;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]) ;
	}
	QuickSort(a,1,n) ;
	for(i=1;i<=n;i++)
	{
		printf("%d " , a[i]);
	}
	printf("\n");
	return 0;
}
