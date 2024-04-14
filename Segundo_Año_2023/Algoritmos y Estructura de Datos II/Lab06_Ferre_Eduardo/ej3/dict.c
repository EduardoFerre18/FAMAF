#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

/*static bool invrep(dict_t d) {
     needs implementation 
    return true;
} */

dict_t dict_empty(void) {
    dict_t dict = NULL;
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    if (dict == NULL) {
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    }
    else {
        if (!key_eq(dict->key, word)) {

            if (key_less(word, dict->key)) {
                dict->left = dict_add(dict->left, word, def);
            }
            else {
                dict->right = dict_add(dict->right, word, def);
            }
        }
        else {
            dict->value = def;
        }
    }
    return dict;
}


value_t dict_search(dict_t dict, key_t word) {
    key_t def = NULL;
    if (dict_exists(dict, word)) {
        if (key_eq(word, dict->key)) {
            def = dict->value;
        }
        else {

            if (key_less(word, dict->key)) {
                def = dict_search(dict->left, word);
            }
            else {
                def = dict_search(dict->right, word);
            }
        }
    }
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool res = false;
    if (dict == NULL) {
        return res;
    }
    else {
        if (key_eq(dict->key, word)) {
            res = true;
        }
        else {
            if (key_less(word, dict->key)) {
                res = dict_exists(dict->left, word);
            }
            else {
                res = dict_exists(dict->right, word);
            }
        }
    }
    return res;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0;
    if (dict != NULL) {
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }
    return length;
}

static dict_t min_value_node(dict_t dict){
    dict_t current = dict ;
    while (current != NULL && current->left !=NULL)
    {
        current = current->left;
    }
    return current;
}

dict_t dict_remove(dict_t dict, key_t word) {
    if (dict_exists(dict,word) || dict != NULL)
    {
        if (key_eq(dict->key,word))
        {
            if (dict->left == NULL)
            {
                dict_t temp = dict;
                dict = dict->right;
                free(temp);
            }else if (dict->right == NULL)
            {
                dict_t temp = dict;
                dict = dict->left;
                temp->key = key_destroy(temp->key);
                temp->value = value_destroy(temp->value);
                free(temp);
            }else{
                dict_t temp = min_value_node(dict->right);
                dict->key = temp->key;
                dict->value = temp->value;
                dict->right = dict_remove(dict->right,temp->key);
            }
        }else
        {
            if (key_less(dict->key,word))
            {
                dict->right = dict_remove(dict->right,word);
            }else
            {
                dict->left = dict_remove(dict->left,word);
            } 
            
        }
    }
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    dict = dict_destroy(dict);
    dict = dict_empty();
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    if (dict != NULL)
    {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        printf(" : ");
        key_dump(dict->value, file);
        printf("\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    if(dict != NULL)
    {
        dict->right = dict_destroy(dict->right);
        dict->left = dict_destroy(dict->left);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict = NULL;
    }else
    {
        free(dict);
        dict = NULL;
    }
    return dict;
}

