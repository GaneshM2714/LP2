#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class nqueens{
    set<vector<int>>st;
    int n;
    vector<bool>diag1,diag2,cols;
    public:
     nqueens(){
        cout<<"Enter the number of queens:";
        cin>>n;
        diag1.resize(2*n-1,false);
        diag2.resize(2*n-1,false);
        cols.resize(n,false);
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
    
     void solve(int row,vector<int>&curr){
        if(row>=n){
            st.insert(curr);
            return;
        }
        for(int col=0;col<n;col++){
            
            if(!cols[col] && !diag1[row-col+n-1] && !diag2[row+col]){
                curr[row] = col;
                cols[col] = diag1[row-col+n-1] = diag2[row+col] = true;
                solve(row+1,curr);
                cols[col] = diag1[row - col + n - 1] = diag2[row + col] = false;
            }
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
