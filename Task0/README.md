
**const**:

Create a program where a variable is declared as const and attempt to modify its value. Observe what happens. Use a pointer to try modifying the value indirectly and see if it's allowed. ALso play with const pointers and const variables. 

Useful links: https://www.geeksforgeeks.org/const-qualifier-in-c/

**static**:

Declare a static variable inside a function and call that function multiple times. Observe how the static variable retains its value between function calls.

Useful links: https://www.geeksforgeeks.org/memory-layout-of-c-program/
              https://www.geeksforgeeks.org/static-variables-in-c/

volatile:

Write a program where a volatile variable's value is updated within a loop by an external function or hardware simulation. Demonstrate how volatile ensures the program doesn't optimize away repeated reads of the variable.

inline:

Write a program with an inline function and call it multiple times in your code. Compare the output and behavior with a regular function by checking whether the compiler substitutes the function body directly.

register:

Declare a variable as register and use it in a loop with heavy computations. Compare its performance to a normal variable.
Check if you can take the address of a register variable (hint: try using the & operator).
