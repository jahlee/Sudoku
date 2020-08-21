//  Sudoku
//  Created on 8/20/20.
//  V1: creates board and has backtracking solution
//  todo: create gui that lets you add, delete, reset, solve, exit
//  future maybe: have multiple different sudokus, save/edit progress(?), files, etc.

#include <iostream>
#include <iomanip>  // for setfill('-') and setw()

const int SIZE = 9;

using namespace std;

/* ans:
     3  1  6  5  7  8  4  9  2
     5  2  9  1  3  4  7  6  8
     4  8  7  6  2  9  5  3  1
     2  6  3  4  1  5  9  8  7
     9  7  4  8  6  3  1  2  5
     8  5  1  7  9  2  6  4  3
     1  3  8  9  4  7  2  5  6
     6  9  2  3  5  1  8  7  4
     7  4  5  2  8  6  3  1  9
 */
int sudoku[SIZE][SIZE] = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

void drawBoard(int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        cout << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
            if (j == 2 || j == 5) { cout << "| "; }
        }
        if (i == 2 || i == 5) {
            cout << "\n ------+-------+------";
        }
        cout << endl;
    }
    cout << endl;
}

// x and y are passed by reference, are both -1 if no empty spots
void findEmpty(int &x, int &y) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                x = i;
                y = j;
                return;
            }
        }
    }
    x = -1;
    y = -1;
}

// check that the row is valid
bool checkRow(int num, int x, int y) {
    for (int i = 0; i < 9; i++) {
        if (i != x && sudoku[i][y] == num) {
            return false;
        }
    }
    return true;
}

// check that the col is valid
bool checkCol(int num, int x, int y) {
    for (int j = 0; j < 9; j++) {
        if (j != y && sudoku[x][j] == num) {
            return false;
        }
    }
    return true;
}

// check that the box is valid
bool checkBox(int num, int x, int y) {
    int boxX = x / 3;
    int boxY = y / 3;
    for (int i = boxX * 3; i < boxX * 3 + 3; i++) {
        for (int j = boxY * 3; j < boxY * 3 + 3; j++) {
            if (i != x && j != y && sudoku[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

// check that the number is valid (checks row, col, box)
bool isValid(int num, int x, int y) {
    return checkRow(num, x, y) && checkCol(num, x ,y) && checkBox(num, x, y);
}


// backtracking solving algorithm
bool solveGame() {
    int x, y;
    findEmpty(x, y);
    
    if (x == -1 || y == -1) {   // base case, true if you are done
        return true;
    }
    
    for (int i = 1; i < 10; i++) {
        if (isValid(i, x, y)) {
            sudoku[x][y] = i;
            
            if (solveGame()) {  // if solving with this new board works (recursive call)
                return true;
            }
            sudoku[x][y] = 0;
        }
    }
    return false;   // current board does not work, backtrack
}

// prints original board and solved board
void run() {
    cout << "Original Board:\n" << endl;
    drawBoard(sudoku);
    
    solveGame();
    cout << setfill('-') << setw(22) << "" << endl;
    cout << "\nSolved Board:\n" << endl;
    drawBoard(sudoku);
}


int main(int argc, const char * argv[]) {
    run();
    return 0;
}
