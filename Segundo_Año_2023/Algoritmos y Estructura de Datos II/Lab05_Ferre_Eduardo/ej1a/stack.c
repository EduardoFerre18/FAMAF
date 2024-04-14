#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    struct _s_stack *next;
};

stack stack_empty(){
	stack s = NULL;
	return s;
}

stack stack_push(stack s, stack_elem e){
	stack p =  malloc(sizeof(stack));
	p->elem = e;
	p->next = s;
	s = p;
	return s;
}

stack stack_pop(stack s){
	stack p = NULL;
	p = s;
	s = s->next;
	free(p);
	return s;
}

unsigned int stack_size(stack s){
	stack p;
	unsigned int n = 0;
	p = s;
	
	while (p != NULL) {
		n = n+1;
		p = p->next;
	}
	
	return n;
}


stack_elem stack_top(stack s){
	assert(s != NULL);
	stack_elem e = s->elem;
	return e;

}

bool stack_is_empty(stack s){
	return (s == NULL);
}

stack_elem *stack_to_array(stack s){
	stack_elem *array = NULL;
	
	if (s == NULL) {
		return NULL;
	}
	
	stack p = s;
	unsigned int size = stack_size(s)-1;
	array = calloc(stack_size(s), sizeof(stack_elem));
		
	while(p != NULL){
		array[size] = stack_top(p);	
		p = p->next;
		size--; 
	}
	
	free(p);
	return array;	
	
}

stack stack_destroy(stack s){
	stack p = NULL;
	p = s;
	while (s!= NULL){
		p = s;
		s = s->next;
		free(p);
	}
	return s;
}


