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
static const float			kMutationRate	= 0.075;//065;

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
    
    // We'll reuse this for each test
    int axisVals[axisLength];

    for (int i = 0; i < axisLength; ++i)
    {
        rowValuesForRowIndex(i,
                             iBoard,
                             axisLength,
                             axisVals);
        
        float rowFitness = rowFitnessFunc(axisVals, axisLength);
        if (totalScore == 0.0f)
        {
            totalScore = rowFitness;
        }
        else
        {
            totalScore *= rowFitness;
        }
    }
    
    // Now the score is 0-1
    totalScore *= 0.5f;
    
    float colScore = 0.0f;
    for (int i = 0; i < axisLength; ++i)
    {
        colValuesForColumnIndex(i,
                               iBoard,
                               axisLength,
                               axisVals);
        
        float colFitness = rowFitnessFunc(axisVals, axisLength);
        if (colScore == 0.0f)
        {
            colScore = colFitness;
        }
        else
        {
            colScore *= colFitness;
        }
    }
    
    // Now the score is 0-1
    totalScore += colScore * 0.25f;

    if (totalScore >= 0.75f)
    {
        
        // 0.125 for unique col bands
        // 0.125 for unique row bands
        /*
        const float uniqueAxisValue = 0.25f;
        const float uniqueBandValue = uniqueAxisValue / bandLength;
        const float uniqueBlockValue = uniqueBandValue / bandLength;
        */
        
        float uniqueBlockValue = 0.25 / axisLength;
        int numUniqueBlocks = 0;
        for (int b = 0; b < axisLength; b++)
        {
            quadValuesForQuadIndex(b, iBoard, axisLength, axisVals);
            int numReps = numRepetitionsInAxis(axisVals, axisLength);
            if (numReps == 0)
            {
                numUniqueBlocks++;
                totalScore += uniqueBlockValue;
            }
        }

        // For each ROW BAND
        // Check if 2 of 3 blocks are unique
        // for each band 0.25 * 0.3333
        /*
        int numUniqueRows = 0;
        for (int horizBand = 0; horizBand < bandLength; ++horizBand)
        {
            int numUniqueBlocks = 0;
            for (int block = 0; block < bandLength; ++block)
            {
                // Check if 2 out of 3 are unique
                int blockIndex = (horizBand * bandLength) + block;
                quadValuesForQuadIndex(blockIndex, iBoard, axisLength, axisVals);
                int numReps = numRepetitionsInAxis(axisVals, axisLength);
                if (numReps == 0)
                {
                    numUniqueBlocks++;
                    totalScore += uniqueBlockValue;
                }
            }
        }
        */
        /*
        // IF the ROW test passes
        // Do the same for each COL BAND
        if (numUniqueRows == bandLength)
        {
            for (int vertBand = 0; vertBand < bandLength; ++vertBand)
            {
                int numUniqueBlocks = 0;
                for (int block = 0; block < bandLength; ++block)
                {
                    // Check if 2 out of 3 are unique
                    int blockIndex = vertBand + (bandLength * block);
                    quadValuesForQuadIndex(blockIndex, iBoard, axisLength, axisVals);
                    int numReps = numRepetitionsInAxis(axisVals, axisLength);
                    if (numReps == 0)
                    {
                        numUniqueBlocks++;
                        totalScore += uniqueBlockValue;
                    }
                }
            }
        }
         */
    }

    // Multiply
    
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
            // printBoard(iBoard, iTileCount);
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
    

    // Randomly split the board
    /*
    int tMid = randomInt( 0, (int)iTileCount );
    for(size_t i = 0; i < iTileCount; i++)
    {
        if (i < tMid)
        {
            oBoard[i] = iBoardA[i];
        }
        else
        {
            oBoard[i] = iBoardB[i];
        }
	}
    */

    int axisLength = sqrt(iTileCount);
    int bandLength = sqrt(axisLength);

    // Pick 2 bands from A and 1 band from B
    // int bandMid = bandLength / 2;
    int bandMid = 1; //randomInt( 1, bandLength + 1);
    for (int band = 0; band < bandLength; ++band)
    {
        // Iterate over the band
        for (int row = 0; row < bandLength; ++row)
        {
            int rowValues[axisLength];
            int rowIndex = (band * bandLength) + row;
            if (band < bandMid)
            {
                rowValuesForRowIndex(rowIndex, iBoardA, axisLength, rowValues);
            }
            else
            {
                rowValuesForRowIndex(rowIndex, iBoardB, axisLength, rowValues);
            }
            insertRowValuesAtRowIndex(rowIndex, oBoard, axisLength, rowValues);
        }
    }

    
    // Split based on columns and rows.
    // This lets use preserve whatever value has been built up in them
    /*
    int tMid = randomInt( 0, getTileValueMax() );
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
    */
}

static void mutateFunc(int* ioBoard, const size_t& iTileCount, const float& iMutationRate)
{
    // Check how fit a row is and use the inverse fitness as a probability for switching its values
    int axisLength = sqrt(iTileCount);
    int numBands = sqrt(axisLength);
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
    
    // Call the fitness function to get the score
    /*
    float fitnessScore = fitnessFunc(ioBoard, iTileCount);
    
    if (fitnessScore >= 0.5f)
    {*/
        // Pick a random column.
        int randCol = randomInt(0, axisLength);
        
        // Get the column values.
        int colVals[axisLength];
        colValuesForColumnIndex(randCol, ioBoard, axisLength, colVals);

        // Check if there are duplicates.
        int count[axisLength];
        for (int i = 0; i < axisLength; ++i)
        {
            count[i] = 0;
        }
        int dupIndex = -1;
        for (int i = 0; i < axisLength; ++i)
        {
            int idx = colVals[i] - 1; // convert to zero based
            int curVal = count[idx];
            if (curVal > 0)
            {
                // This is a duplicate. Store the index.
                dupIndex = i;
                break;
            }
            // Otherwise remember
            count[idx] = curVal+1;
        }
        // ... swap it with a random value in it's own row.
        if (dupIndex != -1)
        {
            int fromIndex = xyToIdx(randCol, dupIndex, axisLength);
            int toCol = randomInt(0, axisLength);
            int toIndex = xyToIdx(toCol, dupIndex, axisLength);
            int fromVal = ioBoard[fromIndex];
            int toVal = ioBoard[toIndex];
            ioBoard[fromIndex] = toVal;
            ioBoard[toIndex] = fromVal;
        }
    //}
    
    
    /*
    // If 0.5-0.75, start swapping columns within a band
    if (fitnessScore >= 0.5f && fitnessScore < 0.75f)
    {
        for (int band = 0; band < numBands; ++band)
        {
            int newColumnOrder[axisLength];
            // NOTE: This permutes the entire axis, not a 2 column swap
            randUniqueAxis(newColumnOrder, axisLength);
            for (int x = 0; x < axisLength; ++x)
            {
                int toCol = x;
                int fromCol = newColumnOrder[x];
                int numBandRows = numBands;
                for (int y = 0; y < numBandRows; ++y)
                {
                    int row = (band * numBandRows) + y;
                    
                    int toIndex = xyToIdx(toCol, row, axisLength);
                    int fromIndex = xyToIdx(fromCol, row, axisLength);
                    
                    // Swap the vals
                    int toVal = ioBoard[toIndex];
                    int fromVal = ioBoard[fromIndex];

                    ioBoard[toIndex] = fromVal;
                    ioBoard[fromIndex] = toVal;                    
                }
            }
        }
    }
    */
    
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
    
    if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate)
    {
        int fromIdx = randomInt(0, axisLength);
        int toIdx = randomInt(0, axisLength);
        int fromValues[axisLength];
        int toValues[axisLength];
        colValuesForColumnIndex(fromIdx, ioBoard, axisLength, fromValues);
        colValuesForColumnIndex(toIdx, ioBoard, axisLength, toValues);
        
        insertColValuesAtColumnIndex(toIdx, ioBoard, axisLength, fromValues);
        insertColValuesAtColumnIndex(fromIdx, ioBoard, axisLength, toValues);
    }
    
    if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate)
    {
        int fromIdx = randomInt(0, axisLength);
        int toIdx = randomInt(0, axisLength);
        int fromValues[axisLength];
        int toValues[axisLength];

        rowValuesForRowIndex(fromIdx, ioBoard, axisLength, fromValues);
        rowValuesForRowIndex(toIdx, ioBoard, axisLength, toValues);
        
        insertRowValuesAtRowIndex(toIdx, ioBoard, axisLength, fromValues);
        insertRowValuesAtRowIndex(fromIdx, ioBoard, axisLength, toValues);

    }
    
    /*
    // Randomly flit tiles
	for(int i = 0; i < iTileCount; i++)
    {
		if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate)
        {
			ioBoard[i] = randomInt( getTileValueMin(), getTileValueMax() + 1 );
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
