//PROBLEM 1 (a)
#include <stdbool.h>
#include <stdio.h>

bool has_zero(int a[], int n)
{
int i;
for (i = 0; i < n; i++) {   //Fixed syntax error of (,) after n. Replaced with colon //Note n could be replaced with a length of array function
    printf("Loop %d \n",i+1);
    if (a[i] == 0) {
        return true; //Fixed case error. Original function returned 0 or 1 and exited loop
        }
    }
return false;
}

//Debug code for Question 1.a
int main()
{
    int i;
    bool x;
    int a[4] = {1,1,1,1};
    x = has_zero(a,4);
    printf("HasZero value is: %d\n",x);
    for (i = 0; i < 4; i++) {
        printf("a[%d] is %d \n",i,a[i]);
    }
}
//End of debug code for Question 1.a
//End of Q1.a

