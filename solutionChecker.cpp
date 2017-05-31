//
//  solutionChecker.cpp
//  sudokuSolver
//
//  Created by Jason  Sands on 5/3/17.
//  Copyright © 2017 James Alford-Golojuch. All rights reserved.
//

#include "solutionChecker.hpp"

#include <iostream>
using namespace std;

bool checkSolver(SudokuPuzzle solution) {
    bool solved = true;
    // Check for conflicts in row and columns
    for(int i = 0; i < SQUARE_SIZE; i++){
        // Check row
        vector<int> tmp = solution.getRow(i);
        if (!checkRow(tmp)){
            solved = false;
        }
    }
    // Check columns
    for(int i = 0; i < SQUARE_SIZE; i++){
        vector<int> tmp = solution.getCol(i);
        if (!checkRow(tmp)){
            solved = false;
        }
    }
    // Check blocks
    for(int i = 0; i < SQUARE_SIZE; i++){
        vector<int> tmp = solution.getBlockVector(i);
        if (!checkRow(tmp)){
            solved = false;
        }
    }
    return solved;
}

// Also used to check column values
bool checkRow(vector<int> row){
    bool rowSolved = true;
    
    // Check for 0 value in row
    if (find(row.begin(), row.end(), 0) != row.end()){
        rowSolved = false;
    } else {
        vector<int> count = {0,0,0,0,0,0,0,0,0};
        // Count up each variable
        for(int i = 0; i < SQUARE_SIZE; i++){
            int tmp = row[i];
            count[tmp-1] = count[tmp-1] + 1;
        }
        // Check for all count being 1
        for(int i = 0; i < SQUARE_SIZE; i++){
            if(count[i] != 1){
                rowSolved = false;
            }
        }
    }
    return rowSolved;
}
