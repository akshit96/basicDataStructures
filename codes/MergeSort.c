#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b

bool less(int a,int b)
{
	return (a<b) ;
}
int aux[105] ;
void mergeUp(int *a,int lo,int hi)
{
	int i,j ;
	for(i=lo;i<=hi;i++)
	{
		aux[i] = a[i] ;
	}
	int mid = (lo + hi)>>1 ;
	i = lo ;
	j = mid + 1 ;
	int k ;
	for(k=lo;k<=hi;k++)
	{
		if(i > mid)
			a[k] = aux[j++] ;
		else if(j > hi)
			a[k] = aux[i++] ;
		else if(less(aux[j],aux[i]))
			a[k] = aux[j++] ;
		else 
			a[k] = aux[i++] ;
	}
}
void mergeSort(int *arr ,int lo,int hi)
{
	if(lo == hi)
	{
		return ;
	}
	int mid = (lo + hi)>>1 ;
	mergeSort(arr,lo,mid) ;
	mergeSort(arr,mid+1,hi) ;

	mergeUp(arr,lo,hi) ;
}
int main()
{
	freopen("input_dsa.txt" , "r" , stdin) ;
	int n;
	scanf("%d",&n) ;
	int i ;
	int arr[102] ;
	for(i=1;i<=n;i++)
		scanf("%d",&arr[i]);
	mergeSort(arr,1,n) ;
	for(i=1;i<=n;i++)
	{
		printf("%d " , arr[i]);
	}
	printf("\n");
	return 0;
}
