#include <stdio.h>
#include <stdlib.h>
#include "duLinkedList.h"

Status InitList_DuL(DuLinkedList *L) {
    // 分配头节点内存
    *L = (DuLinkedList)malloc(sizeof(DuLNode));
    if (*L == NULL) {
        return ERROR;  // 内存分配失败
        return SUCCESS;
    }
    
    // 初始化头节点
    (*L)->prior = NULL;
    (*L)->next = NULL;
    return SUCCESS;
}

void DestroyList_DuL(DuLinkedList *L) {
    DuLinkedList temp;
    
    // 循环释放所有节点内存
    while (*L != NULL) {
        temp = *L;  // 保存当前节点
        *L = (*L)->next;  // 移动到下一个节点
        free(temp);  // 释放当前节点内存
    }
}

Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
    if (p == NULL || q == NULL) {
        return ERROR;
    }
    
    // 设置q的前后指针
    q->prior = p->prior;
    q->next = p;
    
    // 如果p不是第一个节点，更新p的前驱节点的next指针
    if (p->prior != NULL) {
        p->prior->next = q;
    }
    
    // 更新p的prior指针
    p->prior = q;
    
    return SUCCESS;
}

Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
    if (p == NULL || q == NULL) {
        return ERROR;
    }
    
    // 设置q的前后指针
    q->prior = p;
    q->next = p->next;
    
    // 如果p不是最后一个节点，更新p的后继节点的prior指针
    if (p->next != NULL) {
        p->next->prior = q;
    }
    
    // 更新p的next指针
    p->next = q;
    
    return SUCCESS;
}

Status DeleteList_DuL(DuLNode *p, ElemType *e) {
    if (p == NULL || p->next == NULL) {
        return ERROR;  // p为空或p是最后一个节点
    }
    
    DuLNode *q = p->next;  // 要删除的节点
    *e = q->data;  // 保存节点数据
    
    // 更新指针
    p->next = q->next;
    if (q->next != NULL) {
        q->next->prior = p;
    }
    
    free(q);  // 释放节点内存
    return SUCCESS;
}

void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
    DuLNode *current = L->next;  // 从第一个实际节点开始
    
    // 遍历所有节点
    while (current != NULL) {
        visit(current->data);  // 访问节点数据
        current = current->next;  // 移动到下一个节点
    }
}