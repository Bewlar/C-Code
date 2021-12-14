//Threaddit
/***

	@inputs
        -t <num> number of threads
        -s <num> Random seed. Uses srand() initialize randomization with seed
	@outputs
		Completely sorted array
   "Sort Complete" printed or an error message
	
	@assumptions
		This program breaks array into equally sized partitions
   Sorts the partitions in different threads
   Merge results back together, multistep process multiple threads merge partitions then those partitions merged after
   Simple routine at end checks final array in sorted order and prints "Sort Complete"
	Uses array size of 64,000 elements	
   
	@erroreturnconditionhecking
        Checks for valid # of threads and random seed
        Prints out error message if otherwise
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
#include <time.h> 
#include <pthread.h>
//EO USER INCLUDES


#define ArrayMax 64000
#define Debugs


//Global Vars
int array[ArrayMax];
int TempMax[ArrayMax];
int g;

typedef struct {
	int start; 
	int end;
	int size;
	int threads;
	} partition_t;


//Header Function Prototypes
void simpleroutine();
void *MyBubble(void *index);
void *MyBubble2 (int start, int end);
void Merge(int A[], int temp[], int left, int mid, int right);
void Mergesort(int A[], int temp[], int left, int right);
void *AlexSort(void *index);




//_____________________MAIN_____________________
int main(int argc, char *argv[]){

 //______1.) SETUP
 #ifdef Debug
 int i;
 #endif
 int seed = 0;
 int threadcount = 0;

 if(strcmp(argv[1],"-t") == 0){
	threadcount = atoi(argv[1+1]);
 }else{
	printf("Error, -t <arg> not specified correctly\n\n");
	exit(1);
 }
 if(strcmp(argv[3],"-s") == 0){
	seed = atoi(argv[3+1]);
 }else{
	printf("-s <arg> not specified correctly\n\n");
	exit(1);
 }
 if(ArrayMax%threadcount != 0){
	printf("Error,threads and arrays not compatible\n\n");
	exit(1);
 }
 
 #ifdef Debug
 printf("The threadcount is %d\n",threadcount);
 printf("The seed is %d\n",seed);
 #endif

 srand(seed);
 //______1.) END SETUP
 
 
 
 //2.) ______Generate Unsorted Array
 #ifdef Debug
 printf("Unsorted Array\n");
 for (i = 0; i<ArrayMax; i++){
   array[i] = rand() % 100;
   printf("%d\n",array[i]);
 }
 printf("\n\n");
 #endif
 //2.) _______END Generate Unsorted Array
 
 
 //ONE SORT ALGORITHM
 partition_t *partitionIndex = (partition_t*) malloc(sizeof(partition_t));
 partitionIndex->start = 0;
 partitionIndex->end = ArrayMax;
 partitionIndex->size = (partitionIndex->end - partitionIndex->start);
 partitionIndex->threads = threadcount;
 AlexSort((void*)partitionIndex);
 free(partitionIndex);
 
 #ifdef Debug
 printf("\n\nSorted Array: \n");
 for(i=0; i<ArrayMax; i++){
   printf("%d\n",array[i]);
 }
 #endif
 
 simpleroutine();
 return 0;
}
//_________________END OF MAIN_____________________







//SIMPLE ROUTINE Array Checks
void simpleroutine(){
	int i = 0;
	for (i=0;i<ArrayMax-1;i++){
		if (array[i] > array[i+1]){
			printf("Error, Sort Failure Position[%d] Value:%d to  Position[%d] Value:%d\n\n",i,array[i],i+1,array[i+1]);
			exit(1);
		}
	}
	printf("Sort Complete\n\n");
}


//BUBBLE FUNCTION
void *MyBubble (void *index){
 partition_t *structPtr = (partition_t*) index;
 int x, y, temp;
 int n = structPtr->end;
	for(x=0; x < (n-1); x++){
		for(y = structPtr->start; y < (n - x - 1); y++){
			if(array[y] > array[y+1]){
				temp = array[y];
				array[y] = array[y+1];
				array[y+1] = temp;
			}
		}
	}
 return 0;
}

void *MyBubble2 (int start, int end){
 int x, y, temp;
 int n = end;
	for(x=0; x < (n-1); x++){
		for(y = start; y < (n - x - 1); y++){
			if(array[y] > array[y+1]){
				temp = array[y];
				array[y] = array[y+1];
				array[y+1] = temp;
			}
		}
	}
 return 0;
}

void Mergesort(int A[], int temp[], int left, int right) {  
	int mid;  
	if(right > left) {  
	mid = (right + left)/ 2;  
	Mergesort(A, temp, left, mid);  
	Mergesort(A, temp, mid+1, right);  
	Merge(A, temp, left, mid+1, right);  
	}  
} 
void Merge(int A[], int temp[], int left, int mid, int right) {  
	int i, left_end, size, temp_pos;  
	left_end = mid - 1;  
	temp_pos = left; 
	size = right - left + 1;  
	while ((left <= left_end) && (mid <= right)) {  
		if(A[left] <= A[mid]) {  
			temp[temp_pos] = A[left];  
			temp_pos = temp_pos + 1;  
			left = left +1;  
		}
		else{  
			temp[temp_pos] = A[mid];  
			temp_pos = temp_pos + 1;  
			mid = mid + 1;  
		}
	}  
	while (left <= left_end) {  
		temp[temp_pos] = A[left];  
		left = left + 1;  
		temp_pos = temp_pos + 1;  
	}  
	while (mid <= right) {  
		temp[temp_pos] = A[mid];  
		mid = mid + 1;  
		temp_pos = temp_pos + 1;  
	}  
	for (i = 0; i <= size; i++) {  
		A[right] = temp[right];  
		right = right - 1;  
	}  
} 
//Karumanchi, Narasimha. Data Structures and Algorithms Made Easy: Data Structure and Algorithmic Puzzles (p. 277). CareerMonk Publications. Kindle Edition. 


//ALEXSORT FUNCTION
void *AlexSort(void *index){
	partition_t *structPtr = (partition_t*) index;
	pthread_t thread;
	int returncondition2;
	
	//Break each branch down to one thread partition to sort
	#ifdef Debug
	//printf("Threads2 = %d\n",structPtr->threads);
	printf("Left start %d\n",structPtr->start);
	printf("Left end %d\n",structPtr->end);
	//printf("Left size %d\n",structPtr->size);
	#endif
	if (structPtr->threads ==1){
		#ifdef Debug
		//printf("Bubble\n");
		#endif
		MyBubble((void*)structPtr);
		return 0;
	}else{
		
		//RIGHT ARRAY
		partition_t *structPtrBranch = (partition_t*) malloc(sizeof(partition_t));
		structPtrBranch->start = (structPtr->start)+(structPtr->size/2);
		structPtrBranch->end = (structPtr->end) ;
		structPtrBranch->size = (structPtr->size/2);
		structPtrBranch->threads = (structPtr->threads/2);
		
		#ifdef Debug
		printf("Right start %d\n",structPtrBranch->start);
		printf("Right end %d\n",structPtrBranch->end);
		//printf("Right size %d\n",structPtrBranch->size);
		#endif
		
		//______CREATE THREAD
		#ifdef Debug
		//printf("Threads = %d\n",structPtrBranch->threads);
		//printf("Creating thread\n");
		#endif
		returncondition2 = pthread_create(&thread, NULL, AlexSort, (void*)structPtrBranch);
		//Error check
		if(returncondition2 != 0){
			perror("ERROR: ");
			printf("Thread Creation Error\n");
			exit(1);
		}
	
		//LEFT ARRAY
		//structPtr->start;
		structPtr->size = (structPtr->size/2);
		structPtr->end = (structPtrBranch->end-structPtr->size);
		structPtr->threads = (structPtr->threads/2);
		
		//________JOIN THREADS
		returncondition2 = pthread_join(thread,NULL);
		#ifdef Debug
	    //printf("Joined thread %d\n",thread);
	    #endif
		if(returncondition2 != 0){
			printf("error joining threads\n");
			exit(1);
		}
		//________ENDJOIN
		
		//MERGE Bubble Sorted Arrays Together
		MyBubble2(structPtr->start,structPtrBranch->end);
		
		//Reiterate down the tree until 1 thread
		AlexSort((void*)structPtr);
		
		
		
		//MERGE
		//Issues with mergesort from Karumanchi, can't execute a variable array mergesort
		//Mergesort(array,TempMax,structPtr->start,structPtrBranch->start);
		
		#ifdef Debug
		printf("Premerge start:%d end:%d\n",structPtrBranch->start,structPtr->end);
		#endif
		
		 
		#ifdef Debug
		printf("\n\nSorted Array2: \n");
		for(g=0; g<ArrayMax; g++){
			printf("%d\n",array[g]);
		}
		#endif
	}
	return 0;
}