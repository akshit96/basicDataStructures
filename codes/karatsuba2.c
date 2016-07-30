#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#define MAX 			1005
#define false 			0
#define true 			1

// MY OWN IMPLEMENTATION OF BIGINT LIBRARY USING CHAR ARRAYS

//*********************************** IMPLEMENTATION STARTS HERE *********************************
void assign(char *a, char *e)
{
	int x = strlen(a);
	int i;
	for(i=0; i<=x; ++i)
		e[i] = a[i];
}

void reduce(char *a)
{
	int x = strlen(a);
	int i, j;
	for (i=0; a[i]=='0'; ++i);
	if (i != x)
	{
		for (j=i; j<=x; ++j)
			a[j-i] = a[j];
	}
	else
	{
		a[0] = '0';
		a[1] = '\0';
	}
}

void get_power_10(char *a, int n)
{
	int i;
	a[0] = '1';
	for(i=1; i<=n; ++i)
		a[i] = '0';
	a[i] = '\0';
}

void make_equal(char *a, char *b)
{
	int x = strlen(a);
	int y = strlen(b);
	if (x==y)
		return ;
	else if (x>y)
	{
		int i, w = x-y;
		for(i=x; i>=0; --i)
		{
			if (i>=w)
				b[i] = b[i-w];
			else
				b[i] = '0';
		}
	}
	else
	{
		int i, w = y-x;
		for(i=y; i>=0; --i)
		{
			if (i>=w)
				a[i] = a[i-w];
			else
				a[i] = '0';
		}
	}
}

char compare(char *a, char *b)
{
	int x = strlen(a);
	int y = strlen(b);
	if (x > y)
		return '>';
	else if (y < x)
		return '<';
	else if (x==y)
	{
		int i;
		for(i=0; i<x; ++i)
		{
			if (a[i]>b[i])
				return '>';
			else if (a[i]<b[i])
				return '<';
			else
				continue;
		}
		return '=';
	}
}

void swap(char *a, char *b)
{
	int x = strlen(a);
	int y = strlen(b);
	if (x!=y)
		make_equal(a, b);

	x = strlen(a);
	char *c = (char *)malloc(x * sizeof(char));
	int i;
	for(i=0; i<=x; ++i)
	{
		c[i] = b[i];
	}
	for(i=0; i<=x; ++i)
	{
		b[i] = a[i];
	}
	for(i=0; i<=x; ++i)
	{
		a[i] = c[i];
	}
}

void add(char *a, char *b, char *c)
{
	reduce(a);
	reduce(b);
	int x = strlen(a);
	int y = strlen(b);
	if (x != y)
		make_equal(a, b);

	int l = strlen(a);
	int i, temp = 0, val;
	for (i=l-1; i>=0; --i)
	{
		val = temp + (a[i]-48) + (b[i]-48);
		c[i] = (val%10) + 48;
		temp = val/10;
	}
	c[l] = '\0';
	if (temp>0)
	{
		for(i=l+1; i>=1; --i)
		{
			c[i] = c[i-1];
		}
		c[0] = temp + 48;
	}
}

void subtract(char *a, char *b, char *c)
{
	reduce(a);
	reduce(b);
	int x = strlen(a);
	int y = strlen(b);
	if (x != y)
		make_equal(a, b);

	if (compare(a, b)=='=')
	{
		c[0] = '0';
		c[1] = '\0';
		return ;
	}
	else if (compare(a, b)=='<')
		swap(a, b);
	reduce(b);
	make_equal(a, b);
	int i, temp = 0, val, l = strlen(a);
	for (i=l-1; i>=0; --i)
	{
		val = temp + (a[i]-48) - (b[i]-48);
		if (val < 0)
		{
			val += 10;
			temp = -1;
		}
		else
		{
			temp = 0;
		}
		c[i] = val + 48;
	}
	c[l] = '\0';
	reduce(c);
}

void multiply_by_10(char *a, char *b, char *c)
{
	reduce(a);
	int x = strlen(a);
	int y = strlen(b) - 1;
	int i, j=0;
	for (i=0; i<x; ++i)
		c[j++] = a[i];
	for (i=0; i<y; ++i)
		c[j++] = '0';
	c[j] = '\0';
}

//***************************** BIGINT IMPLEMENTATION OVER ************************************

// Structs for Tree, Queue and Stacks

struct node
{
	char num1[MAX];
	char num2[MAX];
	char res[MAX*2];
	int size1;
	int size2;
	int evaluated;
	struct node * left;				// value of a
	struct node * right;			// value of c
	struct node * middle;			// value of b
	struct node * parent;			// for help in reversal order traversal
};

typedef struct node tree;

struct q
{
	struct q *next;
	tree *node;
};

typedef struct q Q;

struct L
{
	Q *front;
	Q *rear;
	int size;
};

typedef struct L queue;

struct S
{
  	tree *t;
  	struct S *next;
};
 
typedef struct S stack;

// ******************************* IMPLEMENTATION FOR OPERATION ON QUEUE ************************
void push(queue *list, tree *n)
{
	Q *a = (Q *)malloc(sizeof(Q));
	a->node = n;
	// base case
	if (list->size == 0)
	{
		list->front = list->rear = a;
		a->next = NULL;
	}
	else
	{
		list->rear->next = a;
		list->rear = a;
		a->next = NULL;
	}
	list->size += 1;
}

int isEmpty(queue *list)
{
	return (list->front==NULL && list->rear==NULL);
}

tree * pop_back(queue *list)
{
	// base case
	if (list->size == 0)		// or equivalently if(isEmpty(list))
	{
		printf("Underflow\n");
	}
	if (list->size == 1)
	{
		Q *temp = list->rear;
		list->size = 0;
		list->front = list->rear = NULL;
		tree *waste = temp->node;
		free(temp);
		return waste;
	}
	Q *temp = list->front;
	Q *prev = temp;
	while (temp->next != NULL)
	{
		prev = temp;
		temp = temp->next;
	}
	list->rear = prev;
	prev->next = NULL;
	list->size -= 1;
	tree *waste = temp->node;
	free(temp);
	return waste;
}

tree * pop_front(queue *list)
{
	//base case
	if (list->size == 0)		//or equivalently if(isEmpty(list))
	{
		printf("Underflow\n");
	}
	if (list->size == 1)
	{
		Q *temp = list->front;
		list->size = 0;
		list->front = list->rear = NULL;
		tree *waste = temp->node;
		free(temp);
		return waste;
	}
	Q *temp = list->front;
	list->front = list->front->next;
	tree *waste = temp->node;
	free(temp);
	list->size -= 1;
	return waste;	
}
 
// ******************************* IMPLEMENTATION FOR QUEUE OVER *********************************

// ******************************* IMPLEMENTATION FOR OPERATION ON STACK ************************
void pushStack(stack **top_ref, tree *t)
{
  	stack *temp = (stack *)malloc(sizeof(stack));
 
 	// base case i.e. memory not available
  	if(temp == NULL)
  	{
     	printf("Stack Overflow \n");
	}

  	temp->t = t; 
  	temp->next = (*top_ref);
  	(*top_ref) = temp;
}
 
int isEmptyStack(stack *top)
{
	return (top == NULL);
}   
 
tree * popStack(stack ** top_ref)
{
  	tree *waste;
  	stack *top;
 
  	//base case
  	if(isEmptyStack(*top_ref))
  	{
     	printf("Stack Underflow \n");
  	}
  	else
  	{
     	top = *top_ref;
     	waste = top->t;
     	*top_ref = top->next;
     	free(top);
     	return waste;
  	}
}

// ************************************** IMPLEMENTATION FOR STACK OVER **************************


// ************************* PROCESS FOR BUILDING DIVIDE & CONQUER TREE *************************
void build(tree *root, queue *list, stack *store, char *a, char *b, int l_a, int l_b)
{
	push (list, root);
	int i, j, no_of_leaves = 0, req_size1, req_size2;
	while (!isEmpty(list))
	{
		tree *temp = pop_front(list);
		temp->evaluated = false;
		// printf("temp data : %s %s %d %d\n", temp->num1, temp->num2, temp->size1, temp->size2);

		// base case for stack pushing i.e. leaf node reached
		if (temp->size1==1 && temp->size2==1)
		{
			pushStack(&store, temp);
			no_of_leaves += 1;
			continue;
		}

		tree *left_child = (tree *)malloc(sizeof(tree));
		tree *right_child = (tree *)malloc(sizeof(tree));
		tree *middle_child = (tree *)malloc(sizeof(tree));
		left_child->parent = right_child->parent = middle_child->parent = temp;
		// parent assigned

		temp->left = left_child;
		temp->right = right_child;
		temp->middle = middle_child;		
		left_child->left = left_child->right = left_child->middle = NULL;
		right_child->left = right_child->right = right_child->middle = NULL;
		middle_child->left = middle_child->right = middle_child->middle = NULL;
		// left, middle and right child assigned

		req_size1 = (temp->size1)/2;
		req_size2 = (temp->size2)/2;
		
		assert(req_size1 == req_size2);

		char *s1 = (char *)malloc((req_size1+2)*sizeof(char));
		char *s2 = (char *)malloc((req_size2+2)*sizeof(char));
		j = 0;
		for (i=0; i<req_size1; ++i)
			s1[j++] = temp->num1[i];
		s1[j] = '\0';
		j = 0;
		for (i=req_size1; i<temp->size1; ++i)
			s2[j++] = temp->num1[i];
		s2[j] = '\0';
		reduce(s1);
		reduce(s2);
		// printf("L1: %s %s, ", s1, s2);
		add(s1, s2, left_child->num1);

		j = 0;
		for (i=0; i<req_size2; ++i)
			s1[j++] = temp->num2[i];
		s1[j] = '\0';
		j = 0;
		for (i=req_size2; i<temp->size2; ++i)
			s2[j++] = temp->num2[i];
		s2[j] = '\0';
		reduce(s1);
		reduce(s2);
		// printf("L2: %s %s, ", s1, s2);
		add(s1, s2, left_child->num2);

		make_equal(left_child->num1, left_child->num2);
		left_child->size1 = strlen(left_child->num1);
		left_child->size2 = strlen(left_child->num2);
		// printf("left data: %s %s %d %d\n", left_child->num1, left_child->num2, left_child->size1, left_child->size2);
		//left data assigned

		j = 0;
		for (i=0; i<req_size1; ++i)
			s1[j++] = temp->num1[i];
		s1[j] = '\0';
		j = 0;
		for (i=0; i<req_size2; ++i)
			s2[j++] = temp->num2[i];
		s2[j] = '\0';

		reduce(s1);
		reduce(s2);
		assign(s1, middle_child->num1);
		assign(s2, middle_child->num2);
		make_equal(middle_child->num1, middle_child->num2);
		middle_child->size1 = strlen(middle_child->num1);
		middle_child->size2 = strlen(middle_child->num2);
		// printf("middle data: %s %s %d %d\n", middle_child->num1, middle_child->num2, middle_child->size1, middle_child->size2);
		//middle data assigned

		j = 0;
		for (i=req_size1; i<temp->size1; ++i)
			s1[j++] = temp->num1[i];
		s1[j] = '\0';
		j = 0;
		for (i=req_size2; i<temp->size2; ++i)
			s2[j++] = temp->num2[i];
		s2[j] = '\0';
		reduce(s1);
		reduce(s2);
		assign(s1, right_child->num1);
		assign(s2, right_child->num2);
		make_equal(right_child->num1, right_child->num2);
		right_child->size1 = strlen(right_child->num1);
		right_child->size2 = strlen(right_child->num2);
		// printf("right data: %s %s %d %d\n", right_child->num1, right_child->num2, right_child->size1, right_child->size2);
		//right data assigned

		push(list, left_child);
		push(list, middle_child);
		push(list, right_child);
		// pushing into queue or stack done
		free(s1);
		free(s2);
	}
	// printf("no of leaves : %d\n", no_of_leaves);
	// first part of tree bulding done and stack created too

	while (no_of_leaves--)
	{
		tree *temp = popStack(&store); 
		int x = temp->num1[0] - 48, y = temp->num2[0] - 48;
		int z = x*y;
		temp->res[0] = (z/10) + 48;
		temp->res[1] = (z%10) + 48;
		temp->res[2] = '\0';
		reduce(temp->res);
		temp->evaluated = true;
		printf("%sX%s=%s\n", temp->num1, temp->num2, temp->res);
		push(list, temp);		
	}
	// contents of stack pushed into queue & leaf nodes evaluated

	// apply karatsuba algorithm
	while (list->size > 1)
	{
		tree *temp = pop_front(list);
		//base case i.e. already evaluated node
		if (temp->evaluated == true)
		{
			if (temp->parent != NULL && temp->parent->left->evaluated==true)
				push(list, temp->parent);
			continue;
		}
		
		tree *right_child; 		
		tree *middle_child;
		tree *left_child;
		left_child = temp->left;
		right_child = temp->right;
		middle_child = temp->middle;
		
		// printf("Leaves: %s %s %s\n", left_child->res, middle_child->res, right_child->res);		
		
		int x = ((temp->size1 + 1)/2) * 2;
		assert(middle_child->size1 == middle_child->size2);
		char *u = (char *)malloc((x+2) * sizeof(char));
		get_power_10(u, x);
		reduce(u);
		
		char *fin1 = (char *)malloc((x*2+2) * sizeof(char));
		char *fin2 = (char *)malloc((x*2+2) * sizeof(char));
		char *fin3 = (char *)malloc((x*2+2) * sizeof(char));
		char *fin4 = (char *)malloc((x*2+2) * sizeof(char));
		char *fin5 = (char *)malloc((x*2+2) * sizeof(char));

		multiply_by_10(middle_child->res, u, fin1);
		
		assign(right_child->res, fin2);

		subtract(left_child->res, middle_child->res, fin3);
		// printf("Primary: 1=%s 2=%s 3=%s\n", fin1, fin2, fin3);		
		subtract(fin3, right_child->res, fin4);
		// printf("Tertiary: 1=%s 2=%s 3=%s 4=%s\n", fin1, fin2, fin3, fin4);		
		get_power_10(u, (temp->size1 + 1)/2);
		multiply_by_10(fin4, u, fin5);
		assign(fin5, fin3);

		reduce(fin1);
		reduce(fin2);
		reduce(fin3);

		// printf("Secondary: 1=%s 2=%s 3=%s 4=%s 5=%s\n", fin1, fin2, fin3, fin4, fin5);
		add(fin1, fin2, fin4);
		reduce(fin4);
		add(fin3, fin4, fin5);

		reduce(fin5);
		assign(fin5, right_child->parent->res);

		right_child->parent->evaluated = true;
		assert(right_child->parent == temp);

		reduce(temp->num1);
		reduce(temp->num2);
		reduce(left_child->res);
		reduce(middle_child->res);
		reduce(right_child->res);

		printf("%sX%s=", temp->num1, temp->num2);
		printf("%sX%sX%s+(%s-%s-%s)X%s+%s=", middle_child->res, u, u, left_child->res, middle_child->res, right_child->res, u, right_child->res);
		printf("%s\n", right_child->parent->res);
		if (temp->parent != NULL && temp->parent->left->evaluated==true)
			push(list, temp->parent);
		free(fin1);
		free(fin2);
		free(fin3);
		free(fin4);
		free(fin5);
	}
	// reversal -order traversal done
	
	tree *waste = pop_front(list);
	// printf("Contents final: %s %s %s\n", waste->num1, waste->num2, waste->res);
	assert(list->size == 0);
}

// ****************************** BUILD FUNCTION ENDS HERE ***************************************

// function to free the memory allocated for tree

void empty (tree *root)
{
    if (root==NULL)
        return;
    empty(root->left);
    empty(root->middle);
    empty(root->right);
    // memory released for all the children nodes
    free(root);
    // memory released for parent node
}

// ****************************** MAIN ACTION BEGINS HERE ****************************************
int main()
{
	#ifndef ONLINE_JUDGE
		freopen("input_dsa.txt", "r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif

	char s[MAX], a[MAX], b[MAX];

	// READ & PROCESS INPUT
	scanf("%s", s);
	int l = strlen(s), i, j = 0, k = 0, done = 0;
	for(i=0; i<l; ++i)
	{
		if (s[i]=='X')
		{
			done = 1;
			a[j++] = '\0';
		} 
		else if (done==0)
		{
			a[j++] = s[i];
		}
		else if (done==1)
		{
			b[k++] = s[i];
		}
		else
		{
			assert(false);
		}
	}
	b[k] = '\0';
	make_equal(a, b);
	int l_a = strlen(a), l_b = strlen(b);

	tree * root = (tree *)malloc(sizeof(tree));
	root->left = root->right = root->middle = root->parent = NULL;
	assign(a, root->num1);
	assign(b, root->num2);
	root->size1 = l_a;
	root->size2 = l_b;
	root->evaluated = false;
	// root initailised

	queue *list = (queue *)malloc(sizeof(queue));
	list->front = list->rear = NULL;
	list->size = 0;
	// queue initialised

	stack *store = (stack *)malloc(sizeof(stack));
	store->next = NULL;
	store->t = NULL;
	//stack initialised

	build(root, list, store, a, b, l_a, l_b);
	// build the game tree

	empty(root);
	// free memory stored for tree

	// All memory was released free
	return 0;
}

// ************************************** ACTION ENDS ******************************************