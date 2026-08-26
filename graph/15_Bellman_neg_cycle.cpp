//Bellman_ford 判断负权回路

#include<iostream>
#include<vector>
#include<climits>
#include<queue>
using namespace std;

struct Edge {
    int to;
    int val;
    Edge(int _to,int _val):to(_to),val(_val){}
};

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<Edge>> edges(n+1);
    vector<int> mindist(n+1,INT_MAX);
    vector<bool> visited(n+1,false);
    vector<int> count(n+1,0);
    for(int i=0;i<m;i++){
        int s,t,v;
        cin>>s>>t>>v;
        edges[s].push_back(Edge(t,v));
    }

    mindist[1]=0;
    queue<int> que;
    que.push(1);
    count[1]++;
    visited[1]=true;
    while(!que.empty()){
        int cur = que.front();
        que.pop();
        visited[cur] = false;
        if(count[cur]>=n){
            cout<<"cycle"<<endl;
            return 0;
        }

        for(auto i:edges[cur]){
            int t=i.to;
            int v=i.val;
            if(mindist[t]>mindist[cur]+v){
                mindist[t] = mindist[cur]+v;
                if(!visited[t]){
                    que.push(t);
                    visited[t] = true;
                    count[t]++;
                }   
            }
        }
    } 

    if(mindist[n]==INT_MAX) cout<<"unconnected"<<endl;
    else cout<<mindist[n]<<endl;
    return 0;
}

/*
if(mindist[t] > mindist[cur]+v){
    mindist[t] = mindist[cur]+v;
    cnt[t] = cnt[cur] + 1;
    if(cnt[t] >= n){ cout<<"cycle"<<endl; return 0; }  // 边数≥n 必有负环
    if(!visited[t]){ que.push(t); visited[t]=true; }
}
或者计边数（<=n-1）
*/