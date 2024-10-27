#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* value;
    struct Node_stack *next;
}Node_stack;

typedef struct {
    Node_stack *top;
}Stack;


Node_stack* createNodeStack(const char* value) {
    Node_stack *node = (Node_stack *)malloc(sizeof(Node_stack));
    node->value = (char*)malloc(strlen(value) + 1);  // +1 for the null terminator
    strcpy(node->value, value);
    node->next = NULL;
    return node;
}

Stack* createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

int isEmpty(const Stack *stack) {
    return stack->top == NULL;
}

void push(Stack *stack, const char* value) {
    Node_stack *node = createNodeStack(value);
    node->next = stack->top;
    stack->top = node;
}

char* pop(Stack *stack) {
    if(isEmpty(stack)) {
        return NULL;
    }
    Node_stack* temp = stack->top;
    char* popped = temp->value;
    stack->top = temp->next;
    free(temp);
    return popped;
}

void print_stack(const Stack *stack) {
    if(isEmpty(stack)) {
        printf("stack is empty\n");
        return;
    }
    printf("Stack: ");
    Node_stack *node = stack->top;
    while(node != NULL) {
        printf("%s ", node->value);
        node = node->next;
    }
    printf("\n");
}

char* top(const Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->top->value;
}

void free_stack(Stack* stack) {
    while (!isEmpty(stack)) {
        free(pop(stack));  // Free each node value
    }
    free(stack);  // Free the stack structure itself
}


typedef struct {
    char* array;
    int capacity;
    int current_size;
}Vector;


Vector* createVector(const int size) {
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    vector->array = (char*)malloc(size * sizeof(char));
    vector->capacity = size;
    vector->current_size = 0;
    return vector;
}

void append(Vector* vector, const char value) {
    if(vector->current_size == vector->capacity) {
        vector->capacity *= 2;
        vector->array = (char*)realloc(vector->array, vector->capacity * sizeof(char));
    }
    vector->array[vector->current_size++] = value;
}

void resize(Vector* vector) {
    vector->capacity *= 2;
    vector->array = (char*)realloc(vector->array, vector->current_size * sizeof(char));
}

void set(const Vector* vector, const int index, const char value) {
    if(index >= vector->current_size || index < 0) {
        printf("out of bounds\n");
        return;
    }
    vector->array[index] = value;
}

char get(const Vector* vector, const int index) {
    if(index >= vector->current_size || index < 0) {
        printf("out of bounds\n");
        return -1;
    }
    return vector->array[index];
}

void removeAt(Vector* vector, const int index) {
    if(index < 0 || index >= vector->current_size) {
        printf("out of bounds\n");
        return;
    }
    for(int i = index; i < vector->current_size - 1; i++) {
        vector->array[i] = vector->array[i + 1];
    }
    vector->current_size--;
}

void insertAt(Vector* vector, const int index, const char value) {
    if(index < 0 || index >= vector->current_size) {
        printf("out of bounds\n");
        return;
    }
    for(int i = vector->current_size - 1; i > index; i--) {
        vector->array[i] = vector->array[i - 1];
    }
    vector->array[index] = value;
    vector->current_size++;

}

void printVector(const Vector* vector) {
    for(int i = 0; i < vector->current_size; i++) {
        printf("%c ", vector->array[i]);
    }
}

void freeVector(Vector* vector) {
    free(vector->array);
    vector->current_size = 0;
    vector->capacity = 0;
}


typedef struct {
    char* tag;
    Vector* content;
    struct Node* children;
    struct Node* next;
    int is_no_close;
}Node;

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

typedef enum {
    BR,
    HR,
    IMG,
    INPUT,
    LINK,
    META,
    SOURCE,
    COL,
    BASE,
    AREA,
    TAG_COUNT // Keep track of the number of tags
} HtmlSelfClosingTag;

const char* TagStrings[TAG_COUNT] = {
    "br",
    "hr",
    "img",
    "input",
    "link",
    "meta",
    "source",
    "col",
    "base",
    "area"
};

int is_self_closing_tag(char* tag) {
    char token[50];
    char* ptr = tag;
    int i = 0;
    while(*ptr != ' ' && *ptr != '\0') {
        token[i++] = *ptr++;
    }
    token[i] = '\0';

    for(int i = 0; i < TAG_COUNT; i++) {
        if(strcmp(token, TagStrings[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void strip_newlines_and_spaces(char* str) {
    int i = 0, j = 0;
    int space_flag = 1;  // To track spaces at the start of lines
    while (str[i] != '\0') {
        // Ignore leading spaces (spaces before any character on a new line)
        if (str[i] == '\n') {
            i++;
            space_flag = 1; // Set flag to ignore leading spaces after a newline
        }
        else if (space_flag && isspace(str[i])) {
            i++;
        }
        else {
            space_flag = 0; // Once a non-space character is found, reset flag
            str[j++] = str[i++];
        }
    }
    str[j] = '\0';  // Null-terminate the modified string
}


void tokenize(const char** html_ptr, Node* root, Stack* stack_tags) {
    const char* str = *html_ptr;

    while(*str != '\0') {
        while(isspace(*str)) str++;
        if(*str == '<') {
            str++;
            if(*str == '/') {
                char* token_close = (char*)malloc(100 * sizeof(char));
                if (!token_close) {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }
                str++;
                int i = 0;
                while(*str != '>' && *str != '\0') {
                    token_close[i++] = *str++;
                }
                token_close[i] = '\0';

                if(strcmp(token_close, top(stack_tags)) == 0) {
                    free(pop(stack_tags));
                    free(token_close);
                    str++;
                    *html_ptr = str;
                    return;
                }
                else {
                    free(token_close);
                    continue;
                }

            }
            else {
                char* token_start = (char*)malloc(100 * sizeof(char));  // Allocate memory for the token
                if (!token_start) {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }

                int i = 0;
                while(*str != '>' && *str != '\0') {
                    token_start[i++] = *str++;
                }
                token_start[i] = '\0';

                if(is_self_closing_tag(token_start)) {
                    char token_no_close[50];
                    char* ptr = token_start;
                    i = 0;
                    while(*ptr != ' ' && *ptr != '\0') {
                        token_no_close[i++] = *ptr++;
                    }
                    token_no_close[i] = '\0';
                    char token_no_close_content[50];
                    i = 0;
                    ptr++;
                    while(*ptr != '\0') {
                        token_no_close_content[i++] = *ptr++;
                    }
                    token_no_close_content[i] = '\0';
                    Node* child = createNode(token_no_close, 1);

                    if(token_no_close != NULL) {
                        char* ptr2 = token_no_close_content;
                        while (*ptr2 != '\0') {
                            append(child->content, *ptr2++);
                        }
                    }
                    addChild(root, child);
                    str++;
                }
                else {
                    push(stack_tags, token_start);
                    Node* child = createNode(token_start, 0);
                    addChild(root, child);
                    str++;
                    tokenize(&str, child, stack_tags);
                }
            }
        }
        else{
            while(*str != '<' && *str != '\0') {
                append(root->content, *str++);
            }
        }
    }
    *html_ptr = str;
}


int main(void) {

    const char* original_html_page =
    "<html>\n"
    "<head>\n"
    "    <meta charset=\"UTF-8\">\n"
    "    <title>Basic HTML Page</title>\n"
    "    <style>\n"
    "        body {\n"
    "            font-family: Arial, sans-serif;\n"
    "        }\n"
    "    </style>\n"
    "    <base href=\"https://example.com/\">\n"
    "</head>\n"
    "<body>\n"
    "    <table>\n"
    "        <colgroup>\n"
    "            <col style=\"background-color: yellow\">\n"
    "            <col style=\"background-color: green\">\n"
    "        </colgroup>\n"
    "    </table>\n"
    "    <h1>Header 1</h1>\n"
    "    <h2>Header 2</h2>\n"
    "    <h3>Header 3</h3>\n"
    "    <img src=\"image.jpg\" width=\"500\" height=\"600\">\n"
    "    <div>\n"
    "        <p>This is a paragraph inside a div.</p>\n"
    "    </div>\n"
    "    <script>\n"
    "        console.log(\"This is a script block.\");\n"
    "    </script>\n"
    "</body>\n"
    "</html>";

    char* html_page = (char*)malloc(strlen(original_html_page) + 1);
    if (html_page == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    strcpy(html_page, original_html_page);
    printf("Original string:\n%s\n\n", html_page);

    char* original_html_page_ptr = html_page;

    Node* root = createNode("root", 1);
    Stack* stack_tags = createStack();
    tokenize(&html_page, root, stack_tags);
    printf("The html page in the tree is: \n");
    printTree(root->children, 0);

    freeTree(root);
    free_stack(stack_tags);
    free(original_html_page_ptr);

    return 0;

}