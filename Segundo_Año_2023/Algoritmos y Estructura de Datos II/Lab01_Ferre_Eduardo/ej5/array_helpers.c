#include "array_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mybool.h" 

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    unsigned int array_size;
    FILE *fp;
    int r = 0;

    fp = fopen (filepath, "r");
    
    assert (fp != NULL); 
    
    r = fscanf(fp, "%u", &array_size);
  
    assert (r != EOF);
    
    assert (array_size <= max_size);
    
    for (unsigned int i = 0; i < max_size && i < array_size; i++) {
    	r = fscanf(fp, "%d", &array[i]);
	assert (r != EOF);    	
    }
    
    fclose(fp);
    
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

mybool array_is_sorted(int a[], unsigned int length) {
	
	if (length == 0) {
		return true;
	}
	else {	
		for (unsigned int i = 0; i < length-1; i++) {
		
			if ((a[i] >= a[i+1]) ) {
			return false;
			}	
		} 
	}
	return true;
}



