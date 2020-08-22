//  Sudoku V2
//  Created on 8/20/20
//  Last updated: 8/22/20

#include <iostream>
#include <iomanip>  // for setfill('-') and setw()

const int SIZE = 9; // constant, we know size will always be 9x9
using namespace std;

// NOTE: cin.clear() and cin.ignore(1000, '\n') are used to handle bad inputs

// Global sudoku game variables
int sudoku1[SIZE][SIZE] = {
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

int sudoku2[SIZE][SIZE] = {
    { 0, 0, 4,   0, 0, 0,   0, 6, 7 },
    { 3, 0, 0,   4, 7, 0,   0, 0, 5 },
    { 1, 5, 0,   8, 2, 0,   0, 0, 3 },
        
    { 0, 0, 6,   0, 0, 0,   0, 3, 1 },
    { 8, 0, 2,   1, 0, 5,   6, 0, 4 },
    { 4, 1, 0,   0, 0, 0,   9, 0, 0 },
        
    { 7, 0, 0,   0, 8, 0,   0, 4, 6 },
    { 6, 0, 0,   0, 1, 2,   0, 0, 0 },
    { 9, 3, 0,   0, 0, 0,   7, 1, 0 }
    };

int sudoku3[SIZE][SIZE] = {
    {5, 0, 0, 0, 0, 9, 7, 6, 0},
    {0, 0, 4, 0, 8, 0, 0, 1, 0},
    {0, 0, 2, 6, 0, 0, 0, 9, 0},
    {0, 0, 0, 0, 0, 8, 0, 0, 0},
    {6, 0, 9, 2, 0, 5, 4, 0, 3},
    {0, 0, 0, 4, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 2, 6, 0, 0},
    {0, 9, 0, 0, 4, 0, 5, 0, 0},
    {0, 5, 6, 8, 0, 0, 0, 0, 9}
    };

/*
 ans1:
     3  1  6  5  7  8  4  9  2
     5  2  9  1  3  4  7  6  8
     4  8  7  6  2  9  5  3  1
     2  6  3  4  1  5  9  8  7
     9  7  4  8  6  3  1  2  5
     8  5  1  7  9  2  6  4  3
     1  3  8  9  4  7  2  5  6
     6  9  2  3  5  1  8  7  4
     7  4  5  2  8  6  3  1  9
 
 ans2:
     2 8 4 | 5 9 3 | 1 6 7
     3 6 9 | 4 7 1 | 8 2 5
     1 5 7 | 8 2 6 | 4 9 3
     ------+-------+------
     5 7 6 | 9 4 8 | 2 3 1
     8 9 2 | 1 3 5 | 6 7 4
     4 1 3 | 2 6 7 | 9 5 8
     ------+-------+------
     7 2 1 | 3 8 9 | 5 4 6
     6 4 5 | 7 1 2 | 3 8 9
     9 3 8 | 6 5 4 | 7 1 2
 
 ans3:
     5 3 8 1 2 9 7 6 4
     9 6 4 5 8 7 3 1 2
     1 7 2 6 3 4 8 9 5
     3 4 5 7 9 8 1 2 6
     6 8 9 2 1 5 4 7 3
     7 2 1 4 6 3 9 5 8
     8 1 3 9 5 2 6 4 7
     2 9 7 3 4 6 5 8 1
     4 5 6 8 7 1 2 3 9
 */

// draw regular board
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

// draw board when editing, shows which [numbers] you are allowed to edit
void drawBoard(int curr[][SIZE], int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        cout << " ";
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                cout << " " << curr[i][j] << "  ";
            }
            else {
                cout << "[" << curr[i][j] << "] ";
            }
            if (j == 2 || j == 5) { cout << "| "; }
        }
        if (i == 2 || i == 5) {
            cout << "\n ------------+-------------+------------";
        }
        cout << endl;
    }
    cout << endl;
}

// row and col are passed by reference, are both -1 if no empty spots
// return true if finds an empty space, false if not
bool findEmpty(int board[][SIZE], int &row, int &col) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                return true;
            }
        }
    }
    row = -1;
    col = -1;
    return false;
}

// check that the row is valid
bool checkRow(int board[][SIZE], int num, int row, int col) {
    for (int i = 0; i < SIZE; i++) {
        if (i != col && board[row][i] == num) {
            return false;
        }
    }
    return true;
}

// check that the col is valid
bool checkCol(int board[][SIZE], int num, int row, int col) {
    for (int j = 0; j < SIZE; j++) {
        if (j != row && board[j][col] == num) {
            return false;
        }
    }
    return true;
}

// check that the box is valid
bool checkBox(int board[][SIZE], int num, int row, int col) {
    int boxRow = row / 3;
    int boxCol = col / 3;
    for (int j = boxRow * 3; j < boxRow * 3 + 3; j++) {
        for (int i = boxCol * 3; i < boxCol * 3 + 3; i++) {
            if (!(j == row && i == col) && board[j][i] == num) {
                return false;
            }
        }
    }
    return true;
}

// check that the number is valid (checks row, col, box)
bool isValid(int board[][SIZE], int num, int row, int col) {
    return checkRow(board, num, row, col)
        && checkCol(board, num, row ,col)
        && checkBox(board, num, row, col);
}


// backtracking algorithm to solve board
bool solveGame(int board[][SIZE]) {
    int row, col;
    
    if (!findEmpty(board, row, col)) {   // base case, true if you are done
        return true;
    }
    
    for (int i = 1; i < 10; i++) {
        if (isValid(board, i, row, col)) {
            board[row][col] = i;
            
            if (solveGame(board)) {  // if solving with this new board works (recursive call)
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;   // current board does not work, backtrack
}

// edit the current board
void editBoard(int curr[][SIZE], int board[][SIZE]) {
    int row,col,val;
    do {
        cout << "\nCurrent board:\n" << endl;
        drawBoard(curr, board);

        
        cout << "Input 2 numbers [row, col] you want to change (1-9)";
        cout << "\n{-1 to quit}" << endl;
        
        cin >> row;
        cin.clear();
        cin.ignore(1000, '\n');
        if (row < 0) { return; }
        
        cin >> col;
        cin.clear();
        cin.ignore(1000, '\n');
        if (col < 0) { return; }
        
        
        if (row > 9 || col > 9) {
            cout << endl << setfill('=') << setw(30) << "" << endl;
            cout << "Row/Col value(s) too high!" << endl;
            cout << setfill('=') << setw(30) << "" << endl;
            continue;
        }
        else if (board[row-1][col-1] != 0) {
            cout << endl << setfill('=') << setw(30) << "" << endl;
            cout << "You can't change this value!" << endl;
            cout << setfill('=') << setw(30) << "" << endl;
            continue;
        }
        
        
        cout << "\nEnter the new value (1-9) for row " << row  << " col " << col << endl;
        cin >> val;
        cin.clear();
        cin.ignore(1000, '\n');
        
        
        if (val < 1 || val > 9) {
            cout << endl << setfill('=') << setw(30) << "" << endl;
            cout << "Value not between 1-9!" << endl;
            cout << setfill('=') << setw(30) << "" << endl;
            continue;
        }
        
        
        if (!isValid(curr, val, row-1, col-1)) {
            cout << endl << setfill('=') << setw(30) << "" << endl;
            cout << "Invalid move!" << endl;
            cout << setfill('=') << setw(30) << "" << endl;
        }
        else {
            curr[row-1][col-1] = val;
        }
        
    } while (col > 0 && row > 0);
}

// sets the values of the current board to those of the original board
void clearBoard(int curr[][SIZE], int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            curr[i][j] = board[i][j];
        }
    }
}

// use this method to play board game
void play(int board[][SIZE]) {
    int row,col;
    int curr[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            curr[i][j] = board[i][j];
        }
    }
    
    while (findEmpty(board, row, col)) {
        char in;
        cout << "\nCurrent board:\n" << endl;
        drawBoard(curr);
        cout << "Enter an option:" << endl;
        cout << "e - edit\nc - clear\ns - solve\nq - quit" << endl;
        cin >> in;
        cin.clear();
        cin.ignore(1000, '\n');
        
        cout << endl;
        switch (in) {
            case 'e':
                editBoard(curr, board);
                break;
            case 'c':
                clearBoard(curr, board);
                break;
            case 's':
                clearBoard(curr, board);
                solveGame(curr);
                cout << "Solved board:\n";
                drawBoard(curr);
                cout << "\nExiting board...\n" << endl;
                break;
            case 'q':
                break;
            default:
                cout << "Bad input, let's try that again." << endl;
        }
        if (in == 'q' || in == 's') {
            break;
        }
    }
}

void run() {
    char choice;
    do {
        cout << "Which board do you want to play? \n(1,2,3) {q to quit}" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
        choice = tolower(choice);
        if (choice == '1') {
            play(sudoku1);
        }
        else if (choice == '2') {
            play(sudoku2);
        }
        else if (choice == '3') {
            play(sudoku3);
        }
        else if (choice != 'q') {
            cout << "Invalid input!\n" << endl;
        }
        
    } while (choice != 'q');
}


int main(int argc, const char * argv[]) {
    run();
    return 0;
}
