#include <stdio.h>
#define COL pow(2,var)
//for evaluation of postfix expression , putting all combinations from arr into the string and checking which will result to 1 , if evaluated result=1 , then that combination is a min term
void toeval(char post1[],char post2[],int **arr,int var)
{
	int k=0,i=0,j=1,m=0,l=0,flag=1,t,*array;
	char ieval[MAX];	//stores string with 0/1 in place of variable names
	
	array = malloc( var*sizeof(int) );
	for(i=0;i<var;i++)
		array[i]=0;
	
	l=0;
	for(i=0;i<COL;i++)
	{
		while(post1[k]!='\0')
		{
				if( (post1[k]!='+')&&(post1[k]!='*') )
				{
					if(post1[k]=='~')
					{
						k++;
						for(t=0;t<var;t++)
                                                {
                                                        if(post2[t]==post1[k])
                                                        {
								array[t] ++;
								if(array[t]!=1)
								{
									if(arr[i][t+1]==0)
                                                       				 ieval[m] = '1';
                                                			else
                                                        			ieval[m] = '0';
									flag=0;
								}
                                                        }
                                                }
						if(flag==1)
						{
							if(arr[i][j]==0)
								ieval[m] = '1';
							else
								ieval[m] = '0';
						}
						flag=1;
					}
					else
					{
						for(t=0;t<var;t++)
						{
							if(post2[t]==post1[k])
							{
								array[t]++;
								if(array[t]!=1)
								{
									ieval[m] = (char) arr[i][t+1] + 48 ;
									flag = 0 ;
								}
							}
						}
						if(flag==1)
						{
							ieval[m] = (char) arr[i][j] + 48 ;
						}
						l++;	flag=1;
					}
					j++;
				}
				else
					ieval[m] = post1[k] ;
				k++; m++;
		}
			ieval[m]='\0' ;
//			printf("%s\n",ieval);
//			printf("\n");
			arr[i][var+1] = evaluate(ieval) ;
			m=0 ; j=1; k=0,l=0;
		
	}
	free(array);
}

