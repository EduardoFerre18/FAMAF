#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char *str){
	size_t size = 0u;
	while(str[size] != '\0'){
		size++;
	}
	return size;
}

char *string_filter(const char *str, char c){
	size_t size = string_length(str);
	char *str2 = malloc(sizeof(str) * size);
	unsigned int i = 0;
	unsigned int j = 0;
	
	while (str[i] != '\0'){
		if (str[i]!= c){
			str2[j] = str[i];
			j++;
		}
		i++;
	}
	return str2;
}


