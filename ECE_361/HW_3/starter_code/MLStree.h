/**
 * MLStree.h - Header file for MLS binary tree app
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 *
 * This is the header file for a binary tree ADT targeted to the
 * MLS standings app (hw3)
 *
 */
#ifndef _MLSTREE_H
#define _MLSTREE_H

#include <stdbool.h>

// Debug constants
// This is a good way to compile debug code into your program as needed and then
// remove it when you have everything working.
// Be sure you use {} in pieces of code that make use of the approach
#define _VERBOSE_ 0		// > 0 compiles in the debug code.  See MLStree.c_str
						// for examples on how to use it.

#define MAXNAME 30		// maximum length for team name

// define conference enum
typedef enum _MLSconf_e {EAST, WEST} MLSconf_t;

// define team info struct
typedef struct _mlsTeamInfo_s {
	char 		name[MAXNAME];
	MLSconf_t	conf;
	float		ppg;
	int			pts;
	int			gp;
	int			win;
	int			loss;
	int			tie;
} TeamInfo_t, *TeamInfoPtr_t;

// define MLS binary tree node
typedef struct _mlsTreeNode_s {
	TeamInfo_t				info;
	struct _mlsTreeNode_s	*leftChild;
	struct _mlsTreeNode_s	*rightChild;
} TreeNode_t, *TreeNodePtr_t;

// define MLS binary tree
typedef struct _mlsBTree_s {
	TreeNodePtr_t	root;
	MLSconf_t		conf;
	int				numTeams;
	int				numPlayoffTeams;
} MLStree_t, *MLStreePtr_t;

// function prototypes
MLStreePtr_t createMLStree(MLSconf_t conf, int numTeams, int numPlayoffTeams);
TreeNodePtr_t insert(MLStreePtr_t tree, TeamInfo_t info);
void printStandings(MLStreePtr_t tree);
void Recursive_inorder_node_printer(TreeNodePtr_t TreeNode, int playoffteams, int *counter);
void WinnerAnnouncement(MLStreePtr_t conf1,MLStreePtr_t conf2);
#endif

