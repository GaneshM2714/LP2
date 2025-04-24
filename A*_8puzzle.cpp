#include <bits/stdc++.h>
using namespace std;

// Set to store visited states to avoid duplicates
set<vector<vector<int>>> visited;

// Heuristic function: counts number of misplaced tiles (excluding blank tile)
int get_h(const vector<vector<int>>& src, const vector<vector<int>>& dest) {
    int ans = 0;
    for (int i = 0; i < src.size(); i++) {
        for (int j = 0; j < src[0].size(); j++) {
            if (src[i][j] != dest[i][j] && src[i][j] != 0) {
                ans++;
            }
        }
    }
    return ans;
}

// Function to find the position of the blank tile (0)
pair<int, int> find_blank(const vector<vector<int>>& state) {
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state[0].size(); j++) {
            if (state[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should never happen for a valid puzzle
}

// Function to generate all possible next states from the current state
vector<pair<vector<vector<int>>, int>> get_new_states(const vector<vector<int>>& state, const vector<vector<int>>& dest) {
    vector<pair<vector<vector<int>>, int>> new_states;
    auto [x, y] = find_blank(state);
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

    for (const auto& [dx, dy] : directions) {
        int new_x = x + dx, new_y = y + dy;
        if (new_x >= 0 && new_x < state.size() && new_y >= 0 && new_y < state[0].size()) {
            vector<vector<int>> new_state = state;
            swap(new_state[x][y], new_state[new_x][new_y]);
            if (visited.find(new_state) == visited.end()) {
                int h = get_h(new_state, dest);
                new_states.push_back({new_state, h});
            }
        }
    }

    return new_states;
}

// A* algorithm to find the shortest path from src to dest
int getpath(vector<vector<int>>& src, vector<vector<int>>& dest) {
    // Priority queue stores {f, h, g, state}
    priority_queue<
        tuple<int, int, int, vector<vector<int>>>,
        vector<tuple<int, int, int, vector<vector<int>>>>,
        greater<>> pq;

    int h = get_h(src, dest);
    int g = 0;
    pq.push({h, h, g, src});
    visited.insert(src);

    while (!pq.empty()) {
        auto [f, h, g, state] = pq.top();
        pq.pop();

        // If current state is the goal state, return the number of moves
        if (state == dest) {
            return g;
        }

        // Generate all possible next states
        auto new_states = get_new_states(state, dest);
        for (const auto& [new_state, new_h] : new_states) {
            visited.insert(new_state);
            int new_g = g + 1;
            int new_f = new_g + new_h;
            pq.push({new_f, new_h, new_g, new_state});
        }
    }

    return -1; // No solution found
}

int main() {
    // Example input
    // vector<vector<int>> src = {
    //     {2, 8, 3},
    //     {1, 6, 4},
    //     {7, 0, 5}
    // };

    // vector<vector<int>> src = { {1, 2, 3}, {8, 6, 4}, {7, 0, 5} };  // 5 moves
    // vector<vector<int>> src = { {2, 8, 3}, {1, 6, 4}, {7, 0, 5} };  // 1
    // vector<vector<int>> src = { {1, 2, 3}, {7, 8, 4}, {6, 0, 5} }; // 5
    // vector<vector<int>> src = { {8, 6, 3}, {2, 0, 4}, {1, 7, 5} }; //10
    vector<vector<int>> src = { {1, 2, 3}, {8, 0, 4}, {7, 6, 5} };  // 0

    vector<vector<int>> dest = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    };

    int moves = getpath(src, dest);
    if (moves != -1) {
        cout << "Minimum number of moves required: " << moves << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}