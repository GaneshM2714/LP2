#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Structure for priority queue
struct State {
    vector<int> board; // board[i] = column of queen in row i
    int row; // Current row being processed
    int conflicts; // Number of attacking pairs

    State(vector<int> b, int r, int c) : board(b), row(r), conflicts(c) {}

    // For min-heap (fewer conflicts have higher priority)
    bool operator>(const State& other) const {
        return conflicts > other.conflicts;
    }
};

// Count conflicts (attacking pairs) in the current board
int countConflicts(const vector<int>& board, int row, int n) {
    int conflicts = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = i + 1; j < row; ++j) {
            // Same column
            if (board[i] == board[j]) conflicts++;
            // Diagonal
            if (abs(i - j) == abs(board[i] - board[j])) conflicts++;
        }
    }
    return conflicts;
}

// Check if placing a queen at (row, col) is safe
bool isSafe(const vector<int>& board, int row, int col, int n) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col || abs(i - row) == abs(board[i] - col)) {
            return false;
        }
    }
    return true;
}

// Branch and Bound for N-Queens
bool solveNQueensBB(int n) {
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<int> initBoard(n, -1); // Empty board
    pq.push(State(initBoard, 0, 0));

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        int row = current.row;
        vector<int> board = current.board;

        // Base case: All queens placed with no conflicts
        if (row == n && current.conflicts == 0) {
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
            return true;
        }

        // Try placing queen in next row
        for (int col = 0; col < n; ++col) {
            if (isSafe(board, row, col, n)) {
                vector<int> newBoard = board;
                newBoard[row] = col;
                int newConflicts = countConflicts(newBoard, row + 1, n);

                // Prune if conflicts are too high (e.g., non-zero after placement)
                if (newConflicts == 0 || row < n - 1) {
                    pq.push(State(newBoard, row + 1, newConflicts));
                }
            }
        }
    }
    return false;
}

int main() {
    int n = 4; // Example: 4x4 board
    cout << "Solving " << n << "-Queens with Branch and Bound\n";
    if (!solveNQueensBB(n)) {
        cout << "No solution exists\n";
    }
    return 0;
}