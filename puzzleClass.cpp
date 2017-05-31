//
//  puzzleClass.cpp
//  sudokuSolver
//
//  Created by Jason  Sands on 4/30/17.
//  Copyright © 2017 James Alford-Golojuch. All rights reserved.
//

#include "puzzleClass.hpp"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// Puzzle constructor
SudokuPuzzle::SudokuPuzzle(){
    puzzle = {SQUARE_SIZE, vector<int>(SQUARE_SIZE, 0)};
}

// Makes puzzle based upon user specifications
// Still need to perform checks to make sure puzzle is within given contraints (assumed for now)
SudokuPuzzle::SudokuPuzzle(vector<vector<int>> tmpPuzzle){
    puzzle = {SQUARE_SIZE, vector<int>(SQUARE_SIZE, 0)};
    // Check for correct puzzle size
    if(tmpPuzzle.size() == SQUARE_SIZE){
        // Check for correct row size
        bool corrSize = true;
        for(int i = 0; i < SQUARE_SIZE && corrSize; i++){
            if(tmpPuzzle[i].size() != SQUARE_SIZE){
                corrSize = false;
            }
        }
        if(!corrSize){
            cout << "Error puzzle is not of correct shape. Setting puzzle to be a blank puzzle" << endl;
            SudokuPuzzle();
        } else {
            puzzle = tmpPuzzle;
        }
    } else {
        cout << "Error puzzle is not of correct shape. Setting puzzle to be a blank puzzle" << endl;
        SudokuPuzzle();
    }
}

void SudokuPuzzle::setValue(int row, int col, int value){
    if(puzzle[row][col] != 0){
        cout << "Error tried to set position Row: " << row << " and Column: " << col << " to value " << value << endl;
    } else {
        puzzle[row][col] = value;
    }
}

void SudokuPuzzle::printPuzzle(){
    // Prints puzzle out with lines separating the 3x3 (or other size) squares in puzzle
    for(int i = 0; i < SQUARE_SIZE; i++){
        if (i % 3 == 0 && i != 0){
            cout << "---------------------" << endl;
        }
        for(int j = 0; j < SQUARE_SIZE; j++){
            if (j % 3 == 0 && j != 0){
                cout << "| ";
            }
            if (puzzle[i][j] == 0){
                cout << "  ";
            } else {
                cout << puzzle[i][j] << " ";
            }
        }
        cout << endl;
    }
}

vector<int> SudokuPuzzle::getRow(int rowNum){
    // Vector to hold row values
    vector<int> tmp = puzzle[rowNum];

    return tmp;
}

vector<int> SudokuPuzzle::getCol(int colNum){
    // Vector to hold row values
    vector<int> tmp;
    for(int i = 0; i < SQUARE_SIZE; i++){
        tmp.push_back(puzzle[i][colNum]);
    }
    return tmp;
}

vector<int> SudokuPuzzle::getBlockVector(int blockNum){
    // Blocknum is number from 0-8
    // Vector to hold the values in the block
    vector<int> tmp;
    vector<int> rowNum = confRow(blockNum);
    vector<int> colNum = confCol(blockNum);
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tmp.push_back(puzzle[rowNum[i]][colNum[j]]);
        }
    }
    return tmp;
}

// Returns the value of a specified location
int SudokuPuzzle::getSpaceValue(int row, int col){
    return puzzle[row][col];
}

// Returns conflicting rows for a block
vector<int> confRow(int blockNum){
    vector<int> rowNum;
    
    // Finds desired row numbers
    if(blockNum >= 0 && blockNum <= 2){
        rowNum = {0,1,2};
    } else if (blockNum >= 3 && blockNum <= 5){
        rowNum = {3,4,5};
    } else {
        rowNum = {6,7,8};
    }
    return rowNum;
}

// Returns conflicting columns for a block
vector<int> confCol(int blockNum){
    vector<int> colNum;
    
    // Finds desired column numbers
    if(blockNum % 3 == 0){
        colNum = {0,1,2};
    } else if(blockNum % 3 == 1){
        colNum = {3,4,5};
    } else {
        colNum = {6,7,8};
    }
    return colNum;
}
