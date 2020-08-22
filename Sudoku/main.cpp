//  Sudoku V3
//  Created on 8/20/20
//  Last updated: 8/22/20

#include "Game.hpp"

// play the game (acts like a main menu, select which board to play)
void run() {
    char choice;
    Game g;
    do {
        cout << "Which board do you want to play? \n(1,2,3) {q to quit}" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
        choice = tolower(choice);
        if (choice == '1') {
            g.playGame1();
        }
        else if (choice == '2') {
            g.playGame2();
        }
        else if (choice == '3') {
            g.playGame3();
        }
        else if (choice != 'q') {
            cout << endl << setfill('=') << setw(30) << "" << endl;
            cout << "Invalid input!" << endl;
            cout << setfill('=') << setw(30) << "" << endl << endl;
        }
        
    } while (choice != 'q');
    
    cout << endl;
}


int main(int argc, const char * argv[]) {
    run();
    return 0;
}
