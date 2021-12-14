/**
 * MLStree_starter.c - Starter source code file for MLS binary tree
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 *
 * This is starter source code for a binary tree ADT targeted to the
 * MLS standings app (ECE 361 hw3).  You need to develop the four
 * functions that say // ADD CODE HERE
 *
 * @note code is based on the BinarySearchTree example used during
 * the ECE 361 lectures
 *
 * @note This is a reasonably sized subset of my binary tree ADT.  You
 * can build on this or go in your own direction.  You are the softare
 * engineer on this project.  If you decide to go your own way, it is
 * in your benefit to preserve the structure of the prototypes in MLStree.harderr
 * because they are used in test_MLStree.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLStree.h"


 /**
 * createMLStree() - creates an MLS tree
 *
 * @param	cont				Eastern or Western conference
 * @param	numTeams			Number of teams in the conference
 * @param 	numPlayoffTeams		Number of teams qualifying for playoffs
 *
 * @return	a pointer to the new MLStree if it succeeds.  NULL if it fails.
 * root node is NULL to start with because the tree has 0 nodes
 *
 */
 MLStreePtr_t createMLStree(MLSconf_t conf, int numTeams, int numPlayoffTeams) {
	MLStreePtr_t temp;

	// allocate space for the new tree
	temp = malloc(sizeof(MLStree_t));
	if (temp == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR(createMLSTree()): Could not allocate space for MLStree\n");
		#endif
		return NULL;
	}

	// ADD YOUR CODE HERE

	//1.) Populate Info into tree handle.
	temp->root = NULL; //ALREADY NULL
	temp->conf = conf; //ERROR 2 MLSconf:: Not sure if this is correct for the enums. Never used them before
	temp->numTeams = numTeams;
	temp->numPlayoffTeams = numPlayoffTeams;
	//END OF USER CODE
	return temp;
}


/**
 * insert() - inserts a new team info record into the tree
 *
 * @param	tree	pointer to the MLStree to add the node to
 * @param	info	team info record to add
 * @return	pointer to the new tree node

 * @note Not a good idea to expose the data node but w/o a pointer to
 * root I don't see much harm and it could be useful...and, in fact, INFO
 * made use of it several times in my application
 */
TreeNodePtr_t insert(MLStreePtr_t tree, TeamInfo_t info) {
	TreeNodePtr_t	 tempNodePtr;		// pointer to a new node
	TreeNodePtr_t	 current, parent;	// pointers to traverse the tree

	// make sure there is a tree
	if (tree == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR(insert(): Not a valid MLS tree\n");
		#endif
		return NULL;
	}

	// add and populate the new node to the tree

	// ADD YOUR CODE HERE

	//Generate temporary node -> Choose root or off of root later
	tempNodePtr = (TreeNodePtr_t)malloc(sizeof(TreeNode_t));
    if (tempNodePtr == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR tempNodePtr not allocated\n");
		#endif
		return NULL;
	}
	tempNodePtr->info = info;
	tempNodePtr->leftChild = NULL;
	tempNodePtr->rightChild = NULL;
    //initialize other nodes
    /*current = (TreeNodePtr_t)malloc(sizeof(TreeNode_t));
    if (current == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR current not allocated\n");
		#endif
		return NULL;
	}
	parent = (TreeNodePtr_t)malloc(sizeof(TreeNode_t));
    if (parent == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR parent not allocated\n");
		#endif
		return NULL;
	}*/

    //1.) Create the root node if not generated
    if (tree->root == NULL){
        tree->root = tempNodePtr;
        return tempNodePtr;
    }else{
        current = tree->root; //START AT ROOT OF TREE IF INSERTING
        parent = NULL;

        while(1){
            parent = current;
            //Check Left or Go Right or Keep going through Tree
            if(info.ppg < parent->info.ppg){
                current = current->leftChild;

                //Insert Left
                if(current == NULL){
                    parent->leftChild = tempNodePtr;
                    return tempNodePtr;
                }
            }
            else{//Insert to right if identical or greater than
                current = current->rightChild;

                //Insert Right
                if(current == NULL){
                    parent->rightChild = tempNodePtr;
                    return tempNodePtr;
                }
            }
        }
    }
    printf("Error, node did not fit into any cases or tree failed\n");
	return NULL;
}

void Recursive_inorder_node_printer(TreeNodePtr_t TreeNode, int playoffteams, int *counter){
    if (TreeNode != NULL){

        Recursive_inorder_node_printer(TreeNode->rightChild, playoffteams, counter);
        //Inorder uses statement in center
        if (*counter > playoffteams){
        printf("%2d   _       %28s     %3d    %.2f   %2d   %2d    %2d    %2d\n",*counter,TreeNode->info.name,TreeNode->info.pts,TreeNode->info.ppg,TreeNode->info.gp,TreeNode->info.win,TreeNode->info.loss,TreeNode->info.tie);
        *counter = *counter + 1;
        }
        //Case 2 - Team is in playoff.
        else if(*counter <= playoffteams){
        printf("%2d   x       %28s     %3d    %.2f   %2d   %2d    %2d    %2d\n",*counter,TreeNode->info.name,TreeNode->info.pts,TreeNode->info.ppg,TreeNode->info.gp,TreeNode->info.win,TreeNode->info.loss,TreeNode->info.tie);
        *counter = *counter + 1;
        }
        Recursive_inorder_node_printer(TreeNode->leftChild, playoffteams, counter);

    }
    return;
}


/**
 * printStandings() - prints the standings (table)
 *
 * @param	tree	pointer to the MLStree to search
 *
 * @note teams that qualify for the playoffs get an x in the first column
 *
 * @note function should do a reverse in-order traversal since we want the
 * teams listed from highest PPG to lowest PPG.
 * Try to mimic the Table entries shown in the hw3_results.txt file.  It's
 * going to take some playing around and likely lots of compiles to get the
 * formatting to where you like it.  That's why writing a makefile for this
 * assignment will be helpful.
 */
 void printStandings(MLStreePtr_t tree) {
	// ADD YOUR CODE HERE
    int counter = 1;
	//1.)Start at root(base case)
    //Error check for data
    if ( tree->root == NULL){
       printf("This tree is empty\n");
       return;
    }

    //Check East or West (0:West, 1:East)
    if (tree->conf == 1){
    printf("Western Conference\n");
    }else{
    printf("Eastern Conference\n");
    }
    printf(" #                                   Club      PTS    PPG   GP    W     L     T\n");

    //Enter recursive loop to print, pass the qualification teams
    Recursive_inorder_node_printer(tree->root, tree->numPlayoffTeams,&counter);
    printf("x - team has qualified for playoffs\n\n");
    counter = 0;
}

void WinnerAnnouncement(MLStreePtr_t conf1,MLStreePtr_t conf2){
TreeNodePtr_t temp1;
TreeNodePtr_t temp2;
float maxval1;
float maxval2;


//Loop Conf 1
temp1 = conf1->root;
while (temp1->rightChild != NULL){
    temp1 = temp1->rightChild;
}
maxval1 = temp1->info.ppg;

//Loop Conf 2
temp2 = conf2->root;
while (temp2->rightChild != NULL){
    temp2 = temp2->rightChild;
}
maxval2 = temp2->info.ppg;



if (maxval1 > maxval2){
    temp2 = temp1;
}
printf("Congratulations MLS Shield Winner: %s \n",temp2->info.name);
printf("Team Information for the: %s \n",temp2->info.name);
if (temp2->info.conf == 1){
    printf("    Conference: Western \n");
}else{
    printf("    Conference: Eastern \n");
}
    printf("    Pointer Per Game PPG %.2f \n",temp2->info.ppg);
    printf("    Total Points (PTS): %2d \n",temp2->info.pts);
    printf("    Number of Games (GP): %2d \n",temp2->info.gp);
    printf("    Record (w-l-t): %2d -%2d -%2d \n",temp2->info.win,temp2->info.loss,temp2->info.tie);
    printf("____________________________________\n\n");
    printf("MLS, 25 years.........................\n");

}
