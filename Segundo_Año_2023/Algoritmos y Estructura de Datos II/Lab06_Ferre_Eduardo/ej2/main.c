#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

#define MAX_LENGTH 100

int main()
{
    char word1[MAX_LENGTH];
    char word2[MAX_LENGTH];

    printf("Ingrese la primera palabra que quiere comparar: ");
    scanf("%s", word1);

    printf("Ingrese la segunda palabra que quiere comparar: ");
    scanf("%s", word2);

    string s1,s2;
    s1 = string_create(word1);
    s2 = string_create(word2);

    bool res1 = string_less(s1,s2);
    bool res2 = string_eq(s1,s2);

    if (res1) {
    
        printf("%s es alfabeticamente menor\n", word1);
    }
    else {
         if (res2) {
            printf("Las palabras son iguales\n");
        }
        else {
        printf("%s es alfabeticamente menor\n", word2);
        } 
    }
    s1 = string_destroy(s1);
    s2 = string_destroy(s2);
    
    return EXIT_SUCCESS;
} 
