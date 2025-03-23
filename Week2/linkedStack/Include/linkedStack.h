/**
 * @file linkedStack.h
 * @brief 基于链表的栈实现的接口定义
 */

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <stdbool.h>

/**
 * @brief 栈中元素的数据类型
 */
typedef int StackElement;

/**
 * @brief 栈节点结构体
 */
typedef struct StackNode {
    StackElement data;         /**< 节点数据 */
    struct StackNode* next;    /**< 指向下一个节点的指针 */
} StackNode;

/**
 * @brief 栈结构体
 */
typedef struct {
    StackNode* top;            /**< 指向栈顶的指针 */
    int size;                  /**< 栈中元素的数量 */
} LinkedStack;

/**
 * @brief 初始化栈
 * @param stack 指向栈的指针
 */
void stackInit(LinkedStack* stack);

/**
 * @brief 检查栈是否为空
 * @param stack 指向栈的指针
 * @return 如果栈为空返回true，否则返回false
 */
bool stackIsEmpty(const LinkedStack* stack);

/**
 * @brief 获取栈的大小
 * @param stack 指向栈的指针
 * @return 栈中元素的数量
 */
int stackSize(const LinkedStack* stack);

/**
 * @brief 将元素压入栈顶
 * @param stack 指向栈的指针
 * @param element 要压入栈的元素
 * @return 操作成功返回true，失败返回false
 */
bool stackPush(LinkedStack* stack, StackElement element);

/**
 * @brief 弹出栈顶元素
 * @param stack 指向栈的指针
 * @return 操作成功返回true，失败返回false
 */
bool stackPop(LinkedStack* stack);

/**
 * @brief 获取栈顶元素
 * @param stack 指向栈的指针
 * @param element 用于存储栈顶元素的指针
 * @return 操作成功返回true，失败返回false
 */
bool stackTop(const LinkedStack* stack, StackElement* element);

/**
 * @brief 清空栈
 * @param stack 指向栈的指针
 */
void stackClear(LinkedStack* stack);

/**
 * @brief 销毁栈
 * @param stack 指向栈的指针
 */
void stackDestroy(LinkedStack* stack);

#endif /* LINKED_STACK_H */ 