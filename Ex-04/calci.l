digit [0-9]+|([0-9]*)"."([0-9]+)
add "+"
sub "-"
mul "*"
div "/"
%{
	#include<stdio.h>
	int op=0,i;
	float a,b;
%}

%%
{add} {op=1;}
{sub} {op=2;}
{mul} {op=3;}
{div} {op=4;}
{digit} {cal();}
\n {printf("The Answer = %f\n\n",a);}
%%
cal()
{
	if(op==0) a=atof(yytext);
	else 
	{
		b=atof(yytext);
		switch(op)
		{
			case 1:a=a+b;break;
			case 2:a=a-b;break;
			case 3:a=a*b;break;
			case 4:a=a/b;break;
		}
		op=0;
	}
}

int main()
{
	yylex();
	return 0;
}
int yywrap(){return 1;}