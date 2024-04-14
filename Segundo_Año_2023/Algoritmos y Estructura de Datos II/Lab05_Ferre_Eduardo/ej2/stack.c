#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

static bool invrep(stack s){
	return s != NULL;
}

stack stack_empty(){
	stack s = NULL;
	s = malloc(sizeof(struct _s_stack));
	s->size=0u;
	s->capacity = 1u;
	s->elems= malloc(sizeof(stack_elem));
	return s;
}

stack stack_push(stack s, stack_elem e){
	if (s->size == s->capacity){
		s->capacity = 2u * s->capacity;
		s->elems = realloc(s->elems,s->capacity * sizeof(stack_elem));
	}
	s->elems[s->size]= e;
	s->size++;
	return s;
}

stack stack_pop(stack s){
	assert(invrep(s));
	s->size--;
	return s;
}

unsigned int stack_size(stack s){
	return s->size;
}


stack_elem stack_top(stack s){
	assert(invrep(s));
	return s->elems[s->size-1];
}

bool stack_is_empty(stack s){
	return (s->size == 0);
}

stack_elem *stack_to_array(stack s){
	assert(invrep(s));
	stack_elem *new_array = calloc(s->size, sizeof(stack_elem));
	for (unsigned int i = 0u; i < s->size; i++){
		new_array[i] = s->elems[i];
	}
	return new_array;
}

stack stack_destroy(stack s){
	assert(invrep(s));
	free(s->elems);
	free(s);
	return s;
}

