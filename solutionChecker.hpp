//
//  solutionChecker.hpp
//  sudokuSolver
//
//  Created by Jason  Sands on 5/3/17.
//  Copyright © 2017 James Alford-Golojuch. All rights reserved.
//

#ifndef solutionChecker_hpp
#define solutionChecker_hpp

#include <stdio.h>
#include <vector>
#include "puzzleClass.hpp"

bool checkRow(std::vector<int> row);

bool checkSolver(SudokuPuzzle solution);

#endif /* solutionChecker_hpp */
