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
#include "CayleyTable.h"
#include <iostream>

using namespace std;

/**
 * THE CONTENTS OF THIS FILE SHOULD BE EDITED TO PRODUCE A WINNING SUDOKU SOLVER...
 */

#pragma mark -
#pragma mark - TEAM_PARAMS

static const std::string	kAuthorTeam		= "🏇 🏆";
static const float			kMutationRate	= 0.075;

#pragma mark -
#pragma mark - TEAM_FUNCTIONS

static void printBoard(const int* iBoard, const size_t& iTileCount)
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

int sortCompare(const void * a, const void * b)
{
    return (*(int*)a - *(int *)b);
}

static float fitnessFunc(const int* iBoard, const size_t& iTileCount)
{
    bool isSolved = getBoardWin((int *)iBoard, iTileCount);
    if (isSolved)
    {
        return 2.0f;
    }

    float totalScore = 0;
    int axisLength = sqrt(iTileCount);
    
    int retValues[axisLength];
    // NOTE: 0 is upper left
    sampleBoardAtIndex(iBoard, ORDER, 0, retValues);
    
    int numErrors = 0;
    for(int row = 0; row < ORDER; row++)
    {
        int offset = row * ORDER;
        int rowVals[] = {retValues[offset + 0], retValues[offset + 1], retValues[offset + 2]};
        qsort(rowVals, ORDER, sizeof(int), sortCompare);
        for (int i = 0; i < ORDER; ++i)
        {
            int curVal = rowVals[i];
            int nextVal = rowVals[(i+1)%ORDER];
            if (i == ORDER-1)
            {
                nextVal+=axisLength;
            }
            int delta = nextVal - curVal;
            if (delta != ORDER)
            {
                numErrors++;
            }
        }
    }
    
    int uniquenessArray[ORDER];
    for (int i = 0; i < ORDER; i++)
    {
        uniquenessArray[i] = 0;
    }
    
    for (int y = 0; y < ORDER; y++)
    {
        // Column 0
        int value = retValues[(y*ORDER)];
        int modValue = value % ORDER;
        int isPresent = uniquenessArray[modValue];
        if (isPresent)
        {
            numErrors++;
        }
        uniquenessArray[modValue] = 1;
    }
    
    totalScore = pow(2, numErrors * -1);
    
    return totalScore;

}

static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount)
{
    int axisLength = sqrt(iTileCount);
   
    int geneA[axisLength];
    sampleBoardAtIndex(iBoardA, ORDER, 0, geneA);
    
    int geneB[axisLength];
    sampleBoardAtIndex(iBoardB, ORDER, 0, geneB);
    
    int child[axisLength];
    
    // Board B (mother) == offsets / mins
    int colModulos[ORDER];
    for (int i = 0; i < ORDER; ++i)
    {
        colModulos[i] = geneB[ORDER * i] % ORDER;
    }
    
    for (int geneRow = 0; geneRow < ORDER; geneRow++)
    {
        // Board A (father) == deltas
        int offset = geneRow * ORDER;
        int rowDeltas[ORDER];
        int minVal = 8;
        for (int i = 0; i < ORDER; ++i)
        {
            int val = geneA[offset + i];
            if (val < minVal)
            {
                minVal = val;
            }
        }

        for (int i = 0; i < ORDER; ++i)
        {
            int val = geneA[offset + i];
            rowDeltas[i] = val - minVal;
        }
        
        // Construct the child row by row
        for (int i = 0; i < ORDER; i++)
        {
            int retValue = ((colModulos[geneRow] + rowDeltas[i]) % GENESIZE);
            child[offset + i] = retValue == 0 ? 9 : retValue;
        }
    }
    
    CayleyTable cTable(child);
    for (int i = 0; i < iTileCount; ++i)
    {
        oBoard[i] = cTable.getbyIndex(i);
    }
}

static void mutateFunc(int* ioBoard, const size_t& iTileCount, const float& iMutationRate)
{
    // Randomly flit tiles
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
