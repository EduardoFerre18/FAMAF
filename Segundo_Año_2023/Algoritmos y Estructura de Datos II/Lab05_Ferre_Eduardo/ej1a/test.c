#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main (){
	
	stack s = stack_empty();
	stack p = stack_empty();
	
	s = stack_push(s, 99);
	printf("El tamaño de la pila es: %u\n", stack_size(s));
	
	s = stack_pop(s);
	printf("Una vez elminando el unico elemento de la pila, el tamaño de la pila es: %u\n", stack_size(s));
	
	s = stack_push(s,101);
	printf("Insertando un elemento a una pila vacia, el tamaño de la pila es: %u\n", stack_size(s));
	
	for (unsigned int i = 0; i < 5; i++){
		p = stack_push(p,i);
	}
	
	stack_elem *a = stack_to_array(p);
	
	for (unsigned int i = 0; i < stack_size(p); i++){
		printf("El elemento %d es %d\n",i, a[i]);
	}
	
	s = stack_destroy(s);
	p = stack_destroy(p);
	free(a);
	
	return 0;
	
	

}
