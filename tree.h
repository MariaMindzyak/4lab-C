#ifndef AB4A_TREE_H
#define AB4A_TREE_H

#include <stdio.h>

enum Errors{
    OK = 1,
    NOT_FOUND = 0,
};


typedef struct Node{
    int key;
    struct Node* right;
    struct Node* left;
    struct Node* next;
    struct Node* prev;
    char* info;
} Node;

typedef struct Tree{
    Node* root;
}Tree;

Tree init_tree();

char *freadline(FILE *file);

int import_tree(const char* filename, Tree* tree);

Node* find_node(Tree* tree, int key); //поиск при вставке эл-та

char* add(Tree* tree, int key, char* info);

Node* find_by_key(Tree* tree, int key, Node** par);

Node* find_next(Tree* tree, Node* ptr, Node* par); //поиск следующего эл-та в обходе

int find_min(Tree* tree);

int find_max(Tree* tree);

int firmware(Tree* tree, int key);

int traversal(Tree* tree, int key);

Node** find_special(Tree* tree, int key);

int node_child(Node* ptr);

int delete(Tree* tree, int key);

void free_node(Node* node);

void free_tree(Tree* tree);

int show_node(Node* ptr); //отладочный

void show(Node* ptr); //отладочный

int show_tree(Tree tree); //отладочный

void print_tree_dfs(Node* node, FILE* file); //graphviz

void print_tree(Tree* tree); //graphviz

void printSpaces(int count);

void printTree(Node* root, int space);

int traversal_2(Node* ptr);


#endif //AB4A_TREE_H
