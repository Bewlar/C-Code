/**
 * MLSapp_Helpers.h - Header file for MLS binary tree app helper functions
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 *
 * This is the header file for a few "helper" functions for the
 * MLS app assignment (ECE 361 hw 3)
 *
 */
#ifndef _MLSTAPPHELPERS_H
#define _MLSTAPPHELPERS_H

#include <stdbool.h>
#include "MLStree.h"

// define constants
#define NUMTEAMINFOFIELDS 8

// function prototypes
TeamInfoPtr_t parseTeamInfo(const char *buf, TeamInfoPtr_t info_ptr);
void printTeamInfo(TeamInfoPtr_t teamInfo);


#endif

