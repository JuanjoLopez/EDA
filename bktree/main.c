#include <stdio.h>

#include "CBKTree.h"

int main()
{
    CBKTree *t = NULL;

    t = bktree_new();
    
    bktree_add(t, "pety", 0);
    bktree_add(t, "pollo", 1);
    bktree_add(t, "gabriel", 2);
    bktree_add(t, "flor", 2);
    bktree_add(t, "gato", 3);
    bktree_add(t, "gata", 4);
    bktree_add(t, "peterete", 5);
    bktree_add(t, "superjan", 6);
    
    int n = 0;
    
    bktree_query(t, "gato", 1, NULL, &n);
    
    printf("%d resultados\n", n);
    
    bktree_delete(t);

    return 0;
}

