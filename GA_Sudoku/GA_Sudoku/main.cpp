//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

#include "Population.h"
#include "Constants.h"

#include "Solver.h"
#include "Helpers.h"

/**
 * GENETIC SUDOKU SOLVER TOURNAMENT
 *
 * Population.h contains a basic, generalized framework for the facilitation of a genetic algorithm.
 * This file may be edited to improve performance or API accessibility but should not be edited in ways that
 * might conflict with a fair competition.
 *
 * Solver.h currently contains some functions stubs. These will be evoked by an instance of the Population class.
 * Each team should edit these functions to produce a winning Sudoku solver.
 *
 * Constants.h contains a few helper functions that are accessible through libSudokuConstants.a, a static library.
 * To help ensure a fair competition, the implementation of these methods has been masked by the use of the static library.
 */

using namespace std;

int main(int argc, const char * argv[])
{
	cout << "Performing sanity check..." << endl;

    // TMP
    TestIntUniquenessFunction();
    TestLongUniquenessFunction();
    TestIsSetUnique();
    TestIdxToXY();
    TestXYToIdx();
    TestQuadIdx();
    printBoard(init_test_correct, getTileCount());
    float bestScore = fitnessFunc(init_test_correct, getTileCount());
    cout << "Best Possible Score: " << bestScore << endl;
    // exit(0);
    
	if( getBoardWin( init_test_correct, getTileCount() ) && !getBoardWin( init_test_incorrect, getTileCount() ) ) {
		cout << "PASSED" << endl << endl;
	}
	else {
		cout << "FAILED" << endl << endl;
		return 0;
	}
	cout << "Running team: \'" << kAuthorTeam << "\'" << endl << endl;
	// Seed random:
	srand( (unsigned int)time( NULL ) );
	// Prepare analytics:
	size_t tAvgDuration = 0;
	size_t tAvgGenCount = 0;
	// Run each test round:
	for(int i = 0; i < getTestRunCount(); i++)
    {
        cout << "Test round #" << i << " started." << endl;
		// Start timer:
		size_t tTimeStart = getTimeNow();
		// Create new population instance:
		Population<int>* mPopulation = new Population<int>( getPopulationSize(), getTileCount(), kMutationRate );
		// Set function bindings:
		mPopulation->setInitializeFunction( randomBoard );
		mPopulation->setFitnessFunction( fitnessFunc );
		mPopulation->setCrossoverFunction( crossoverFunc );
		mPopulation->setMutationFunction( mutateFunc );
		mPopulation->setPrintFunction( printBoard );
		// Initialize the population:
		mPopulation->initialize();
		// While running flag is set, keep running algorithm:
		while( mPopulation->isRunning() )
        {
//            cout << ".";
			mPopulation->runGeneration();
		}
		// End timer:
		size_t tTimeStop = getTimeNow();
		// Update analytics:
		tAvgDuration += ( tTimeStop - tTimeStart );
		tAvgGenCount += mPopulation->getGenerationNumber();
		// Print win state:
		mPopulation->printWinState();
		// Delete population:
		delete mPopulation;
		// Report progress:
		cout << endl << "Test round #" << i << " completed." << endl << endl;
	}
	// Print score:
	cout << "TEAM SCORE: \'" << kAuthorTeam << "\'" << endl;
	cout << "\tAverage Duration: " << ( (float)tAvgDuration / (float)getTestRunCount() ) << " milliseconds" << endl;
	cout << "\tAverage Generation Count: " << ( (float)tAvgGenCount / (float)getTestRunCount() ) << endl;
	// Return:
    return 0;
}

