#include <bits/stdc++.h>
using namespace std;


class Graph
{
    
    vector<vector<int>> adjL;
    
    int n;
    // Set to store all unique valid colorings found
    set<vector<int>> ways;

public:
    
    void Graph_info()
    {
        cout << "Enter the number of nodes: ";
        cin >> n;

        
        adjL.resize(n);

        
        addedges();
    }

private:
    
    void addedges()
    {
        cout << "Enter the edges in the form (u v) (-1 -1 to exit): ";
        while (true)
        {
            int u, v;
            cin >> u >> v;

            
            if (u == -1 && v == -1)
            {
                return;
            }
            
            if (u >= 0 && u < n && v >= 0 && v < n) {
                adjL[u].push_back(v);
                adjL[v].push_back(u);
            } else {
                
                cout << "Invalid node indices. Please enter values between 0 and " << n - 1 << "." << endl;
            }
        }
    }

public:
    
    bool isvalid(int u, int clr, const vector<int>& colors) const {
        
        for (int v : adjL[u]) {
            if (colors[v] != -1 && colors[v] == clr) {
                return false;
            }
        }
        return true;
    }


    void getways(int m)
    {
        ways.clear();
        vector<int> colors(n, -1);

        color_graph(0, m, colors);

        
        cout << "The Total number of ways via which the graph can be colored using " << m << " colors are: " << ways.size() << endl;
        cout << "Possible color combinations (node 0 to node " << n - 1 << "): \n";
        
        for (const auto& way : ways) {
            for (int i = 0; i < n; ++i) {
                cout << way[i] << (i == n - 1 ? "" : " ");
            }
            cout << endl;
        }
    }

private:
    // This version includes a forward-checking-like pruning step
    void color_graph(int node, int m, vector<int>& colors)
    {
        
        if (node == n) {
            
            ways.insert(colors);
            return; 
        }

        for (int color = 1; color <= m; ++color)
        {
            if (isvalid(node, color, colors))
            {
                colors[node] = color;

                // --- Pruning Step (Forward Checking) ---
                // After assigning a color to 'node', check if this assignment makes it impossible
                // to color any of its *uncolored* neighbors with the remaining available colors.
                bool possible_to_continue = true;
                // Iterate through all neighbors of the current node
                for (int neighbor : adjL[node]) {
                    // If the neighbor is currently uncolored
                    if (colors[neighbor] == -1) {
                        // Check if this uncolored neighbor still has at least one valid color option left (from 1 to m)
                        bool neighbor_has_option = false;
                        // Iterate through all possible colors for the neighbor
                        for (int neighbor_color = 1; neighbor_color <= m; ++neighbor_color) {
                            // Check if 'neighbor_color' is valid for the 'neighbor' given the *current* state of 'colors'
                            // (which includes the color just assigned to 'node')
                            if (isvalid(neighbor, neighbor_color, colors)) {
                                neighbor_has_option = true; // Found at least one valid color for this neighbor
                                break; // No need to check other colors for this specific neighbor
                            }
                        }
                        // If after coloring 'node', the 'neighbor' has no valid color options left
                        if (!neighbor_has_option) {
                            possible_to_continue = false; // This branch cannot lead to a complete valid coloring -> Prune it
                            break; // No need to check other neighbors of 'node', this path is dead
                        }
                    }
                }
                // --- End Pruning Step ---

                // If the pruning step determined that it's still possible to complete the coloring from this state
                if (possible_to_continue) {
                    color_graph(node + 1, m, colors);
                }

                colors[node] = -1;
            }
        }
    }
};

int main()
{
    
    Graph g;

    g.Graph_info();

    while (true)
    {
        cout << "\nEnter the number of colors (enter 0 or negative to exit): ";
        int m;
        cin >> m;

        if (m <= 0) {
            break; 
        }

        g.getways(m);
    }

    return 0;
}
