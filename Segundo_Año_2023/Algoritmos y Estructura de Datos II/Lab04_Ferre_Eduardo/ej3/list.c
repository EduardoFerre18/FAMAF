#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct node_t{
    list_elem elem;
    struct node_t *next;
};

list empty(void){
	list l = NULL;
	return l;
}

list addl(list_elem e, list l){
	list p = malloc(sizeof(list_elem));
	p->elem = e;
	p->next = l;
	l = p;
	return l;
}



bool is_empty(list l){
	return (l == NULL);
}

list_elem head(list l){
	assert(!is_empty(l));
	return l->elem;
}

list tail(list l){
	assert(!is_empty(l));
	list p = l;
	l = l->next;
	free(p);
	return l;
}

list addr(list_elem e, list l){
	list p, q;
	q = malloc(sizeof(struct node_t));
	p = l;
	if (p != NULL){
		while (p->next != NULL){
			p = p->next;
		}
		q->elem = e;
		q->next = NULL;
		p->next = q; 
	}
	else {
		q->elem = e;
		q->next = NULL;
		l = q;
	}

	return l;
}

unsigned int length(list l) {
	unsigned int n = 0;
	list p = l;
	while (p != NULL){
		n = n+1;
		p = p->next;
		
	}
	return n;
}

list concat(list l, list l0){
	list p,q;
	p = l;
	q = copy_list(l0);
	if (p != NULL){
		while (p->next != NULL){
		p = p->next;
		}
		p->next = q;
	}
	else {
		l = q;
	}
	return l;
}


list_elem index(list l, unsigned int n){
	assert(length(l) > n);
	list p = l;
	for (unsigned int i=0u; i < n; i++) {
		p = p->next;
	}
	return p->elem;
}

list take(list l, unsigned int n){
	list p, q;
	unsigned int i = 0u;
	p = l;
	if (n == 0) {
		l = NULL;
		destroy(p);
	}
	else if (l != NULL){
		while (p->next != NULL && i < n-1) {
			p = p->next;
			i++;
		}
		q = p->next;
		p->next = NULL;
		destroy(q);
	}
	return l;
}


list drop(list l, unsigned int n){
	unsigned int i = 0u;
	while (l != NULL && i < n){
		l = tail(l);
		i++;
	}
	return l;
}



list copy_list(list l){
	list p;
	list l1;
	p = l;
	l1 = empty();
	while (p != NULL) {
		l1 = addr(p->elem, l1);
		p = p->next;
	}
	return l1;
}

void destroy(list l) {
    while (l != NULL) {
        list p = l;
        l = l->next;
        free(p);
    }
}

