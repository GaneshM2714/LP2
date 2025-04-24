#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include<set>
#include <limits>
#include<algorithm>

using namespace std;

void dijkstraAlt(const map<string, vector<pair<string, double>>>& graph, const string& src) {
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<>> pq;
    map<string, double> dist;
    map<string, string> prev;
    set<string> done;

    for (const auto& node : graph) {
        dist[node.first] = numeric_limits<double>::infinity();
        prev[node.first] = "";
    }
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        string u = pq.top().second;
        double d = pq.top().first;
        pq.pop();

        if (done.find(u) != done.end()) continue;
        done.insert(u);

        for (const auto& edge : graph.at(u)) {
            string v = edge.first;
            double w = edge.second;

            if (d + w < dist[v]) {
                dist[v] = d + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Dijkstra's Shortest Paths (Alt) from " << src << ":\n";
    for (const auto& node : dist) {
        if (node.second == numeric_limits<double>::infinity()) {
            cout << node.first << ": Unreachable\n";
        } else {
            vector<string> path;
            string curr = node.first;
            while (!curr.empty()) {
                path.push_back(curr);
                curr = prev[curr];
            }
            reverse(path.begin(), path.end());
            cout << node.first << ": Distance = " << node.second << ", Path = ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
}

int main() {
    map<string, vector<pair<string, double>>> graph = {
        {"A", {{"B", 2}, {"D", 5}}},
        {"B", {{"A", 2}, {"C", 1}, {"D", 3}}},
        {"C", {{"B", 1}, {"D", 4}}},
        {"D", {{"A", 5}, {"B", 3}, {"C", 4}}}
    };

    string src = "A";
    dijkstraAlt(graph, src);

    return 0;
}