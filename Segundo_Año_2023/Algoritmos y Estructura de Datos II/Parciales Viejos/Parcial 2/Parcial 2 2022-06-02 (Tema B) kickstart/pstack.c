#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *front;    
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next; 
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool res = true;
    if (s == NULL) {
        return false;
    }
    else {
        struct s_node *p = s->front;
        while(res && p != NULL && p->next != NULL) {
            res = res && p->priority >= p->next->priority;
            p = p->next;
        }
    }  
    return res;
}

pstack pstack_empty(void) {
    pstack s =NULL;
    s = malloc(sizeof(struct s_pstack));
    s->size = 0u;
    s->front = NULL;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    s->size++;

    if (s->front == NULL || priority >= s->front->priority) {
        new_node->next = s->front;
        s->front = new_node;
    } else {
        struct s_node *current = s->front;
        while (current->next != NULL && priority < current->next->priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    assert(invrep(s));
    return s;
}



bool pstack_is_empty(pstack s) {
    return (s->size == 0);
}

pstack_elem pstack_top(pstack s) {
    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) {
    return s->front->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s));
    struct s_node *p = NULL;
    p = s->front;
    s->front = (s->front)->next;
    s->size--;
    p->next = NULL;
    free(p);
    p = NULL;
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node = s->front;
    while (node != NULL) {
        struct s_node *killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

