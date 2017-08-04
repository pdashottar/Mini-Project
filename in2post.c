//Converting an infix expression to postfix
#include <stdio.h>
#include <stdlib.h>
#define MAX 50
char stack[MAX];
int top=-1;

void push(char x)
{
	if(top==MAX-1)
	{
		printf("\nStack overflowed!\n");
		return ;
	}
	stack[++top]=x;
}

char pop()
{
	char x;
	if(top==-1)
	{
		printf("\nStack underflowed!\n");
		return 1;
	}
	x = stack[top--];
	return x;
}

int priority(char x)
{
	if(x=='(')
		return 0;
	if(x=='+')
		return 1;
	if(x=='*')
		return 2;
}

char *conversion(char s[],char *r)
{
	int i=0,j=0;
	char x;
	while(s[i]!='\0')
        {
                if(s[i]=='(')
                        push(s[i]);
                else if ( (s[i]=='+')||(s[i]=='*') )
                {
                        if( (priority(s[i])<=priority(stack[top])) )
                        {
                                do
                                {
                                        x = pop();
                                        r[j++] = x ;
                                        push(s[i]);
                                }while( (priority(s[++i])<=priority(stack[top]))&&(s[i]!='(')&&(s[i]!=')')&&( (s[i]=='+')||(s[i]=='*')) );
                        i--;
                        }
                        else
                                push(s[i]);
                }
                else if( s[i]==')')
                {
                        while(stack[top]!='(')
                        {
                                x = pop();
                                r[j++]= x ;
                        }
                        x = pop();

                }
                else if(s[i]==' ')
                {
                        i++;
                        continue ;
                }
                else
                {
                        r[j++]=s[i];
                }
                i++;
        }
	 while(top!=-1)
        {
                x = pop();
                r[j++] = x ;
        }
        r[j]='\0' ;
	return r;
}
/*
main()
{
	char s[MAX],r[MAX],x;
	int i=0,j=0;

	printf("Give an infix expression : ");
	gets(s);



	conversion(s,r) ;

	printf("\nThe corresponding postfix expression is : \n");
	j=0;
	while(r[j]!='\0')
		printf("%c",r[j++]);

	printf("\n");
}*/
