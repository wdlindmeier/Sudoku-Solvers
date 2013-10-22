//
//  Helpers.h
//  GA_Sudoku
//
//  Created by William Lindmeier on 10/11/13.
//  Copyright (c) 2013 Patrick J Hebron. All rights reserved.
//

#ifndef GA_Sudoku_Helpers_h
#define GA_Sudoku_Helpers_h

#include <map>

template <typename T>
static bool VectorFind(const T & item, const std::vector<T> & vec)
{
    return std::find(vec.begin(), vec.end(), item) != vec.end();
}

static bool isSetUnique(int set[], int rowLength)
{
    std::map<int, int> valueCounts;
    for (int i = 0; i < rowLength; ++i)
    {
        int val = set[i];
        if (valueCounts.find(val) != valueCounts.end())
        {
            return false;
        }
        else
        {
            valueCounts[val] += 1;
        }
    }
    return true;
}

static void randUniqueAxis(int values[], int axisLength)
{
    for (int i = 0; i < axisLength; ++i)
    {
        int randIndex = randomInt(0, i+1);
        values[i] = values[randIndex];
        values[randIndex] = i;
    }
}

static void shuffleAxisValues(int values[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        int randSwapIndex = randomInt(0, length);
        int value = values[i];
        int otherValue = values[randSwapIndex];
        values[i] = otherValue;
        values[randSwapIndex] = value;
    }
}

static int numRepetitionsInAxis(int set[], int rowLength)
{
    int count[rowLength];// = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < rowLength; ++i)
    {
        count[i] = 0;
    }
    
    int numReps = 0;
    for (int i = 0; i < rowLength; ++i)
    {
        int idx = set[i] - 1; // convert to zero based
        int curVal = count[idx];
        if (curVal > 0)
        {
            numReps++;
        }
        // Mark as taken
        count[idx] = curVal + 1;
    }
    return numReps;
}

static float intUniquenessScalar(int set[], int rowLength)
{
    int count[rowLength];// = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < rowLength; ++i)
    {
        count[i] = 0;
    }
    
    for (int i = 0; i < rowLength; ++i)
    {
        int idx = set[i] - 1; // convert to zero based
        int curVal = count[idx] + 1;
        count[idx] = curVal;
    }
    int totalVal = 0;
    for (int i = 0; i < rowLength; ++i)
    {
        int idxVal = abs(1 - count[i]);
        totalVal += idxVal;
    }
    
    // Worst case scenario is all the same number
    // 8 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1
    
    // Best is 0
    
    float worstValue = (rowLength-1) * 2;
    // 0 is worst.
    // 1 is best.
    float result = 1.0f - ((float)totalVal / worstValue);
    /*
    if (result < 1.0f)
    {
        // Give it a boost if its unique
        result = result * 0.5f;
    }
    */
    return result;
}

static float longUniquenessScalar(long longs[], int rowLength)
{
    // Add value if the combination of numbers is unique
    int dupCount = 0;
    int dupCalcs = 0;
    for (int i = 0; i < rowLength; ++i)
    {
        long l1 = longs[i];
        for (int j = 0; j < rowLength; ++j)
        {
            if (i != j)
            {
                dupCalcs++;
                long l2 = longs[j];
                if (l1 == l2)
                {
                    dupCount++;
                }
            }
        }
    }
    float dupScore = 1.0f - ((float)dupCount / (float)dupCalcs);
    if (dupScore < 1.0f)
    {
        // Give it a boost if its unique
        dupScore = dupScore * 0.5f;
    }
    return dupScore;
}

static void TestIsSetUnique()
{
    int uniqueSet[] = {1,2,3,4,5,6,7};
    if (!isSetUnique(uniqueSet, 7))
    {
        // Ooops
        std::cout << "ERROR: Unique set doesn't return true.";
        exit(1);

    }
    int dupSet[] = {1,1,3,4,5,6,7};
    if (isSetUnique(dupSet, 7))
    {
        // Ooops
        std::cout << "ERROR: Non-Unique set doesn't return false.";
        exit(1);

    }
}

static void TestLongUniquenessFunction()
{
    int tAxisLen = 9;
    long bestLongs[tAxisLen];
    for (int i = 0; i < tAxisLen; ++i)
    {
        std::string newLong = "";
        for (int j = 0; j < tAxisLen; ++j)
        {
            newLong += std::to_string((j + i) % tAxisLen);
        }
        bestLongs[i] = stol(newLong);
    }
    float bestVal = longUniquenessScalar(bestLongs, tAxisLen);
    if(bestVal != 1.0f)
    {
        // Ooops
        std::cout << "ERROR: Best value is not 1.";
        exit(1);
    }
    
    long worstLongs[tAxisLen];
    for (int i = 0; i < tAxisLen; ++i)
    {
        std::string newLong = "";
        for (int j = 0; j < tAxisLen; ++j)
        {
            newLong += std::to_string(j);
        }
        worstLongs[i] = stol(newLong);
    }
    float worstVal = longUniquenessScalar(worstLongs, tAxisLen);
    if(worstVal != 0.0f)
    {
        // Ooops
        std::cout << "ERROR: Worst value is not 0.";
        exit(1);
    }
}

static void TestIntUniquenessFunction()
{
    int tAxisLen = 9;
    int worstSet[tAxisLen];
    for (int i = 0; i < tAxisLen; ++i)
    {
        worstSet[i] = 8;
    }
    float worstVal = intUniquenessScalar(worstSet, tAxisLen);
    if(worstVal != 0)
    {
        // Ooops
        std::cout << "ERROR: Worst value is not 0.";
        exit(1);
    }
    
    int bestSet[tAxisLen];
    for (int i = 0; i < tAxisLen; ++i)
    {
        bestSet[i] = i + 1;
    }
    float bestVal = intUniquenessScalar(bestSet, tAxisLen);
    if(bestVal != 1)
    {
        // Ooops
        std::cout << "ERROR: Best value is not 1.";
        exit(1);
    }
}

static int xyToIdx(const int x, const int y, const int axisLength)
{
    // NOTE: Backwards
    return (x * axisLength) + y;
}


static void quadValuesForQuadIndex(const int quadIndex, const int* board, const int axisLength, int returnValues[])
{
    // The Quad at index i
    // 0 1 2
    // 3 4 5
    // 6 7 8
    int quadsLen = sqrt(axisLength);
    int quadXOff = (quadIndex % quadsLen) * quadsLen; // the number of x tile offset
    int quadYOff = (quadIndex / quadsLen) * quadsLen; // the number of y tile offset
    for (int j = 0; j < axisLength; ++j)
    {
        int qX = j % quadsLen;
        int qY = j / quadsLen;
        int tileX = quadXOff + qX;
        int tileY = quadYOff + qY;
        //int plotIdx = (tileX * axisLength) + tileY;
        int plotIdx = xyToIdx(tileX, tileY, axisLength);
        returnValues[j] = board[plotIdx];
    }
}

static int quadIndexForTileIndex(const int index, const int axisLength)
{
    int quadAxisLength = sqrt( axisLength );
    
    // swapped
    int col = index / axisLength;
    int row = index % axisLength;
    
    int quadX = col / quadAxisLength;
    int quadY = row / quadAxisLength;
    
    return (quadY * quadAxisLength) + quadX;
}

void TestQuadIdx()
{
    if (quadIndexForTileIndex(0, 9) != 0)
    {
        std::cout << "ERROR: Expected index 0 to be Quad 0\n";
        exit(1);
    }
    if (quadIndexForTileIndex(80, 9) != 8)
    {
        std::cout << "ERROR: Expected index 80 to be Quad 8\n";
        exit(1);
    }
    if (quadIndexForTileIndex(40, 9) != 4)
    {
        std::cout << "ERROR: Expected index 40 to be Quad 4\n";
        exit(1);
    }
}

static void _quadValuesForTileIndex(const int index,
                                    const int* board,
                                    const int axisLength,
                                    int returnValues[])
{
    int quadIndex = quadIndexForTileIndex(index, axisLength);
    quadValuesForQuadIndex(quadIndex, board, axisLength, returnValues);
}

static void _rowValuesForTileIndex(const int index,
                                   const int* board,
                                   const int axisLength,
                                   int returnValues[])
{
    int col = index % axisLength;
    
    for (int i = 0; i < axisLength; ++i)
    {
        int plotIdx = (i * axisLength) + col;
        returnValues[i] = board[plotIdx];
    }
}

static void rowValuesForRowIndex(const int index,
                                 const int* board,
                                 const int axisLength,
                                 int returnValues[])
{
    return _rowValuesForTileIndex(index, board, axisLength, returnValues);
}

static void _colValuesForTileIndex(const int index,
                                  const int* board,
                                  const int axisLength,
                                  int returnValues[])
{
    int row = index / axisLength;
    //    int col = index % axisLength;
    for (int i = 0; i < axisLength; ++i)
    {
        int plotIdx = (row * axisLength) + i;
        returnValues[i] = board[plotIdx];
    }
}

static void colValuesForColumnIndex(const int index,
                                    const int* board,
                                    const int axisLength,
                                    int returnValues[])
{
    return _colValuesForTileIndex(index * axisLength, board, axisLength, returnValues);
}

static void insertColValuesAtColumnIndex(int index, int * board, int axisLength, int values[])
{
    for (int i = 0; i < axisLength; ++i)
    {
        int plotIdx = (index * axisLength) + i;
        board[plotIdx] = values[i];
    }
}

static void insertRowValuesAtRowIndex(int index, int * board, int axisLength, int values[])
{
    int col = index % axisLength;
    
    for (int i = 0; i < axisLength; ++i)
    {
        int plotIdx = (i * axisLength) + col;
        board[plotIdx] = values[i];
    }
}

static void insertQuadValuesAtQuadIndex(int index, int * board, int axisLength, int values[])
{
    int quadsLen = sqrt(axisLength);
    int quadXOff = (index % quadsLen) * quadsLen; // the number of x tile offset
    int quadYOff = (index / quadsLen) * quadsLen; // the number of y tile offset
    for (int j = 0; j < axisLength; ++j)
    {
        int qX = j % quadsLen;
        int qY = j / quadsLen;
        int tileX = quadXOff + qX;
        int tileY = quadYOff + qY;
        int plotIdx = xyToIdx(tileX, tileY, axisLength);
        board[plotIdx] = values[j];
    }
}

static void TestXYToIdx()
{
    int idx = xyToIdx(1, 2, 9);
    if (idx != 11)
    {
        std::cout << "ERROR: Expected x: 1, y: 2 to be index 11\n";
        exit(1);
    }
}

static void idxToXY(const int idx, int *xy, const int axisLength)
{
    // NOTE: Backwards
    xy[0] = idx / axisLength;
    xy[1] = idx % axisLength;
}

static void TestIdxToXY()
{
    int xy[2];
    idxToXY(11, xy, 9);
    if (xy[0] != 1 && xy[1] != 2)
    {
        std::cout << "ERROR: Expected index 11 to be x: 1, y: 2\n";
        exit(1);
    }
}

// A recursive function to create a success state
static bool solveBoard(const int tileIndex,
                       const int axisLength,
                       const int nextValue,
                       int *successBoard)
{
    int tileCount = axisLength * axisLength;
    if (tileIndex == tileCount)
    {
        // They've all been solved
        return true;
    }
    
    // Check if the incoming value will satisfy the current board:
    bool didEncounterError = false;
    
    int xy[2];
    idxToXY(tileIndex, xy, axisLength);
    int x = xy[0];
    int y = xy[1];
    int myQuadIdx = quadIndexForTileIndex(tileIndex, axisLength);
    for (int pi = 0; pi < tileIndex; ++pi)
    {
        int pxy[2];
        idxToXY(pi, pxy, axisLength);
        
        int px = pxy[0];
        int py = pxy[1];
        
        int prevQuadIdx = quadIndexForTileIndex(pi, axisLength);
        
        if (px == x || // Same column
            py == y || // Same row
            prevQuadIdx == myQuadIdx) // Same quad
        {
            int prevVal = successBoard[pi];
            if (prevVal == nextValue)
            {
                didEncounterError = true;
                break;
            }
        }
    }
    
    // If NO, return false.
    if (didEncounterError)
    {
        return false;
    }
    
    // If YES, dig deeper with new values.
    successBoard[tileIndex] = nextValue;
    
    // The current board works, start trying more values.
    for (int i = 0; i < axisLength; ++i)
    {
        if(solveBoard(tileIndex + 1,
                      axisLength,
                      i+1,
                      successBoard))
        {
            // This works!
            return true;
        }
    }
    
    // There are no feasible paths on this line.
    return false;
    
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


// TODO: This could be optimized to only try further
// values that conform to the previous state of the
// board, but board generation doesn't seem to be the bottleneck
// for this trial.
static bool randSuccessBoard(const size_t& iTileCount,
                             int successBoard[],
                             int startingValue)
{
    return solveBoard(0, sqrt( iTileCount ), startingValue, successBoard);
}

static void TestRandSuccessBoard()
{
    int tileLength = getTileCount();
    int successBoard[tileLength];
    for (int i = 0; i < tileLength; ++i)
    {
        // Clear it out
        successBoard[i] = 0;
    }
    for (int i = getTileValueMin(); i < getTileValueMax() + 1; i++)
    {
        if (!randSuccessBoard(tileLength, successBoard, i))
        {
            std::cout << "ERROR: Couldn't create a random board with seed: " << i << std::endl;
            // printBoard(successBoard, tileLength);
            exit(1);
        }
    }
}







// TEST ----

static int uniqueValues(int set[], int rowLength)
{
    int count[rowLength];// = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < rowLength; ++i)
    {
        count[i] = 0;
    }
    
    int numDups = 0;
    for (int i = 0; i < rowLength; ++i)
    {
        int idx = set[i] - 1; // convert to zero based
        int curVal = count[idx] + 1;
        count[idx] = curVal;
        if (curVal > 1)
        {
            numDups++;
            // Clear the dup
            set[i] = 0;
        }
    }
    
    return numDups;
}

static void dedupBoard(int board[], int axisLength)
{
    int tileCount = axisLength*axisLength;

    // Store the initial value
    int oldBoard[tileCount];
    for (int i = 0; i < tileCount; ++i)
    {
        oldBoard[i] = board[i];
    }
    
    for(int i = 0; i < axisLength; i++)
    {
        int quadVals[axisLength];
        quadValuesForQuadIndex(i,
                               board,
                               axisLength,
                               quadVals);
        int numQuadDups = uniqueValues(quadVals, axisLength);
        if (numQuadDups > 0)
        {
            // Replace the board values
            int quadsLen = sqrt(axisLength);
            int quadXOff = (i % quadsLen) * quadsLen; // the number of x tile offset
            int quadYOff = (i / quadsLen) * quadsLen; // the number of y tile offset
            for (int j = 0; j < axisLength; ++j)
            {
                int qX = j % quadsLen;
                int qY = j / quadsLen;
                int tileX = quadXOff + qX;
                int tileY = quadYOff + qY;
                int plotIdx = xyToIdx(tileX, tileY, axisLength);
                int val = quadVals[j];
                if (val == 0)
                {
                    board[plotIdx] = val;
                }
            }
        }
//    }
//    for(int i = 0; i < axisLength; i++)
//    {
        int colVals[axisLength];
        colValuesForColumnIndex(i,
                                board,
                                axisLength,
                                colVals);
        int numColDups = uniqueValues(colVals, axisLength);
        
        if (numColDups > 0)
        {
            for (int j = 0; j < axisLength; j++)
            {
                int tileIndex = (j * axisLength) + i;
                int val = colVals[j];
                if (val == 0)
                {
                    board[tileIndex] = val;
                }
            }
        }
//    }
//    for(int i = 0; i < axisLength; i++)
//    {
        int rowVals[axisLength];
        rowValuesForRowIndex(i,
                             board,
                             axisLength,
                             rowVals);
        int numRowDups = uniqueValues(rowVals, axisLength);
        if (numRowDups > 0)
        {
            // Replace the board values
            for (int j = 0; j < axisLength; j++)
            {
                int tileIndex = (i * axisLength) + j;
                int val = rowVals[j];
                if (val == 0)
                {
                    board[tileIndex] = val;
                }
            }
        }
    }
    
    // NOW: Go back through and try to re-add values that
    // were removed (but are now valid)
    for (int i = 0; i < tileCount; ++i)
    {
        bool didDup = false;
        int oldValue = oldBoard[i];
        
        int scratchValues[axisLength];
        
        _quadValuesForTileIndex(i, board, tileCount, scratchValues);
        for (int j = 0; j < axisLength; ++j)
        {
            if (scratchValues[j] == oldValue)
            {
                didDup = true;
                break;
            }
        }
        
        if (!didDup)
        {
            _colValuesForTileIndex(i, board, tileCount, scratchValues);
            for (int j = 0; j < axisLength; ++j)
            {
                if (scratchValues[j] == oldValue)
                {
                    didDup = true;
                    break;
                }
            }
        }

        if (!didDup)
        {
            _rowValuesForTileIndex(i, board, tileCount, scratchValues);
            for (int j = 0; j < axisLength; ++j)
            {
                if (scratchValues[j] == oldValue)
                {
                    didDup = true;
                    break;
                }
            }
        }
        
        if (!didDup)
        {
            board[i] = oldValue;
        }
    }
}

bool isValueValid(int value, int board[], int index, int axisLength)
{
    int tileCount = axisLength*axisLength;
    int scratchVals[axisLength];
    _rowValuesForTileIndex(index, board, tileCount, scratchVals);
    for (int i = 0; i < axisLength; ++i)
    {
        if (scratchVals[i] == value)
        {
            return false;
        }
    }
    
    _colValuesForTileIndex(index, board, tileCount, scratchVals);
    for (int i = 0; i < axisLength; ++i)
    {
        if (scratchVals[i] == value)
        {
            return false;
        }
    }
    
    _quadValuesForTileIndex(index, board, tileCount, scratchVals);
    for (int i = 0; i < axisLength; ++i)
    {
        if (scratchVals[i] == value)
        {
            return false;
        }
    }
    return true;
}

static long long NumIterations = 0;
static bool solveTile(const int tileIndex,
                      const int axisLength,
                      const int nextValue,
                      int *successBoard)
{
    NumIterations++;
    if (NumIterations > 10000000)
    {
        return false;
    }

    int tileCount = axisLength * axisLength;
    if (tileIndex == tileCount)
    {
        // They've all been solved
        return true;
    }
    
    bool isBlank = successBoard[tileIndex] == 0;
    
    if (isBlank)
    {
        // Only check undefined values.
        if (isValueValid(nextValue, successBoard, tileIndex, axisLength))
        {
            // If YES, dig deeper with new values.
            successBoard[tileIndex] = nextValue;
        }
        else
        {
            return false;
        }
    }    
    
    // The current board works, start trying more values.
    for (int i = 0; i < axisLength; ++i)
    {
        int checkValue = i+1;
        if(solveTile(tileIndex + 1,
                     axisLength,
                     checkValue,
                     successBoard))
        {
            // This works!
            return true;
        }
    }
    
    // There are no feasible paths on this line.
    // Revert the value if necessary.
    if (isBlank)
    {
        successBoard[tileIndex] = 0;
    }
    
    return false;
    
}

// Returns the number of steps it took to solve the board.
// Returns -1 if the board was not solved.
static long long boardSolver(int randBoard[], const size_t& iTileCount)
{
    // First, remove all duplicates
    int axisLength = sqrt(iTileCount);
    dedupBoard(randBoard, axisLength);
    
    NumIterations = 0;
    bool didSolve = solveTile(0, axisLength, 1, randBoard);
    if (didSolve)
    {
        std::cout << "Solved?\n";
    }
    else
    {
        std::cout << "Unsolved?\n";
    }    
    // Check if there are any undecided values left
    didSolve = true;
    for (int i = 0; i < iTileCount; ++i)
    {
        if (randBoard[i] == 0)
        {
            didSolve = false;
            break;
        }
    }
    if (didSolve)
    {
        std::cout << "SOLVED BOARD" << std::endl;
    }
    else
    {
        std::cout << "DIDNT SOLVE BOARD" << std::endl;
    }
    return NumIterations;
}

#endif
