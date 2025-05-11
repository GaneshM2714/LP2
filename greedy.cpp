#include <bits/stdc++.h>
using namespace std;

void selection_sort()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> a(n);

    for (auto &i : a)
        cin >> i;

    cout << "Array Before Sorting: ";
    for (auto &i : a)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        int idx = i;
        
        for (int j = i + 1; j < n; j++)
        {
            if (a[idx] > a[j])
                idx = j;
        }
        if (idx != i)
            swap(a[idx], a[i]);
    }
    cout << "Array After Sorting: ";
    for (auto &i : a)
        cout << i << " ";
    cout << endl;
}

// Conditions for a valid **Minimum Spanning Tree (MST)** in graph:

// 1. **Undirected Graph**: The graph must be undirected (edges have no direction).
// 2. **Connected**: All nodes must be reachable from any node (single component).
// 3. **Weighted**: Edges have weights (typically non-negative).
// 4. **Spanning**: The MST includes all nodes (n nodes).
// 5. **Tree**: The MST has exactly n-1 edges and contains no cycles.
// 6. **Minimum Weight**: The total weight of the MST edges is the smallest possible among all spanning trees.

class Graph
{
    int n;
    vector<vector<pair<int, int>>> adjL;
    vector<int>par,rank;

public:
    void Graph_info()
    {
        cout << "Enter the number of nodes: ";
        cin >> n;
        adjL.resize(n);
        rank.resize(n,0);
        par.resize(n,0);
        for(int i=0;i<n;i++) par[i]=i;
        getedges();
    }

    void getedges()
    {
        cout << "Enter the egdes in format (u v wt) (-1 -1 -1 to exit): \n";
        while (true)
        {
            int u, v, wt;
            cin >> u >> v >> wt;

            if (u == -1 && v == -1 && wt == -1)
            {
                return;
            }

            adjL[u].push_back({v, wt});
            adjL[v].push_back({u, wt});
        }
    }

    void Djikstra()
    {
        cout << "Enter the source node: ";
        int src;
        cin >> src;
        cout << "Enter the destination node: ";
        int dest;
        cin >> dest;

        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
        vector<bool> visited(n, false);
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty())
        {
            int d = pq.top()[0];
            int x = pq.top()[1];
            pq.pop();

            if (visited[x])
                continue;
            visited[x] = true;

            if (x == dest)
            {
                cout << "Shortest Path Distance: " << d << endl;
                cout << "Shortest Path: ";
                vector<int> path;
                for (int v = dest; v != -1; v = parent[v])
                {
                    path.push_back(v);
                }
                reverse(path.begin(), path.end());
                for (int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if (i < path.size() - 1)
                        cout << " -> ";
                }
                cout << endl;
                return;
            }

            for (auto &[v, wt] : adjL[x])
            {
                if (!visited[v] && d + wt < dist[v])
                {
                    dist[v] = d + wt;
                    parent[v] = x;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "No path exists" << endl;
    }

    void prims() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<bool> visited(n, false);
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        int totalWeight = 0;
    
        // Start from node 0
        dist[1] = 0;
        pq.push({0, 1});
    
        while (!pq.empty()) {
            int wt = pq.top().first;
            int u = pq.top().second;
            pq.pop();
    
            if (visited[u]) continue;
            visited[u] = true;
    
            // If not the starting node, add edge to MST
            if (parent[u] != -1) {
                cout << min(parent[u], u) << " " << max(parent[u], u) << " " << wt << endl;
                totalWeight += wt;
            }
    
            // Explore neighbors
            for (auto& [v, w] : adjL[u]) {
                if (!visited[v] && w < dist[v]) {
                    dist[v] = w;
                    parent[v] = u;
                    pq.push({w, v});
                }
            }
        }
    
        cout << "Total Weight: " << totalWeight << endl;
    }
    

    // Prerequesites for Kruskal: Union and Find
    int find(int x){
        if(par[x]==x) return x;
        return par[x] = find(par[x]); //Path Compression
    }
    void Union(int u, int v){
        int x = find(u) , y = find(v);
        if(x==y){
            return;
        }

        else if(rank[x]>rank[y]){
            par[y] = x;
        }
        else if(rank[x]<rank[y]){
            par[x] = y;
        }
        else{
            par[y] = x;
            rank[x]++;
        }

    }

    void kruskal()
    {
        vector<vector<int>> wts;
        for (int i = 0; i < n; i++)
        {
            int u = i;
            for (auto &[v, wt] : adjL[u])
                wts.push_back({wt, u, v});
        }

        sort(wts.begin(), wts.end());

        int cost = 0;
        vector<vector<int>>res;

        for(auto& edge:wts){
            int u = edge[1] , v = edge[2] , wt = edge[0];
            if(find(u)!=find(v)){
                Union(u,v);
                res.push_back(edge);
            }
        }
        cout<<"Edge\tWeight"<<endl;
        for(auto& edge:res){
            cout<<edge[1]<<"->"<<edge[2]<<"\t"<<edge[0]<<endl;
            cost+=edge[0];
        }
        cout << "Cost of the minimum spanning tree is : " << cost << endl;
    }
};

static bool comp(vector<int>& a, vector<int>& b){
    if(a[0]!=b[0]) return a[0]<b[0];
    if(a[1]!=b[1]) return a[1]>b[1];
    return a[2]<b[2];
}

void Job_Schedule(){
    vector<vector<int>>jobs;
    cout<<"Enter Jobs in form (JobID Deadline Profit) (-1 -1 -1 to exit): ";

    while(true){
        int id,dl,pr;
        cin>>id>>dl>>pr;
        if(id==-1 && dl==-1 && pr==-1){
            break;
        }

        jobs.push_back({dl,pr,id});
    }

    
    sort(jobs.begin(),jobs.end(),comp);

    cout<<"SORTED JOBS: \n";
    cout<<"JobID"<<setw(10)<<"Deadline"<<setw(10)<<"Profit\n";
    for(auto& job:jobs){
        cout<<job[2]<<setw(10)<<job[0]<<setw(10)<<job[1]<<endl;
    }

    int curr = 1;
    vector<vector<int>>res;
    for(auto& job:jobs){
        if(job[0]>=curr){
            res.push_back(job);
            curr++;
        }
        
    }
    int profit = 0;
    cout<<"SCHEDULED JOBS: \n";
    cout<<"JobID"<<setw(10)<<"Deadline"<<setw(10)<<"Profit\n";
    for(auto& job:res){
        cout<<job[2]<<setw(10)<<job[0]<<setw(10)<<job[1]<<endl;
        profit+=job[1];
    }

    cout<<"TOTAL PROFIT: "<<profit<<endl;
}

int main()
{
    Graph g;

    bool havegraph = false;
    while (true)
    {
        cout << "Select an option:\n 1.Selection Sort\n 2.Djikstra's Shortest Path\n 3.Prims MST\n 4.Kruskals Algorithm\n 5.Job Scheduling\n 6.Exit";
        int ch;
        cin >> ch;

        switch (ch)
        {
        case 1:
            selection_sort();
            break;
        case 2:
            if (!havegraph)
            {
                g.Graph_info();
                havegraph = true;
            }
            g.Djikstra();
            break;
        case 3:
            if (!havegraph)
            {
                g.Graph_info();
                havegraph = true;
            }
            g.prims();
            break;
        case 4:
            if (!havegraph)
            {
                g.Graph_info();
                havegraph = true;
            }
            g.kruskal();
            break;

        case 5:
            Job_Schedule();
            break;
        case 6:
            exit(0);

        default:
            cout<<"Please enter a valid option\n";
            break;
        }
    }
    return 0;
}