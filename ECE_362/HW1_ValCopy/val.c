#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*** This code scans a user input with command and will add or
	multiply the values. The key argument is -m or nothing specified.
	The program should process argv and argc parameters to main.
	A separate makefile is included which should use help, compile, test and clean.
	REQUIRED INPUT FOR ADDDITION IS 1 VALUE, 2 INPUTS REQUIRED FOR MULTIPLICATION...
	
	@user inputs - Signed integers (-2147483647 to 2147483647)
	@outputs - Added or multiplied set
	@errorchecking - Checks for invalid inputs that are non numbers.
*/

int main(int argc, char *argv[]){
	
	int total = 0;
	int count = 1;
	int i = 0;
	
	//MULTIPLY MODE - Start past -m
	if(strcmp(argv[count],"-m") == 0){
		total = atoi(argv[count+1]);
			for (i=0;i<strlen(argv[count+1]);i++){//BASE CASE FIRST VALUE
					if(!isdigit((argv[count+1][i]))){
						printf("Bad non-number found! Value is %c\nEXITING\n\n",argv[count+1][i]);
						exit(0);
					}
			}
		for (count=2; count<argc-1; count++){
			for (i=0;i<strlen(argv[count+1]);i++){//REGULAR CASES AFTER FIRST VALUE 
				if(!isdigit((argv[count+1][i]))){
					printf("Bad non-number found! Value is %c\nEXITING\n\n",argv[count+1][i]);
					exit(0);
				}
			}
			total = total * atoi(argv[count+1]);
			
		}
	}
	//ADDITION MODE - Start at "-m" position
	else{
		for (count=1; count<argc; count++){
			for (i=0;i<strlen(argv[count]);i++){
				if(!isdigit((argv[count][i]))){
					printf("Bad non-number found! Value is %c\nEXITING\n\n",argv[count][i]);
					exit(0);
				}
			}
			total = total + atoi(argv[count]);
		}
	}		
	
	printf("The total is %d\n\n", total);
	return 0;
}	


//POSSIBLE ERROR SUMMARY
/*
Letters

Debug print if needed
//printf("argv i[%d]order is %c\n", i,argv[count+1][i]);
*/