//
//  solutionFinder.hpp
//  sudokuSolver
//
//  Created by Jason  Sands on 5/3/17.
//  Copyright © 2017 James Alford-Golojuch. All rights reserved.
//

#ifndef solutionFinder_hpp
#define solutionFinder_hpp

#include <stdio.h>
#include "puzzleClass.hpp"

SudokuPuzzle solutionFinder(SudokuPuzzle puzzle);

std::vector<int> missingNumbers(std::vector<int> row);
std::vector<int> possibleNums(std::vector<int> row, std::vector<int> col, std::vector<int> missingNums);
std::vector<std::vector<int>> countBlockValidNums(std::vector<std::vector<int>> validNums);
std::vector<std::vector<std::vector<int>>> findPairs(SudokuPuzzle puzzle);

#endif /* solutionFinder_hpp */
