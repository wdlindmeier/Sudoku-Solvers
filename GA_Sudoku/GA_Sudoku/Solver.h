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

static const std::string	kAuthorTeam		= "Bill & Omer";
static const float			kMutationRate	= 0.01; //0.005; //0.0005f; // 0.01f

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

static float AvgBreakIdx = 0.0f;
const static float kMaxErrorPercentage = 0.05f; // SOLVED WITH 0.05 and a constant mutation rate;

static float fitnessFunc(const int* iBoard, const size_t& iTileCount)
{
    int axisLength = sqrt( iTileCount );
    float totalScore = 0.0f;
    
    bool didBreak = false;
    int numErrors = 0;
    
    // This reads over each value and checks the validity based on the values that
    // preceeded it. If it encounters too many errors in the solution, it breaks.
    // This is pretty slow.
    for (int myIdx = 0; myIdx < iTileCount; ++myIdx)
    {
        if (didBreak) break;

        int xy[2];
        idxToXY(myIdx, xy, axisLength);
        int x = xy[0];
        int y = xy[1];
        
        int myVal = iBoard[myIdx];
        int myQuadIdx = quadIndexForTileIndex(myIdx, axisLength);
        
        bool tileIsValid = true;
        for (int pi = 0; pi < myIdx; ++pi)
        {
            if (didBreak) break;
            
            int pxy[2];
            idxToXY(pi, pxy, axisLength);
            
            int px = pxy[0];
            int py = pxy[1];
            
            int prevQuadIdx = quadIndexForTileIndex(pi, axisLength);
            
            if (px == x || // Same column
                py == y || // Same row
                prevQuadIdx == myQuadIdx) // Same quad
            {
                int prevVal = iBoard[pi];
                if (prevVal != myVal)
                {
                    // Give it some points
                    totalScore += 1.0f;
                }
                else
                {
                    totalScore -= 1.0f;
                    numErrors++;
                    tileIsValid = false;
                    
                    // Don't let it proceed if it's hit a certain error rate.
                    if (((float)numErrors / (float)myIdx) > kMaxErrorPercentage)
                    {
                        didBreak = true;
                        AvgBreakIdx = (AvgBreakIdx * 0.9) + (myIdx * 0.1);
                    }
                }
            }
        }
    }

    static long long checkCount = 0;
    checkCount++;
    float ret = totalScore * totalScore; // iTileCount;
    if (checkCount % 5000 == 0)
    {
        std::cout << "score: " << ret << " (" << totalScore << "). AvgBreakIdx: " << AvgBreakIdx << " numErrors: " << numErrors << std::endl;
//        printBoard(iBoard, iTileCount);
    }
	return ret;
}

static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount)
{
    // Split in 1/2
	int tMid = randomInt( 0, (int)iTileCount );
	for(size_t i = 0; i < iTileCount; i++) {
		if(i < tMid) { oBoard[i] = iBoardA[i]; }
		else         { oBoard[i] = iBoardB[i]; }
	}
    
    /*
    int axisLength = sqrt( iTileCount );

    int splitMode = randomInt( 0, 3 );
    if (splitMode == 0)
    {
        // Randomly pick a row
        for (int row = 0; row < axisLength; ++row)
        {
            int tMid = randomInt( 0, (int)iTileCount );
            bool pickFromA = tMid < (iTileCount / 2);
            
            for (int j = 0; j < axisLength; ++j)
            {
                int plotIdx = (row * axisLength) + j;
                if(pickFromA)
                {
                    oBoard[plotIdx] = iBoardA[plotIdx];
                }
                else
                {
                    oBoard[plotIdx] = iBoardB[plotIdx];
                }
            }
        }
    }
    else if (splitMode == 1)
    {
        // Randomly pick a col
        for (int col = 0; col < axisLength; ++col)
        {
            int tMid = randomInt( 0, (int)iTileCount );
            bool pickFromA = tMid < (iTileCount / 2);
            
            for (int j = 0; j < axisLength; ++j)
            {
                int plotIdx = (j * axisLength) + col;
                if(pickFromA)
                {
                    oBoard[plotIdx] = iBoardA[plotIdx];
                }
                else
                {
                    oBoard[plotIdx] = iBoardB[plotIdx];
                }
            }
        }
    }
    else if (splitMode == 2)
    {
        // Randomly pick a quad
        for (int quadIndex = 0; quadIndex < axisLength; ++quadIndex)
        {
            // Choose which quad to pick
            int tMid = randomInt( 0, (int)iTileCount );
            bool pickFromA = tMid < (iTileCount / 2);
            
            // Get quad values
            int quadsLen = sqrt(axisLength);
            int quadXOff = (quadIndex % quadsLen) * quadsLen; // the number of x tile offset
            int quadYOff = (quadIndex / quadsLen) * quadsLen; // the number of y tile offset
            for (int j = 0; j < axisLength; ++j)
            {
                int qX = j % quadsLen;
                int qY = j / quadsLen;
                int tileX = quadXOff + qX;
                int tileY = quadYOff + qY;
                int plotIdx = (tileY * axisLength) + tileX;
                //returnValues[j] = board[plotIdx];
                if (pickFromA)
                {
                    oBoard[plotIdx] = iBoardA[plotIdx];
                }
                else
                {
                    oBoard[plotIdx] = iBoardB[plotIdx];
                }
            }
        }
    }
    else
    {
        std::cout << "ERROR: Unkown split mode" << std::endl;
    }
    */
    
    /*
    // Randomly pick from each tile
    for(size_t i = 0; i < iTileCount; i++) {
        int tMid = randomInt( 0, (int)iTileCount );
		if(tMid < (iTileCount / 2)) { oBoard[i] = iBoardA[i]; }
		else         { oBoard[i] = iBoardB[i]; }
	}
    */
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

    // Replace an entire col/row/quad with random numbers
    
    /*
    while( ( (float)rand() / (float)RAND_MAX ) < iMutationRate )
    {
        // Mutate a whole row, column or quad
        int axisLength = sqrt( iTileCount );

        int randIndex = randomInt( 0, axisLength );
        
        int mutMode = randomInt( 0, 3 );
        if (mutMode == 0)
        {
            // Randomize a row
            for (int j = 0; j < axisLength; ++j)
            {
                int randVal = randomInt( getTileValueMin(), getTileValueMax() + 1 );
                
                int plotIdx = (randIndex * axisLength) + j;
                ioBoard[plotIdx] = randVal;
            }
        }
        else if (mutMode == 1)
        {
            // Randomize a col
            for (int j = 0; j < axisLength; ++j)
            {
                int randVal = randomInt( getTileValueMin(), getTileValueMax() + 1 );
                int plotIdx = (j * axisLength) + randIndex;
                ioBoard[plotIdx] = randVal;
            }
        }
        else if (mutMode == 2)
        {
            // Randomize a quad
            int quadsLen = sqrt(axisLength);
            int quadXOff = (randIndex % quadsLen) * quadsLen; // the number of x tile offset
            int quadYOff = (randIndex / quadsLen) * quadsLen; // the number of y tile offset
            for (int j = 0; j < axisLength; ++j)
            {
                int randVal = randomInt( getTileValueMin(), getTileValueMax() + 1 );
                int qX = j % quadsLen;
                int qY = j / quadsLen;
                int tileX = quadXOff + qX;
                int tileY = quadYOff + qY;
                int plotIdx = (tileY * axisLength) + tileX;
                //returnValues[j] = board[plotIdx];
                ioBoard[plotIdx] = randVal;
            }
        }
        else
        {
            std::cout << "ERROR: Unkown split mode" << std::endl;
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
