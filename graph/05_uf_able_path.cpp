/*给定一个包含 n 个节点的无向图中，节点编号从 1 到 n （含 1 和 n ）。
你的任务是判断是否有一条从节点 source 出发到节点 destination 的路径存在。
输入描述
第一行包含两个正整数 N 和 M，N 代表节点的个数，M 代表边的个数。
后续 M 行，每行两个正整数 s 和 t，代表从节点 s 与节点 t 之间有一条边。
最后一行包含两个正整数，代表起始节点 source 和目标节点 destination。
输出描述
输出一个整数，代表是否存在从节点 source 到节点 destination 的路径。
如果存在，输出 1；否则，输出 0。*/

#include<iostream>
#include<vector>
using namespace std;

//并查集
int N;
vector<int> father;

void init(){
    for(int i=1;i<=N;i++) {father[i]=i;}
}

int find(int u){
    if(father[u]==u) return u;
    return father[u]=find(father[u]);
}

bool inSame(int u,int v){
    int s=find(u);
    int e=find(v);
    return s==e;
}

void join(int u,int v){
    int s=find(u);
    int e=find(v);
    if(s==e) return;
    else father[s]=e;
}

int main(){
    int M,st,ed;
    cin>>N>>M;
    father.resize(N+1);
    init();

    for(int i=0;i<M;i++){
        int u,v;
        cin>>u>>v;
        join(u,v);
    }

    cin>>st>>ed;
    if(inSame(st,ed)) {cout<<1;}
    else {cout<<0;}
}