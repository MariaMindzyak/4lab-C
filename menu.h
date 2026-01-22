#ifndef AB4A_MENU_H
#define AB4A_MENU_H

#include "dialog.h"

const char *msgs[] = {
        "0.Quit",
        "1.Import",
        "2.Add",
        "3.Find",
        "4.Find special",
        "5.Delete",
        "6.Traversal",
        "7.Show",
        "8.Timing"
};

int (*fptr[])(Tree *) = {
        NULL,
        D_Import,
        D_Add,
        D_find,
        D_find_special,
        D_delete,
        D_traversal,
        D_show,
        D_timing
};

int N = sizeof(msgs) / sizeof(msgs[1]);

#endif //AB4A_MENU_H
