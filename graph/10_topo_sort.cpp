/*某个大型软件项目的构建系统拥有 N 个文件，文件编号从 0 到 N - 1，在这些文件中，某些文件依赖于其他文件的内容，这意味着如果文件 A 依赖于文件 B，则必须在处理文件 A 之前处理文件 B （0 <= A, B <= N - 1）。
请编写一个算法，用于确定文件处理的顺序。
输入描述：
第一行输入两个正整数 N, M。表示 N 个文件之间拥有 M 条依赖关系。
后续 M 行，每行两个正整数 S 和 T，表示 T 文件依赖于 S 文件。
输出描述：
输出共一行，如果能处理成功，则输出文件顺序，用空格隔开。
如果不能成功处理（相互依赖），则输出 -1。*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void toposort (const vector<vector<int>>& graph,vector<int>& inDegree,vector<int>& result,int N){
    queue<int> que;
    for(int i=0;i<N;i++){
        if(inDegree[i]==0){
            que.push(i);
            result.push_back(i);
        } 
    }

    while(!que.empty()){
        int cur = que.front();
        que.pop();
        for(auto i:graph[cur]){
            inDegree[i]--;
            if(inDegree[i]==0){
                que.push(i);
                result.push_back(i);
            }
        }
    }

    if(result.size()==N){
        for(auto i:result) { cout<<i<<' '; }
        cout<<endl;
        return;
    }
    cout<<-1<<endl;
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> graph(N);
    vector<int> inDegree(N,0);
    vector<int> result;
    for(int i=0;i<M;i++){
            int u,v;
            cin>>u>>v;
            inDegree[v]++;
            graph[u].push_back(v);
    }

    toposort(graph,inDegree,result,N);
    return 0;
}