#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

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

// Recursive backtracking function
bool colorGraph(map<string, vector<string>>& graph, 
                map<string, int>& colors, 
                const vector<string>& nodes, 
                int nodeIdx, 
                int m) {
    // Base case: All nodes colored
    if (nodeIdx == nodes.size()) return true;

    string node = nodes[nodeIdx];
    // Try each color
    for (int c = 0; c < m; ++c) {
        if (isSafe(graph, colors, node, c)) {
            colors[node] = c; // Assign color
            if (colorGraph(graph, colors, nodes, nodeIdx + 1, m)) {
                return true;
            }
            colors.erase(node); // Backtrack
        }
    }
    return false;
}

void printColoring(const map<string, int>& colors) {
    cout << "Graph Coloring Solution:\n";
    for (const auto& pair : colors) {
        cout << "Node " << pair.first << ": Color " << pair.second << endl;
    }
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
    map<string, int> colors;
    vector<string> nodes = {"A", "B", "C", "D"}; // Ordered nodes

    cout << "Solving Graph Coloring with Backtracking (m=" << m << " colors)\n";
    if (colorGraph(graph, colors, nodes, 0, m)) {
        printColoring(colors);
    } else {
        cout << "No solution exists with " << m << " colors\n";
    }

    return 0;
}