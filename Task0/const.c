#include <stdio.h>

int main(void){

//0.	We cannot change const var
	const int x = 1;
//	x = 10;
	

//1. POINTER to VARIABLE
//   - WE CAN CHANGE ADDR
//   - WE CAN CHANGE VALUE
{	int a = 10, b = 20;
	int *ptr = &a;
	*ptr = 100;  // Modifies `a`
	ptr = &b;    // Now `ptr` points to `b`

}
//2. POINTER to CONSTANT
//    - WE CAN CHANGE ADDR
//    - WE CANNOT CHANGE VALUE	
{
	const int a = 10, b = 20;
	const int *ptr = &a;
	// *ptr = 100;  // Error: Cannot modify the value of `a`
	ptr = &b;      // Valid: Now `ptr` points to `b`
}
//3. CONSTANT POINTER to VARIABLE
//	- WE CANNOT CHANGE ADDR
//	- WE CAN CHANGE VALUE
{
	int a = 10, b = 20;
	int *const ptr = &a;
	*ptr = 100;  // Modifies `a`
	// ptr = &b;  // Error: Cannot reassign `ptr`
}
//4. CONSTANT POINTER to CONSTANT VARIABLE
//	- WE CANNOT CHANGE ADDR
//	- WE CANNOT CHANGE VALUE
{
	const int a = 10, b = 20;
	const int *const ptr = &a;
	// *ptr = 100;  // Error: Cannot modify the value of `a`
	// ptr = &b;    // Error: Cannot reassign `ptr`
}
	return (0);
}
