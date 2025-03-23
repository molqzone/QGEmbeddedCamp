/**
 * @file linkedStack.c
 * @brief 基于链表的栈实现
 */

#include "linkedStack.h"
#include <stdlib.h>
#include <assert.h>

/**
 * @brief 初始化栈
 * @param stack 指向栈的指针
 */
void stackInit(LinkedStack* stack) {
    assert(stack != NULL);
    
    stack->top = NULL;
    stack->size = 0;
}

/**
 * @brief 检查栈是否为空
 * @param stack 指向栈的指针
 * @return 如果栈为空返回true，否则返回false
 */
bool stackIsEmpty(const LinkedStack* stack) {
    assert(stack != NULL);
    
    return stack->top == NULL;
}

/**
 * @brief 获取栈的大小
 * @param stack 指向栈的指针
 * @return 栈中元素的数量
 */
int stackSize(const LinkedStack* stack) {
    assert(stack != NULL);
    
    return stack->size;
}

/**
 * @brief 将元素压入栈顶
 * @param stack 指向栈的指针
 * @param element 要压入栈的元素
 * @return 操作成功返回true，失败返回false
 */
bool stackPush(LinkedStack* stack, StackElement element) {
    assert(stack != NULL);
    
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        return false;  // 内存分配失败
    }
    
    newNode->data = element;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    
    return true;
}

/**
 * @brief 弹出栈顶元素
 * @param stack 指向栈的指针
 * @return 操作成功返回true，失败返回false
 */
bool stackPop(LinkedStack* stack) {
    assert(stack != NULL);
    
    if (stackIsEmpty(stack)) {
        return false;  // 栈为空，无法弹出元素
    }
    
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    
    return true;
}

/**
 * @brief 获取栈顶元素
 * @param stack 指向栈的指针
 * @param element 用于存储栈顶元素的指针
 * @return 操作成功返回true，失败返回false
 */
bool stackTop(const LinkedStack* stack, StackElement* element) {
    assert(stack != NULL);
    assert(element != NULL);
    
    if (stackIsEmpty(stack)) {
        return false;  // 栈为空，无法获取栈顶元素
    }
    
    *element = stack->top->data;
    return true;
}

/**
 * @brief 清空栈
 * @param stack 指向栈的指针
 */
void stackClear(LinkedStack* stack) {
    assert(stack != NULL);
    
    while (!stackIsEmpty(stack)) {
        stackPop(stack);
    }
}

/**
 * @brief 销毁栈
 * @param stack 指向栈的指针
 */
void stackDestroy(LinkedStack* stack) {
    assert(stack != NULL);
    
    stackClear(stack);
    // 栈结构本身通常由调用者负责释放，这里只清理节点
} 