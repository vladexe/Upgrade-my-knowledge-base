#include<stdio.h>
#include<time.h>

void foo_copy(int *aa, int *bb, int num){

	clock_t start, stop;

	start = clock();
	while(num-- > 0){
		bb[num] = aa[num];
	}
	stop = clock();
	printf("\nTime for copying without restrict arrays %f", (double)(stop-start) / CLOCKS_PER_SEC);
}

void foo_copy_restrict(int *restrict aa, int *restrict bb, int num){

	clock_t start, stop;

        start = clock();
	while(num-- > 0){
                bb[num] = aa[num];
        }
	stop = clock();
        printf("\nTime for copying with restrict arrays %f\n", (double)(stop-start) / CLOCKS_PER_SEC);
}

int main(void){

	int a[50000];
	int b[50000];

	for (int i = 0; i < 50000; i++) {
	    a[i] = i;
	}
	
	//Copying without restrict
	foo_copy(a, b, 50000);
	//Copying with restrict will increase the speed 
	foo_copy_restrict(a, b, 50000);

	return (0);
}
