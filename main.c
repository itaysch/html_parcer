#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "vector.h"
#include "tree.h"

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
    TAG_COUNT
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
    int space_flag = 1;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            i++;
            space_flag = 1;
        }
        else if (space_flag && isspace(str[i])) {
            i++;
        }
        else {
            space_flag = 0;
            str[j++] = str[i++];
        }
    }
    str[j] = '\0';
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
                char* token_start = (char*)malloc(100 * sizeof(char));
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