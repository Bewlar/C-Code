/*Copyright (c) 2016 CareerMonk Publications and others.
#E-Mail            : info@careermonk.com
#Creation Date     : 2008-01-10 06:15:46
#Created by        : Narasimha Karumanchi
#Book Title        : Data Structures And Algorithms Made Easy
#Warranty          : This software is provided "as is" without any
#                    warranty; without even the implied warranty of
#                    merchantability or fitness for a particular purpose.*/

#include<stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ListNode;

struct Stack;

struct Stack *createStack();

void push(struct Stack *stk, int data);

int size(struct Stack *stk);

int isEmpty(struct Stack *stk);

int pop(struct Stack *stk);

int peek(struct Stack * stk);

void deleteStack(struct Stack *stk);
