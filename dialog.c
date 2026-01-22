#include "dialog.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if(n<0){
            return 0;
        }
        if(n==0){
            printf("%s\n", "Error! Repeat, please");
            scanf("%*[^\n]");
            scanf("%*c");

        }
    }while(n==0);
    return 1;
}

char *getStr(){
    int flag = 1, len = 0;
    char *input = NULL;
    while (flag > 0){
        char *buff = malloc(200 * sizeof(char));
        flag = scanf("%199[^\n]", buff);
        if (flag == EOF) {
            input = NULL;
        } else if (flag == 0) {
            scanf("%*c");
        } else {
            int buffLen = strlen(buff);
            input = realloc(input, (len + buffLen) * sizeof(char));
            for (int i = 0; i < buffLen; i++) {
                input[len + i] = buff[i];
            }
            len += buffLen;
        }
        free(buff);
    }
    if (flag != - 1) {
        input = realloc(input, (len + 1) * sizeof(char));
        input[len] = '\0';
    }
    return input;
}

int dialog(const char *msgs[], int N) {
    char *errmsg = "";
    int rc;
    int i, n;
    do {
        puts(errmsg);
        errmsg = "You're wrong. Repeat, please!\n";
        for (i = 0; i < N; i++) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        n = getInt(&rc);
        if (n == 0) rc = 0;

    } while (rc < 0 || rc >= N);
    return rc;
}

int D_Import(Tree* tree){
    char* filename;
    printf("Enter filename --> ");
    filename = getStr();
    if (filename == NULL){
        printf("%s\n", Error_names[ERR_INPUT]);
        return 0;
    }
    import_tree(filename, tree);
    free(filename);
    return 1;
}

int D_Add(Tree* tree) {
    int k, n;
    char *info = NULL;
    char* rc;
    printf("%s", "Enter key --> ");
    n = getInt(&k);
    scanf("%*c");
    if (n == 0) {
        printf("%s\n", Error_names[ERR_INPUT]);
        return 0;
    }
    printf("%s", "Enter info --> ");
    info = getStr();

    if (info == NULL) {
        printf("%s\n", Error_names[ERR_INPUT]);
        return 0;
    }
    rc = add(tree, k, info);
    show_tree(*tree);
    free(info);
    return 1;
}

int D_find(Tree* tree){
    int k, n;
    printf("Enter key --> ");
    n = getInt(&k);
    Node* par;
    Node* ptr = find_by_key(tree, k, &par);
    if (ptr == NULL){
        printf("ERROR NOT FOUND");
        return 1;
    }

    show_node(ptr);
    return 1;
}

int D_delete(Tree* tree){
    int k, rc, n;
    printf("%s", "Enter key --> ");
    n = getInt(&k);
    rc = delete(tree, k);
    if(rc == NOT_FOUND){
        printf("ERROR NOT FOUND");
        return 1;
    }
    show_tree(*tree);
    return 1;
}

int D_traversal(Tree* tree){
    int k, rc, n;
    printf("%s", "Enter key --> ");
    n = getInt(&k);
    rc = traversal(tree, k);
    return 1;
}

int D_find_special(Tree* tree){
    int k, rc, n;
    printf("%s", "Enter key --> ");
    n = getInt(&k);
    Node* par;
    Node* ptr = find_by_key(tree, k, &par);
    if (ptr != NULL){
        printf("ERROR THE NODE IS IN THE TREE\n");
        show_node(ptr);
        return 1;
    }
    Node** array = find_special(tree, k);
    for (int i = 0; i <= 1; i++){
        if (array[i] != NULL) {
        show_node(array[i]);
        }
    }
    free(array); /////////////////////////////////
    return 1;
}

int D_timing(){
    Node* par;
    Tree tree = init_tree();
    int n = 10, key[1000], k, cnt = 10, i, m, len = 0;
    clock_t first, last;
    srand(time(NULL));
    while(n-- > 0){
        for (i = 0; i < 1000; i++){
            key[i] = rand() * rand();
        }
        /*for (i = 0; i < cnt; ){
            k = rand() * rand();
            if (add(&tree, k, NULL) == NULL) ++i;
        }*/
        while(len < cnt){
        	k = rand()*rand();
        	if (add(&tree, k, NULL) == NULL) len++;
        }
        m = 0;
        first = clock();
        for (i = 0; i < 1000; ++i){
            if (find_by_key(&tree, key[i], &par)) ++m;
        }
        last = clock();
        printf("%d items was found \n", m);
        printf("test #%d, number of nodes = %d, time = %f\n", 10 - n, cnt, ((double)(last - first)/CLOCKS_PER_SEC));
        cnt = cnt * 10;
    }
    free_tree(&tree);
    return 1;
}

int D_show(Tree* tree){
    //show_tree(*tree);
    printTree(tree->root, 0);
    return 1;
}
