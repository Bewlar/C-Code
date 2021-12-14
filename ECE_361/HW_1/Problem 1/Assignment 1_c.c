#include <stdio.h>

int list[4];

int sum(int a[], int n){

    if (n == 0 ){
        return a[0];
    }
    else{
        return a[n]+sum(a, n-1);
    }
}

int main(){
    printf("enter four integers: ");
    scanf("%d %d %d %d", &list[0],&list[1],&list[2],&list[3]);
    printf("Their sum is: %d\n", sum(list,3));
    return 0;
}

/*The function sum() is called for the first time by the main program.
From the second time on, it is called by itself.
How many times is sum() called altogether, including the call from main()?
Explain your answer and/or show your work.
*/

//Answer
/*
After scanf, List[4] numbers, 3,2,6,4 with n = 3

Main call to sum - a[3] = 4 + sum | n=3 | Call sum loop 1
sum call sum - a[2] = 6 + sum | n=2     | Call sum loop 2
sum call sum - a[1] = 2 + sum | n=1     | Call sum loop 3
sum call sum - a[0] = 3 | n=0     | Sum loop 4, return up stack
Returns value to loop 3
Loop 3 = 2+3
Return Loop 2
Loop 2 = 5+6
Return Loop 1
Loop 1 = 11+4
Return Main
Value = 15

In total sum is called 4 times.
*/
