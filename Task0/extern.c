#include<stdio.h>

// EXTERN is used for variable to clarify for compiler 
// that it is not variable definition and we don't need 
// to create a new one variable in memory
extern int a;
// EXTERN is only used for declaration function
// when line ends with ";"
extern int add(int a, int b);

int main(void){

	int x;
	x = add(56, 0);
	printf("Sum of the = %d", x);

	return (0);
}
