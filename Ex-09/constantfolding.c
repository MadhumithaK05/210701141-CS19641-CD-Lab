#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VAR_COUNT 100
#define MAX_EXPR_LENGTH 100

// Structure to store variable values
typedef struct {
    char name[10];
    int value;
    int is_constant;
} Variable;

// Array to store variables
Variable variables[MAX_VAR_COUNT];
int var_count = 0;

// Function to check if a string is a number
int is_number(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to evaluate a simple arithmetic expression with two operands
int evaluate_expression(int left, char op, int right) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        default: printf("Unsupported operator\n"); exit(1);
    }
}

// Function to get the value of a variable
int get_variable_value(const char* var_name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, var_name) == 0) {
            return variables[i].value;
        }
    }
    printf("Variable %s not found\n", var_name);
    exit(1);
}

// Function to check if a variable is constant
int is_variable_constant(const char* var_name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, var_name) == 0) {
            return variables[i].is_constant;
        }
    }
    return 0;
}

// Function to add or update a variable
void add_variable(const char* var_name, int value, int is_constant) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, var_name) == 0) {
            variables[i].value = value;
            variables[i].is_constant = is_constant;
            return;
        }
    }
    strcpy(variables[var_count].name, var_name);
    variables[var_count].value = value;
    variables[var_count].is_constant = is_constant;
    var_count++;
}

// Function to perform constant folding
void constant_folding(char* expr) {
    char var_name[10], left_operand[10], right_operand[10], operator;
    int left, right, result;

    // Parse the assignment statement
    if (sscanf(expr, "%s = %s %c %s", var_name, left_operand, &operator, right_operand) == 4) {
        // Check if the left operand is a constant or a variable with a constant value
        if (is_number(left_operand)) {
            left = atoi(left_operand);
        } else if (is_variable_constant(left_operand)) {
            left = get_variable_value(left_operand);
        } else {
            printf("No optimization applied: %s\n", expr);
            return;
        }

        // Check if the right operand is a constant or a variable with a constant value
        if (is_number(right_operand)) {
            right = atoi(right_operand);
        } else if (is_variable_constant(right_operand)) {
            right = get_variable_value(right_operand);
        } else {
            printf("No optimization applied: %s\n", expr);
            return;
        }

        // Evaluate the expression
        result = evaluate_expression(left, operator, right);

        // Add or update the variable with the optimized value
        add_variable(var_name, result, 1);

        // Print the optimized expression
        printf("Optimized expression: %s = %d\n", var_name, result);
    } else if (sscanf(expr, "%s = %s", var_name, left_operand) == 2) {
        // Check if the assignment is a constant value
        if (is_number(left_operand)) {
            int value = atoi(left_operand);
            add_variable(var_name, value, 1);
            printf("Assignment: %s = %d\n", var_name, value);
        } else {
            printf("No optimization applied: %s\n", expr);
        }
    } else {
        printf("Invalid expression: %s\n", expr);
    }
}

int main() {
    char expr[MAX_EXPR_LENGTH];

    printf("Enter assignment statements (enter 'exit' to stop):\n");

    while (1) {
        printf("> ");
        if (fgets(expr, sizeof(expr), stdin) == NULL) {
            break;
        }

        // Remove the newline character from the input if present
        size_t len = strlen(expr);
        if (len > 0 && expr[len - 1] == '\n') {
            expr[len - 1] = '\0';
        }

        // Check if the user wants to exit
        if (strcmp(expr, "exit") == 0) {
            break;
        }

        constant_folding(expr);
    }

    return 0;
}
