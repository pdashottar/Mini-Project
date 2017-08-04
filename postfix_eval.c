#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#define MAX 20
int stack1[MAX];
int top1=-1;
void pushstack(char c)
{
        top1++;
        stack1[top1]=(int)(c-48);
//	printf("\nstacktop = %d \n",stack1[top1]);
}
void calculator(char c)
{
        int a,b,ans;
        a=stack1[top1];
	stack1[top1]=0;
        top1--;
        b=stack1[top1];
	stack1[top1]=0;
        top1--;
//	printf("\na=%d,b=%d\n",a,b);
        switch(c)
        {
                case '+':
                        if( (b==a) && (b==1) )
                                ans = 1;
                        else
                                ans=b+a;
                        break;
                case '*':
                        ans=b*a;
                        break;
                default:
                        printf("HI");
        }
//	printf("\nAns = %d \n",ans);
	top1++;
        stack1[top1]=ans;
}

int evaluate(char post[])
{
//	char post[MAX];
	top1=-1;
	int i;
//	printf("Insert a postfix notation :: ");
//	gets(post);
	for(i=0;i<strlen(post);i++)
 	{
  		if(post[i]=='0' || post[i]=='1')
  		{
   			pushstack(post[i]);
  		}
  		if(post[i]=='+' || post[i]=='*')
  		{
   			calculator(post[i]);
  		}
 	}
//	 printf("\n\nResult :: %d\n",stack1[top1]);
	return stack1[top1] ;
}
/*
main()
{
	evaluate();
}*/
