/*有一个图，它是一棵树，他是拥有 n 个节点（节点编号1到n）和 n - 1 条边的连通无环无向图（其实就是一个线形图），
现在在这棵树上的基础上，添加一条边（依然是n个节点，但有n条边），使这个图变成了有环图，
先请你找出冗余边，删除后，使该图可以重新变成一棵树。

输入描述
第一行包含一个整数 N，表示图的节点个数和边的个数。
后续 N 行，每行包含两个整数 s 和 t，表示图中 s 和 t 之间有一条边。
输出描述
输出一条可以删除的边。如果有多个答案，请删除标准输入中最后出现的那条边。*/
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
bool inSame(int u,int v){
    int U=find(u);
    int V=find(v);
    return U==V;
}
void join(int u,int v){
    int U=find(u);
    int V=find(v);
    if(U==V) return;
    father[U]=V;
}

int main(){
    cin>>n;
    father.resize(n+1);
    init();
    int u,v;
    for(int i=0;i<n;i++){
        cin>>u>>v;
        if(inSame(u,v)) {cout<<u<<' '<<v;return 0;}
        join(u,v);
    }
}