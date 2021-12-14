/***

	@inputs
        1 flags(-l or -u or combination of both)
		2 Alphabetic characters(any ASCII value also)
	@outputs
		1 -l alphabetic characters output in lowercase
		2 -u alphabetic characters output in uppercase
		3 -l -u or -u -l uppercase -> lowercase output and lowercase -> uppercase output
	
	@assumptions
		1 input of -l and -u will be in argv[1] and argv[2] in either order
		2 character inputs may contain symbol ASCII. Need the range of a-z and A-Z in value. 
		3 character flipping will have 3 modes - mode 1 flip to lower, mode 2 flip to upper, mode 3 flip both
		
	@errorchecking
        1 Name of file validity
        2 Line sequence validity 0<value<=100, Non existent lines return 0
*/

//USER INCLUDES
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//EO USER INCLUDES

#define mincharlower 'a'
#define maxcharlower 'z'
#define mincharupper 'A'
#define maxcharupper 'Z'

void Filecheck(int ByteReturned);

int main(int argc, char *argv[]){
    //Buffers
	char linestring [8192];
	char* message = malloc(sizeof(*message));
	//Vague Items
	int bytesreturned;
	//int bytesreturned2;
	int modeupper = 0;
	int modelower = 0;
	int modeboth = 0;
	//Hard Limits
	int maxasciichar = 255;
	int minasciichar = 0;
	//Counters
	int i;
	int resetflag;

	
	
	
	//3.)FLAG VALIDATION CMD LINE PROGRAM INPUT 
	//-l | -u | both
	for(i=1; i<argc; i++){ //Note strlen(linestring) didn't work here for some reason
		//Lower flag 
		if (strcmp(argv[i],"-l")==0){
			//sprintf(message,"Found lowercase flag\n");//Debug 
			//bytesreturned2 = write(STDERR_FILENO,message,strlen(message));
			//Filecheck(bytesreturned2);
			modelower = 1;
		}
		//Upper Flag
		if (strcmp(argv[i],"-u")==0){
			//sprintf(message,"Found uppercase flag\n");//Debug 
			//bytesreturned2 = write(STDERR_FILENO,message,strlen(message));
			//Filecheck(bytesreturned2);
			modeupper = 1;
		}
		//Both Flag
		if ((modelower == 1) && (modeupper == 1)){
			//sprintf(message,"Found both flags\n");//Debug 
			//bytesreturned2 = write(STDERR_FILENO,message,strlen(message));
			//Filecheck(bytesreturned2);
			modeboth = 1;
		}
	}
	
	
	
	//MAIN LOOP
    while(1){
		
		//1.)Prompt User to Input characters
		//sprintf(message, "Write a sequence of characters followed by enter key or press control-d to exit\n");
		//bytesreturned = write(STDOUT_FILENO,message,strlen(message));
		Filecheck(bytesreturned);
		
		//2.)Read UserInput character stream from STDIN
		bytesreturned = read(STDIN_FILENO,linestring,8192);
		Filecheck(bytesreturned);
		
		//2.5)Exit if CTL+D
		if(bytesreturned == 0) {
			//sprintf(message,"Ctl+d, Terminating\n");
			//bytesreturned = write(STDERR_FILENO,message,strlen(message));
			exit(0);
		}
		
		
		//2.75)RESET ALL FLAGS
		resetflag = 0; 
		
		
		//3.)ASCII Validation
		//-l | -u | both
		for(i=0; i<bytesreturned-1; i++){ //Note strlen(linestring) didn't work here for some reason
			//ASCII Check
			if ((linestring[i] < minasciichar) || (linestring[i] > maxasciichar)){
				//sprintf(message,"Found error in ascii input, exiting\n");
				//bytesreturned2 = write(STDERR_FILENO,message,strlen(message));
				//Filecheck(bytesreturned2);
				resetflag = 1;
				if(resetflag == 1){continue;}//Reset the loop, bad STDIN
			}
		}
		//Flags validated for conversion mode, ASCII validated to continue
		
		
		//4.)Convert values based on ASCII
		for(i=0; i<bytesreturned-1; i++){
			
			//Convert uppwer or lower check
			if( (linestring[i] <= maxcharlower) && (linestring[i] >= mincharlower) && (modeboth == 1 || modeupper == 1) ){
				//Convert lower to upper 
				linestring[i] ^= 0x20; //Stanford flip 5th bit to convert https://web.stanford.edu/class/cs107/lab1/practice.html
			
			}else if( (linestring[i] <= maxcharupper) && (linestring[i] >= mincharupper) && (modeboth == 1 || modelower == 1) ){
				//Convert upper to lower
				linestring[i] ^= 0x20; //Stanford flip 5th bit to convert +32
			}
		}
		//String has been converted for ASCII symbols, ready to output to terminal window
		
		
		//5.)WRITE CHARS TO STDOUT
		bytesreturned = write(STDOUT_FILENO,linestring,bytesreturned);
		//End of char input and output, repeat
    }
	return 0;
}




void Filecheck(int ByteReturned){
	if(ByteReturned == -1){
        write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
		write(STDERR_FILENO,"\n",strlen("\n"));
        exit(-1);
	}
	
}