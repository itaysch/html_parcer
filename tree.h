#ifndef TREE_H
#define TREE_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

typedef struct {
    char* tag;
    Vector* content;
    struct Node* children;
    struct Node* next;
    int is_no_close;
}Node;

Node* createNode(const char* tag, int is_no_close);
void addChild(Node* parent, Node* child);
void printTree(const Node* root, const int depth);
void freeTree(Node* root);

#endif //TREE_H