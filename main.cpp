//
//  main.cpp
//  sudokuSolver
//
//  Created by James Alford-Golojuch on 4/28/17.
//  Copyright © 2017 James Alford-Golojuch. All rights reserved.
//

#include "puzzleClass.hpp"
#include "solutionChecker.hpp"
#include "solutionFinder.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    // Easy
    vector<vector<int>> easy = {{0,0,5,6,0,7,4,0,0},{0,9,0,1,0,2,0,5,0},{1,0,0,5,8,4,0,0,2},
        {6,5,8,0,0,0,1,9,7},{0,0,3,0,0,0,5,0,0},{9,4,1,0,0,0,6,2,3},
        {5,0,0,3,7,1,0,0,4},{0,7,0,8,0,9,0,1,0},{0,0,6,2,0,5,8,0,0}};
    // Medium
    vector<vector<int>> med = {{0,3,0,0,2,0,0,1,0},{4,0,0,1,0,7,0,0,2},{0,0,9,0,0,0,8,0,0},
        {6,0,3,0,0,0,2,0,8},{0,0,4,6,0,9,3,0,0},{8,0,1,0,0,0,9,0,4},
        {0,0,6,0,0,0,1,0,0},{3,0,0,2,0,4,0,0,6},{0,7,0,0,5,0,0,8,0}};
    // Solved
    vector<vector<int>> tough1 = {{8,3,0,0,0,0,0,4,6},{0,2,0,1,0,4,0,3,0},{0,0,0,0,0,0,0,0,0},
        {0,0,2,9,0,6,5,0,0},{1,4,0,0,0,0,0,2,3},{0,0,5,4,0,3,1,0,0},
        {0,0,0,0,0,0,0,0,0},{0,6,0,3,0,8,0,7,0},{9,5,0,0,0,0,0,6,2}};
    // Solved
    vector<vector<int>> tough2 = {{4,0,0,8,0,0,0,0,0},{0,0,0,7,4,0,0,6,9},{0,0,6,0,0,0,0,1,3},
        {0,6,0,0,9,0,3,0,0},{5,0,0,0,0,0,0,0,6},{0,0,3,0,8,0,0,4,0},
        {9,3,0,0,0,0,2,0,0},{2,1,0,0,7,5,0,0,0},{0,0,0,0,0,9,0,0,8}};
    // Not Solved
    vector<vector<int>> tough3 = {{2,0,0,0,1,0,0,8,0},{5,0,0,7,0,2,1,0,0},{0,6,3,9,0,0,0,0,0},
        {7,3,2,0,0,5,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,4,0,0,9,3,2},
        {0,0,0,0,0,8,5,9,0},{0,0,5,2,0,7,0,0,4},{0,8,0,0,5,0,0,0,7}};

    SudokuPuzzle puzzle(tough3);

    cout << "Puzzle before solution" << endl;
    puzzle.printPuzzle();
    cout << endl;
    
    SudokuPuzzle solution = solutionFinder(puzzle);
    cout << "Puzzle after solution" << endl;
    solution.printPuzzle();
    
    return 0;
}
