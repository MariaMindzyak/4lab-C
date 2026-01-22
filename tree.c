#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Tree init_tree(){
    Tree tree;
    tree.root = NULL;
    return tree;
}

char *freadline(FILE *file) {
    char *ptr = (char *)malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        } else if (n == 0) {
            fscanf(file, "%*c");
        } else {
            len += strlen(buf);
            ptr = (char *)realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

int import_tree(const char* filename, Tree* tree){
    FILE* file = fopen(filename, "r");
    if (!file) perror("fopen");
    if (file == NULL) {
        printf("Cannot read file\n");
        return 1;
    }
    char* str_key = freadline(file);
    while(str_key != NULL){
        int key = atoi(str_key);
        char* info = freadline(file);
        add(tree, key, info);
        free(str_key);
        free(info);
        str_key = freadline(file);
    }
    return 1;
}

char* add(Tree* tree, int key, char* info) {
    Node *par;
    Node *new_node = (Node*) calloc(1, sizeof(Node));  
    new_node->key = key;
    if (info != NULL) new_node->info = strdup(info);
    else new_node->info = NULL;
    if (tree->root == NULL) {
        tree->root = new_node;
        return NULL;
    }
    Node *ptr = find_node(tree, key);
    if (key > ptr->key){
        ptr->right = new_node;
        find_by_key(tree, ptr->key, &par);
        if (par == NULL) firmware(tree, ptr->right->key);
        else firmware(tree, par->key);
    }
    else if (key < ptr->key){
        ptr->left = new_node;
        firmware(tree, ptr->key);
    }
    else {
        char* copy_info = ptr->info;
        if (info != NULL) ptr->info = strdup(info);
        else ptr->info = NULL;
        free_node(new_node);
        return copy_info;
    }
    return NULL;
}

Node* find_node(Tree* tree, int key){
    Node* ptr = tree->root;
    Node* par = NULL;
    while (ptr != NULL){
        par = ptr;
        if(key < ptr->key) {
            ptr = ptr->left;
        }

        else if (key == ptr->key){
            return par;
        }

        else {
            ptr = ptr->right;
        }
    }
    return par;
}

Node* find_by_key(Tree* tree, int key, Node** par){
    Node* ptr = tree->root;
    while(ptr != NULL){
        *par = ptr;
        if(ptr->key < key) {
            ptr = ptr->right;
        }
        else if(ptr->key > key) {
            ptr = ptr->left;
        }
        if (ptr == NULL || ptr->key == key) break;
    }
    if (ptr == tree->root) *par = NULL;
    return ptr;
}

int node_child(Node* ptr){
    int n = 0;
    if(ptr->left == NULL && ptr->right == NULL) n = 0;
    else if(ptr->left != NULL && ptr->right == NULL) n = 1;
    else if(ptr->left == NULL && ptr->right != NULL) n = 1;
    else if(ptr->left != NULL && ptr->right != NULL) n = 2;
    return n;
}

int delete(Tree* tree, int key) {
	int prev_key = 0;
    Node *par;
    int flag_root = 0;
    Node *ptr = find_by_key(tree, key, &par);
    if (ptr == NULL) return NOT_FOUND;
    Node* prev = ptr->prev;
    if (prev == NULL) ptr->next->prev = NULL;
    else prev_key = prev->key;
    if (ptr == tree->root) flag_root = 1;
    if (node_child(ptr) == 0) {
        if (flag_root == 1) {
            tree->root = NULL;
                //return OK;
        }
        else {
            if (ptr->key > par->key){
            	free(par->right->info);
            	free(par->right);
            	par->right = NULL;
            }
            else if (ptr->key < par->key){
            	free(par->left->info); 
            	free(par->left);
            	par->left = NULL;
            }
        }
    }
    else if (node_child(ptr) == 1) {
        if (ptr->right != NULL) {
            if (flag_root == 1) {
                tree->root = ptr->right;
            }
            else {
                if (ptr->key > par->key) par->right = ptr->right;
                else if (ptr->key < par->key) par->left = ptr->right;
            }
            free(ptr->info);
            free(ptr); 
        }
        else {
            if (flag_root == 1) {
                tree->root = ptr->left;
            }
            else {
                if (ptr->key > par->key) par->right = ptr->left;
                else if (ptr->key < par->key) par->left = ptr->left;
            }
            free(ptr->info);
            free(ptr);
        }
    }
    else if (node_child(ptr) == 2) {
        Node *min = ptr->right;
        while (min->left != NULL) {
            min = min->left;
        }
        int copy_key = min->key;
        char *copy_info = strdup(min->info);
        delete(tree, min->key);
        ptr->key = copy_key;
        free(ptr->info); ///////////////////////////////////
        ptr->info = copy_info;
        if (flag_root == 1) tree->root = ptr;
    }
    if (prev_key) firmware(tree, prev_key);
    return OK;
}


int firmware(Tree* tree, int key){
    Node* par = NULL;
    Node* ptr = find_by_key(tree, key, &par);
    ptr->next = find_next(tree, ptr, par);

    if (ptr->next != NULL) {
        ptr->next->prev = ptr;
        firmware(tree, ptr->next->key);
    }
    
    return 1;
}

int traversal(Tree* tree, int key){
    Node* par = (Node*) calloc(1, sizeof(Node));
    Node* ptr = find_by_key(tree, key, &par);
    while (ptr != NULL){
        show_node(ptr);
        ptr = ptr->next;
    }
    return 1;
}

Node* find_next(Tree* tree, Node* ptr, Node* par){
    if (ptr->left != NULL){
        ptr = ptr->left;
        while(ptr->right != NULL){
            ptr = ptr->right;
        }
        return ptr;
    }

    if (ptr->key == find_min(tree)) {
        ptr = NULL;
        return ptr;
    }

    while((par != NULL) && (ptr == par->left)){
        ptr = par;
        find_by_key(tree, par->key, &par);
    }
    ptr = par;
    return ptr;
}


int find_min(Tree* tree){
    Node* ptr = tree->root;
    while(ptr->left != NULL) ptr = ptr->left;
    return ptr->key;
}

int find_max(Tree* tree){
    Node* ptr = tree->root;
    while(ptr->right != NULL) ptr = ptr->right;
    return ptr->key;
}

Node** find_special(Tree* tree, int key){
    Node* par;
    Node** array = (Node**) calloc(2, sizeof(Node*));
    Node* ptr = tree->root;
    int min = find_min(tree);
    int max = find_max(tree);
    if (key < min){
        array[0] = find_by_key(tree, min, &par);
    }
    else if (key > max){
        array[0] = find_by_key(tree, max, &par);
    }

    else {
        while (ptr->next != NULL && ptr->key > key && ptr->next->key > key) {
            ptr = ptr->next;
        }
        while (ptr->prev != NULL && ptr->key < key && ptr->prev->key < key) {
            ptr = ptr->prev;
        }
        if(key < tree->root->key){
            if ((ptr->key - key) > (key - ptr->next->key)) array[0] = find_by_key(tree, ptr->next->key, &par);
            else if ((ptr->key - key) < (key - ptr->next->key)) array[0] = find_by_key(tree, ptr->key, &par);
            else if ((ptr->key - key) == (key - ptr->next->key)){
                array[0] = find_by_key(tree, ptr->next->key, &par);
                array[1] = find_by_key(tree, ptr->key, &par);

            }
        }
        if(key > tree->root->key){
            if ((ptr->prev->key - key) > (key - ptr->key)) array[0] = find_by_key(tree, ptr->key, &par);
            else if ((ptr->prev->key - key) < (key - ptr->key)) array[0] = find_by_key(tree, ptr->prev->key, &par);
            else if ((ptr->prev->key - key) == (key - ptr->key)){
                array[0] = find_by_key(tree, ptr->key, &par);
                array[1] = find_by_key(tree, ptr->prev->key, &par);

            }
        }
    }
    return array;
}

int show_node(Node* ptr){
    if (ptr != NULL && ptr->next != NULL && ptr->prev != NULL)
        printf("key: %d| info: %s| next: %d| prev: %d\n", ptr->key, ptr->info, ptr->next->key, ptr->prev->key);
    else if (ptr != NULL && ptr->next != NULL && ptr->prev == NULL)
        printf("key: %d| info: %s| next: %d\n", ptr->key, ptr->info, ptr->next->key);
    else if (ptr != NULL && ptr->next == NULL && ptr->prev != NULL)
        printf("key: %d| info: %s| prev: %d\n", ptr->key, ptr->info, ptr->prev->key);
    else if(ptr != NULL && ptr->next == NULL && ptr->prev == NULL) {
        printf("key: %d| info: %s\n", ptr->key, ptr->info);
    }
    return 1;
}

void show(Node* ptr){
    show_node(ptr);
    if (ptr != NULL) {
        show(ptr->left);
        show(ptr->right);
    }
}

int show_tree(Tree tree) {
    show(tree.root);
    return 1;
}

void free_node(Node* node){
    free(node->info);
    if (node->left != NULL) free_node(node->left);
    if (node->right != NULL) free_node(node->right);
    free(node);
}

void free_tree(Tree* tree){
    if (tree->root != NULL) free_node(tree->root);
}

void print_tree(Tree* tree) {
    FILE* file = fopen("tree.dot", "w");

    if (file == NULL) {
        printf("Ошибка при открытии файла");
        return;
    }

    fprintf(file, "digraph G {\n");
    fprintf(file, "\tnode [shape=circle];\n");
    print_tree_dfs(tree->root, file);
    fprintf(file, "\n}");

    fclose(file);
}
void print_tree_dfs(Node* node, FILE* file) {
    if (node == NULL) {
        fprintf(file, "null");
        return;
    }

    fprintf(file, "%d", node->key);

    if (node->left != NULL || node->right != NULL) {
        fprintf(file, " [");
        print_tree_dfs(node->left, file);
        fprintf(file, ", ");
        print_tree_dfs(node->right, file);
        fprintf(file, "]");
    }
}


void printSpaces(int count){
	for (int i = 0; i < count; i++){
		printf(" ");
	}
}

void printTree(Node* root, int space){
	if(root == NULL) return;
	int count = 6;
	space += count;
	printTree(root->right, space);
	printf("\n");
	printSpaces(space - count);
	printf("%d", root->key);
	if(root->right != NULL){
		printf("\n");
		printSpaces(space - count - 3);
		printf("/");
	}
	if (root->left != NULL){
		printf("\n");
		printSpaces(space - count);
		printf("\\");
	}
	printTree(root->left, space);
}


int traversal_2(Node* ptr){
    if (ptr != NULL) {
        traversal_2(ptr->right);
        show_node(ptr);
        traversal_2(ptr->left);
    }
    return 1;
}