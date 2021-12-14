/*
Q1 HW 2
Author Alex Beaulier
Description: Code to recursively find smallest int between list[0]
and list[n] and return the value as an int. Can be +/- input.
Output value in main, not function
10/20/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Q1.h"

//Can't recursively return without having this function. Doesn't seem to run on multi line ifs so generating function to check for code compression
int smallerval(int val1,int val2){
    if (val1<val2) {
        return val1;
    }
    else{
        return val2;
    }
}

int Minimum(int list[], int n){
    //Base Case, first element(last call in function)
    //printf("Debug1\n");
    //printf("Debug Value of n is: %d || Value of list[n] is %d \n",n,list[n]);
    //printf("\n",list[n]);

    //BASE CASE BELOW, BASE CASE OCCURS AND ENTERS AS FINAL RECURSIVE CALL
    if (n==0)
        return list[n];
    //printf("Debug2\n");

    return smallerval(Minimum((int*)list,n-1),list[n-1]);// Can't figure out why comparison before works but not the if statements below

    /*Can't get the nested if's to work. Generated code above 10/22/20 to compress comparisons outside of recursive call. Leaving to discuss at office hours Tues
    //Check the largest value of all other pairs with the recursion call. Then compares base case if it traverses up from returns.
    if ((Minimum((int*)list[n-1],n-1)) < list[n-1]){
        return Minimum((int*)list[n-1],n-1);
    }
    else {
        return list[n-1];
    }
    */
    //printf("Debug4");
}
/*
int main(){
    //int Testarray[3] = {-5,2,3};
    int answer = 0;
    //answer = Minimum(Testarray,3);
    printf("Smallest value:%d", answer);
    return 0;
}
*/




