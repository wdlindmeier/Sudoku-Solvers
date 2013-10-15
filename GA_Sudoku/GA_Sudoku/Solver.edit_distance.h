//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include "Constants.h"
#include "Helpers.h"
#include <iostream>

using namespace std;

/**
 * THE CONTENTS OF THIS FILE SHOULD BE EDITED TO PRODUCE A WINNING SUDOKU SOLVER...
 */

#pragma mark -
#pragma mark - TEAM_PARAMS

static const std::string	kAuthorTeam		= "🏇 🏆";
static const float			kMutationRate	= 0.002;

#pragma mark -
#pragma mark - TEAM_FUNCTIONS

static void printBoard(const int* iBoard, const size_t& iTileCount) //(int* iBoard, const size_t& iTileCount)
{
	int tAxisLen = sqrt( iTileCount );
	printf( "%ix%i BOARD:\n", tAxisLen, tAxisLen );
	for(int i = 0; i < tAxisLen; i++) {
		for(int j = 0; j < tAxisLen; j++) {
			printf( "%i ", iBoard[ j * tAxisLen + i ] );
		}
		printf( "\n" );
	}
	printf( "\n" );
}

static float fitnessFunc(const int* iBoard, const size_t& iTileCount)
{
    // Simply scores against a known good board.
    // Seems to be the fastest solution.
    static int *knownGoodBoard = NULL;

    // HOWEVER, we must always check if its a win state,
    // since all but 1 win state will fail the comparison with
    // the known good board.
    if (getBoardWin((int *)iBoard, iTileCount))
    {
        // Clear out the known good board.
        delete knownGoodBoard;
        knownGoodBoard = NULL;
        // Return the max possible value
        return std::numeric_limits<float>::max();
    }
    
    if (knownGoodBoard == NULL)
    {
        knownGoodBoard = new int[iTileCount];
        // All of the starting boards are the same,
        // so seed the target board with a random number
        // so we have a variation of solutions.
        int seed = randomInt( getTileValueMin(), getTileValueMax() + 1 );
        randSuccessBoard(iTileCount, knownGoodBoard, seed);
    }

    double totalScore = 1.0f;
    for (int i = 0; i < iTileCount; ++i)
    {
        if(iBoard[i] == knownGoodBoard[i])
        {
            totalScore *= 3.0;
        }
    }
    
	return totalScore / iTileCount;
}

static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount)
{
    // Split in 1/2
	int tMid = randomInt( 0, (int)iTileCount );
	for(size_t i = 0; i < iTileCount; i++) {
		if(i < tMid) { oBoard[i] = iBoardA[i]; }
		else         { oBoard[i] = iBoardB[i]; }
	}
}

static void mutateFunc(int* ioBoard, const size_t& iTileCount, const float& iMutationRate)
{    
	for(int i = 0; i < iTileCount; i++)
    {
		if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate)
        {
			ioBoard[i] = randomInt( getTileValueMin(), getTileValueMax() + 1 );
		}
	}
}

static void randomBoard(int* ioBoard, const size_t& iTileCount)
{
	// EXERCISE: The contents of this function can be edited for testing, but will be reverted for league play...
	
	for(int i = 0; i < iTileCount; i++) {
		ioBoard[i] = randomInt( getTileValueMin(), getTileValueMax() + 1 );
	}
}
