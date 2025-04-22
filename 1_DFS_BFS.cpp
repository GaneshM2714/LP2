#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <string>

using namespace std;

// DFS Recursive
void dfsRecursiveHelper(const map<string, vector<string>>& graph,
                        const string& current,
                        set<string>& visited,
                        vector<string>& traversal) {
    visited.insert(current);
    traversal.push_back(current);

    for (const string& neighbor : graph.at(current)) {
        if (visited.find(neighbor) == visited.end()) {
            dfsRecursiveHelper(graph, neighbor, visited, traversal);
        }
    }
}

void dfsRecursive(const map<string, vector<string>>& graph, const string& source) {
    set<string> visited;
    vector<string> traversal;
    cout << "DFS Recursive from " << source << ": ";
    dfsRecursiveHelper(graph, source, visited, traversal);
    for (size_t i = 0; i < traversal.size(); ++i) {
        cout << traversal[i];
        if (i < traversal.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// DFS Iterative
void dfsIterative(const map<string, vector<string>>& graph, const string& source) {
    stack<string> s;
    set<string> visited;
    vector<string> traversal;

    s.push(source);
    visited.insert(source);

    cout << "DFS Iterative from " << source << ": ";
    while (!s.empty()) {
        string current = s.top();
        s.pop();
        traversal.push_back(current);

        // Push neighbors in reverse order to match recursive exploration
        const vector<string>& neighbors = graph.at(current);
        for (int i = neighbors.size() - 1; i >= 0; --i) {
            const string& neighbor = neighbors[i];
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                s.push(neighbor);
            }
        }
    }

    for (size_t i = 0; i < traversal.size(); ++i) {
        cout << traversal[i];
        if (i < traversal.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// BFS Iterative
void bfsIterative(const map<string, vector<string>>& graph, const string& source) {
    queue<string> q;
    set<string> visited;
    vector<string> traversal;

    q.push(source);
    visited.insert(source);

    cout << "BFS Iterative from " << source << ": ";
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        traversal.push_back(current);

        for (const string& neighbor : graph.at(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    for (size_t i = 0; i < traversal.size(); ++i) {
        cout << traversal[i];
        if (i < traversal.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// BFS Recursive Helper
void bfsRecursiveHelper(const map<string, vector<string>>& graph,
                        queue<string>& q,
                        set<string>& visited,
                        vector<string>& traversal) {
    if (q.empty()) return;

    string current = q.front();
    q.pop();
    traversal.push_back(current);

    for (const string& neighbor : graph.at(current)) {
        if (visited.find(neighbor) == visited.end()) {
            visited.insert(neighbor);
            q.push(neighbor);
        }
    }

    bfsRecursiveHelper(graph, q, visited, traversal);
}

void bfsRecursive(const map<string, vector<string>>& graph, const string& source) {
    queue<string> q;
    set<string> visited;
    vector<string> traversal;

    q.push(source);
    visited.insert(source);

    cout << "BFS Recursive from " << source << ": ";
    bfsRecursiveHelper(graph, q, visited, traversal);

    for (size_t i = 0; i < traversal.size(); ++i) {
        cout << traversal[i];
        if (i < traversal.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Define the unweighted graph as an adjacency list
    map<string, vector<string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"A", "C", "D"}},
        {"C", {"A", "B", "D", "E"}},
        {"D", {"B", "C", "E"}},
        {"E", {"C", "D"}}
    };

    string source = "A";

    // Run all traversal algorithms
    dfsRecursive(graph, source);
    dfsIterative(graph, source);
    bfsIterative(graph, source);
    bfsRecursive(graph, source);

    return 0;
}