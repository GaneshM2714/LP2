#include <bits/stdc++.h>
using namespace std;

class Graph
{
    vector<vector<int>> adjL;
    int n;
    // set<vector<int>>temp;
    set<vector<int>>ways;

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
            adjL[u].push_back(v);
            adjL[v].push_back(u);
        }
    }

public:

    bool isvalid(int u ,int clr,vector<int>&colors){
        for(auto& v:adjL[u]){
            if(colors[v]==clr) return false;
        }

        return true;
    }



    void getways(int m)
    {       
            ways.clear();

            vector<int> colors(n, -1);
            color_graph(0, m, colors);


            cout<<"The Total number of ways via which the graph can be colored are: "<<ways.size()<<endl;
            cout<<"Possible color combinations: \n";
            for(auto& way:ways){
                for(auto& i:way){
                    cout<<i<<" ";
                }
                cout<<endl;
            }
    }

    void color_graph(int node, int m, vector<int> &colors)
    {
        if(node>=n){
            bool valid = true;
            for(auto& i:colors){
                if(i==-1){
                    valid=false;
                    break;
                }
            }
            if(valid) ways.insert(colors);
            return;
        }

        for (int i = 1; i <= m; i++)
        {   
            if(isvalid(node, i,colors)){
                colors[node] = i;
                color_graph(node+1, m , colors);
                colors[node] = -1;
            }
        }
    }
};

int main()
{
    bool havegraph = false;
    Graph g;
    while (true)
    {
        if (!havegraph)
        {
            g.Graph_info();
            havegraph = true;
        }

        cout << "Enter the number of colors: ";
        int m;
        cin >> m;

        g.getways(m);
    }
}