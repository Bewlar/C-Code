/**
 * test_MLStree.c - Source code file for a simple test program for the MLS binary tree
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 * 
 * This is source code for testing my MLStree binary tree ADT that is
 * used in the MLS standings app (ECE 361 hw3)
 *
 * @note you may have to make some modifications to tailor the test program
 * to your binary tree ADT
 *
 * @note this program tests the three functions you need to create in your
 * binary tree ADT.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLStree.h"
#include "MLSapp_Helpers.h"

// function prototypes
void insertTeams(MLStreePtr_t tree);

// initialize the Cascadia cup team info structs
// I hadn't seen this format before but it does make it
// clear what you are assigning all of the variables in the
// struct to.  Matches my more typing...less debug strategy
TeamInfo_t POR = {
	.name = "Portland Timbers",
	.conf = WEST,
	.ppg = 1.75,
	.pts = 35,
	.gp = 20,
	.win = 10,
	.loss = 10,
	.tie = 5
};

TeamInfo_t SEA = {
	.name = "Seattle Sounders FC",
	.conf = WEST,
	.ppg = 1.84,
	.pts = 35,
	.gp = 19,
	.win = 10,
	.loss = 4,
	.tie = 5
};

TeamInfo_t VAN = {
	.name = "Vancouver Whitecaps FC",
	.conf = WEST,
	.ppg = 1.14,
	.pts = 24,
	.gp = 21,
	.win = 8,
	.loss = 13,
	.tie = 0
};

// main program
int main() {
	MLStreePtr_t west_conf;
	
	// Western conference has 12 teams, and in this
	// test program the top two teams qualify for the playoffs
	west_conf = createMLStree(WEST, 12, 2);
	insertTeams(west_conf);
	
	printf("\nThe current standings are:\n");
	printStandings(west_conf);	
}


// helper functions

// populates the tree and shows whether the team info was added correctly
void insertTeams(MLStreePtr_t tree){
	TreeNodePtr_t newNode;

	printf("Adding Portland Timbers\n");
	newNode = insert(tree, POR);
	if (newNode == NULL) {
		printf("ERROR:  POR team info not added to tree\n");
	};
	printTeamInfo(&newNode->info);	
	
	printf("Adding Vancouver Whitecaps FC\n");	
	newNode = insert(tree, VAN);
	if (newNode == NULL) {
		printf("ERROR:  VAN team info not added to tree\n");
	};
	printTeamInfo(&newNode->info);
	
	printf("Adding Seattle Sounders FC\n");	
	newNode = insert(tree, SEA);
	if (newNode == NULL) {
		printf("ERROR:  SEA team info not added to tree\n");
	};
	printTeamInfo(&newNode->info);
}





