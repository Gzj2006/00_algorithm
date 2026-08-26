//Bellman_ford 单源有限最短路径

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> edges;
    vector<int> minDist(n+1,INT_MAX);
    for(int i=0;i<m;i++){
        int s,t,v;
        cin>>s>>t>>v;
        edges.push_back({s,t,v});
    }
    int start,end,k;
    cin>>start>>end>>k;

    minDist[start]=0;
    for(int i=0;i<=k;i++){
        vector<int> min_copy=minDist;
        for(auto edge : edges){
            int s = edge[0];
            int t = edge[1];
            int v = edge[2];
            if(min_copy[s]!=INT_MAX && minDist[t]>min_copy[s]+v){
                minDist[t] = min_copy[s]+v;
            }
        }
    }

    if(minDist[end]==INT_MAX) cout<<"unconnected"<<endl;
    else cout<<minDist[end]<<endl;
    return 0;
}
