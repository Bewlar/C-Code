/*Copyright (c) 2016 CareerMonk Publications and others.
#E-Mail            : info@careermonk.com
#Creation Date     : 2008-01-10 06:15:46
#Created by        : Narasimha Karumanchi
#Book Title        : Data Structures And Algorithms Made Easy
#Warranty          : This software is provided "as is" without any
#                    warranty; without even the implied warranty of
#                    merchantability or fitness for a particular purpose.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//#include "QueueADT_LL.h"

struct Queue {
    int front, rear;
    int capacity;
    int size;
    char *array;
};

// Create an empty queue
struct Queue *createQueue(int capacity) {
    struct Queue *Q = malloc(sizeof(struct Queue));
    if(!Q){
        printf("Failed2\n");
        return NULL;
    }
    Q->capacity = capacity;
    Q->front = -1;
    Q->rear = -1;
    Q->size = 0;
    Q->array= malloc(Q->capacity * sizeof(char));
    if(!Q->array){
        printf("Failed1\n");
        return NULL;
    }
    return Q;
}

// Returns queue size
int size(struct Queue *Q) {
    return Q->size;
}

// Returns Frnt Element of the Queue
char frontElement(struct Queue *Q) {
    return Q->array[Q->front];
}

// Returns the Rear Element of the Queue
char rearElement(struct Queue *Q) {
    return Q->array[Q->rear];
}

// Check's if Queue is empty or not
int isEmpty(struct Queue *Q) {
    // if the condition is true then 1 is returned else 0 is returned
    return (Q->size == 0);
}

// Check's if Queue is full or not
int isFull(struct Queue *Q) {
    // if the condition is true then 1 is returned else 0 is returned
    return (Q->size == Q->capacity);
}

// Adding elements in Queue
int enQueue(struct Queue *Q, char chardata) {
    if(isFull(Q)){
        //
        //printf("Queue overflow insertion failure\n");
        return 0;
    }
    else {
        Q->rear = (Q->rear+1)% Q->capacity;
        Q->array[Q->rear]= chardata;
        if(Q->front == -1)
            Q->front = Q->rear;
        Q->size += 1;
        //printf("Queue Insertion Successful\n");
        return 1;
    }
}

// Removes an element from front of the queue
int deQueue(struct Queue *Q) {
    char data = CHAR_MIN; //or element which does not exist in Queue
    if(isEmpty(Q)){
        //printf("Queue is empty\n");
        return data;
    }
    data = Q->array[Q->front];
    //printf("Dequeue front: %d\n",Q->front);
    //printf("Dequeue rear: %d\n",Q->rear);
    if(Q->front == Q->rear) {
        Q->front = Q->rear = -1;
        Q->size = 0;
    } else {
        //printf("Entered Else statement\n");
        Q->front = (Q->front+1)% Q->capacity;
        Q->size -= 1;
    }
    return data;
}

void deleteQueue(struct Queue *Q) {
    if(Q) {
        if(Q->array)
            free(Q->array);
    free(Q);
    }
}

int listQueueContents(struct Queue *Q) {
    int count = 0;
    int temp = Q->front;

    if (Q->size == 0) {
        //printf("Queue is Empty\n");
        return 0;
    }
    //printf("Debug front value is %d\n",Q->front);
    //printf("Debug rear value is %d\n",Q->rear);
    while(temp <= Q->rear){
        printf("Queue position[%d] is: %c\n",temp,Q->array[temp]);
        temp++;
        count++;
    }
    //printf("Count was %d\n",count);
    return count;
}
