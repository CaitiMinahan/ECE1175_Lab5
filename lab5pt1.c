//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int result = 0; 
	const long long int repeating_time = 2000000000;
	
	//randomly initialize the matrices:
	srand((unsigned)time(NULL)); 
	
	//set up timer
	clock_t start_time = clock(); 

	for(long int i = 0; i<repeating_time; i++){ 
		if(result>1000){ result -= 1;}
		else{ result += 1; }
	}

	clock_t end_time = clock(); 
	float elapse = (float)(end_time - start_time)/CLOCKS_PER_SEC; 
	printf("Execution time: %.4f seconds\n", elapse); 
	
	return 0;
}

