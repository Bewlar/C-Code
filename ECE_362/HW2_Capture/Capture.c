/***
    Capture:
	Program accepts string argument to create a new file
	Checks for valid arg and doesn't already exist
	Filter program reads STDIN and writes to STDOUT and new file
	Any errors displayed should be on STDERR

	@inputs - string argument through STDIN
	@outputs - STDOUT and file update
	@errorchecking - Errors reported in STDERR
*/

//char validateArgCheck(char *string);

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

    int FileDescription;
    int bytesreturned;
    int bytesreturned2;
    char buf[8000];
	
	//1.) Read String Bytes for Inputting- argv
	//2.) Check if file exists, write the newly created file.
    FileDescription = open(argv[1], O_CREAT | O_WRONLY | O_EXCL, S_IRWXU);

    //3.) Error check - Failures enabled O_EXCL
    if(FileDescription == -1){
		write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
        
        exit(-1);
    }
	
	while(1){
		//4.) Read STDIN
		bytesreturned = read(STDIN_FILENO,buf,8000);
		if(bytesreturned == -1){
			write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
			exit(-1);
		}
		
		//5.)Ctl+d Exit
		if(bytesreturned == 0){
			break;
		}
		
		//6.) Write to STDOUT & File
		bytesreturned2 = write(STDOUT_FILENO,buf,bytesreturned);
		if(bytesreturned2 == -1){
			write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
			exit(-1);
		}

		//7.) Write to FILE
		bytesreturned2 = write(FileDescription,buf,bytesreturned);
		if(bytesreturned2 == -1){
			write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
			exit(-1);
		}
	}
	
    return 0;
}

