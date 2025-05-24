#include <stdio.h>

int add(int a, int b){
	return ((a)+(b));
}

int multiply(int a, int b){
	return ((a)*(b));
}

int divide(int a,  int b){
	return (b != 0) ? ((a)/(b)) : 0;
}

int subtract(int a, int b){
	return ((a)-(b));
}

int main(void){

	int (*operations[4])(int, int);
	int num = -1, a, b;

	operations[0] = &add;
	operations[1] = &multiply;
	operations[2] = &divide;
	operations[3] = &subtract;

	do{
		puts("Enter the number of operation\n 0 - add\n 1 - multiply\n 2 - divide\n 3 - subtract");
		scanf("%d", &num);
	}while(num < 0 || num > 3);
	puts("Enter A:\n");
	scanf("%d", &a);
	puts("Enter B:\n");
	scanf("%d", &b);
	printf("Operation is %d Result is %d\n", num, operations[num](a,b));

	return (0);
}
