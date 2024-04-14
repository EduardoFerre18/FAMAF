#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node **array;
    priority_t min_priority;
    unsigned size;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = calloc(1, sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pqueue q)
{   
    bool b=true;
    if (q->size==0) {   
        for (unsigned int i = 0; i < q->min_priority+1 ; i++){
            b = q->array[i] == NULL;
        }
    }
    else{
        bool existe=false;
        for (unsigned int i = 0; i < q->min_priority+1 && !(existe) ; i++) {
            existe = q->array[i] != NULL;
        }
        b = existe && q->size > 0;
    }
    return b;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    q = calloc(1, sizeof(struct s_pqueue));
    q->size = 0;
    q->min_priority = min_priority;
    q->array = calloc(min_priority + 1, sizeof(struct s_node));
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    q->size = q->size+1;
    struct s_node *newnode = create_node(e);
    if (q->array[priority] == NULL) {    
        q->array[priority] = newnode;
    }
    else {
        struct s_node *aux=NULL;
        aux=q->array[priority];

        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newnode;
    }
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}
bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return (q->size == 0);
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem p;
    bool b = true;
    for (unsigned int i = 0; i <= q->min_priority+1 && b; i++) {
        if (q->array[i] != NULL)
        {
            p = q->array[i]->elem;
            b = false;
        }
    }
    return p;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t p;
    bool b = true;
    for (unsigned int i = 0; i <= q->min_priority +1 && b; i++) {
        if (q->array[i] != NULL)
        {
            p = i;
            b = false;
        }
    }
    return p;
}

size_t pqueue_size(pqueue q){
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q){
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t p;
    bool b = true;
    for (unsigned int i = 0; i < q->min_priority+1 && b; i++){
        if (q->array[i] != NULL) {
            p = i;
            b = false;        
        }
    }

    if (q->array[p]->next == NULL) {
        q->array[p] = destroy_node(q->array[p]);
    }
    else {   
        struct s_node *aux=NULL;
        aux = q->array[p];
        q->array[p] = q->array[p]->next;
        aux = destroy_node(aux);
    }
    q->size = q->size-1;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q){
    assert(invrep(q));
    while (q->size != 0) {
        q = pqueue_dequeue(q);
    }
    free(q->array);
    q->array = NULL;
    free(q);
    q=NULL;
    return q;
}
