#include <stdio.h>
#include <string.h>
#include <ctype.h>

int iskey(char t[]) {
    char key[32][15] = {"int","auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    for(int i = 0; i < 32; i++) {
        if(strcmp(key[i], t) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char s[1000];
    printf("Enter C code (press Ctrl+D to end input):\n");
    while (fgets(s, sizeof(s), stdin) != NULL) {
        char temp[30];
        int j = 0;
        printf("\n");
        for(int i = 0; i < strlen(s); i++) {
            char x = s[i];
            switch(x) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '=':
                case ';':
                case ',':
                case '(':
                case ')':
                case '{':
                case '}':
                case '[':
                case ']':
                    if(j != 0) {
                        temp[j] = '\0';
                        j = 0;
                        if(iskey(temp) == 1 && strcmp(temp, "") != 0) {
                            printf("%s Keyword\n", temp);
                        }
                        else if(strcmp(temp, "") != 0) {
                            printf("%s Identifier\n", temp);
                        }
                    }
                    if(x != ' ') {
                        printf("%c %s\n", x, (x == '=' ? "Operator" : "Delimiter"));
                    }
                    break;
                default:
                    if(isalpha(x)) {
                        temp[j++] = x;
                    }
                    else if((x == ' ' || x == ';') && j != 0) {
                        temp[j] = '\0';
                        j = 0;
                        if(iskey(temp) == 1 && strcmp(temp, "") != 0) {
                            printf("%s Keyword\n", temp);
                        }
                        else if(strcmp(temp, "") != 0) {
                            printf("%s Identifier\n", temp);
                        }
                    }
            }
        }
    }
    return 0;
}
