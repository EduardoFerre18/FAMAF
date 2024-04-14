#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    unsigned int size;
    struct _s_stack *next;
};

static bool invrep(stack s){
	return s != NULL;
}

stack stack_empty(){
	stack s = NULL;
	s = malloc(sizeof(struct _s_stack));
	s->next = NULL;
	s->size =0;
	assert(invrep(s));
	return s;
}

stack stack_push(stack s, stack_elem e){
	stack p = NULL; 
	p =  malloc(sizeof(struct _s_stack));
	p->elem = e;
	p->size = s->size + 1;
	p->next = s;
	assert(invrep(s));
	return p;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    stack p = s;
    unsigned int tmp = s->size;
    s = s->next;
    free(p);
    p = NULL;
    if(!stack_is_empty(s)){
    	s->size = tmp - 1u;
    }
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s){
	assert(invrep(s));
	int size = 0;
	if (s!=NULL){
		size = s->size;
	}
	return size;
}


stack_elem stack_top(stack s){
	assert(!stack_is_empty(s));
	stack_elem e = s->elem;
	return e;

}

bool stack_is_empty(stack s){
	assert(invrep(s));
	return (s->size == 0);
}

stack_elem *stack_to_array(stack s) { 
   unsigned int len = stack_size(s);
    stack_elem *array = calloc(len, sizeof(stack_elem));
    stack p = s;
    for (unsigned int i = len; i > 0; --i){
        array[i-1] = p->elem;
        p = p->next;
    }     
    return array;
}

stack stack_destroy(stack s) {
    assert(invrep(s));
    stack p = NULL;
    while (s != NULL) {
        p = s;
        s = s->next;
        free(p);
    }
    return s;
}


