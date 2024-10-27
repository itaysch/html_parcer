#include "tree.h"

Node* createNode(const char* tag, int is_no_close) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->tag = strdup(tag);
    node->content = createVector(4);
    node->children = NULL;
    node->next = NULL;
    node->is_no_close = is_no_close;
    return node;
}

void addChild(Node* parent, Node* child) {
    if(!parent->children) {
        parent->children = child;
    }
    else {
        Node* temp = parent->children;
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = child;
    }
}

void printTree(const Node* root, const int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    if(root->is_no_close ? printf("%s", root->tag) : printf("%s\n", root->tag))

        if(root->content->current_size > 0) {
            if(root->is_no_close) {
                printf(" ");
            }
            else {
                for (int i = 0; i < depth + 1; i++) printf("  ");
            }
            for (int i = 0; i < root->content->current_size; i++) {
                printf("%c", root->content->array[i]);
            }
            printf("\n");
        }

    Node* child = root->children;
    while(child) {
        printTree(child, depth + (root->is_no_close ? 0 : 1));
        child = child->next;
    }
    if (!root->is_no_close) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("%s\n", root->tag);
    }
}

void freeTree(Node* root) {
    if(!root) return;
    free(root->tag);
    freeVector(root->content);
    Node* child = root->children;
    while (child) {
        Node* next = child->next;
        free(child);
        child = next;
    }
    free(root);
}
