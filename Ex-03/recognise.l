letter [a-zA-Z]
digit [0-9]
id [_|a-zA-Z]
ao [+|-|*|/|%]
ro [<|>|<=|>=|==]
%{
	#include<stdio.h>
	int n=0;
%}

%%
void {printf("%s is a return type\n",yytext);}
{letter}*[(][)] {printf("%s is a function\n",yytext);}
if|else|int|float|printf {printf("%s is a keyword\n",yytext);}
{id}({id}|{digit})* {printf("%s is an Identifier\n",yytext);}
{digit}* {printf("%s is a number\n",yytext);}
{ao} {printf("%s is an Arithmetic Operator\n",yytext);}
{ro} {printf("%s is a Relational Operator\n",yytext);}
; {printf("%s is a Delimiter\n",yytext);}
\n {n++;}
%%
int main()
{
	printf("Enter Code : ");
	yylex();
	return 0;
}
int yywrap()
{
	return 1;
}