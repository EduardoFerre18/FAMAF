#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int
data_from_file(FILE *file,
			unsigned int indexes[],
			char letters[],
			unsigned int max_size){
			
    unsigned int i = 0u;
    
    while (i < max_size && fscanf(file, "%u -> *%c*\n", &indexes[i], &letters[i]) == 2) {
        i++;
    }
 
   if (!feof(file) && fscanf(file, "%u -> %c\n", &indexes[i], &letters[i]) != 2) {
        perror("Error de lectura del archivo");
    }

    return i;
}			




void sort_by_indexes(unsigned int indexes[], char letters[], char sorted[], unsigned int length) {
    for (unsigned int i = 0u; i < length; i++) {
        sorted[indexes[i]] = letters[i];  
    }
}

int main(int argc,char *argv[]) {
    FILE *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0;
    
    
    if (argc < 2) {
        printf("Uso: %s archivo_de_entrada\n", argv[0]);
        return 1;
    }
    
    file = fopen(argv[1], "r");
    if (file == NULL) {
		perror("Error no se ha podido abrir el archivo");
		return 1;
	}
    
    length = data_from_file(file, indexes, letters, MAX_SIZE);
    
    sort_by_indexes(indexes, letters, sorted, length);

    dump(sorted, length);
    
    fclose(file);

    return EXIT_SUCCESS;
}

