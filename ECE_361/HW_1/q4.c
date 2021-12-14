#include <stdio.h>
#include <stdlib.h>
#define billquantity 4

int bills[billquantity]= {20, 10, 5, 1};
int i;
int dollarinput;
int dollaroutput [billquantity] = {0,0,0,0};



int main(){
printf("Enter in a dollar amount with no change: ");
scanf("%d",&dollarinput);
//dollarinput = 69;

if (dollarinput<=0) {
    printf("Bad quantity");
    exit(0);
}


//Check 20's
//printf("\nFirst bill is %d\n",bills[0]);
dollaroutput[0] = dollarinput / bills[0];
//printf("The 20 dollar bill quantity is: %d\n\n",dollaroutput[0]);
dollarinput = dollarinput - (bills[0] * dollaroutput[0]);
//printf("20's value is:%d\n",dollaroutput[1]);

//Check 10's
//printf("Second bill is %d\n",bills[1]);
dollaroutput[1] = dollarinput / bills[1];
//printf("The 10 dollar bill quantity is: %d\n\n",dollaroutput[1]);
dollarinput = dollarinput - (bills[1] * dollaroutput[1]);

//Check 5's
//printf("Third bill is %d\n",bills[2]);
dollaroutput[2] = dollarinput / bills[2];
//printf("The 5 dollar bill quantity is: %d\n\n",dollaroutput[2]);
dollarinput = dollarinput - (bills[2] * dollaroutput[2]);

//Check remainder 1's
//printf("Fourth bill is %d\n",bills[3]);
dollaroutput[3] = dollarinput / bills[3];
//printf("The 1 dollar bill quantity is: %d\n\n",dollaroutput[3]);
dollarinput = dollarinput - (bills[3] * dollaroutput[3]);

printf("$20's:%d  $10's:%d  $5's:%d  $1's:%d\n",dollaroutput[0],dollaroutput[1],dollaroutput[2],dollaroutput[3]);
return 0;
}
