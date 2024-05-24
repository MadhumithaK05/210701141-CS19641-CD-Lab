%{
	#include<stdio.h>
	#include<string.h>
	int c=0;
%}

%%
([a-zA-Z0-9])* {c++;}
"\n" {printf("%d\n",c);c=0;}
%%
int main()
{
	yylex();
	return 0;
}
int yywrap(void)
{}