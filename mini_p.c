//Tabular Method
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"in2post.c"
#include"postfix_eval.c"
#include"toeval.c"
#include"gate.c"
#define COL pow(2,var)

int **array(int var)
{
	int **arr,i,j,t=0,count=1,m=1;
	arr = (int **)malloc( COL*sizeof(int *)) ;
	for(i=0;i<COL;i++)
		arr[i] = (int *)malloc((var+2)*sizeof(int));
	for(j=var;j>0;j--)		//making all possible combinations for var no. of variables
	{
		for(i=0;i<COL;i++)
		{
			arr[i][j] = t;
			if( count%m == 0 )
			{
				if(t==0)
					t=1;
				else
					t=0;
			}
			count++;
		}
		m=m*2;
		count = 1 ;
		t=0 ;
	}
	j=0;
	count =0 ;
	for(i=0;i<COL;i++)
		arr[i][j] = count++;
	return arr;
}

int table(int **tab,int row,int d,int col,int min,int cycle,int **PI,int col2)
{
	int j,k,**tab1,p,i,t,l,m,col1=0,flag=0;

	tab1 = (int **)malloc((col*col)*sizeof(int *));	//next table
        for(i=0;i<(col*col);i++)
                tab1[i] = (int *)malloc((row+d)*sizeof(int));	//no. of rows increased
//	printf("col=%d\n",col);
	for(i=0;i<col-1;i++)
	{
		l=0;
		for(k=i+1;k<col;k++)
		{
			t=0;
			for(j=d;j<row-1;j++)
			{
				if(tab[i][j]!=tab[k][j])
				{
					t++;		//comparing all bits , we need only 1 bit difference
				}
			}
//			printf("\nbit difference = %d\n",t);
			if(t==1)
			{
				tab[i][row-1]=1;	//rows are selected so, tick = 1
				tab[k][row-1]=1;
				l=0;
				for(p=0;p<cycle;p++)
				{
					tab1[col1][l]=0;
					tab1[col1][l++]=tab[i][p]; //filling up new table (when get matches)
				}
				for(p=0;p<cycle;p++)
					tab1[col1][l++]=tab[k][p];
				p=l;
				for(j=d;j<row-1;j++)
				{
					if(tab[i][j]!=tab[k][j])
						tab1[col1][p] = 2 ;	//for bits which differ
					else
						tab1[col1][p] = tab[i][j] ;
					p++;
				}
				tab1[col1][row+d-1] = 0;	//no tick initialization
				col1++;
			}
		}
	}
			
	printf("\ntab[] = \n");
	for(i=0;i<col;i++)
	{
		for(j=0;j<row;j++)
			printf("%d",tab[i][j]);
		printf("\n");
	}

/*	printf("tab1[] = \n");
	for(i=0;i<col1;i++)
        {
                for(j=0;j<(row+d);j++)
                        printf("%d",tab1[i][j]);
		printf("\n");
        }

*/	for(i=0;i<col;i++)
	{
		if(tab[i][row-1]==0)	// rows which aint paired up , put it in PI array
		{
			PI[col2] = (int *)malloc(row*sizeof(int));
			
			PI[col2][0] = row;
			for(j=1;j<row;j++)
				PI[col2][j]=tab[i][j-1];
			col2++;
		}
	}
	for(i=0;i<col;i++)
	{
		if(tab[i][row-1]==1)
			flag=1;		//if atleast 1 row in tab array is paired up then continue it recursively
	}

	if(flag==1)
	{
//		printf("\nNew recursive table starts \n");
		col2 = table(tab1,row+d,2*d,col1,min,cycle+1,PI,col2);	//new tab = tab1 
		flag=0;
	}
//	free(tab1);
	return col2;
}

	
main()
{
	int k,p,rarray[10][10],u,v,**ePI,**PI,d=1,**tab,l=0,i=0,var=0,j=-1,**arr,eval[MAX],m,flag=1,min=0,col=0,col2=0;
	char bexp[MAX],post1[MAX],post2[MAX-1],post3[MAX],post_3[MAX];	
	printf("Give a boolean expression : ");
	scanf("%[^\n]s",bexp);	//taking input string with spaces

	conversion(bexp,post1);	//postfix conversion
        printf("postfix expression of the input is : ");
	puts(post1);

	while(post1[i]!='\0')	//finding no. of variables (var)
	{
		if( ( (post1[i]>='a')&&(post1[i]<='z') ) || ( (post1[i]>='A')&&(post1[i]<='Z') ) )
		{
			for(m=0;m<=j;m++)	//for checking repeatation
			{
				if(post2[m]==post1[i])	//post2[] contains only variables
				{
					i++;
				}
			}
				if( ( (post1[i]>='a')&&(post1[i]<='z') ) || ( (post1[i]>='A')&&(post1[i]<='Z') ) )
				{
					 for(m=0;m<=j;m++)       //for checking repeatation
                        		{
                                		if(post2[m]==post1[i])  //post2[] contains only variables
                                        	{
							i++;
							flag=0;
						}
                        		}
					if(flag==1)
					{
						post2[++j]=post1[i];
						var++;
					}
					flag=1;
				}
		}
		i++;
	}
	post2[++j]='\0';
	var = j;
        arr = array(var);	//2D array to make table for all possible min terms
	puts(post2);
	toeval(post1,post2,arr,var);

	printf("The 2d array for storing possible min terms is :\n");
        for(i=0;i<COL;i++)
        {
                for(j=0;j<var+2;j++)
                        printf("%d ",arr[i][j]);
                printf("\n");
        }

	for(i=0;i<COL;i++)
        {
                if(arr[i][var+1]==1)    //is a min term
                        min++;		// min- no. of min terms
        }
        tab = (int **)malloc(min*sizeof(int *));	//for storing min terms
        for(i=0;i<min;i++)
                tab[i] = (int *)malloc( (var+2)*sizeof(int));
        for(i=0;i<COL;i++)
        {
                if(arr[i][var+1]==1)    //is a min term
                {
                        tab[col][0]=arr[i][0];
                        l=1;
                        for(m=1;m<=var;m++)
                        {
                                tab[col][l++]=arr[i][m];
                        }
                        tab[col][var+1]=0;      //no tick
                        col++;
                }
        }
	PI = (int **)malloc(col*sizeof(int *));		//for prime implicants
	col2=table(tab,var+2,d,col,min,1,PI,col2);	//makes tables recursively , col2 = no. of columns in PI. PI col0 contains size of corresponding row
	printf("\nPI[][] = \n");

	for(i=0;i<col2;i++)
	{
		for(j=1;j<PI[i][0];j++)
			printf("%d",PI[i][j]) ;
		printf("\n");
	}

	//Essential PIs
	ePI = (int **)malloc((col2+1)*sizeof(int *));
	for(i=0;i<(col2+1);i++)
		ePI[i] = (int *)malloc(min*sizeof(int));
	i=0;
	for(j=0;j<COL;j++)
	{
		if(arr[j][var+1]==1)	//if is a min term
			ePI[0][i++] = arr[j][0];	// 0th row (with all min terms)
	}

	for(i=0;i<min;i++)
	{
		for(j=1;j<=col2;j++)
			ePI[j][i]=0;	//initialization
	}
	for(i=1;i<(col2+1);i++)
	{
		for(l=1;l<(PI[i-1][0]-var);l++)	//PIs in binary are from 1 to PI[i-1][0]-var
		{
			for(j=0;j<min;j++)
			{
				if(PI[i-1][l]==ePI[0][j])
					ePI[i][j]=1;		
			}
		}
	}
//	printf("\nmin = %d ",min);
	printf(" ePI[][] = \n");
	for(j=0;j<(col2+1);j++)
	{
        	for(i=0;i<min;i++)
                	printf("%d ",ePI[j][i]);
		printf("\n");
	}

	u=0;
	for(i=0;i<min;i++)	//finding no. of 1's in each col , if no. of 1's = 1 , that row is selected and stored in rarray
	{
		l=0;
		for(j=1;j<(col2+1);j++)
		{
			if(ePI[j][i]==1)
			{
				l++;
				p=j;
			}
		}
//		printf("l=%d\n",l);
		if(l==1)
		{
			v=1;
			printf("\nPI[%d][0] = %d\n",p-1,PI[p-1][0]);
			for(m=PI[p-1][0]-var;m<PI[p-1][0];m++)
				rarray[u][v++]=PI[p-1][m];
			rarray[u][0] = v;
			for(m=0;m<min;m++)
			{
				if(ePI[p][m]==1)
					ePI[0][m]=-1;
			}
			u++;
		}
	}

	for(i=0;i<min;i++)
	{
		if(ePI[0][i]!=-1)
		{
			for(j=1;j<=col2;j++)
			{
				if(ePI[j][i]==1)
				{
					v=1;
					for(m=PI[j-1][0]-var;m<PI[j-1][0];m++)
                                		rarray[u][v++]=PI[j-1][m];
                        		rarray[u][0] = v;
					ePI[0][i]=-1;
					for(k=0;k<min;k++)
					{
						if(ePI[j][k]==1)
							ePI[0][k]=-1;
					}
					u++;
					break;
				}
			}
		}
	}
	
//	printf("\nno. of col in rarray =%d\n",u);
	printf("rarray[] = \n");
	for(i=0;i<u;i++)
	{

		for(j=0;j<rarray[i][0];j++)
			printf("%d ",rarray[i][j]);
		printf("\n");
	}

	flag=0;
	for(i=0;i<u-1;i++)
	{
		for(l=(i+1);l<u;l++)
		{
			for(j=1;j<rarray[i][0];j++)
			{
				if(rarray[i][j]!=rarray[l][j])	//to avoid repeatation
					flag=1;
			}
			if(flag==0)
				rarray[l][0]=0;
			flag=0;
		}
	}
	k=0;flag=1;
	printf("rarray[] = \n");
        for(i=0;i<u;i++)
        {
                for(j=0;j<rarray[i][0];j++)
		{
			flag=0;
                        printf("%d ",rarray[i][j]);
		}
		if(flag==0)
			k++;
		flag=1;
                printf("\n");
        }

	l=0;
	m=0; flag=0;
	for(i=0;i<k;i++)		//post3[] contains final result (after adding '~' '*' '+' wherever required)
	{
		for(j=1;j<rarray[i][0];j++)
		{
			if(rarray[i][j]==1)
			{
				if( (flag==1)&&(post3[m-1]!='+') )
					post3[m++]='*';
				post3[m++]=post2[l];
				flag=1;
				

			}
			if(rarray[i][j]==0)
			{
				if( (flag==1)&&(post3[m-1]!='+') )
					post3[m++]='*';
				post3[m++]='~';
				post3[m++]=post2[l];
				flag=1;
			}
			l++;
			
		}
		if(flag==1)
			post3[m++]='+';
		l=0;
	}
	post3[m-1]='\0';

	printf("\npost3[] = ");
	for(i=0;i<m-1;i++)
		printf("%c",post3[i]);
	printf("\n");
	conversion(post3,post_3);
	printf("post_3 = %s\n",post_3);
	make_circuit(post_3);
	free(tab);
	free(arr);
	free(ePI);
}
