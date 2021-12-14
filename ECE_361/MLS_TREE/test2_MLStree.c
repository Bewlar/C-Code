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
BuildMLSTrees(west_conf,east_conf);
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




