/*给定一个有向图，包含 N 个节点，节点编号分别为 1，2，...，N。现从 1 号节点开始
，如果可以从 1 号节点的边可以到达任何节点，则输出 1，否则输出 -1。

【输入描述】
第一行包含两个正整数，表示节点数量 N 和边的数量 K。 后续 K 行,
每行两个正整数 s 和 t，表示从 s 节点有一条边单向连接到 t 节点。

【输出描述】
如果可以从 1 号节点的边可以到达任何节点，则输出 1，否则输出 -1。*/
#include<iostream>
#include<vector>
using namespace std;

void dfs(const vector<vector<int>>& graph,int key,vector<bool>& visited){
    for(auto i:graph[key]){
        if(visited[i]==false){
            visited[i]=true;
            dfs(graph,i,visited);
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> graph(N+1);
    vector<bool> visited(N+1,false);
    for (int i = 0; i < M; i++){
        int st,ed;
        cin>>st>>ed;
        graph[st].push_back(ed);
    }

    visited[1] = true;
    dfs(graph,1,visited);
    for(int i = 1; i <= N; i++) {
        if(visited[i]==false) {cout<<-1;return 0;}
    }
    cout<<1;
}