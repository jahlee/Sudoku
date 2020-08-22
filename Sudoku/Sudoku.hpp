//  Sudoku.hpp

#ifndef Sudoku_hpp
#define Sudoku_hpp

#include <iomanip>      // for setfill('-') and setw()
#include <vector>
#include <iostream>
using namespace std;
const int SIZE = 9;     // constant, we know size will always be 9x9

class Sudoku {
public:
    Sudoku(vector<vector<int>> &in);
    void drawBoard() const;
    void drawUserBoard() const;
    bool findEmpty(vector<vector<int>> &curr, int &row, int &col);
    bool checkRow(vector<vector<int>> &curr, int num, int row, int col) const;
    bool checkCol(vector<vector<int>> &curr, int num, int row, int col) const;
    bool checkBox(vector<vector<int>> &curr, int num, int row, int col) const;
    bool isValid(vector<vector<int>> &curr, int num, int row, int col) const;
    bool solveGame();
    void editBoard();
    void clearBoard();
    void play();

private:
    vector<vector<int>> user;
    vector<vector<int>> orig;
};

#endif /* Sudoku_hpp */
