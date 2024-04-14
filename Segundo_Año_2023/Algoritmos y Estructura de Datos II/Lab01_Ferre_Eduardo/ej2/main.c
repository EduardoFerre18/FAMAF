/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000



unsigned int array_from_stdin(int array[],
                             unsigned int max_size) {
    unsigned int array_size;
    
    FILE *fp;
    
    fp = stdin;
    
    printf("Ingrese el tamaño del arreglo\n");
    
    fscanf(fp, "%u", &array_size);
    
    assert (array_size <= max_size);
    
    for (unsigned int i = 0; i < array_size && i < max_size; i++) {
    	printf ("Ingrese el valor en la posicion %d\n", i);
    	fscanf(fp, "%d", &array[i]);
    }
    
    return array_size;
    
}

void array_dump(int a[], unsigned int length) {
    printf ("[");
    
    if (length > 0) {
    	for (unsigned i = 0; i < length-1; i++) {
    		printf ("%d, ", a[i]);
    	}
    	printf ("%d", a[length-1]);
    }
    printf ("]");
    printf ("\n");


}


int main() {
    //char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    //filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
