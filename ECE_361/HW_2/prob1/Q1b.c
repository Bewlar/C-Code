

/*
Q1b HW 2
Author Alex Beaulier
Description: Code to test Q1 code
b (10) Write a test program that verifies that your function works correctly. Your main()
should use scanf() and take as input an integer count followed by the values on a single
line. Output the original values followed by the smallest integer. Terminate the program
when the user enters a zero or negative count.
10/22/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Q1.h"

int main(){

    //Skeleton Code
    int dynamiclist1[99999];
    char endofline;
    int output;
    int n = 0;
    int m = 0;

    //1.) User enters in all data
    printf("Give quantity of integers as an integer value followed by other values separated by spaces:");
    //|  I assume (\n) for end of the list and no chars
    //Note without doing a while loop I couldn't find any possible way to scan a list in. Unknown if other way to do this.
    while(endofline != '\n'){
        scanf("%d%c", &dynamiclist1[n], &endofline);
        n++;
    }
    printf("\n");
    int mylist[dynamiclist1[0]];

    //Debug Print size of new list
    //printf("Length of array: %d\n", (int)( sizeof(mylist) / sizeof(mylist[0]) )); //Seems to validate rishitosh comment
    //printf("n:%d \n",n);
    //10/23/20 Found odd segmentation error if negative input for qty
    //Randomly occurs, not sure how to fix...

    //Error out if size of list is greater than entered qty
    if ((int)( sizeof(mylist) / sizeof(mylist[0])!=n-1)){
        printf("Error, size doesn't match list length");
        exit(0);
        }


    /*for(m=0; m<n; m++){
        printf("%d ",mylist[m]);
    }*/
    //Debug print the statement
    /*for(m=0; m<n; m++){
        printf("%d ",dynamiclist1[m]);
    }*/
    //printf("\n%d\n",n);
    //Edge case check
    //Edge case characters (-) (0) for quantityints
    if (dynamiclist1[0] <= 0){
        printf("Error, value entered was <= 0 \n");
        exit(0);
    }

    //2.) Break data into new list for length of user input
    //Get size of array to set for loop interation (Done with n from while loop above
    for (m=0; m<n; m++){
        if (m>0){
           mylist[m-1] = dynamiclist1[m];
        }
    }

    //Debug print the statement
    /*for(m=0; m<n-1; m++){
        printf("Mylist is %d ",mylist[m]);
    }*/

    //3.) Return and Put the list into recursive minimum function
    output = Minimum(mylist, n-1);
    //4.) print the list and the output from above
    printf("Original List:");
    for (m=0; m<n-1; m++){
        printf("%d ",mylist[m]);
    }
    printf("\nSmallest Value:%d\n",output);
    return 0;
}
