/**
 * test2_MLStree.c - Source code file for a simple test program for the MLS binary tree
 *
 * Author:  Alex Beaulier (Beaulier@pdx.edu)
 * Date: 11/10/2020
 *
 * This is source code for testing my MLStree binary tree ADT that is
 * used in the MLS standings app (ECE 361 hw3)
 */

/**
 * Referenced read_string.c - Sample code for how to read a string from a file
 *
 * Source:  "C in a Nutshell:2e" by Peter P. and Tony C. page 429
 * Example is under the C library call fgets()
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLStree.h"
#include "MLSapp_Helpers.h"

// main program
int main() {

MLStreePtr_t east_conf;
MLStreePtr_t west_conf;

//1.) Initialize Conferences
// Western conference has 12 teams, and in this
// test program the top two teams qualify for the playoffs
west_conf = createMLStree(WEST, 12, 8);
east_conf = createMLStree(EAST, 14, 10);
//1.) END



//2.) Initialize Teams with Buffer
FILE *titlefile;
char title[256];
int counter = 0;
TeamInfoPtr_t tempInfoPtr;//need to malloc
tempInfoPtr = (TeamInfoPtr_t)malloc(sizeof(TeamInfo_t));

//MLS2020 doesn't work on my computer even in same directory. Not sure why path doesn't search in same location as code...
//if((titlefile = fopen("MLS2020.txt", "r")) == NULL)

if((titlefile = fopen("C:\\Users\\ajbea\\Desktop\\ece361f20_hw3_r1_0\\starter_code\\MLS2020.txt", "r")) == NULL)
    perror("Opening title file");
else {
//1.) If buffer == Null exit for loop
//break;
    while (fgets(title, 256, titlefile) != NULL){

        title[strlen(title) - 1] = '\0'; // trim off newline character
        if(parseTeamInfo(title,tempInfoPtr)!=NULL){
            switch(tempInfoPtr->conf){
                case 0: //EAST
                insert(east_conf, *tempInfoPtr);
                break;

                case 1: //WEST
                insert(west_conf, *tempInfoPtr);
                break;
            }//EOS
        #if (_VERBOSE_ > 0)

        printf("DEBUG PRINT %3d: \"%s\"\n", ++counter, title);
        printf("Name %s       Points:%d  PPG:%f   GP:%d   Win:%d    Loss:%d    Tie:%d\n",tempInfoPtr->name,tempInfoPtr->pts,tempInfoPtr->ppg,tempInfoPtr->gp,tempInfoPtr->win,tempInfoPtr->loss,tempInfoPtr->tie);//2.) else if buffer info.conf = west
        #endif
        }//EOIf

        //insertTeams(west_conf);

        //3.) else if buffer info.conf = east
        //insertTeams(east_conf);

    }//EOW


    // fgets() returned NULL: either EOF or an error occurred
    if (feof(titlefile)){
        #if (_VERBOSE_ > 0)
			printf("DEBUG PRINT Total: %d titles.\n", counter);
		#endif
    }

}//EOE
//2.) END


//3.) Print the Standings
printf("Welcome to the MLS2020 COVID Season\n\n");
printf("\nThe current standings are:\n");
printStandings(west_conf);
printStandings(east_conf);
//3.) END

//4.) Grand Winner
WinnerAnnouncement(west_conf,east_conf);
return 0;
}




