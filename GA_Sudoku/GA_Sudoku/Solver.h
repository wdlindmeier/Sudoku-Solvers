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
static const float			kMutationRate	= 0.0065;

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

static float rowFitnessFunc(int rowVals[], const int axisLength)
{
    int numRepetitions = numRepetitionsInAxis(rowVals, axisLength);
    return pow(2, -numRepetitions);
}

static float fitnessFunc(const int* iBoard, const size_t& iTileCount)
{
    int axisLength = sqrt( iTileCount );
    float totalScore = 0.0f;
    for (int i = 0; i < axisLength; ++i)
    {
        int rowVals[axisLength];
        rowValuesForRowIndex(i,
                             iBoard,
                             axisLength,
                             rowVals);
        
        float rowFitness = rowFitnessFunc(rowVals, axisLength);
        if (totalScore == 0.0f)
        {
            totalScore = rowFitness;
        }
        else
        {
            totalScore *= rowFitness;
        }
    }
    
    // float total = fitnessR1 * fitnessR2 * fitnessR3
    
    /*
    for(int i = 0; i < tAxisLen; i++)
    {
        int colVals[tAxisLen];
        colValuesForColumnIndex(i,
                                iBoard,
                                tAxisLen,
                                colVals);
        totalScore += intUniquenessScalar(colVals, tAxisLen);
        
        int rowVals[tAxisLen];
        rowValuesForRowIndex(i,
                             iBoard,
                             tAxisLen,
                             rowVals);
        totalScore += intUniquenessScalar(rowVals, tAxisLen);
              
        int quadVals[tAxisLen];
        quadValuesForQuadIndex(i,
                               iBoard,
                               tAxisLen,
                               quadVals);
        totalScore += intUniquenessScalar(quadVals, tAxisLen);
        
    }
    */
    
    static long numCounts = 0;
    numCounts++;
    if (numCounts % 5000 == 0)
    {
        if (totalScore == 1.0f)
        {
            
            printBoard(iBoard, iTileCount);
        }
        cout << "totalScore: " << totalScore << endl;
    }
    return totalScore;

}

static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount)
{
    // Randomly pick a tile
    /*
    for(size_t i = 0; i < iTileCount; i++) {
        int tMid = randomInt( 0, (int)iTileCount );
		if(tMid < (iTileCount / 2)) { oBoard[i] = iBoardA[i]; }
		else         { oBoard[i] = iBoardB[i]; }
	}
    */

    // Split based on columns and rows.
    // This lets use preserve whatever value has been built up in them
    int tMid = randomInt( 0, getTileValueMax() );
    int axisLength = sqrt(iTileCount);
    int splitMode = arc4random() % 3;
    
    for (int i = 0; i < axisLength; ++i)
    {
        int values[axisLength];
        
        bool chooseA = randomInt( 0, (int)iTileCount ) < (iTileCount / 2);
        
        if (splitMode == 0)
        {
            if (chooseA) //
//            if (i < tMid)
            {
                // pick col from a
                colValuesForColumnIndex(i, iBoardA, axisLength, values);
            }
            else
            {
                // pick col from b
                colValuesForColumnIndex(i, iBoardB, axisLength, values);
            }
            // Stick them in
            insertColValuesAtColumnIndex(i, oBoard, axisLength, values);
        }
        else if (splitMode == 1)
        {
            if (chooseA)
//            if (i < tMid)
            {
                // pick row from a
                rowValuesForRowIndex(i, iBoardA, axisLength, values);
            }
            else
            {
                // pick row from b
                rowValuesForRowIndex(i, iBoardB, axisLength, values);
            }
            // Stick them in
            insertRowValuesAtRowIndex(i, oBoard, axisLength, values);
        }
        else if (splitMode == 2)
        {
            if (chooseA)
//            if (i < tMid)
            {
                // pick quad from a
                quadValuesForQuadIndex(i, iBoardA, axisLength, values);
            }
            else
            {
                // pick quad from b
                quadValuesForQuadIndex(i, iBoardB, axisLength, values);
            }
            // Stick them in
            insertQuadValuesAtQuadIndex(i, oBoard, axisLength, values);
        }
    }

}

static void mutateFunc(int* ioBoard, const size_t& iTileCount, const float& iMutationRate)
{
    // Randomly flit tiles
    /*
	for(int i = 0; i < iTileCount; i++)
    {
		if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate)
        {
			ioBoard[i] = randomInt( getTileValueMin(), getTileValueMax() + 1 );
		}
	}*/
    
    // Check how fit a row is and use the inverse fitness as a probability for switching its values
    int axisLength = sqrt(iTileCount);
    for (int i = 0; i < axisLength; ++i)
    {
        int rowVals[axisLength];
        rowValuesForRowIndex(i,
                             ioBoard,
                             axisLength,
                             rowVals);
        
        float rowFitness = rowFitnessFunc(rowVals, axisLength);

        bool didChangeVal = false;
        for (int j = 0; j < axisLength; ++j)
        {
            if (( (float)rand() / (float)RAND_MAX ) > rowFitness)
            {
                rowVals[j] = randomInt( getTileValueMin(), getTileValueMax() + 1 );
                didChangeVal = true;
            }
        }
        if (didChangeVal)
        {
            insertRowValuesAtRowIndex(i, ioBoard, axisLength, rowVals);
        }
    }

    /*
    // Randomly swap rows / cols / quads within a grid
    // NOTE: The likelyhood of swapping is increased dramatically by dividing by tilecount.
    if ( ( (float)rand() / (float)RAND_MAX ) < iMutationRate )
    {
        int axisLength = sqrt(iTileCount);
        int splitMode = arc4random() % 3;
        int fromIdx = arc4random() % (axisLength);
        int toIdx = arc4random() % (axisLength);

        if (fromIdx != toIdx)
        {
            int fromValues[axisLength];
            int toValues[axisLength];
            if (splitMode == 0)
            {
                colValuesForColumnIndex(fromIdx, ioBoard, axisLength, fromValues);
                colValuesForColumnIndex(toIdx, ioBoard, axisLength, toValues);

                insertColValuesAtColumnIndex(toIdx, ioBoard, axisLength, fromValues);
                insertColValuesAtColumnIndex(fromIdx, ioBoard, axisLength, toValues);
            }
            else if (splitMode == 1)
            {
                rowValuesForRowIndex(fromIdx, ioBoard, axisLength, fromValues);
                rowValuesForRowIndex(toIdx, ioBoard, axisLength, toValues);
                
                insertRowValuesAtRowIndex(toIdx, ioBoard, axisLength, fromValues);
                insertRowValuesAtRowIndex(fromIdx, ioBoard, axisLength, toValues);
            }
            else if (splitMode == 2)
            {
                quadValuesForQuadIndex(fromIdx, ioBoard, axisLength, fromValues);
                quadValuesForQuadIndex(toIdx, ioBoard, axisLength, toValues);
                
                insertQuadValuesAtQuadIndex(toIdx, ioBoard, axisLength, fromValues);
                insertQuadValuesAtQuadIndex(fromIdx, ioBoard, axisLength, toValues);
            }
        }
    }
    */
}

static void randomBoard(int* ioBoard, const size_t& iTileCount)
{
	// EXERCISE: The contents of this function can be edited for testing, but will be reverted for league play...
	
	for(int i = 0; i < iTileCount; i++) {
		ioBoard[i] = randomInt( getTileValueMin(), getTileValueMax() + 1 );
	}
}
