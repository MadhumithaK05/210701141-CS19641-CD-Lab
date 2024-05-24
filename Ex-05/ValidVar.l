%{
	#include<stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z_0-9]* {printf("%s is a Valid Variable\n",yytext);}
[0-9][a-zA-Z_][a-zA-Z_0-9]* {printf("%s is an Invalid Variable\n",yytext);}
. {printf("%s is an Invalid Variable\n",yytext);}
\n {/*do nothing*/}
%%
int main()
{
	yylex();
	return 0;
}
int yywrap(){return 1;}