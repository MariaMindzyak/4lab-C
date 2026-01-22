#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "dialog.h"
#include "menu.h"

int main() {
    Tree tree = init_tree();
    import_tree("C:\\Users\\mindz\\CLionProjects\\lab4a\\input.txt", &tree);
    /*int rc;
    while (rc = dialog(msgs, N)) {
        if (!fptr[rc](&tree)) break;
    }
    printTree(tree.root, 0);
    free_tree(&tree);*/
    //print_tree(&tree);
    //system("dot -Tpng tree.dot -o tree.png");
	//system("catimg tree.png");
    traversal_2(tree.root);
    return 1;
}
