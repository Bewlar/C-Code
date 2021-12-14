/*
Q2 HW 2
Author Alex Beaulier
Description: RPN Calc

//Task
(20 pts) Write a program that evaluates RPN expressions using the refactored stack
implementation that you created in part a. The operands will be single-digit integers (0, 1,
2…, 9). The operators are +, -, *, /, and =. The = operator causes the top stack item to be
displayed. After the stack item is displayed the stack should be cleared and the user should
be prompted to enter another expression. The process continues until the user enters a
character that is not a valid operator or operand. For example:
Enter an RPN expression: 1 2 3 * + =
Value of expression: 7
Enter an RPN expression: 5 8 * 4 9 - / =
Value of expression: -8
Enter an RPN expression: q
Use scanf(“ %c”, &ch) to read the operators and operands.

10/20/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "stackADT_LL.h"


int main(){
char ch;
char tempch;
int count = 0;
int temp1;
int temp2;
//Skeleton Code
//Endless Loop

while(1){

//0.) Initialize Stack
    struct Stack *stkRPN = createStack();
    printf("Enter an RPN expression:");
//1.) Scan for input RPN,tally the length of the char array and continue until end of input
    count = 0;
    while (tempch != '\n'){
    scanf("%c%c",&ch,&tempch);
//2.) Convert string to integer value and push into stack
        switch(ch){
            //Operands 1-9
            case '1' : push(stkRPN,1); break;
            case '2' : push(stkRPN,2); break;
            case '3' : push(stkRPN,3); break;
            case '4' : push(stkRPN,4); break;
            case '5' : push(stkRPN,5); break;
            case '6' : push(stkRPN,6); break;
            case '7' : push(stkRPN,7); break;
            case '8' : push(stkRPN,8); break;
            case '9' : push(stkRPN,9); break;
            case '0' : push(stkRPN,0); break;
            //Operators +, -, *, /, and = |
            //Steps 1.) Pop 2 items from stack 2.) operand items together 3.) push back to stack
            case '+' : temp1 = pop(stkRPN); temp2 = pop(stkRPN); push(stkRPN, (temp2+temp1)); break;
            case '-' : temp1 = pop(stkRPN); temp2 = pop(stkRPN); push(stkRPN, (temp2-temp1)); break;//reversed after -8 check issue from example. Noticed RPN uses first item as denominator
            case '*' : temp1 = pop(stkRPN); temp2 = pop(stkRPN); push(stkRPN, (temp2*temp1)); break;
            case '/' : temp1 = pop(stkRPN); temp2 = pop(stkRPN); push(stkRPN, (temp2/temp1)); break;

            //Last operator
            case '=' : printf("Element top of stack is: %d\n",peek(stkRPN)), deleteStack(stkRPN),count = 1;
            default : break;
            }
    //printf("Stack size1 is %d and Top Element is %d\n", size(stkRPN),peek(stkRPN));
    }

    //printf("Element top of stack is; %d\n",peek(stkRPN));
    //ERROR CHECK THEIR STACKS FOR FAULTY INPUT
    if (count <= 0){
    printf("Invalid input\n");
    exit(0);
    }
    count = 0;
    //printf("End of stack generation\n");
    tempch = 'a'; // RESET CH so code doesn't error out
}
return 0;
}
