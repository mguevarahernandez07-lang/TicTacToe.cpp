//  Tic-Tac-Toe Game
//  Author: Melissa Guevara Hernandez
//  Class: CISC 192
//  Assignment: TicTacToe 

#include <iostream>
using namespace std;

// This class handles the entire Tic-Tac-Toe game.
class TicTacToe {
private:
    char board[3][3];   // 3x3 board: each spot is 'X', 'O', or ' '
    char currentPlayer; // whose turn it is right now: 'X' or 'O'
    int moveCount;      // how many moves have been played so far

public:
    // Constructor: set up an empty board and let 'X' start
    TicTacToe() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
        currentPlayer = 'X';   // Player 1 starts with X
        moveCount = 0;
    }

    // Show the board in a nice format so players can see the game state
    void displayBoard() {
        cout << "\n   1   2   3\n";
        for (int i = 0; i < 3; ++i) {
            cout << i + 1 << "  ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) {
                cout << "  ---+---+---\n";
            }
        }
        cout << "\n";
    }

    // Check if the chosen row/column is on the board and currently empty
    bool isValidMove(int row, int col) {
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            return false; // out of range
        }
        return board[row][col] == ' ';
    }

    // Put the current player's symbol on the chosen spot
    void makeMove(int row, int col) {
        board[row][col] = currentPlayer;
        moveCount++;
    }

    // See if the current player just made a winning move
    bool checkWinner() {
        char p = currentPlayer;

        // Check all rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == p && board[i][1] == p && board[i][2] == p) {
                return true;
            }
        }

        // Check all columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] == p && board[1][j] == p && board[2][j] == p) {
                return true;
            }
        }

        // Check the two diagonals
        if (board[0][0] == p && board[1][1] == p && board[2][2] == p) {
            return true;
        }
        if (board[0][2] == p && board[1][1] == p && board[2][0] == p) {
            return true;
        }

        return false; // no win yet
    }

    // If all 9 moves are used and nobody won, it's a draw
    bool isDraw() {
        return moveCount == 9;
    }

    // Change turns: X -> O or O -> X
    void switchPlayer() {
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
        } else {
            currentPlayer = 'X';
        }
    }

    // Main game loop: keep asking for moves until someone wins or it's a draw
    void playGame() {
        cout << "=== Tic-Tac-Toe ===\n";
        cout << "Player 1: X\nPlayer 2: O\n";

        bool gameOver = false;

        while (!gameOver) {
            displayBoard();
            cout << "Player " << currentPlayer
                 << ", enter your move (row and column 1-3): ";

            int row, col;
            cin >> row >> col;

            // Handle non-number or weird input
            if (!cin) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter two numbers between 1 and 3.\n";
                continue;
            }

            // Change from 1–3 to 0–2 so it matches our array indexes
            row--;
            col--;

            if (!isValidMove(row, col)) {
                cout << "That spot is not available. Try again.\n";
                continue;
            }

            makeMove(row, col);

            // Check if this move ended the game with a win
            if (checkWinner()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins! 🎉\n";
                gameOver = true;
            }
            // If no winner but board is full, it's a tie
            else if (isDraw()) {
                displayBoard();
                cout << "It's a draw! 🤝\n";
                gameOver = true;
            } else {
                // Game goes on, so we swap to the other player
                switchPlayer();
            }
        }
    }
};

int main() {
    TicTacToe game;  // create a game object
    game.playGame(); // start playing
    return 0;
}
