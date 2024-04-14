#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    pqueue_elem elem;
    unsigned priority;
    struct s_node *next;    
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
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

static bool invrep(pqueue q) {
    bool res = true;
    if (q == NULL){
        return false;
    }
    else {
        struct s_node *p = q->front;
        while (res && p != NULL && p->next != NULL){
            res = res && p->priority <= p->next->priority;
            p = p->next;
        }
    }
    return res;
}

pqueue pqueue_empty(void) {
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    q->front = NULL;
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if (q->front == NULL || priority < q->front->priority){
        new_node->next = q->front;
        q->front = new_node;
    }
    else {
        struct s_node *p = q->front;
        while (p->next!= NULL && priority >= p->next->priority) {
            p = p->next;
        }
        new_node->next = p->next;
        p->next = new_node;

    }
    q->size++;
    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return (q->size == 0);
}

pqueue_elem pqueue_peek(pqueue q) {
    return q->front->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node * killme=q->front;
    q->front = q->front->next;
    q->size--;
    killme = destroy_node(killme);
    free(killme);
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node=q->front;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
