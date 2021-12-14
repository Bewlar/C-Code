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

struct Queue;

struct Queue *createQueue(int capacity);

int size(struct Queue *Q);

int frontElement(struct Queue *Q);

int rearElement(struct Queue *Q);

int isEmpty(struct Queue *Q);

int isFull(struct Queue *Q);

int enQueue(struct Queue *Q, char chardata);

char deQueue(struct Queue *Q);

void deleteQueue(struct Queue *Q);

int listQueueContents(struct Queue *Q);
