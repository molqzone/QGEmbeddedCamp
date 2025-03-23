/**
 * @file main.c
 * @brief Integer calculator for arithmetic expressions based on linked stack
 * @note Supports integers, operations (+,-,*,/), and parentheses
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "linkedStack/Include/linkedStack.h"

#define MAX_EXPR_LEN 100    /**< Maximum expression length */
#define ERROR_VALUE -999999  /**< Error value identifier */

/* Function declarations */
int calculateExpression(const char* expr);
bool isOperator(char ch);
int getPriority(char op);
bool performOperation(LinkedStack* numStack, LinkedStack* opStack);
void clearInputBuffer(void);
bool isValidExpression(const char* expr);

/**
 * @brief Main function
 * @return Program exit status code
 */
int main() {
    char expr[MAX_EXPR_LEN];
    int result;
    bool continueCalc = true;
    
    printf("Welcome to the Arithmetic Calculator\n");
    printf("Supported operations: Addition(+), Subtraction(-), Multiplication(*), Division(/), Parentheses()\n");
    printf("Type \"exit\" to quit the program\n");
    
    while (continueCalc) {
        printf("\nPlease enter an expression: ");
        if (fgets(expr, MAX_EXPR_LEN, stdin) == NULL) {
            printf("Input error, please try again\n");
            continue;
        }
        
        // Remove newline character
        expr[strcspn(expr, "\n")] = '\0';
        
        // Check for exit command
        if (strcmp(expr, "exit") == 0) {
            continueCalc = false;
            printf("Exiting calculator. Thank you for using!\n");
            continue;
        }
        
        // Handle empty input
        if (strlen(expr) == 0) {
            printf("Expression cannot be empty, please try again\n");
            continue;
        }
        
        // Validate expression format
        if (!isValidExpression(expr)) {
            printf("Invalid expression format, please check and try again\n");
            continue;
        }
        
        // Calculate expression
        result = calculateExpression(expr);
        
        // Display result
        if (result != ERROR_VALUE) {
            printf("Result: %d\n", result);
        } else {
            printf("Calculation error, please check your expression\n");
        }
    }
    
    return 0;
}

/**
 * @brief Validate expression format
 * @param expr Expression to validate
 * @return true if expression format is correct, false otherwise
 */
bool isValidExpression(const char* expr) {
    int i = 0;
    int parenCount = 0;
    bool lastWasOp = true; // Expression start is considered as preceding an operator
    
    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        
        if (expr[i] == '(') {
            parenCount++;
            lastWasOp = true;
        } else if (expr[i] == ')') {
            parenCount--;
            if (parenCount < 0) {
                return false; // Parentheses do not match
            }
            lastWasOp = false;
        } else if (isdigit(expr[i])) {
            lastWasOp = false;
            // Skip entire number
            while (isdigit(expr[i])) {
                i++;
            }
            continue;
        } else if (isOperator(expr[i])) {
            if (lastWasOp && expr[i] != '+' && expr[i] != '-') {
                return false; // No consecutive non-positive/negative sign operators allowed
            }
            lastWasOp = true;
        } else {
            return false; // Invalid character
        }
        i++;
    }
    
    return parenCount == 0 && !lastWasOp; // Parentheses must match, expression cannot end with an operator
}

/**
 * @brief Calculate expression value
 * @param expr Expression to calculate
 * @return Calculated result, ERROR_VALUE if calculation error
 */
int calculateExpression(const char* expr) {
    LinkedStack numStack;  // Number stack
    LinkedStack opStack;   // Operator stack
    int i = 0;
    bool lastWasOp = true; // Used to determine positive/negative sign
    int op, result;
    
    stackInit(&numStack);
    stackInit(&opStack);
    
    while (expr[i] != '\0') {
        // Skip spaces
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        
        // Process number
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            stackPush(&numStack, num);
            lastWasOp = false;
            continue;
        }
        
        // Process left parenthesis
        if (expr[i] == '(') {
            stackPush(&opStack, (int)'(');
            lastWasOp = true;
            i++;
            continue;
        }
        
        // Process right parenthesis
        if (expr[i] == ')') {
            // Calculate all operations within parentheses
            while (!stackIsEmpty(&opStack)) {
                stackTop(&opStack, &op);
                if (op == '(') {
                    stackPop(&opStack); // Pop left parenthesis
                    break;
                }
                if (!performOperation(&numStack, &opStack)) {
                    stackDestroy(&numStack);
                    stackDestroy(&opStack);
                    return ERROR_VALUE;
                }
            }
            lastWasOp = false;
            i++;
            continue;
        }
        
        // Process operator
        if (isOperator(expr[i])) {
            char currentOp = expr[i];
            
            // Process unary positive/negative sign
            if ((currentOp == '+' || currentOp == '-') && lastWasOp) {
                if (currentOp == '-') {
                    stackPush(&numStack, 0); // Push 0 for subtraction processing
                }
                // Unary + sign is not treated specially
                if (currentOp == '-') {
                    stackPush(&opStack, (int)currentOp);
                }
                lastWasOp = true;
                i++;
                continue;
            }
            
            // Process regular operators
            while (!stackIsEmpty(&opStack)) {
                stackTop(&opStack, &op);
                
                if (op == '(' || getPriority(currentOp) > getPriority((char)op)) {
                    break;
                }
                
                if (!performOperation(&numStack, &opStack)) {
                    stackDestroy(&numStack);
                    stackDestroy(&opStack);
                    return ERROR_VALUE;
                }
            }
            
            stackPush(&opStack, (int)currentOp);
            lastWasOp = true;
        }
        
        i++;
    }
    
    // Process remaining operators
    while (!stackIsEmpty(&opStack)) {
        stackTop(&opStack, &op);
        
        if (op == '(') {
            printf("Expression error: Mismatched parentheses\n");
            stackDestroy(&numStack);
            stackDestroy(&opStack);
            return ERROR_VALUE;
        }
        
        if (!performOperation(&numStack, &opStack)) {
            stackDestroy(&numStack);
            stackDestroy(&opStack);
            return ERROR_VALUE;
        }
    }
    
    // Get final result
    if (stackSize(&numStack) == 1) {
        stackTop(&numStack, &result);
        stackDestroy(&numStack);
        stackDestroy(&opStack);
        return result;
    } else {
        printf("Expression error: Invalid expression format\n");
        stackDestroy(&numStack);
        stackDestroy(&opStack);
        return ERROR_VALUE;
    }
}

/**
 * @brief Determine if character is an operator
 * @param ch Character to check
 * @return true if character is an operator, false otherwise
 */
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

/**
 * @brief Get operator priority
 * @param op Operator
 * @return Priority value, higher value means higher priority
 */
int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

/**
 * @brief Execute operation
 * @param numStack Number stack
 * @param opStack Operator stack
 * @return true if operation successful, false otherwise
 */
bool performOperation(LinkedStack* numStack, LinkedStack* opStack) {
    int num1, num2, result;
    int op;
    
    // Check element count in stack
    if (stackSize(numStack) < 2) {
        printf("Expression error: Operator missing operands\n");
        return false;
    }
    
    // Pop two operands and one operator
    stackTop(opStack, &op);
    stackPop(opStack);
    
    stackTop(numStack, &num2);
    stackPop(numStack);
    stackTop(numStack, &num1);
    stackPop(numStack);
    
    // Execute operation
    switch ((char)op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero\n");
                return false;
            }
            result = num1 / num2;
            break;
        default:
            printf("Error: Unknown operator %c\n", (char)op);
            return false;
    }
    
    // Push result back to stack
    stackPush(numStack, result);
    return true;
}

/**
 * @brief Clear input buffer
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
