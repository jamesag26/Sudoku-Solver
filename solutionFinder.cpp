//
//  solutionFinder.cpp
//  sudokuSolver
//
//  Created by Jason  Sands on 5/3/17.
//  Copyright © 2017 James Alford-Golojuch. All rights reserved.
//

#include "solutionFinder.hpp"
#include "solutionChecker.hpp"
#include <iostream>
#include <stdlib.h> 
#include <random>

using namespace std;

SudokuPuzzle solutionFinder(SudokuPuzzle puzzle){
    int cntr = 0;
    bool puzzleChanged = true;
    while(!checkSolver(puzzle) && puzzleChanged){
        puzzleChanged = false;
        cntr++;
        // Attempts to solve by block first
        for(int i = 0; i < SQUARE_SIZE; i++){
            // Finds blocks conflicting rows and columns
            vector<int> confR = confRow(i);
            vector<int> confC = confCol(i);
        
            // Get block vector
            vector<int> block = puzzle.getBlockVector(i);
            // Get missing numbers from block
            vector<int> missingNum = missingNumbers(block);
            
            
            /*// Print count
            cout << "Block " << i << " Missing Numbers: ";
            for(int j = 0; j < missingNum.size(); j++){
                cout << missingNum[j] << " ";
            }
            cout << endl;
            */
            
            // Runs through block again if a value was changed
            bool valueChanged = true;
            
            // Contains all possible numbers at each location in block
            vector<vector<int>> totalValidNums = {{}, {}, {}, {}, {}, {}, {}, {}, {}};
            
            while(valueChanged){
                valueChanged = false;
                // Calculates corresponding row and column
                int r = 0;
                int c = 0;
                // Searches through the block for an open space
                for(int j = 0; j < SQUARE_SIZE; j++){
                    // If space is open compare missing numbers list to conflicting rows and cols
                    if(block[j] == 0){
                        // Find possible numbers for space after eliminating
                        vector<int> validNums = possibleNums(puzzle.getRow(confR[r]), puzzle.getCol(confC[c]), missingNum);
                        // If only 1 number is valid add the number to the space in the puzzle
                        if(validNums.size() == 1){
                            puzzleChanged = true;
                            valueChanged = true;
                            puzzle.setValue(confR[r], confC[c], validNums[0]);
                            // Remove number from possible numbers
                            missingNum.erase(find(missingNum.begin(), missingNum.end(), validNums[0]));
                        } else {
                            // Updates possible valid numbers for the space
                            totalValidNums[j] = validNums;
                        }
                    }
                    // Increments corresponding r and c values
                    if ((j+1) % 3 == 0 && j != 0){
                        r++;
                    }
                    c = (c+1) % 3;
                }
                
                // If no value was changed, check to see if there are numbers who can only go in one space
                if(!valueChanged){
                    vector<vector<int>> numbersToFillIn = countBlockValidNums(totalValidNums);
                    // There are numbers that need to be filled in in the block
                    for(int j = 0; j < numbersToFillIn.size(); j++){
                        // Reset the position of r and c
                        r = 0;
                        c = 0;
                        // Loop through each square space and if that space is in numbersToFillIn
                        // Then set that space equal to numbersToFillIn[k][1]
                        for(int k = 0; k < SQUARE_SIZE; k++){
                            
                            if(numbersToFillIn[j][1] == k){
                                puzzle.setValue(confR[r], confC[c], numbersToFillIn[j][0]);
                                // Remove number from possible numbers
                                missingNum.erase(find(missingNum.begin(), missingNum.end(), numbersToFillIn[j][0]));
                                // Look at later
                                // This changes everything for some weird reason
                                //valueChanged = true;
                                puzzleChanged = true;
                            }
                            
                            // Increments corresponding r and c values
                            if ((k+1) % 3 == 0 && k != 0){
                                r++;
                            }
                            c = (c+1) % 3;
                        }
                    }
                }
            }
        }
    }
    /*
    // Test stuff for guessing
    if(!checkSolver(puzzle)){
        // Initialize random number genrator
        default_random_engine eng((random_device())());
        
        // Will be used to hold the new puzzle with the guessed value to be solved
        SudokuPuzzle tmp = puzzle;
        
        // Holds value for which pair to solve for
        int randPair = 0;

        // Finds number of pairs in puzzle so that we can guess one of the two values for a square in the puzzle
        vector<vector<vector<int>>> pairs = findPairs(puzzle);
        
        // If no pairs puzzle cant be solved currently and alert user and return puzzle as is
        if(pairs.size() == 0){
            // If no pairs exist alert user
            //cout << "No pairs exist in the puzzle" << endl;
            return puzzle;
        }
        
        if (pairs.size() > 1) {
            // Randomly select a pair to solve for
            uniform_int_distribution<int> randPairDist(0, int(pairs.size()) - 1);
            randPair = randPairDist(eng);
        }
            
        // Random uniform distribution from 0 to 1
        uniform_int_distribution<int> randDist(0, 1);
        int rand = randDist(eng);
        
        // Used if pair is in a block
        vector<int> tmpConfRow;
        vector<int> tmpConfCol;
        int rowPos = -1;
        
        // The pair is in a row
        if(pairs[randPair][0][0] < SQUARE_SIZE){
            // Sets the first space of the pair to be equal to rand pair value
            tmp.setValue(pairs[randPair][0][0], pairs[randPair][1][0], pairs[randPair][2][rand]);
        } else if(pairs[randPair][0][0] < SQUARE_SIZE*2){
            // The pair is in a column
            // Sets the first space of the pair to be equal to rand pair value
            tmp.setValue(pairs[randPair][1][0], pairs[randPair][0][0] - SQUARE_SIZE, pairs[randPair][2][rand]);
        } else {
            // The pair is in a block
            // Find the row and col for the pairs space
            tmpConfRow = confRow(pairs[randPair][0][0]);
            tmpConfCol = confCol(pairs[randPair][0][0]);
            // Every set of 3 numbers in a block vector represents a new row
            if(pairs[randPair][1][0] < 3){
                rowPos = 0;
            } else if(pairs[randPair][1][0] < 6){
                rowPos = 1;
            } else {
                rowPos = 2;
            }
            // Sets the first space of the pair to be equal to rand pair value
            tmp.setValue(tmpConfRow[rowPos], tmpConfCol[pairs[randPair][1][0]%3], pairs[randPair][2][rand]);
        }
        // Try to solve for the new puzzle
        tmp = solutionFinder(tmp);

        // If solution wasnt found then try the other value for the pair
        // Change value for puzzle since puzzle contains the original values before the guess
        if (checkSolver(tmp)){
            return tmp;
        } else {
            // The pair is in a row
            if(pairs[randPair][0][0] < SQUARE_SIZE){
                // Sets the first space of the pair to be equal to rand pair value
                puzzle.setValue(pairs[randPair][0][0], pairs[randPair][1][0], pairs[randPair][2][(rand+1)%2]);
            } else if(pairs[randPair][0][0] < SQUARE_SIZE*2){
                // The pair is in a column
                // Sets the first space of the pair to be equal to rand pair value
                puzzle.setValue(pairs[randPair][1][0], pairs[randPair][0][0] - SQUARE_SIZE, pairs[randPair][2][(rand+1)%2]);
            } else {
                // The pair is in a block
                // Sets the first space of the pair to be equal to rand pair value
                if (rowPos != -1 && tmpConfRow.size()==int(sqrt(SQUARE_SIZE)) && tmpConfCol.size()==int(sqrt(SQUARE_SIZE))){
                    tmp.setValue(tmpConfRow[rowPos], tmpConfCol[pairs[randPair][1][0]%3], pairs[randPair][2][rand]);
                } else {
                    cout << "Error the blocks information hasnt been properly stored." << endl;
                    return puzzle;
                }
            }
            
            puzzle = solutionFinder(puzzle);
        }
    }
    */
    return puzzle;
}

// Takes row, col or block of numbers and finds the numbers that are missing
vector<int> missingNumbers(vector<int> row){
    vector<int> missingNum;
    vector<int> count;
    
    // Populate count with 0's (9 unless puzzle size changes)
    for(int i = 0; i < SQUARE_SIZE; i++){
        count.push_back(0);
    }
    
    // Count up each variable
    for(int i = 0; i < SQUARE_SIZE; i++){
        int tmp = row[i];
        if(tmp > 0 && tmp <= SQUARE_SIZE){
            count[tmp-1] = count[tmp-1] + 1;
        }
    }
    
    // Check for all count being 1
    for(int i = 0; i < SQUARE_SIZE; i++){
        if(count[i] < 1){
            missingNum.push_back(i+1);
        }
        
        if(count[i] > 1){
            // Return vector with value -1 to represent an error
            vector<int> tmp = {-1};
            return tmp;
        }
    }
    return missingNum;
}

vector<int> possibleNums(vector<int> row, vector<int> col, vector<int> missingNums){
    vector<int> possibleNums;
    
    for(int i = 0; i < missingNums.size(); i++){
        // Check for conflicting number in row if not check column
        if(!(find(row.begin(), row.end(), missingNums[i]) != row.end())){
            // Check for conflicting number in column
            if(!(find(col.begin(), col.end(), missingNums[i]) != col.end())){
                // Add number to possible numbers
                possibleNums.push_back(missingNums[i]);
            }
        }
    }
    return possibleNums;
}

// Returns a vector containing a vector in the format of {numberToFillIn, belongsAtThisSpace}
// For when a number can only go in one space but that space can contain multiple numbers
vector<vector<int>> countBlockValidNums(vector<vector<int>> validNums){
    // Keeps track of what location a number was valid in
    vector<vector<int>> app;
    // Contains a vector of format {{numberToFillIn, atThisSpace}, ...}
    vector<vector<int>> spacesToFill;
    
    // Populate count with 0's
    for(int i = 0; i < SQUARE_SIZE; i++){
        app.push_back({});
    }
    
    // Count up each time a number is a validnumber
    for(int i = 0; i < validNums.size(); i++){
        for(int j = 0; j < validNums[i].size(); j++){
            int tmp = validNums[i][j];
            if(tmp > 0){
                // Add location of valid space to app
                app[tmp-1].push_back(i);
            }
        }
    }
    
    for(int i = 0; i < app.size(); i++){
        if(app[i].size() == 1){
            spacesToFill.push_back({i+1,app[i][0]});
        }
    }
    return spacesToFill;
}

// Finds
vector<vector<vector<int>>> findPairs(SudokuPuzzle puzzle){
    // Format is pairs{{row(#0-8)/col(#9-17)/block(#18-26)}, {position in row/col/block}, {possible number pairs}}
    vector<vector<vector<int>>> pairs;
    
    // Search through the rows for pairs
    for(int i = 0; i < SQUARE_SIZE; i++){
        vector<int> row = puzzle.getRow(i);
        vector<int> missNums = missingNumbers(row);
        if(missNums.size() == 2){
            vector<int> pos;
            for(int j = 0; j < SQUARE_SIZE; j++){
                if(row[j] == 0){
                    pos.push_back(j);
                }
            }
            pairs.push_back({{i}, {pos},  {missNums}});
        }
    }
    
    // Search through the columns for pairs
    for(int i = 0; i < SQUARE_SIZE; i++){
        vector<int> col = puzzle.getCol(i);
        vector<int> missNums = missingNumbers(col);
        if(missNums.size() == 2){
            vector<int> pos;
            for(int j = 0; j < SQUARE_SIZE; j++){
                if(col[j] == 0){
                    pos.push_back(j);
                }
            }
            pairs.push_back({{i+SQUARE_SIZE}, {pos},  {missNums}});
        }
    }
    
    // Search through the blocks for pairs
    for(int i = 0; i < SQUARE_SIZE; i++){
        vector<int> block = puzzle.getBlockVector(i);
        vector<int> missNums = missingNumbers(block);
        if(missNums.size() == 2){
            vector<int> pos;
            for(int j = 0; j < SQUARE_SIZE; j++){
                if(block[j] == 0){
                    pos.push_back(j);
                }
            }
            pairs.push_back({{i+(SQUARE_SIZE*2)}, {pos},  {missNums}});
        }
    }
    
    return pairs;
}
