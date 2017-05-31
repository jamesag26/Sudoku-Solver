//
//  puzzleClass.hpp
//  sudokuSolver
//
//  Created by Jason  Sands on 4/30/17.
//  Copyright © 2017 James Alford-Golojuch. All rights reserved.
//

#ifndef puzzleClass_hpp
#define puzzleClass_hpp

#include <stdio.h>
#include <vector>

int const SQUARE_SIZE = 9;

class SudokuPuzzle{
private:
    std::vector<std::vector<int>> puzzle;
public:
    SudokuPuzzle();
    SudokuPuzzle(std::vector<std::vector<int>> tmpPuzzle);
    void setValue(int row, int col, int value);
    void printPuzzle();
    std::vector<int> getRow(int rowNum);
    std::vector<int> getCol(int colNum);
    std::vector<int> getBlockVector(int blockNum);
    int getSpaceValue(int row, int col);
};

std::vector<int> confRow(int blockNum);
std::vector<int> confCol(int blockNum);
#endif /* puzzleClass_hpp */
