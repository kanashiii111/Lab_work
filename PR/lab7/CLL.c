#include <stdio.h>
#include <stdlib.h>
#include "CLL.h"

void findNodeByPos(int position, Node* lastNode) {
    if (lastNode == NULL) {
        printf("Список пустой.\n");
        return;
    }
    Node* current = lastNode->next;
    int currentPos = 0;
    do {
        if (currentPos == position) {
            printf("На позиции %d найдено значение: %d\n", position, current->value);
            return;
        }
        currentPos++;
        current = current->next;
    } while (current != lastNode->next);
    printf("Позиция %d выходит за пределы списка.\n", position);
}

void insertFront(Node** lastNode, int nodeValueToInsert) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = nodeValueToInsert;

    if (*lastNode == NULL) {
        newNode->next = newNode;
        *lastNode = newNode;
    } else {
        newNode->next = (*lastNode)->next;
        (*lastNode)->next = newNode;
    }
    printf("Узел со значением %d успешно добавлен в список.\n", nodeValueToInsert);
}

void removeNode(Node** lastNode, int NodeValueToRemove) {
    if (*lastNode == NULL) {
        printf("Список пуст.\n");
        return;
    }
    Node* current = (*lastNode)->next;
    Node* prev = *lastNode;
    do {
        if (current->value == NodeValueToRemove) {
            if (current == *lastNode && current->next == current) {
                *lastNode = NULL;
            } else if (current == *lastNode) {
                prev->next = current->next;
                *lastNode = prev; 
            } else {
                prev->next = current->next;
            }

            printf("Вершина %d убрана из списка.\n", NodeValueToRemove);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != (*lastNode)->next);

    printf("Вершина %d не найдена.\n", NodeValueToRemove);
}

void printList(Node** lastNode) {
    if (*lastNode == NULL) {
        printf("Список пуст.\n");
        return;
    }
    Node* current = (*lastNode)->next;
    do {
        printf("%d -> ", current->value);
        current = current->next;
    } while (current != (*lastNode)->next);
    printf("(цикл)\n");
}

void clearList(Node** lastNode) {
    if (*lastNode == NULL) {
        printf("Список пуст.\n");
        return;
    }
    Node* current = (*lastNode)->next;
    Node* nextNode;
    (*lastNode)->next = NULL;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *lastNode = NULL;
    printf("Список успешно очищен.\n");
}

void clearCMD() {
    system("cls");
    printf("Для получения списка комманд введите help\n");
}

void help() {
    printf("add <число> - добавить элемент в начало списка\n");
    printf("remove <число> - убрать элемент из списка\n");
    printf("print - вывести список на экран\n");
    printf("clear - очистить список\n");
    printf("find <позиция> - найти значение элемента на заданной позиции\n");
    printf("exit - выход из программы\n");
    printf("screenClear - очистить консоль\n");
}
