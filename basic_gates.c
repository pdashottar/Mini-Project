/*Mini Project - Task 1

This program takes expression involving only 1 operation of (AND/OR/NOT)

X=A+B
X=A*B
X=~A

Output will be an image in svg which shows the circuit diagram of it.
For drawing the circuit, I have considered a reference point so that I can locate the points w.r.t the reference point. It will help in making larger circuits.*/

#include<stdio.h>
#define WRITEFILE "basic_gates.svg"

main()
{
	char e[4];
	FILE *fp;

	printf("Give a boolean expression involving only 1 operator (without spaces): ");
	scanf("%s",e);

	fp=fopen(WRITEFILE,"w");
	fprintf(fp,"<svg height=\"500\" width=\"500\">\n");

	//Make background rectangle
	fprintf(fp,"<rect width=\"499\" height=\"499\" style=\"fill:rgb(255,255,255);stroke-width:1;stroke:rgb(0,0,0)\" />\n");

	if(e[2]=='~')
	{
		//Printing operand
		fprintf(fp,"<text x=\"100\" y=\"100\" fill=\"black\" font-size=\"30\">%c</text>\n",e[3]);

		//Making line
		fprintf(fp,"<line x1=\"115\" y1=\"115\" x2=\"250\" y2=\"115\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

		//Make a triangle
		fprintf(fp,"<polygon points=\"250,80 250,150 300,115\" style=\"fill:white;stroke:black;stroke-width:3\" />\n");

		//Make not (circle)
		fprintf(fp,"<circle cx=\"305\" cy=\"115\" r=\"5\" stroke=\"black\" stroke-width=\"3\" fill=\"white\" />\n");

		//Make line
		fprintf(fp,"<line x1=\"310\" y1=\"115\" x2=\"450\" y2=\"115\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

		//Writing text
		fprintf(fp,"<text x=\"452\" y=\"100\" fill=\"black\" font-size=\"30\">%c</text>\n",e[0]);
	}
	else if(e[3]=='*')
	{
		//Printing operand 1
                fprintf(fp,"<text x=\"100\" y=\"100\" fill=\"black\" font-size=\"30\">%c</text>\n",e[2]);

                //Making line
                fprintf(fp,"<line x1=\"115\" y1=\"115\" x2=\"250\" y2=\"115\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

		 //Printing operand
                fprintf(fp,"<text x=\"100\" y=\"150\" fill=\"black\" font-size=\"30\">%c</text>\n",e[4]);

                //Making line
                fprintf(fp,"<line x1=\"115\" y1=\"165\" x2=\"250\" y2=\"165\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

		//Making gate
                fprintf(fp,"<line x1=\"250\" y1=\"105\" x2=\"250\" y2=\"175\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

                fprintf(fp,"<line x1=\"250\" y1=\"105\" x2=\"300\" y2=\"105\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");
                fprintf(fp,"<line x1=\"250\" y1=\"175\" x2=\"300\" y2=\"175\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

		fprintf(fp,"<path d=\"M300 105 Q 335 135 300 175\" stroke=\"black\" stroke-width=\"3\"  fill=\"transparent\"/>\n");

		//Print output
		fprintf(fp,"<text x=\"395\" y=\"120\" fill=\"black\" font-size=\"30\">%c</text>\n",e[0]);

		fprintf(fp,"<line x1=\"319\" y1=\"135\" x2=\"400\" y2=\"135\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");
	}
	else if(e[3]=='+')
	{
		 //Printing operand 1
                fprintf(fp,"<text x=\"100\" y=\"100\" fill=\"black\" font-size=\"30\">%c</text>\n",e[2]);

                //Making line
                fprintf(fp,"<line x1=\"115\" y1=\"115\" x2=\"250\" y2=\"115\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

                 //Printing operand
                fprintf(fp,"<text x=\"100\" y=\"150\" fill=\"black\" font-size=\"30\">%c</text>\n",e[4]);

                //Making line
                fprintf(fp,"<line x1=\"115\" y1=\"165\" x2=\"250\" y2=\"165\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

		//Making Gate
		fprintf(fp,"<path d=\"M250 175 Q 260 140 250 105\" stroke=\"black\" stroke-width=\"3\"  fill=\"transparent\"/>\n");
		fprintf(fp,"<path d=\"M250 105 Q 300 100 350 140\" stroke=\"black\" stroke-width=\"3\"  fill=\"transparent\"/>\n");
		fprintf(fp,"<path d=\"M250 175 Q 300 180 350 140\" stroke=\"black\" stroke-width=\"3\"  fill=\"transparent\"/>\n");

		//Make line
		fprintf(fp,"<line x1=\"350\" y1=\"140\" x2=\"450\" y2=\"140\" style=\"stroke:rgb(0,0,0);stroke-width:3\" />\n");

		 //Print output
                fprintf(fp,"<text x=\"445\" y=\"125\" fill=\"black\" font-size=\"30\">%c</text>\n",e[0]);

	}
	else
	{
		printf("This expression will not work for this program\n:");
	}
	fprintf(fp,"\n</svg>");
}
