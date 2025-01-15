#include<stdio.h>

void try_static(void);
//IT WILL BE STORED IN THE DATA SEGMENT
int global = 1;
//IT WILL BE STORED IN THE BSS
int flobal;

int main(void){

	printf("\ni first time:");
	try_static();
	printf("\ni next time:");
	try_static();
	return (0);
}

void try_static(void){
	// IT WILL BE STORED IN THE DATA SEGMENT TOO
	static int i = 10;
	// IT WILL BE STORED IN THE BSS
	static int d;
	// IT WILL BE STORED IN THE STACK
	int x;
	// IT WILL BE STORED IN THE STACK
	int y = 12;
	i=++i;
	printf("%d\n", i);

}
