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

static int checkSumForValues(int *values, int axisLength)
{
    int val = 0;
    for(int i = 0; i < axisLength; i++)
    {
        val += values[i];
    }
    return val;
}

static float fitnessFunc(const int* iBoard, const size_t& iTileCount)
{
    int tAxisLen = sqrt( iTileCount );
    float numCorrect = 0.0f;
    for(int i = 0; i < tAxisLen; i++)
    {
        int colVals[tAxisLen];
        colValuesForTileIndex(i,
                              iBoard,
                              iTileCount,
                              colVals);
        numCorrect += intUniquenessScalar(colVals, tAxisLen);
        /*
        if (checkSumForValues(colVals, tAxisLen) == 45)
        {
            numCorrect++;
        }
        */
        
        int rowVals[tAxisLen];
        rowValuesForTileIndex(i * tAxisLen,
                              iBoard,
                              iTileCount,
                              rowVals);
        numCorrect += intUniquenessScalar(rowVals, tAxisLen);
        //numCorrect -= abs(checkSumForValues(rowVals, tAxisLen) - 45);
        /*
        if(checkSumForValues(rowVals, tAxisLen) == 45)
        {
            numCorrect++;
        }
        */
        
        int quadVals[tAxisLen];
        quadValuesAtQuadIndex(iBoard,
                              i,
                              tAxisLen,
                              quadVals);
        numCorrect += intUniquenessScalar(quadVals, tAxisLen);
        //numCorrect -= abs(checkSumForValues(quadVals, tAxisLen) - 45);
        /*
        if (checkSumForValues(quadVals, tAxisLen) == 45)
        {
            numCorrect++;
        }
        */
    }
    static long numCounts = 0;
    numCounts++;
    if (numCounts % 5000 == 0)
    {
        cout << "numCorrect: " << numCorrect << endl;
    }
    return numCorrect;
}

static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount)
{
    for(size_t i = 0; i < iTileCount; i++) {
        int tMid = randomInt( 0, (int)iTileCount );
		if(tMid < (iTileCount / 2)) { oBoard[i] = iBoardA[i]; }
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
