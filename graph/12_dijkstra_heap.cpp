#include<iostream>
#include<vector>
#include<climits>
#include<queue>
using namespace std;

struct MyComparison{
    bool operator()(const pair<int,int>& le,const pair<int,int>& ri) const{
        return le.second>ri.second;
    }
};

struct Edge{
    int to;
    int val;
    Edge(int _to,int _val):to(_to),val(_val){};
};

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<Edge>> graph(n+1);
    int st,ed,val;
    for(int i=1;i<=m;i++){
        cin>>st>>ed>>val;
        graph[st].push_back(Edge(ed,val));
    }
  
    vector<int> minDist(n+1,INT_MAX);
    vector<bool> visited(n+1,false);
    priority_queue<pair<int,int>,vector<pair<int,int>>,MyComparison> que;
    minDist[1]=0;
    que.push({1,0});
    visited[1]=true;

    while(!que.empty()){
        auto [cur,dist]=que.top();
        que.pop();
        if(dist>minDist[cur]) continue;
        
        for(auto [to,val]:graph[cur]){
            if(minDist[to]>dist + val){
                minDist[to] = dist +val;
                que.push({to,minDist[to]});
            }
        }
    }

    if(minDist[n]==INT_MAX) cout<<-1<<endl;
    else cout<<minDist[n];
    return 0;
}