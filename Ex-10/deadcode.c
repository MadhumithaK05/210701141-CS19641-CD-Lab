#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STATEMENTS 100
#define MAX_LENGTH 100

typedef struct {
    char left[MAX_LENGTH];
    char right[MAX_LENGTH];
} Statement;

int statement_count = 0;
Statement statements[MAX_STATEMENTS];
int used[MAX_STATEMENTS];

void read_statements() {
    printf("Enter assignment statements (type 'end' to finish):\n");
    while (1) {
        char input[MAX_LENGTH];
        fgets(input, MAX_LENGTH, stdin);
        if (strcmp(input, "end\n") == 0) {
            break;
        }
        sscanf(input, "%s = %[^\n]", statements[statement_count].left, statements[statement_count].right);
        used[statement_count] = 0;
        statement_count++;
    }
}

void print_statements() {
    for (int i = 0; i < statement_count; i++) {
        printf("%s = %s\n", statements[i].left, statements[i].right);
    }
}

void eliminate_dead_code() {
    // Mark last occurrence of each variable on the left side
    for (int i = 0; i < statement_count; i++) {
        for (int j = 0; j < statement_count; j++) {
            if (strstr(statements[i].right, statements[j].left)) {
                used[j] = 1;
            }
        }
    }

    // Remove unused statements
    int new_count = 0;
    for (int i = 0; i < statement_count; i++) {
        if (used[i] || i == statement_count - 1) {
            statements[new_count++] = statements[i];
        }
    }
    statement_count = new_count;
}

void eliminate_common_subexpressions() {
    for (int i = 0; i < statement_count; i++) {
        for (int j = i + 1; j < statement_count; j++) {
            if (strcmp(statements[i].right, statements[j].right) == 0) {
                // Replace right side of j with the left side of i
                strcpy(statements[j].right, statements[i].left);
            }
        }
    }
}

int main() {
    read_statements();

    printf("\nIntermediate Code:\n");
    print_statements();

    eliminate_dead_code();
    printf("\nAfter Dead Code Elimination:\n");
    print_statements();

    eliminate_common_subexpressions();
    printf("\nAfter Eliminating Common Subexpressions:\n");
    print_statements();

    return 0;
}
