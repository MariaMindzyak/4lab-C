#ifndef AB4A_DIALOG_H
#define AB4A_DIALOG_H

#include "tree.h"

enum Errors_{
    ERR_INPUT = 0
};

static char* Error_names[] = {
        "ERROR INPUT\n"
};

int dialog(const char *msgs[], int N);

int getInt(int *a);

char *getStr();

int D_Import(Tree* tree);

int D_Add(Tree* tree);

int D_find(Tree *tree);

int D_delete(Tree *tree);

int D_traversal(Tree* tree);

int D_find_special(Tree* tree);

int D_timing();

int D_show(Tree *tree);

#endif //AB4A_DIALOG_H
