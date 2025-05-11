#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class nqueens{
    set<vector<int>>st;
    int n;
    public:
     nqueens(){
        cout<<"Enter the number of queens:";
        cin>>n;
        vector<int>curr(n,-1);
        solve(0,curr);
        printBoards();
     }

     bool isSafe(int row, int col, vector<int>& curr){
        for(int i = 0; i < row; i++){
            if(curr[i] == col || abs(curr[i] - col) == abs(i - row))
                return false;
        }
        return true;
    }
    
     void solve(int x,vector<int>curr){
        if(x>=n){
            st.insert(curr);
            return;
        }

            for(int col=0;col<n;col++){
                curr[x] = col;
                if(isSafe(x,col,curr)){
                    solve(x+1,curr);
                }
                curr[x] = -1;
            }
     }

     void printBoards(){
        for (auto& curr:st){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(curr[i] == j) cout<<"Q ";
                    else cout<<". ";
                }
                cout<<"\n";
            }
            cout<<"\n";
        }
        cout<<"Total Possible Ways: "<<st.size()<<endl;
     }
};

int main(){
   
    nqueens nq;

}   
