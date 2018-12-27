/*
 ============================================================================
 Name        : retodfa.c
 Author      : 3931
 Version     :
 Copyright   : Your copyright notice
 Description : re to dfa
 ============================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct node
{
	struct node *rc,*lc;
	char data;
	int f[5],l[5],position,nullable;
}node;

struct stack
{
	struct node *data;
	struct stack *next;
}*top;

struct foll
{
  int follpos[10];
  char ch;
};
struct foll folltab[100];

int dstates[10][10],dfaa[30],df=0,state[10][10];
char input[10];

void push(struct node *x);
struct node* pop();

void uni(int a[10],int b[10]);
void copy(int a[10],int b[10]);
int check(int [],int);

struct node* alloc(char ch);
struct node* c_tree(char a[10]);
void display(struct node *head);
void follow(struct node *n1,struct node *n2);
void print_follow();
void dfa();
void display_dfa();

int main()
{
	char a[10];
	struct node *head=NULL;
	int i,j,l;

	printf("Enter expression :");
	scanf("%s",a);
	strcat(a,"#.");
	l=strlen(a);

	input[0]=NULL;
	for(i=0;i<l-1;++i)
	{
	     j=0;
	     while(input[j]!=NULL)
	     {
	       if(input[j]==a[i])
	         break;
	       j++;
	     }
	     if(input[j]!=a[i] && a[i]!='|' && a[i]!='*' && a[i]!='.' && a[i]!='#')
	     {
	       input[j]=a[i];
	       input[j+1]=NULL;
	     }
	}
	head = c_tree(a);
	display(head);
	print_follow();
	dfa();
	display_dfa();
	return 0;
}

void push(struct node *x)
{
	struct stack *s1;
	s1 = (struct stack*)malloc(sizeof(struct stack));
	s1->data = x;
	s1->next=top;
	top=s1;
}

struct node* pop()
{
	struct node* n1;
	n1 = top->data;
	top=top->next;
	return n1;
}

struct node* alloc(char ch)
{
	struct node * temp;
	temp=(struct node *)malloc(sizeof(struct node));
	temp->lc=NULL;
	temp->rc=NULL;
	temp->data=ch;
	temp->f[0]=-1;
	temp->l[0]=-1;
	return temp;
}

struct node* c_tree(char a[10])
{
	struct node *head=NULL,*temp=NULL,*left=NULL,*right=NULL;
	head = (struct node*)malloc(sizeof(struct node));
	int i,pos=0;

	for(i=0;a[i]!='\0';i++)
	{
		temp = alloc(a[i]);
		if(isalpha(a[i]) || a[i]=='#')
		{
			++pos;
			temp->position = pos;
			temp->nullable = 0;
			temp->f[0] = pos;
			temp->l[0] = pos;
			temp->f[1] = -1;
			temp->l[1] = -1;
			folltab[pos].ch=a[i];
			folltab[pos].follpos[0]=-1;
			push(temp);
		}
		else if(a[i] == '|')
		{
			right=NULL;
			left=NULL;
			right = pop();
			left = pop();
			temp->lc = left;
			temp->rc = right;
			temp->position = 0;
			temp->nullable = temp->rc->nullable || temp->lc->nullable;
			uni(temp->f,temp->lc->f);
			uni(temp->f,temp->rc->f);
			uni(temp->l,temp->lc->l);
			uni(temp->l,temp->rc->l);
			push(temp);
		}
		else if(a[i] == '.')
		{
			right=NULL;
			left=NULL;
			right = pop();
			left = pop();
			temp->lc = left;
			temp->rc = right;
			temp->position = 0;
			temp->nullable = temp->rc->nullable && temp->lc->nullable;
			if(temp->lc->nullable)
			{
				uni(temp->f,temp->lc->f);
				uni(temp->f,temp->rc->f);
			}
			else
			{
				copy(temp->lc->f,temp->f);
			}
			if(temp->rc->nullable)
			{
				uni(temp->l,temp->lc->l);
				uni(temp->l,temp->rc->l);
			}
			else
			{
				copy(temp->rc->l,temp->l);
			}
			follow(left,right);
			push(temp);
		}
		else if(a[i] == '*')
		{
			left=NULL;
			right=NULL;
			left = pop();
			temp->lc = left;
			temp->rc = NULL;
			temp->nullable =1;
			temp->position= 0;
			copy(temp->lc->f,temp->f);
			copy(temp->lc->l,temp->l);
			follow(temp,NULL);
			push(temp);
		}
	}
	head = pop();
	folltab[pos].ch = '\0';
	return head;
}

void display(struct node *head)
{
	int i=0;

	if(head!=NULL)
	{
		display(head->lc);

		printf("\n%c\nFirst:",head->data);

		while(head->f[i]!=-1)
		{
			printf(" %d ",head->f[i]);
			i++;
		}
		i=0;
		printf("\nLast: \n");
		while(head->l[i]!=-1)
		{
			printf(" %d ",head->l[i]);
			i++;
		}
		display(head->rc);
	}
}

void uni(int a[10],int b[10])
{
	int i=0,j=0,k=0,flag;

	while(a[i]!= -1)
	{
		i++;
	}
	j=0;
	while(b[j]!=-1)
	{
		flag=0;
		while(b[k]!=-1)
		{
			if(a[j] == b[k])
			{
				flag =1;
				break;
			}
			else
				flag=0;
			k++;
		}
		if(flag==0)
		{
			a[i++]=b[j];
		}
		j++;
	}
	a[i] = -1;
}

void copy(int a[10],int b[10])
{
	int i=0;

	while(a[i]!= -1)
	{
		b[i] = a[i];
		i++;
	}
	b[i]=-1;
}

void follow(struct node *n1,struct node *n2)
{
	int i=0,temp[10],fs;

	if(n2 == NULL)
	{
		copy(n1->l,temp);
		while(n1->f[i]!= -1)
		{
			fs++;
			i++;
		}
		for(i=0;i<fs;i++)
		{
			uni(folltab[temp[i]].follpos,n1->f);
		}
	}
	else
	{
		copy(n1->l,temp);
		while(n1->l[i]!= -1)
		{
			fs++;
			i++;
		}
		for(i=0;i<fs;i++)
		{
			uni(folltab[temp[i]].follpos,n2->f);
		}
	}
}

void print_follow()
{
	int i=0,j;

	printf("\n\nFOLLOWPOS : ");
	printf("\nChar : Values");
	do
	{
		printf("\n %c : ",folltab[i].ch);

		for(j=0;folltab[i].follpos[j]!=-1;j++)
		{
			printf(" %d ",folltab[i].follpos[j]);
		}
		i++;
	}while(folltab[i].ch!='\0');
}

void dfa()
{
	int i,j=0,k=0,l,m,temp[10],nos=1;

	temp[0]=-1;
	for(i=0;i<10;++i)
		state[i][0]=-1;
	i=0;
	uni(state[0],folltab[1].follpos);
	while(1)
	{
		for(i=0;input[i]!=NULL;++i)
		{
			for(j=0;state[k][j]!=-1;++j)
			{
				if(folltab[state[k][j]].ch==input[i])
				{
					uni(temp,folltab[state[k][j]].follpos);
				}
			}
			m=check(temp,nos);
			if(m==-1)
			{
				uni(state[nos++],temp);
				m=nos-1;
			}
			dfaa[df++]=m;
			temp[0]=-1;
		}
		if(k==nos-1)
			break;
		k++;
	}

	printf("\n\nSTATES : ");
	for(j=0;j<nos;j++)
	{
		printf("\n%c : ",j+65);
		for(l=0;state[j][l]!=-1;l++)
			printf("%d ",state[j][l]);
	}
	printf("\n");

}

int check(int temp[],int nos)
{
	int i,j;

	for(i=0;i<nos;++i)
    {
    	for(j=0;temp[j]!=-1;++j)
    	{
    		if(temp[j]!=state[i][j])
    			break;
    	}
    	if(temp[j]==-1 && state[i][j]==-1)
    		return i;
    }
    return -1;
}

void display_dfa()
{
   int i,j,k;

   printf("\nDFA TABLE : \n ");
   for(i=0;input[i]!=NULL;i++)
	   printf("\t%c",input[i]);
   for(j=0;j<(df/i);j++)
   {
	   printf("\n%c\t",j+65);
	   for(k=j*i;k<(j*i)+i;k++)
       printf("%c\t",dfaa[k]+65);
   }
}
