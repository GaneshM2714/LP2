#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include<set>

using namespace std;

void primMST(const map<string, vector<pair<string, double>>>& graph) {
    priority_queue<pair<double, pair<string, string>>,
                   vector<pair<double, pair<string, string>>>,
                   greater<>> pq; // {weight, {u, v}}
    set<string> visited;
    vector<pair<string, string>> mst;
    double total = 0;

    // Start from first node
    string start = graph.begin()->first;
    visited.insert(start);

    // Add all edges from start
    for (const auto& edge : graph.at(start)) {
        pq.push({edge.second, {start, edge.first}});
    }

    while (!pq.empty() && visited.size() < graph.size()) {
        double weight = pq.top().first;
        string u = pq.top().second.first;
        string v = pq.top().second.second;
        pq.pop();

        if (visited.find(v) != visited.end()) continue;

        visited.insert(v);
        mst.push_back({u, v});
        total += weight;

        // Add edges from new node
        for (const auto& edge : graph.at(v)) {
            if (visited.find(edge.first) == visited.end()) {
                pq.push({edge.second, {v, edge.first}});
            }
        }
    }

    cout << "Minimum Spanning Tree (Prim's):\n";
    for (const auto& edge : mst) {
        cout << edge.first << " - " << edge.second << endl;
    }
    cout << "Total weight: " << total << endl;
}

int main() {
    map<string, vector<pair<string, double>>> graph = {
        {"A", {{"B", 1}, {"C", 3}}},
        {"B", {{"A", 1}, {"C", 3}, {"D", 6}}},
        {"C", {{"A", 3}, {"B", 3}, {"D", 4}}},
        {"D", {{"B", 6}, {"C", 4}}}
    };

    primMST(graph);

    return 0;
}