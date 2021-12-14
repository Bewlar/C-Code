//thread1
/***

	@inputs
        -t <num> number of threads
	@outputs
		Prints Thread ID
	
	@assumptions
		Uses 1 4 or 8 threads
   
	@errorchecking
        Checks for Thread count correctly 1 4 or 8
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
#include <pthread.h>
//EO USER INCLUDES


//Functions
void *PrintPID();


//MAIN@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int main(int argc, char *argv[]){
	int threadcount = atoi(argv[2]);
	int i;
	int returncondition;

	//printf("threadcount is %d\n",threadcount);
	//Check proper integer
	if(threadcount != 1 && threadcount != 4 && threadcount != 8){//|| threadcount != 4 || threadcount != 8){
		printf("Error, threadcount outside of 1, 4 or 8 bounds.\n");
		exit(0);
	}

	pthread_t thread[threadcount];
	


	//Create Threads
	for(i=0; i<threadcount; i++){
		int returncond = pthread_create(&thread[i], NULL, PrintPID, NULL);
		if(returncond != 0){
			printf("Error creating thread\n");
			exit(1);
		}
	}
	
	//Join threads
	for(i=0; i<threadcount; i++){
		returncondition = pthread_join(thread[i],NULL);
		//printf("Joined thread %d\n",i);
		if(returncondition != 0){
			printf("Error: Joining Thread\n");
			exit(1);
		}
	}
	return 0;
}
//MAIN@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//Function Full Definitions
void *PrintPID (){
	sleep(1);
	printf("Thread ID = %d \n",  (int) pthread_self());
	pthread_exit(NULL);
	return 0;
}