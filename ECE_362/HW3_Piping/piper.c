/***
    Piper
	Pipes to three children and takes input during flip stages, 
	See flip for input requirements
	Piper also should close all pips and end on CNTL D input
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Filecheck(int ByteReturned);

int main(int argc, char *argv[]){
	
	int LowChild, UpChild, LowUpChild;
	int piperlow[2];
	int piperhigh[2];
	int piperlowhigh[2];
	int fdlow = 0;
	int fdhigh = 0;
	int bytesreturned;
	argv[0] = "./flip";
	argv[2] = NULL;
	//Buffers
	char linestring [8192];
	char* message = malloc(sizeof(*message));
	
		
	//LOWER Pipe
	pipe(piperlow);
	LowChild = fork();
	Filecheck(LowChild);
	if (LowChild ==0) { 
		close(STDIN_FILENO); 					//Close STDIN for replacement
		dup(piperlow[0]);						//Put read to STDIN
		close(STDOUT_FILENO);					//Close STDOUT
		fdlow = open("lower.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);	//Open the lower text file to read and write
		Filecheck(fdlow);
		close(piperlow[1]);						//Child close write
		argv[1] = "-l";							//Setup lower 
		execv(argv[0],argv);					//Execute process with lower
		exit(0);
	}
	
	
	//UPPER Pipe
	pipe(piperhigh);
	UpChild = fork();
	Filecheck(UpChild);
	if (UpChild ==0) { 
		close(piperlow[0]);
		close(piperlow[1]);
		close(STDIN_FILENO);
		dup(piperhigh[0]);
		close(STDOUT_FILENO);
		fdhigh = open("upper.txt",  O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		Filecheck(fdhigh);
		//(fdhigh);
		//close(piperhigh[0]);
		close(piperhigh[1]);
		argv[1] = "-u";
		execv(argv[0],argv);
		exit(0);
	}
	
	
	
	//Double Pipe
	pipe(piperlowhigh);
	LowUpChild = fork();
	Filecheck(LowUpChild);
	if (LowUpChild ==0) {
		close(piperhigh[0]);
		close(piperhigh[1]);
		close(piperlow[0]);
		close(piperlow[1]);
		close(STDIN_FILENO);
		dup(piperlowhigh[0]);
		//close(STDOUT_FILENO);
		//dup(piperlowhigh[0]);
		//close(piperlowhigh[0]);
		close(piperlowhigh[1]);
		argv[1] = "-u";
		argv[2] = "-l";
		argv[3] = NULL;
		execv(argv[0],argv);
		exit(0);
	}
	
	
	// Parent - Read from STDIN, send to children
	while((bytesreturned = read(STDIN_FILENO,linestring,8192)) > 0){
	//bytesreturned = read(STDIN_FILENO,linestring,8192);			//Parent Process read the input
	//Write to all pipes for 3 cases
	write(piperlow[1],linestring,bytesreturned); 
	write(piperhigh[1],linestring,bytesreturned);
	write(piperlowhigh[1],linestring,bytesreturned);
	}
	
	//Check for ctl+d
	//sprintf(message,"Ctl+d, Terminating\n");
	//bytesreturned = write(STDERR_FILENO,message,strlen(message));
	close(fdhigh);
	close(fdlow);
	//Close read end
	close(piperhigh[0]);
	close(piperlow[0]);
	close(piperlowhigh[0]);
	//Close write end
	close(piperhigh[1]);
	close(piperlow[1]);
	close(piperlowhigh[1]);
	//Reap it all
	wait(NULL);
	wait(NULL);
	wait(NULL);
	exit(0);
}

void Filecheck(int ByteReturned){
	if(ByteReturned == -1){
        write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
		write(STDERR_FILENO,"\n",strlen("\n"));
        exit(-1);
	}
}

