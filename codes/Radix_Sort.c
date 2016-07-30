#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b

int idx(char ch){	if(ch == '\0')	return 0 ;  return (ch - 'a' + 1) ;}
struct word
{
	char s[102] ;
	int pages[102] ;
	bool taken[102] ;
	int pg_cnt ;
};

struct word wrd[202] ;
struct word auxi_wrd[202] ;
int count[28] ;

int main()
{
	freopen("input_dsa.txt" , "r" , stdin) ;
	int pn ;

	char content[4002] ;
	char current_word[102];
	int word_cnt = 0 ;int i,j ;
	while(~scanf("%d\n",&pn))
	{
		fgets(content,4000,stdin);
		int len = strlen(content) ;
		for(i=0;i<len;i++)
		{
			if('A'<=content[i] && content[i]<='Z')
				content[i] += 32 ;
		}
		i = 0 , j = 0 ;
		for(;i<len;i++)
		{
			j = 0 ;
			if(!isalpha(content[i]))
			{
				continue ;
			}
			while(isalpha(content[i]))
			{
				current_word[j++] = content[i++] ;
			}
			current_word[j] = 0 ;
			bool found = false ;
			int k ;
			for(k = 1 ; k <= word_cnt ; k++)
			{
				if( (strcmp(wrd[k].s , current_word) == 0) )
				{
					found = 1 ;
					if(wrd[k].taken[pn] == false)
					{
						wrd[k].taken[pn] = true ;
						wrd[k].pages[++wrd[k].pg_cnt] = pn ;
					}
					break ;
				}
			}
			if(!found)
			{
				word_cnt++ ;
				wrd[word_cnt].pg_cnt++ ;
				wrd[word_cnt].pages[wrd[word_cnt].pg_cnt] = pn ;
				wrd[word_cnt].taken[pn] = true ;
				strcpy(wrd[word_cnt].s , current_word) ;
			}
		}
	}
	int l = 0 ;
	for(i=1;i<=word_cnt;i++)
	{
		l = max(l,strlen(wrd[i].s)) ;
	}
	for(j=l-1 ; j>=0 ;j--)
	{
		for(i=0;i<=26;i++)
			count[i] = 0 ;
		for(i=1;i<=word_cnt;i++)
		{
			count[idx(wrd[i].s[j])]++ ;
		}
		for(i=1;i<=26;i++)
		{
			count[i] += count[i-1] ;
		}
		for(i = word_cnt;i >= 1; i--) // reverse for stable sorting else doesn't matter in this case
		{
			auxi_wrd[count[idx(wrd[i].s[j])]--] = wrd[i] ; 
		}
		for(i=1;i<=word_cnt;i++)
		{
			wrd[i] = auxi_wrd[i] ;
		}
	}
	for(i=1;i<=word_cnt;i++)
	{
		printf("%s " , wrd[i].s) ;
		for(j=1;j<wrd[i].pg_cnt;j++)
		{
			printf("%d, ",wrd[i].pages[j]) ;
		}
		printf("%d\n",wrd[i].pages[j]);
	}
	return 0;
}
