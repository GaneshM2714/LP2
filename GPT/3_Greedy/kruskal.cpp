#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Edge {
    string u, v;
    double w;
};

struct DSU {
    map<string, string> parent;
    map<string, int> rank;

    DSU(const vector<string>& nodes) {
        for (const string& node : nodes) {
            parent[node] = node;
            rank[node] = 0;
        }
    }

    string find(const string& x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(const string& x, const string& y) {
        string px = find(x), py = find(y);
        if (px == py) return;
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

void kruskal(const map<string, vector<pair<string, double>>>& graph) {
    vector<Edge> edges;
    vector<string> nodes;

    // Collect edges and nodes
    for (const auto& node : graph) {
        nodes.push_back(node.first);
        for (const auto& edge : node.second) {
            if (node.first < edge.first) { // Avoid duplicates
                edges.push_back({node.first, edge.first, edge.second});
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    // Run Kruskal's
    DSU dsu(nodes);
    vector<Edge> mst;
    double sum = 0;

    for (const Edge& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mst.push_back(e);
            sum += e.w;
        }
    }

    cout << "Kruskal's MST:\n";
    for (const Edge& e : mst) {
        cout << e.u << " - " << e.v << endl;
    }
    cout << "Total weight: " << sum << endl;
}

int main() {
    map<string, vector<pair<string, double>>> graph = {
        {"A", {{"B", 1}, {"C", 3}}},
        {"B", {{"A", 1}, {"C", 3}, {"D", 6}}},
        {"C", {{"A", 3}, {"B", 3}, {"D", 4}}},
        {"D", {{"B", 6}, {"C", 4}}}
    };

    kruskal(graph);

    return 0;
}