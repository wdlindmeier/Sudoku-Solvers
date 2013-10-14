//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <cmath>

/** @brief Returns the GA population size = 1000 */
extern int		getPopulationSize();

/** @brief Returns the GA population count = 50 */
extern int		getTestRunCount();

/** @brief Returns the Sudoku axis length = 9 */
extern int		getTileAxis();

/** @brief Returns the Sudoku tile count = 81 */
extern int		getTileCount();

/** @brief Returns the minimum Sudoku tile value = 1 */
extern int		getTileValueMin();

/** @brief Returns the maximum Sudoku tile value = 9 */
extern int		getTileValueMax();

/** @brief Returns the current time in milliseconds */
extern size_t	getTimeNow();

/** @brief Returns whether the input board represents a Sudoku win state */
extern bool		getBoardWin(int* iBoard, const size_t& iTileCount);

// Moved from main.cpp
static int init_test_correct[] = {
	8, 3, 5, 4, 1, 6, 9, 2, 7,
	2, 9, 6, 8, 5, 7, 4, 3, 1,
	4, 1, 7, 2, 9, 3, 6, 5, 8,
	5, 6, 9, 1, 3, 4, 7, 8, 2,
	1, 2, 3, 6, 7, 8, 5, 4, 9,
	7, 4, 8, 5, 2, 9, 1, 6, 3,
	6, 5, 2, 7, 8, 1, 3, 9, 4,
	9, 8, 1, 3, 4, 5, 2, 7, 6,
	3, 7, 4, 9, 6, 2, 8, 1, 5
};

static int init_test_incorrect[] = {
	8, 3, 5, 4, 1, 6, 9, 2, 7,
	2, 9, 6, 8, 5, 7, 4, 3, 1,
	4, 1, 7, 2, 9, 3, 6, 5, 8,
	5, 6, 9, 1, 3, 4, 7, 8, 2,
	1, 2, 3, 6, 7, 8, 5, 4, 9,
	7, 4, 8, 5, 2, 9, 1, 6, 3,
	6, 5, 2, 7, 8, 1, 3, 9, 4,
	9, 8, 1, 3, 4, 5, 2, 7, 6,
	3, 7, 4, 9, 6, 2, 8, 1, 1
};
