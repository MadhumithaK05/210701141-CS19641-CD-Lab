#include <stdio.h>
#include<string.h>
#include<ctype.h>
int main() {
    
    char s[100];
    fgets(s,100,stdin);

    for(int i=0;i<strlen(s);i++)
    {
        char x=s[i];
        switch(x)
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '=':
                printf("%c Operator\n",x);
                break;
            case ';':
            case ',':
                printf("%c Delimiter\n",x);
                break;
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
                printf("%c Symbol\n",x);
        }
        if(isalpha(x))
        {
            printf("%c Identifier\n",x);
        }
    }

    return 0;
}
