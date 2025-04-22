#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

// Structure for priority queue
struct State {
    map<string, int> colors; // Current coloring
    int nodeIdx; // Index of next node to color
    int conflicts; // Number of conflicting edges

    State(map<string, int> c, int idx, int conf) 
        : colors(c), nodeIdx(idx), conflicts(conf) {}

    // For min-heap (fewer conflicts have higher priority)
    bool operator>(const State& other) const {
        return conflicts > other.conflicts;
    }
};

// Count conflicts (edges with same-colored endpoints)
int countConflicts(const map<string, vector<string>>& graph, 
                   const map<string, int>& colors) {
    int conflicts = 0;
    for (const auto& node : graph) {
        string u = node.first;
        if (colors.find(u) == colors.end()) continue;
        int colorU = colors.at(u);
        for (const string& v : node.second) {
            if (colors.find(v) != colors.end() && colors.at(v) == colorU) {
                conflicts++;
            }
        }
    }
    return conflicts / 2; // Each conflict counted twice (u-v and v-u)
}

// Check if assigning color c to node is safe
bool isSafe(const map<string, vector<string>>& graph, 
            const map<string, int>& colors, 
            const string& node, 
            int c) {
    for (const string& neighbor : graph.at(node)) {
        if (colors.find(neighbor) != colors.end() && colors.at(neighbor) == c) {
            return false;
        }
    }
    return true;
}

// Branch and Bound for Graph Coloring
bool colorGraphBB(map<string, vector<string>>& graph, 
                  int m, 
                  const vector<string>& nodes) {
    priority_queue<State, vector<State>, greater<State>> pq;
    map<string, int> initColors;
    pq.push(State(initColors, 0, 0));

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        int nodeIdx = current.nodeIdx;
        map<string, int> colors = current.colors;

        // Base case: All nodes colored with no conflicts
        if (nodeIdx == nodes.size() && current.conflicts == 0) {
            cout << "Graph Coloring Solution:\n";
            for (const auto& pair : colors) {
                cout << "Node " << pair.first << ": Color " << pair.second << endl;
            }
            return true;
        }

        // Try coloring the next node
        string node = nodes[nodeIdx];
        for (int c = 0; c < m; ++c) {
            if (isSafe(graph, colors, node, c)) {
                map<string, int> newColors = colors;
                newColors[node] = c;
                int newConflicts = countConflicts(graph, newColors);

                // Only pursue if conflicts are low or not final node
                if (newConflicts == 0 || nodeIdx < nodes.size() - 1) {
                    pq.push(State(newColors, nodeIdx + 1, newConflicts));
                }
            }
        }
    }
    return false;
}

int main() {
    // Define the graph
    map<string, vector<string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"A", "C", "D"}},
        {"C", {"A", "B", "D"}},
        {"D", {"B", "C"}}
    };

    int m = 3; // Number of colors (0, 1, 2)
    vector<string> nodes = {"A", "B", "C", "D"}; // Ordered nodes

    cout << "Solving Graph Coloring with Branch and Bound (m=" << m << " colors)\n";
    if (colorGraphBB(graph, m, nodes)) {
        // Solution printed in function
    } else {
        cout << "No solution exists with " << m << " colors\n";
    }

    return 0;
}