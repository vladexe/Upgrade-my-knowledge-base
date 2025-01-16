
volatile int status = 0;

// It's hard to show real example on this stage but on point that i understand
// In this case I have declared the status with 0
// but in real case for example if we did in the next way
//
// volatile int* status = 0x0fff0000 
//
// And declare some memory port address
// In our programm compliler will not see any changes, but if we changed the 
// value on that address from another programm and manually our program will 
// never see it until we declared the variable as volatile


int main(void){

	while (status == 0)
	{
		//infinity loop until we change the status outside of the 
		//program
	}
}
