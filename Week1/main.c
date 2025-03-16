#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void printNode(ElemType e) {
    printf("%d -> ", e);
}

LNode* createNode(ElemType data) {
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Status createListFromInput(LinkedList* L) {
    int n, data;
    printf("Enter the number of nodes to create: ");
    scanf("%d", &n);
    
    if (n < 0) {
        printf("Number of nodes cannot be negative!\n");
        return ERROR;
    }
    
    if (InitList(L) == ERROR) {
        printf("List initialization failed!\n");
        return ERROR;
    }
    
    LNode* current = *L;
    printf("Please enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        LNode* newNode = createNode(data);
        if (newNode == NULL) {
            return ERROR;
        }
        InsertList(current, newNode);
        current = newNode;
    }
    return SUCCESS;
}

void printMenu() {
    printf("\n=== Linked List Operations Menu ===\n");
    printf("1. Create New List\n");
    printf("2. Swap Odd-Even Nodes\n");
    printf("3. Find Middle Node\n");
    printf("4. Check if List has Loop\n");
    printf("5. Reverse List (Non-recursive)\n");
    printf("6. Reverse List (Recursive)\n");
    printf("7. Print List\n");
    printf("0. Exit Program\n");
    printf("Choose an operation [0-7]: ");
}

int main() {
    LinkedList L = NULL;
    int choice;
    ElemType midData;
    LNode* midNode;
    
    while (1) {
        printMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 0:
                if (L != NULL) {
                    DestroyList(&L);
                }
                printf("Program terminated.\n");
                return 0;
                
            case 1:
                if (L != NULL) {
                    DestroyList(&L);
                }
                if (createListFromInput(&L) == SUCCESS) {
                    printf("List created successfully! Current list: ");
                    TraverseList(L, printNode);
                    printf("NULL\n");
                }
                break;
                
            case 2:
                if (L == NULL) {
                    printf("Please create a list first!\n");
                    break;
                }
                L = ReverseEvenList(&L);
                printf("List after odd-even swap: ");
                TraverseList(L, printNode);
                printf("NULL\n");
                break;
                
            case 3:
                if (L == NULL) {
                    printf("Please create a list first!\n");
                    break;
                }
                midNode = FindMidNode(&L);
                if (midNode != NULL) {
                    printf("Middle node value: %d\n", midNode->data);
                }
                break;
                
            case 4:
                if (L == NULL) {
                    printf("Please create a list first!\n");
                    break;
                }
                if (IsLoopList(L)) {
                    printf("This is a circular linked list!\n");
                } else {
                    printf("This is not a circular linked list.\n");
                }
                break;
                
            case 5:
                if (L == NULL) {
                    printf("Please create a list first!\n");
                    break;
                }
                if (ReverseList(&L) == SUCCESS) {
                    printf("List reversed successfully! Current list: ");
                    TraverseList(L, printNode);
                    printf("NULL\n");
                }
                break;
                
            case 6:
                if (L == NULL) {
                    printf("Please create a list first!\n");
                    break;
                }
                L = ReverseList_Recursive(L);
                printf("List recursively reversed successfully! Current list: ");
                TraverseList(L, printNode);
                printf("NULL\n");
                break;
                
            case 7:
                if (L == NULL) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Current list: ");
                TraverseList(L, printNode);
                printf("NULL\n");
                break;
                
            default:
                printf("Invalid choice, please try again!\n");
        }
    }
    
    return 0;
}