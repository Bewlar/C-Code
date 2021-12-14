/***

	@inputs
        1 Takes name of file - Stores into buffer
        2 Line number sequence followed by enter key - Prints out each line of text
		
	@outputs
		1 Displays line of text
		
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

void Filecheck(int ByteReturned);

int main(int argc, char *argv[]){
    
	char linestring [8192];
	char filestring [8192];
	char* message = malloc(sizeof(*message));
	
    int FileDescription;
	int bytesreturned;
	int linerequestconversion;
	
	int maxnumber = 100;
	int minnumber = 1;
	int resetflag = 0;
	
	int i;
	int startreadingposition;
	

	//1.) Take filename - argv [1] filename - Return errorcode and exit if faulty 
    FileDescription = open(argv[1], O_RDONLY,0777);
	Filecheck(FileDescription);
	//->File opened, ready to read

	//Read FileDescription into a buffer for parsing later
	bytesreturned = read(FileDescription,filestring,8192);
	Filecheck(bytesreturned);
	//Set last byte to \n to stop algorithm - Rishitosh recommended
	filestring[bytesreturned] = '\n';


    //x.) Prompt user for line and display the lines insequence to output, exit using ctl+d
    while(1){
		
		//Prompt User to Input Line Number
		sprintf(message, "Write a sequence of line numbers followed by enter key or press control-d to exit\n");
		bytesreturned = write(STDOUT_FILENO,message,strlen(message));
		Filecheck(bytesreturned);


		
		//Read UserInput Line# from STDIN
		bytesreturned = read(STDIN_FILENO,linestring,8192);
		Filecheck(bytesreturned);
		//Exit if CTL+D
		if(bytesreturned == 0) {
			sprintf(message,"ctl+d, exiting\n");
			bytesreturned = write(STDERR_FILENO,message,strlen(message));
			exit(0);
		}

		
		
		resetflag = 0; //Reset the Reset Flag
		//Validate - Check the string for only numbers, ignore newline
		for(i=0; i<bytesreturned-1; i++){ //Note strlen(linestring) didn't work here for some reason
			if ((linestring[i] < '0')||('9' <linestring[i])){
				sprintf(message,"Invalid characters|Use integers 0-9|prefix 0's acceptable\n");
				bytesreturned = write(STDERR_FILENO,message,strlen(message));
				Filecheck(bytesreturned); //Invalid input, need to reset loop
				resetflag = 1;
				break;
			}				
		}
		if(resetflag == 1){continue;}//Reset the loop
		//Else the line number is almost valid
		
		
		
		//Validate Confirmed - Convert to Integer & Validate Check 1-100
		linerequestconversion = atoi(linestring);//atoi already converts without adding '\0' therefore I ommitted it, note the \n addition above while(1)
		if((linerequestconversion > maxnumber) || (linerequestconversion < minnumber)){
			sprintf(message,"Invalid line #. Valid(1-100)\n");
			bytesreturned = write(STDERR_FILENO,message,strlen(message));
			Filecheck(bytesreturned);
			resetflag = 1; //Invalid input, need to reset loop
		}
		if(resetflag == 1){continue;}//Reset Loop again
		//Else the line number has been generated, continue
		
		
		
		
		//Begin looking into the buffer for the line number start position
		startreadingposition = 0;
		for (i=1;i<linerequestconversion; i++){ 
			while(filestring[startreadingposition]!= '\n'){
				startreadingposition++; 
			}
			startreadingposition = startreadingposition+1; //Increment 1 to get over \n
		} 


		
		//Start Acquired, begin writing to output until newline \n
		while(filestring[startreadingposition]!='\n'){
			bytesreturned = write(STDERR_FILENO,(void*)&filestring[startreadingposition],1);
			Filecheck(bytesreturned);
			startreadingposition++;
		}
		sprintf(message,"\n");
		bytesreturned = write(STDERR_FILENO,message,strlen(message));
		Filecheck(bytesreturned);
		//Reset loop naturally;
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