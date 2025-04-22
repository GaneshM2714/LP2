#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <limits>
#include<algorithm>

using namespace std;

// Structure to represent a node in the priority queue
struct Node {
    string id; // Node identifier (e.g., "A")
    double g;  // Cost from start to this node
    double h;  // Heuristic estimate to goal
    double f;  // Total cost (f = g + h)
    string parent; // Parent node for path reconstruction

    Node(string id, double g, double h, string parent = "")
        : id(id), g(g), h(h), f(g + h), parent(parent) {}

    // For priority queue (min-heap)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// A* algorithm for a weighted graph with predefined heuristic distances
void astar(const map<string, vector<pair<string, double>>>& graph,
           const string& start,
           const string& goal,
           const map<string, double>& heuristics) {
    // Priority queue to store nodes to explore, sorted by f(n)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    // Track visited nodes to avoid cycles
    set<string> visited;
    // Store the best known cost to each node
    map<string, double> g_costs;
    // Store parent for path reconstruction
    map<string, string> parents;

    // Initialize
    g_costs[start] = 0;
    pq.push(Node(start, 0, heuristics.at(start)));
    visited.insert(start);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // If goal is reached, reconstruct and print the path
        if (current.id == goal) {
            cout << "Goal reached! Path: ";
            vector<string> path;
            string node = goal;
            double total_cost = current.g;
            while (!node.empty()) {
                path.push_back(node);
                node = parents[node];
            }
            reverse(path.begin(), path.end());
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << "\nTotal cost: " << total_cost << endl;
            return;
        }

        // Explore neighbors
        for (const auto& neighbor : graph.at(current.id)) {
            string next_node = neighbor.first;
            double edge_cost = neighbor.second;
            double new_g = current.g + edge_cost;

            // If we found a better path to next_node
            if (g_costs.find(next_node) == g_costs.end() || new_g < g_costs[next_node]) {
                g_costs[next_node] = new_g;
                double h = heuristics.at(next_node);
                parents[next_node] = current.id;
                pq.push(Node(next_node, new_g, h, current.id));
            }
        }
    }

    cout << "No path found from " << start << " to " << goal << endl;
}

int main() {
    // Define the weighted graph as an adjacency list
    // Format: map<node, vector<pair<neighbor, edge_weight>>>
    map<string, vector<pair<string, double>>> graph = {
        {"A", {{"B", 4}, {"C", 2}}},
        {"B", {{"A", 4}, {"C", 1}, {"D", 5}}},
        {"C", {{"A", 2}, {"B", 1}, {"D", 8}, {"E", 10}}},
        {"D", {{"B", 5}, {"C", 8}, {"E", 2}}},
        {"E", {{"C", 10}, {"D", 2}}}
    };

    // Define heuristic distances to the goal (e.g., node E)
    // These are admissible (never overestimate true distance)
    map<string, double> heuristics = {
        {"A", 7.0},
        {"B", 3.0},
        {"C", 5.0},
        {"D", 2.0},
        {"E", 0.0}
    };

    string start = "A";
    string goal = "E";

    cout << "Running A* from " << start << " to " << goal << endl;
    astar(graph, start, goal, heuristics);

    return 0;
}