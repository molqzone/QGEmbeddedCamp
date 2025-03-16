#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

Status InitList(LinkedList *L) {
    // 分配头节点内存
    *L = (LinkedList)malloc(sizeof(LNode));
    if (*L == NULL) {
        return ERROR;  // 内存分配失败
    }
    
    // 初始化头节点
    (*L)->next = NULL;
    return SUCCESS;
}

void DestroyList(LinkedList *L) {
    LinkedList temp;
    
    // 循环释放所有节点内存
    while (*L != NULL) {
        temp = *L;  // 保存当前节点
        *L = (*L)->next;  // 移动到下一个节点
        free(temp);  // 释放当前节点内存
    }
}

Status InsertList(LNode *p, LNode *q) {
    if (p == NULL || q == NULL) {
        return ERROR;
    }
    
    // 将q节点插入到p节点之后
    q->next = p->next;
    p->next = q;
    
    return SUCCESS;
}

Status DeleteList(LNode *p, ElemType *e) {
    if (p == NULL || p->next == NULL) {
        return ERROR;  // p为空或p是最后一个节点
    }
    
    LNode *q = p->next;  // 要删除的节点
    *e = q->data;  // 保存节点数据
    
    // 更新指针
    p->next = q->next;
    
    free(q);  // 释放节点内存
    return SUCCESS;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
    LNode *current = L->next;  // 从第一个实际节点开始
    
    // 遍历所有节点
    while (current != NULL) {
        visit(current->data);  // 访问节点数据
        current = current->next;  // 移动到下一个节点
    }
}

Status SearchList(LinkedList L, ElemType e) {
    LNode *current = L->next;  // 从第一个实际节点开始
    
    // 遍历查找值为e的节点
    while (current != NULL) {
        if (current->data == e) {
            return SUCCESS;  // 找到目标节点
        }
        current = current->next;
    }
    
    return ERROR;  // 未找到目标节点
}

Status ReverseList(LinkedList *L) {
    if (*L == NULL || (*L)->next == NULL) {
        return ERROR;  // 空链表或只有一个节点
    }
    
    LNode *prev = NULL;
    LNode *current = (*L)->next;
    LNode *next = NULL;
    
    // 头节点指向NULL
    (*L)->next = NULL;
    
    // 逐个节点反转
    while (current != NULL) {
        next = current->next;  // 保存下一个节点
        current->next = prev;  // 反转指针
        prev = current;  // 移动prev
        current = next;  // 移动current
    }
    
    // 更新头节点的next指针
    (*L)->next = prev;
    
    return SUCCESS;
}

Status IsLoopList(LinkedList L) {
    if (L == NULL || L->next == NULL) {
        return ERROR;  // 空链表或只有一个节点
    }
    
    LNode *slow = L->next;
    LNode *fast = L->next;
    
    // 快慢指针法检测环
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return SUCCESS;  // 存在环
        }
    }
    
    return ERROR;  // 不存在环
}

LNode* ReverseEvenList(LinkedList *L) {
    if (*L == NULL || (*L)->next == NULL || (*L)->next->next == NULL) {
        return *L;  // 链表为空或节点数小于2
    }
    
    LNode *prev = *L;
    LNode *current = (*L)->next;
    LNode *next;
    
    // 两两交换节点
    while (current != NULL && current->next != NULL) {
        next = current->next->next;  // 保存下一对的起始节点
        
        // 交换相邻两个节点
        prev->next = current->next;
        current->next->next = current;
        current->next = next;
        
        // 移动指针
        prev = current;
        current = next;
    }
    
    return *L;
}

LNode* FindMidNode(LinkedList *L) {
    if (*L == NULL || (*L)->next == NULL) {
        return *L;  // 空链表或只有头节点
    }
    
    LNode *slow = (*L)->next;
    LNode *fast = (*L)->next;
    
    // 快慢指针法找中间节点
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;  // 返回中间节点
}

LinkedList ReverseList_Recursive(LinkedList head) {
    // 空链表或只有一个节点
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    // 递归反转剩余部分
    LinkedList newHead = ReverseList_Recursive(head->next);
    head->next->next = head;  // 反转指针
    head->next = NULL;        // 避免循环
    return newHead;
}