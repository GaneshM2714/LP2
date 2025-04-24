// A B C D E F

// A ->0 B ->1 C->2 D->3 E->4 F->5

// 0 --> [5,1]
// 1 --> [0,2,3,4]
// 2 -->
// 3 -->
// 4 -->

// key is idx which is also a node and arr[idx] is list of adjacent nodes stored

#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class Graph{
    int n;
    vector<vector<int>>adjL;
    public:
    Graph(){
        cout<<"Enter Total Nodes: ";
        cin>>n;
        adjL.resize(n);
    }

    void getgraph(){
        for(int i=0;i<n;i++){
            cout<<"NODE "<<i<<": \n";
            for(auto& ngbr: adjL[i]) cout<<ngbr<<" ";
            cout<<endl;
        }
    }
    int getn(){
        return n;
    }

    void addedge(int u,int v){
        if(u<0 || v<0){
            cout<<"Please enter a valid edge.\n";
            return;
        }

        adjL[u].push_back(v);
        adjL[v].push_back(u);

    }

    void it_bfs(int src){

        cout<<"Iterative BFS: \n";
        queue<int>q;
        q.push(src);

        vector<bool>visited(n,false);
        visited[src] = true;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            
            
            cout<<x<<" ";
            for (auto& ngbr:adjL[x]){
                if(!visited[ngbr]) {
                    q.push(ngbr);
                    visited[ngbr] = true;
                }
            }
        }
        cout<<endl;
        
    }

    void rec_dfs(int x,vector<bool>&visited){
        visited[x] = true;
        cout<<x<<" ";
        for(auto& ngbr: adjL[x]){
            if(!visited[ngbr]){
                rec_dfs(ngbr,visited);
            }
        }
    }

    void it_dfs(int src){

        cout<<"Iterative DFS: \n";
        vector<bool>visited(n,false);

        stack<int>st;

        st.push(src);
        visited[src] = true;
        while (!st.empty())
        {
            int x = st.top();
            st.pop();
            
            cout<<x<<" ";
            for(auto& ngbr:adjL[x]){
                if(!visited[ngbr]) {
                    st.push(ngbr);
                    visited[ngbr] = true;
                }
            }

        }

        cout<<endl;
        
    }

};

int main(){

    Graph g;
    
    cout<<"Enter the edges in form u v (-1 -1 to exit) :\n";
    

    while (true)
    {
        int u,v;
        cin>>u>>v;

        if(u==-1 && v==-1) break;
        g.addedge(u,v);
    }
    

    g.getgraph();
    cout<<" \n--------------------------------\n";

    g.it_bfs(0);
    g.it_dfs(0);

    cout<<"Recursive DFS: \n";
    int n = g.getn();
    vector<bool>visited(n,false);
    g.rec_dfs(0,visited);
    cout<<endl;

    return 0;

}