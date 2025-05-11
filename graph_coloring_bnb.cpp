#include <iostream>
#include <vector>
#include <algorithm> // For std::max
#include <set>       // To store unique colorings

using namespace std;

// Class to represent the graph
class Graph {
private:
    vector<vector<int>> adjL; // Adjacency list
    int n; // Number of nodes
    set<vector<int>> valid_colorings_with_m; // Stores the colorings that use exactly m colors

public:
    // Constructor
    Graph(int num_nodes) : n(num_nodes), adjL(num_nodes) {}

    // Add an edge between nodes u and v
    void add_edge(int u, int v) {
        if (u >= 0 && u < n && v >= 0 && v < n) {
            // Add edge in both directions for an undirected graph
            adjL[u].push_back(v);
            adjL[v].push_back(u);
        } else {
            cout << "Invalid node indices for edge: (" << u << ", " << v << ")" << endl;
        }
    }

    // Check if assigning color 'clr' to node 'u' is valid
    // It checks only neighbors that are already colored (indices < u)
    bool is_valid(int u, int clr, const vector<int>& colors) const {
        // Iterate through neighbors of node u
        for (int v : adjL[u]) {
            // If the neighbor v is already colored (its index is less than u)
            // and it has the same color as clr, then this assignment is invalid.
            // We only need to check nodes with index < u because nodes with index >= u
            // are not yet colored in this recursive path.
            if (v < u && colors[v] == clr) {
                return false;
            }
        }
        // If no colored neighbor has the same color, the assignment is valid.
        return true;
    }

    // Recursive function to find all valid colorings using colors 1 to m
    // node_index: The index of the node currently being colored
    // colors: Vector storing the assigned colors for nodes 0 to node_index-1
    // m: The maximum number of colors allowed (colors 1 to m)
    void find_colorings_recursive(int node_index, vector<int>& colors, int m) {
        // --- Base Case ---
        // If all nodes have been colored (successfully reached beyond the last node)
        if (node_index == n) {
            // All nodes are colored. Now check if this coloring uses exactly m colors.
            int max_color_used = 0;
            for (int color : colors) {
                max_color_used = max(max_color_used, color);
            }

            // If the maximum color used is exactly m, this is a valid coloring
            // using exactly m colors. Store it.
            if (max_color_used == m) {
                valid_colorings_with_m.insert(colors);
            }
            return;
        }

        // --- Branching Step ---
        // Try assigning colors from 1 to m to the current node (node_index)
        for (int color = 1; color <= m; ++color) {
            // Check if assigning this color to the current node is valid
            if (is_valid(node_index, color, colors)) {
                // Assign the color
                colors[node_index] = color;

                // Recursively call for the next node
                find_colorings_recursive(node_index + 1, colors, m);

                // --- Backtracking Step ---
                // Unassign the color to explore other possibilities for the current node
                colors[node_index] = 0; // Use 0 to indicate uncolored
            }
        }
    }

    // Function to find and display all valid colorings using exactly m colors
    void find_and_display_colorings(int m) {
        // Clear previous results
        valid_colorings_with_m.clear();

        // Initialize colors vector (0 means uncolored)
        vector<int> colors(n, 0);

        // Start the recursive search from the first node (index 0)
        find_colorings_recursive(0, colors, m);

        // Output the results
        cout << "\nTotal number of ways to color the graph using exactly " << m << " colors: " << valid_colorings_with_m.size() << endl;
        cout << "Possible color combinations using exactly " << m << " colors (node 0 to node " << n - 1 << "):" << endl;

        if (valid_colorings_with_m.empty()) {
            cout << "No valid colorings found using exactly " << m << " colors." << endl;
        } else {
            for (const auto& coloring : valid_colorings_with_m) {
                for (int i = 0; i < n; ++i) {
                    cout << coloring[i] << (i == n - 1 ? "" : " ");
                }
                cout << endl;
            }
        }
    }
};

int main() {
    int num_nodes;
    cout << "Enter the number of nodes: ";
    cin >> num_nodes;

    if (num_nodes <= 0) {
        cout << "Number of nodes must be positive." << endl;
        return 1;
    }

    Graph g(num_nodes);

    cout << "Enter the edges in the form (u v) (-1 -1 to exit):" << endl;
    while (true) {
        int u, v;
        cin >> u >> v;

        if (u == -1 && v == -1) {
            break;
        }

        g.add_edge(u, v);
    }

    while (true) {
        int m;
        cout << "\nEnter the number of colors (m) to find colorings for (enter 0 or negative to exit): ";
        cin >> m;

        if (m <= 0) {
            break; // Exit loop if m is 0 or negative
        }

        // Find and display colorings using exactly m colors
        g.find_and_display_colorings(m);
    }

    return 0;
}
