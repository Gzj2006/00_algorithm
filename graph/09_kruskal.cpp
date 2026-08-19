//kruskal法求最小生成树
/*在世界的某个区域，有一些分散的神秘岛屿，每个岛屿上都有一种珍稀的资源或者宝藏。
不同岛屿之间，路途距离不同，国王希望你可以规划建公路的方案，如何可以以最短的总公路距离将所有岛屿联通起来。
给定一张地图，其中包括了所有的岛屿，以及它们之间的距离。以最小化公路建设长度，确保可以链接到所有岛屿。
输入描述：
第一行包含两个整数V和E，V代表顶点数，E代表边数。顶点编号是从1到V。例如：V=2，一个有两个顶点，分别是1和2。
接下来共有E行，每行三个整数v1，v2和val，v1和v2为边的起点和终点，val代表边的权值。
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge{
    int u,v,val;
};

int n;
vector<int> father;
void init(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
}

int find(int u){
    return father[u]==u ? u : father[u]=find(father[u]);
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
    else father[ru]=rv;
}

int main(){
    int e;
    cin>>n>>e;
    father.resize(n+1);
    vector<Edge> edges;

    for(int i=0;i<e;i++){
        int l,r,val;
        cin>>l>>r>>val;
        edges.push_back({l,r,val});
    }

    sort(edges.begin(),edges.end(),[](Edge a,Edge b)
    {return a.val<b.val;});

    init();
    int result=0;
    vector<Edge> minTree;
    for(const auto& cur:edges){
        if(isSame(cur.u,cur.v)) continue;
        result+=cur.val;
        minTree.push_back(cur);
        join(cur.u,cur.v);
    }

    cout<<result<<endl;
    for(const auto& cur:minTree){
        cout<<cur.u<<"->"<<cur.v<<' '<<cur.val<<endl;
    }
}