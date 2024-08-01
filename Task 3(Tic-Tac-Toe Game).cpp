#include <iostream>

using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char currentPlayer = 'X';

void displayBoard() {
    cout << "Tic-Tac-Toe Board:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isWinner() {
    for (int i = 0; i < 3; i++) {
        // Check rows and columns
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void makeMove() {
    int move;
    cout << "Player " << currentPlayer << ", enter the number of the cell where you want to place your mark: ";
    cin >> move;

    bool validMove = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == move + '0') {  // Convert move to corresponding character
                board[i][j] = currentPlayer;
                validMove = true;
                break;
            }
        }
        if (validMove) break;
    }

    if (!validMove) {
        cout << "Invalid move! Try again." << endl;
        makeMove();
    }
}

int main() {
    while (true) {
        displayBoard();
        makeMove();

        if (isWinner()) {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }

        if (isDraw()) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        switchPlayer();
    }

    return 0;
}

