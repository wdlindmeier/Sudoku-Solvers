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


static void quadValuesAtQuadIndex(const int* board, const int quadIndex, const int axisLength, int returnValues[])
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
        int plotIdx = (tileX * axisLength) + tileY;
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

static void quadValuesForTileIndex(const int index,
                                   const int* board,
                                   const size_t& iTileCount,
                                   int returnValues[])
{
    int axisLength = sqrt( iTileCount );
    int quadIndex = quadIndexForTileIndex(index, axisLength);
    quadValuesAtQuadIndex(board, quadIndex, axisLength, returnValues);
}

static void rowValuesForTileIndex(const int index,
                                  const int* board,
                                  const size_t& iTileCount,
                                  int returnValues[])
{
    int axisLength = sqrt( iTileCount );
    //    int row = index / axisLength;
    int col = index % axisLength;
    
    for (int i = 0; i < axisLength; ++i)
    {
        int plotIdx = (i * axisLength) + col;
        returnValues[i] = board[plotIdx];
    }
}

static void colValuesForTileIndex(const int index,
                                  const int* board,
                                  const size_t& iTileCount,
                                  int returnValues[])
{
    int axisLength = sqrt( iTileCount );
    int row = index / axisLength;
    //    int col = index % axisLength;
    for (int i = 0; i < axisLength; ++i)
    {
        int plotIdx = (row * axisLength) + i;
        returnValues[i] = board[plotIdx];
    }
}

static int xyToIdx(const int x, const int y, const int axisLength)
{
    // NOTE: Backwards
    return (x * axisLength) + y;
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

#endif
