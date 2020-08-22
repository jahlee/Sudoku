//  Sudoku.cpp
//  NOTE: cin.clear() and cin.ignore(1000, '\n') are used to handle bad inputs

#include "Sudoku.hpp"

// constructor, takes in sudoku board
Sudoku::Sudoku(vector<vector<int>> &in) {
    orig = vector<vector<int>>(in);   // deep copy
}

// draw original board
void Sudoku::drawBoard() const {
    for (int i = 0; i < SIZE; i++) {
        cout << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << user.at(i).at(j) << " ";
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
void Sudoku::drawUserBoard() const {
    for (int i = 0; i < SIZE; i++) {
        cout << " ";
        for (int j = 0; j < SIZE; j++) {
            if (orig.at(i).at(j) != 0) {
                cout << " " << user.at(i).at(j) << "  ";
            }
            else {
                cout << "[" << user.at(i).at(j) << "] ";
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
bool Sudoku::findEmpty(vector<vector<int>> &curr, int &row, int &col) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
            if (curr.at(i).at(j) == 0) {
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
bool Sudoku::checkRow(vector<vector<int>> &curr, int num, int row, int col) const {
    for (int i = 0; i < SIZE; i++) {
        if (i != col && curr.at(row).at(i) == num) {
            return false;
        }
    }
    return true;
}

// check that the col is valid
bool Sudoku::checkCol(vector<vector<int>> &curr, int num, int row, int col) const {
    for (int j = 0; j < SIZE; j++) {
        if (j != row && curr.at(j).at(col) == num) {
            return false;
        }
    }
    return true;
}

// check that the box is valid
bool Sudoku::checkBox(vector<vector<int>> &curr, int num, int row, int col) const {
    int boxRow = row / 3;
    int boxCol = col / 3;
    for (int j = boxRow * 3; j < boxRow * 3 + 3; j++) {
        for (int i = boxCol * 3; i < boxCol * 3 + 3; i++) {
            if (!(j == row && i == col) && curr.at(j).at(i) == num) {
                return false;
            }
        }
    }
    return true;
}

// check that the number is valid (checks row, col, box)
bool Sudoku::isValid(vector<vector<int>> &curr, int num, int row, int col) const {
    return checkRow(curr, num, row, col)
        && checkCol(curr, num, row, col)
        && checkBox(curr, num, row, col);
}


// backtracking algorithm to solve curr board
bool Sudoku::solveGame() {
    int row, col;
    
    if (!findEmpty(user, row, col)) {   // base case, true if you are done
        return true;
    }
    
    for (int i = 1; i < 10; i++) {
        if (isValid(user, i, row, col)) {
            user.at(row).at(col) = i;
            
            if (solveGame()) {  // if the curent value of i is the correct solution (recursive call)
                return true;
            }
            user.at(row).at(col) = 0;
        }
    }
    return false;   // current board does not work, backtrack
}

// edit the current board
void Sudoku::editBoard() {
    int row,col,val;
    do {
        cout << "\nCurrent board:\n" << endl;
        drawUserBoard();

        
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
        else if (orig[row-1][col-1] != 0) {
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
        
        
        if (!isValid(user, val, row-1, col-1)) {
            cout << endl << setfill('=') << setw(30) << "" << endl;
            cout << "Invalid move!" << endl;
            cout << setfill('=') << setw(30) << "" << endl;
        }
        else {
            user[row-1][col-1] = val;
        }
        
    } while (col > 0 && row > 0);
}

// sets the values of the current board to those of the original board
void Sudoku::clearBoard() {
    user = orig;    // shallow copy
}

// use this method to play board game
void Sudoku::play() {
    int row,col;
    
    clearBoard();   // shallow copy
    
    while (findEmpty(user, row, col)) {
        char in;
        cout << "\nCurrent board:\n" << endl;
        drawBoard();
        cout << "Enter an option:" << endl;
        cout << "e - edit\nc - clear\ns - solve\nq - quit" << endl;
        cin >> in;
        cin.clear();
        cin.ignore(1000, '\n');
        
        cout << endl;
        switch (in) {
            case 'e':
                editBoard();
                break;
            case 'c':
                clearBoard();
                break;
            case 's':
                clearBoard();
                solveGame();
                cout << "Solved board:\n\n";
                drawBoard();
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

