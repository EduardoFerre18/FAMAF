#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool res = true;
    if (tree != NULL)
    {
        if (tree->left != NULL)
        {
            res = (tree->left->elem < tree->elem) && invrep(tree->left);
        }
        if (tree->right != NULL)
        {
            res = (tree->right->elem > tree->elem) && invrep(tree->right);
        }
    }
     
    return res;
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL){
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }
    else {
        if (!elem_eq(e, tree->elem)) {
            if (elem_less(e, tree->elem)){
                tree->left = abb_add(tree->left, e);
            }
            else {
                tree->right = abb_add(tree->right, e);
            }
        }
        assert(invrep(tree) && abb_exists(tree, e));
    }
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty = (tree == NULL);
    assert(invrep(tree));
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    if (abb_is_empty(tree)){
        return exists;
    }
    else {
        if (elem_eq(tree->elem, e)){
            return true;
        }
        else {
            if (elem_less(e, tree->elem)){
                exists = abb_exists(tree->left, e);
            }
            else {
                exists = abb_exists(tree->right, e);
            }
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    unsigned int length_tree_left = 0;
    unsigned int length_tree_right = 0;
    length_tree_left += abb_length(tree->left);
    length_tree_right+= abb_length(tree->right);
    length = 1 + length_tree_left + length_tree_right;
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (abb_exists(tree, e))
    {

        if (!elem_eq(tree->elem, e))
        {
            if (elem_less(e, tree->elem))
            {
                tree->left = abb_remove(tree->left, e);
            }
            else
            {
                tree->right = abb_remove(tree->right, e);
            }
        }
        else 
        {
            if ((tree->right == NULL) && (tree->left == NULL))
            {
                free(tree);
                tree = NULL;
                return NULL;
            }
            else
            {
                if (tree->right != NULL)
                {
                    abb_elem min = abb_min(tree->right);
                    tree->elem = min;
                    tree->right = abb_remove(tree->right, min);
                }
                else
                {

                    abb_elem max = abb_max(tree->left);
                    tree->elem = max;
                    tree->left = abb_remove(tree->left, max);
                }
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem; 
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (tree->right == NULL)
    {
        max_e = tree->elem;
    }
    else
    {
        max_e = abb_max(tree->right);
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (tree->left == NULL)
    {
        min_e = tree->elem;
    }
    else
    {
        min_e = abb_min(tree->left);
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}


abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(tree->left != NULL){
        abb_destroy(tree->left);
    }
    
    if(tree->right != NULL)
    {
        abb_destroy(tree->right);
    }
    
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

