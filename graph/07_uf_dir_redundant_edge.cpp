/*有一种有向树,该树只有一个根节点，所有其他节点都是该根节点的后继。
该树除了根节点之外的每一个节点都有且只有一个父节点，而根节点没有父节点。有向树拥有 n 个节点和 n - 1 条边。如图：
现在有一个有向图，有向图是在有向树中的两个没有直接链接的节点中间添加一条有向边。
输入一个有向图，该图由一个有着 n 个节点(节点编号 从 1 到 n)。
n 条边，请返回一条可以删除的边，使得删除该条边之后该有向图可以被当作一颗有向树。

输入描述
第一行输入一个整数 N，表示有向图中节点和边的个数。
后续 N 行，每行输入两个整数 s 和 t，代表这是 s 节点连接并指向 t 节点的单向边
输出描述
输出一条可以删除的边，若有多条边可以删除，请输出标准输入中最后出现的一条边。*/
#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int> father;
void init(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
}

int find(int u){
    if(father[u]==u) return u;
    return father[u]=find(father[u]);
}

bool isSame(int u,int v){
    int ru=find(u);
    int rv=find(v);
    return ru==rv;
}

void join(int u,int v){
    int ru=find(u);
    int rv=find(v);
    if(ru==rv) return;
    father[ru]=rv;
}

bool isTree(const vector<pair<int,int>>& edges,const pair<int,int>& skip){
    init();
    for(auto [u,v]:edges){
        if(u == skip.first && v == skip.second) continue;
        if(isSame(u,v)) return false;
        join(u,v);
    }
    return true;
}

void getRemoveEdge(vector<pair<int,int>> edges){
    init();
    pair<int,int> result{0,0};
    for(auto [u,v]:edges){
        if(isSame(u,v)) result={u,v};
        else join(u,v);
    }
    cout<<result.first<<' '<<result.second<<endl;
}

int main(){
    cin>>n;
    father.resize(n+1);
    vector<pair<int,int>> edges;
    vector<int> degree(n+1,0);

    for(int i=0;i<n;i++){
        int u,v;
        cin>>u>>v;
        edges.push_back({u,v});
        degree[v]++;
    }

    for(int i = 1; i <= n; i++){
        if(degree[i] == 2){
            pair<int,int> result{0,0};
            for(auto [s,t]:edges){
                if(t==i && isTree(edges,{s,t})) result={s,t};
            }
            cout<<result.first<<' '<<result.second<<endl;
        return 0;
        }
    }
    
    //无入度2
    getRemoveEdge(edges);
    return 0;
}