#pragma once
#ifndef CLL_H
#define CLL_H

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void findNodeByPos(int position, Node* lastNode);
void insertFront(Node** lastNode, int value);
void removeNode(Node** lastNode, int value);
void printList(Node** lastNode);
void clearList(Node** lastNode);
void help();
void clearCMD();


#endif