/**
 * test_queueADT.c - Source code for program to test the Queue ADT
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 17-Oct-2020
 *
 * This is the source code to test the array-based Queue ADT
 *
 * @note Code is based on Oliver Rew's HW #3 solution (10/2018)
 */
// include files
#include <stdio.h>
#include <stdlib.h>
#include "QueueADT_LL.h"

// main program
int main()
{
    int i = 0;
    int tempsize = 0;
    //INITiAliZE QUEUE
	struct Queue *TestQueue = createQueue(10);

	printf("\n\n======STARTING QUEUE TESTS======\n\n");
	//use this char to test dequeue
	char first = 'c';

	//Add queue enough to fill the queue
	enQueue(TestQueue, first);
	enQueue(TestQueue, 'g');
	enQueue(TestQueue, 't');
	enQueue(TestQueue, 'Y');
	enQueue(TestQueue, 'H');
	enQueue(TestQueue, 'X');
	enQueue(TestQueue, 'r');
	enQueue(TestQueue, 'm');
	enQueue(TestQueue, 'n');
	enQueue(TestQueue, 'y');
	enQueue(TestQueue, 'p');	// should fail, queue is full
	enQueue(TestQueue, 'Z');	// should fail,

    printf("Testqueue size %d\n",size(TestQueue));
	if(listQueueContents(TestQueue) == size(TestQueue))
		printf("----List Queue Contents 1 Test Successful\n");//Should test here
	else
		printf("----List Queue Contents 1 Test Failure\n");

	if(isFull(TestQueue))
		printf("----Queue Full 1 Test Successful\n"); //Should test here
	else
		printf("----Queue Full 1 Test Failure\n");
    printf("Front element is %c\n",frontElement(TestQueue));
    printf("Rear element is %c\n",rearElement(TestQueue));

	if(deQueue(TestQueue) == first)
		printf("----Dequeue 1 Test Successful\n"); //Should test here
	else
		printf("----Dequeue 1 Test Failure\n");
    //Debug test other case if full
    if(isFull(TestQueue))
		printf("----Queue Full 2 Test: Full\n");
	else
		printf("----Queue Full 2 Test: Not full\n");//Should test here
    printf("Testqueue size2 %d\n\n",size(TestQueue)); // Should be 9 after the dequeue
    printf("Front element is %c\n",frontElement(TestQueue));
    printf("Rear element is %c\n",rearElement(TestQueue));


	//empty the queue
	printf("Empty the queue\n");
	tempsize = size(TestQueue);
	for(i = 0; i < tempsize; ++i){
		printf("deQueued Element %c\n",deQueue(TestQueue));
		printf("Size is %d\n",size(TestQueue));
	}
	printf("Queue should be empty - nothing displayed\n");
	printf("Testqueue size3 %d\n",size(TestQueue));
	listQueueContents(TestQueue);

	if(isEmpty(TestQueue))
		printf("----Queue Empty Test3 Successful\n");
	else
		printf("----Queue Empty Test3 Failure\n");

	printf("---Testing partial fills---\n");
	printf("   Adding p and Z to queue\n");
	enQueue(TestQueue, 'p');
	enQueue(TestQueue, 'Z');
	listQueueContents(TestQueue);
	printf("Testqueue size5 %d\n",size(TestQueue));
	printf("   Removing p\n");
	deQueue(TestQueue);
	printf("Testqueue size6 %d\n",size(TestQueue));
	listQueueContents(TestQueue);
	printf("   Adding ! to queue\n");
	enQueue(TestQueue, '!');
	listQueueContents(TestQueue);
	printf("----Queue Test Complete\n");
	return 0;
}
