#include <iostream>
#include <vector>

using namespace std;

// Check if placing a queen at (row, col) is safe
bool isSafe(const vector<int>& board, int row, int col, int n) {
    for (int i = 0; i < row; ++i) {
        int prevCol = board[i];
        // Check same column
        if (prevCol == col) return false;
        // Check diagonals
        if (abs(i - row) == abs(prevCol - col)) return false;
    }
    return true;
}

// Recursive backtracking function
bool solveNQueens(vector<int>& board, int row, int n) {
    // Base case: All queens placed
    if (row == n) return true;

    // Try each column in current row
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            board[row] = col; // Place queen
            if (solveNQueens(board, row + 1, n)) return true;
            // Backtrack: Remove queen if no solution found
            board[row] = -1;
        }
    }
    return false;
}

void printBoard(const vector<int>& board, int n) {
    cout << "Solution for " << n << "-Queens:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
    cout << "Queen positions (row, col): ";
    for (int i = 0; i < n; ++i) {
        cout << "(" << i << ", " << board[i] << ")";
        if (i < n - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    int n = 4; // Example: 4x4 board
    vector<int> board(n, -1); // board[i] = column of queen in row i

    cout << "Solving " << n << "-Queens with Backtracking\n";
    if (solveNQueens(board, 0, n)) {
        printBoard(board, n);
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}