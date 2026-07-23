/*
给定一个有 n 个节点的有向无环图，节点编号从 1 到 n。请编写一个函数，找出并返回所有从节点 1 到节点 n 的
路径。每条路径应以节点编号的列表形式表示
*/

//图的存储
//邻接矩阵存储
/*
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
    }
        1表示节点之间有边（无权）
*/

//邻接表存储
/*
    vector<list<int>> graph(n + 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
*/

//表写法
#include<iostream>
#include<vector>
using namespace std;

void dfs(vector<vector<int>>& graph,int s,int t,vector<int>& path,vector<vector<int>>& result){
    for(int i=0;i<graph[s].size();i++){
        if(graph[s][i]==t){
            path.push_back(t);
            result.push_back(path);
        }
        else{
            path.push_back(graph[s][i]);
            dfs(graph,graph[s][i],t,path,result);
            path.pop_back();
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> graph(n+1);
    while(m--){
        int s,t;
        cin>>s>>t;
        graph[s].push_back(t);
    }
    vector<int> path;
    path.push_back(1);
    vector<vector<int>> result;
    dfs(graph,1,n,path,result);

    if (result.empty()) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[i].size(); j++) {
                if (j > 0) cout << " ";
                cout << result[i][j];
            }
            cout << endl;
        }
    }
}

