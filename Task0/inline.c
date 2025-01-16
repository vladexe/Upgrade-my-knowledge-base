#include <stdio.h>


// So first o
// in binary files with gcc -O3 -o inline_o3 inline.c will be no foo function call
// and in binary with gcc -o inline inline.c will be the foo function call
//
static inline int foo(int a, int b) {

	return (a*b);
}

int main(void){

	printf("Test the inline and non-inline behaviour %d\n", foo(4,5));

}
