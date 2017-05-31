# Sudoku-Solver
Still in development. Currently can solve easy problems all the way up to some hard problems. Currently no user interface.

Currently no user interface. User has to directly set puzzle value by passing function a vector of vectors of size 9x9. In the future I hope to include the ability of the program to be able to solve other perfect square sudoku puzzles such as 4x4 puzzle. 
The program searches each block of the 9 squares the puzzle for obvious spaces to fill such as a sqaure that only has 1 available space left which means that number is guaranteed to be a certain number or if a square with many open spaces has a space that can only be filled with one number. It loops through each square until a whole loop through every square results in no changes to the puzzle.
This allows the solver to solve for most easy and medium difficulty puzzles in my experience testing the program. For the harder puzzle it comes to a point where a row, column or square has 2 or more possible values where the puzzle can no longer be solved into a decision regarding one of those values is made. After all obvious spaces have been filled the program calls a function that looks for such pairs of open spaces in every row, column or square. Then a random pair is chosen and the value is guessed to be one of the possible values for the pair. The program then attempts to solve the program by following the same steps as before. If no solution is found because that guess was wrong the puzzle attempts the other value for the pair since the pairs must be one of those two values.
For some harder problems this is where my program is currently having problems since the function guesses too many times creating a stack that is too big for my current computer's memory. Need to find a way to optimize the guessing of pairs to limit the size of the stack.
