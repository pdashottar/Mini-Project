//Mini Project

#include<stdio.h>
#define WRITEFILE "gate.svg"
FILE *fp;
struct coordinate
{
        int x,y;
}stk[MAX];
int ttop=-1;

void text(int x,int y,char c)
{
        fprintf(fp,"<text x=\"%d\" y=\"%d\" fill=\"black\" font-size=\"20\">%c</text>\n",x,y-2,c);
}
void line(int x1,int y1,int x2,int y2)
{
        fprintf(fp,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n",x1,y1,x2,y2);
}

void not(int x,int y)
{
		line(x,y,x+20,y);
                //Make a triangle
                fprintf(fp,"<polygon points=\"%d,%d %d,%d %d,%d\" style=\"fill:white;stroke:black;stroke-width:2\" />\n",x+20,y-10,x+20,y+10,x+30,y);

                //Make not (circle)
                fprintf(fp,"<circle cx=\"%d\" cy=\"%d\" r=\"2\" stroke=\"black\" stroke-width=\"1\" fill=\"white\" />\n",x+33,y);
        
                line(x+35,y,x+40,y);
}

struct coordinate and(int x,int y1,int y2)
{
	int ym;
	struct coordinate t;
	ym = (y1+y2)/2;
                //Making gate
		line(x,y1,x,y2);

		line(x,y1,x+25,y1);
		line(x,y2,x+25,y2);

                fprintf(fp,"<path d=\"M%d %d Q %d %d %d %d\" stroke=\"black\" stroke-width=\"2\"  fill=\"transparent\"/>\n",x+25,y2,x+50,ym,x+25,y1);
		line(x+38,ym,x+50,ym);

	t.x=x+50;
	t.y = ym ;
		return t;
}

struct coordinate or(int x,int y1,int y2)
{
	int ym;
	struct coordinate t;
	ym = (y1+y2)/2;
                //Making Gate
                fprintf(fp,"<path d=\"M%d %d Q %d %d %d %d\" stroke=\"black\" stroke-width=\"1\"  fill=\"transparent\"/>\n",x,y2,x+5,ym,x,y1);
                fprintf(fp,"<path d=\"M%d %d Q %d %d %d %d\" stroke=\"black\" stroke-width=\"1\"  fill=\"transparent\"/>\n",x,y1,x+20,y1,x+40,ym);
                fprintf(fp,"<path d=\"M%d %d Q %d %d %d %d\" stroke=\"black\" stroke-width=\"1\"  fill=\"transparent\"/>\n",x,y2,x+20,y2+10,x+40,ym);

		line(x+40,ym,x+50,ym);
	t.x = x+50;
	t.y = ym;
	return t;
}

void ppush(struct coordinate t)
{
	if(ttop==MAX)
		printf("Stack overflowed\n");
	else
	{
		ttop++;
		stk[ttop].x = t.x;
		stk[ttop].y = t.y;
//		printf("\nPushed value : %d,%d \n",stk[ttop].x,stk[ttop].y);
	}
}
struct coordinate ppop()
{
	struct coordinate t;
	if(ttop==-1)
		printf("stack underflowed\n");
	else
	{
		t.x = stk[ttop].x;
		t.y = stk[ttop].y;
//		printf("\nPopped value : %d,%d \n",stk[ttop].x,stk[ttop].y);

		ttop--;
		return t;
	}
}

void make_circuit(char *p)
{
	int x,y=100,i=0,j=0,k;
	struct coordinate co[MAX],t,r;
	fp=fopen(WRITEFILE,"w");
	fprintf(fp,"<svg height=\"500\" width=\"500\">\n");

	//Make background rectangle
	fprintf(fp,"<rect width=\"500\" height=\"500\" style=\"fill:rgb(255,255,255);stroke-width:1;stroke:rgb(0,0,0)\" />\n");
	
	x=20;y=20;
	
	while(p[i]!='\0')	//p is post expression
	{
		if( ( (p[i]>='a')&&(p[i]<='z') )||( (p[i]>='A')&&(p[i]<='Z') )||(p[i]=='~') )
		{
			if(p[i]=='~')
			{
				text(x,y,p[++i]);
				not(x,y);
			}
			else
			{
				text(x,y,p[i]);
				line(x,y,x+40,y);
			}
			co[j].x=x+40;
			co[j++].y=y;
			y+=40;
		}
		i++;
	}

	printf("\nco[]=\n");
	for(i=0;i<j;i++)
		printf("%d,%d\n",co[i].x,co[i].y);

	//Stack operation
	i=0;k=0;
	while(p[i]!='\0')
	{
		if( ( (p[i]>='a')&&(p[i]<='z') )||( (p[i]>='A')&&(p[i]<='Z') ) )
		{
			ppush(co[k]);
			k++;
		}
		else if(p[i]=='+')
		{
			t = ppop();
			r = ppop();
			if(t.x>r.x)
			{
				line(r.x,r.y,t.x,r.y);
				r.x = t.x ;
			}
			else if(t.x<r.x)
                        {
                                line(t.x,t.y,r.x,t.y);
                                t.x = r.x ;
                        }

//			printf("\nor input coordinates : %d,%d . %d,%d\n",t.x,t.y,r.x,r.y);
			t = or(t.x,t.y,r.y);
			ppush(t);
		}
		else if(p[i]=='*')
		{
			t = ppop();
                        r = ppop();
			 if(t.x>r.x)
                        {
                                line(r.x,r.y,t.x,r.y);
                                r.x = t.x ;
                        }
                        else if(t.x<r.x)
                        {
                                line(t.x,t.y,r.x,t.y);
                                t.x = r.x ;
                        }

//			printf("\nand input coordinates : %d,%d . %d,%d\n",t.x,t.y,r.x,r.y);
                        t = and(t.x,t.y,r.y);
                        ppush(t);
		}
		i++;
	}
	fprintf(fp,"\n</svg>");
}
