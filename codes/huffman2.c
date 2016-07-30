// heap && heap sort && huffman_Coding
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

struct Key ;
typedef struct Key Key ;
struct Key
{
	int frq ;
	char data;
	Key *lc,*rc ;
};
bool taken[54] ;
int order[54] ;
Key *pq[1002] ;
int n ;
char s[105] ;
int freq[27] = {0};
int parent(int k){return (k>>1) ;}
int leftChild(int k){return (k<<1);}
int rightChild(int k){return (k<<1|1) ;}
int indx(char ch)
{
	if('A'<=ch && ch<='Z')
	{
		return (ch - 'A' + 1) ;
	}
	else
	{
		return (ch - 'a' +26) ;
	}
}
void swap(Key *a,Key *b)
{
	
	// printf("%s ... \n",a->str) ;
	Key temp = *a ;
	*a = *b ;
	*b = temp ;
	// printf("%s...$$ \n",a->str ) ;
}
bool less(int i,int j)// logic for comparision of keys, (>) for min-heap
{
	if(pq[i]->frq > pq[j]->frq)
	{
		return 1 ;
	}
	// else if(pq[i]->frq == pq[j]->frq) 
	// {
	// 	if(order[ indx(pq[i]->data) ] < order[ indx(pq[j]->data) ])
	// 	{
	// 		return 0 ;
	// 	}
	// 	else
	// 	{
	// 		return 1 ;
	// 	}
	// }
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
	// pq[++n].frq = val ;
	// strcpy(pq[n].str,st) ;
	// pq[++n] = key ;
	// pq[++n] = key;
	// pq[++n] = (Key* )malloc(sizeof(key)) ;
	// *pq[n] = *key ;
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
	// pq[n]->frq = -1 ;
	// pq[n]->data = '\0'; 
	pq[n] = NULL ;
	n-- ;
	sinkDown(1) ;
	return ret ;
}

Key getHeapTop(){return (*pq[1]);}

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
		swap(pq[1],pq[n]) ;
		n-- ;
		sinkDown(1) ;
	}
}
struct huffmanTree;
typedef struct huffmanTree tree ;
struct huffmanTree
{
	tree *lc,*rc ;
	Key key ; 
};
int numNodes ;
Key* makeTree()
{
// 	printf("priority Q init.. \n") ;
// 	int i ;for(i=1;i<=n;i++){
// 		printf("%c",pq[i]->data);
// 	}
// 	printf("\n") ;
// 	Key one = getHeapTop() ;
// 	pop();
// for(i=1;i<=n;i++){
// 		printf("%c",pq[i]->data);
// 	}
// 	printf("\n") ;
// 	// Key two = *(pop()) ;
// 	//Key one = two ;
// 	Key two = one ;
// 	printf("%c%c\n",one.data,two.data) ;

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

		Key* newkey = (Key* )malloc(sizeof(Key)) ;
		numNodes++ ;
		newkey->lc = lft ;
		newkey->rc = rgt ;
		newkey->data = '0' ;
		newkey->frq = lft->frq + rgt->frq ;
		printf("lft data = %c .. rgt data = %c\n",lft->data,rgt->data) ;
		if(lft->lc == NULL)
		{
			printf("check1 of leaf left\n"); 
		}
		if(lft->rc == NULL)
		{
			printf("check2 of leaf left\n"); 
		}
		if(rgt->lc == NULL)
		{
			printf("check1 of leaf right\n"); 
		}
		if(rgt->rc == NULL)
		{
			printf("check2 of leaf right\n"); 
		}


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


int main()
{
	// freopen("inp.txt" , "r" , stdin) ;

	// char a[222][5] ;
	Key* one = (Key*)malloc(sizeof(Key)) ;
	Key* two = (Key*)malloc(sizeof(Key)) ;
	Key* three = (Key*)malloc(sizeof(Key)) ;
	Key* four = (Key*)malloc(sizeof(Key)) ;
	int cnt = 0 ;
	one->lc = one->rc = two->lc = two->rc = three->lc = three->rc = four->lc = four->rc = NULL;
	one->frq = 1 ;
	one->data = 'A' ;

	two->frq = 2 ;
	two->data = 'B' ;
	three->data = 'C';
	four->data = 'D' ;
	three->frq = four->frq = 3 ;
	insert(three) ;
	order[indx(three->data)] = cnt++ ;
	insert(one) ;
	order[indx(three->data)] = cnt++ ;
	insert(two) ;
	order[indx(two->data)] = cnt++ ;
	insert(four) ;
	order[indx(four->data)] = cnt++ ;

	int i ;
	for(i=1;i<=n;i++)
	{
		printf("%c %d\n",pq[i]->data,pq[i]->frq) ;
	}
	printf("\n");
	insert(one) ;
	for(i=1;i<=n;i++)
	{
		printf("%c %d\n",pq[i]->data,pq[i]->frq) ;
	}
	printf("\n");
	insert(two); 
	for(i=1;i<=n;i++)
	{
		printf("%c %d\n",pq[i]->data,pq[i]->frq) ;
	}
	printf("\n");
	insert(four) ;
	for(i=1;i<=n;i++)
	{
		printf("%c %d\n",pq[i]->data,pq[i]->frq) ;
	}
	printf("\n");
	for(i=1;i<=n;i++)
	{
		printf("%c %d\n",pq[i]->data,pq[i]->frq) ;
	}
	printf("\n") ;
	// swap(pq[3],pq[4]) ;
	for(i=1;i<=n;i++)
	{
		printf("%c %d\n",pq[i]->data,pq[i]->frq) ;
	}
	printf("\npoping in order\n") ;
	while(n)
	{
		printf("%c %d\n",pq[1]->data,pq[1]->frq) ;
		pop();
	}
	// printf(".. %c\n",getHeapTop().data) ;
	// pop();
	// printf(".. %c\n",getHeapTop().data) ;
	// pop();

// 	int i ;
// 	int numChars = 0 ;
// 	scanf("%s",s) ;
// 	int len = strlen(s) ;
// 	for(i=0;i<len;i++)
// 	{
// 		if(freq[s[i] - 'A' + 1] == 0)
// 			numChars++ ;
// 		freq[s[i] - 'A' + 1]++ ;
// 	}
// 	// char ch[2] ;
// 	// ch[1] = '\0' ;
// 	// Key tempKey ;
// 	for(i=0;i<len;i++)
// 	{
// 		if(!taken[s[i]-'A'+1])
// 		{
// 		Key *newkey = (Key*)malloc(sizeof(Key)) ;
// 		newkey->data = s[i] ;
// 		newkey->frq = freq[s[i]-'A'+1] ;
// 		newkey->lc = NULL ;
// 		newkey->rc = NULL ;
// 		insert(newkey) ;
// 		taken[s[i]-'A'+1] = 1 ;			
// 		}

// 		// printf("\n%s %d\n",ch,freq[ch[0] - 'A' + 1]);
// 	}
// 	for(i=1;i<=n;i++)
// 	{
// 		printf("%c %d\n",pq[i]->data,pq[i]->frq) ;
// 	}
// 	numNodes = numChars ;
// 	Key* root = makeTree() ;
// 	// assert(0);
// 	// pop();
// 	// pop();
// 	// printf("n = %d\n",n );
// 	for(i=1;i<=n;i++)
// 	{
// 		printf("pq.. %c\n",pq[i]->lc->data);
// 	}
// 	// if(isLeaf(root->lc->lc)) 
// 	// {
// 	// 	printf("chutzpah max...\n");
// 	// }
// 	// printf("%d",numNodes) ;
// 	// printf("\n%c",root->data) ;

// 	// while(root->lc != NULL)
// 	// {
// 	// 	printf(" data lc %c\n",root->data) ;
// 	// 	root = root->lc ;
// 	// }
// 	printf("postorder...\n");
// 	postOrder(root);
// // assert(0);
// 	printf("inorder...\n") ;
// 	inOrder(root) ;

	return 0;
}
