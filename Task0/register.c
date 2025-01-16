#include<stdio.h>
#include<time.h>

// register cannot be a global variable
// register int q = 2;

int main(void){
	//So if we declared the register variable it will be store faster than
	//non-register, but also this variable will have not own addr as it 
	//will be stored in register
	//
	//register.c:7:9: error: address of register variable ‘u’ requested

	//register int u = 0;	
	int u = 0;
	printf("\nAddr: u= %p", &u);

	clock_t start, end;

    	// Test with register variable
    	start = clock();
    	register int i;
    	for (i = 0; i < 2000000000; i++) {
        	// Increment loop
    	}
    	end = clock();
    	printf("\nTime with register: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    	// Test without register variable
    	start = clock();
    	int j;
    	for (j = 0; j < 2000000000; j++) {
        	// Increment loop
    	}
    	end = clock();
    	printf("Time without register: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	return(0);
}
