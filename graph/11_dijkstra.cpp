/*小明是一位科学家，他需要参加一场重要的国际科学大会，以展示自己的最新研究成果。
小明的起点是第一个车站，终点是最后一个车站。然而，途中的各个车站之间的道路状况、交通拥堵程度以及可能的自然因素（如天气变化）等不同，这些因素都会影响每条路径的通行时间。
小明希望能选择一条花费时间最少的路线，以确保他能够尽快到达目的地。
【输入描述】
第一行包含两个正整数，第一个正整数 N 表示一共有 N 个公共汽车站，第二个正整数 M 表示有 M 条公路。
接下来为 M 行，每行包括三个整数，S、E 和 V，代表了从 S 车站可以单向直达 E 车站，并且需要花费 V 单位的时间。
【输出描述】
输出一个整数，代表小明从起点到终点所花费的最小时间。*/

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> graph(n+1,vector<int>(n+1,0));
    vector<bool> visited(n+1,false);
    vector<int> minDist(n+1,INT_MAX);
    for(int i=0;i<m;i++){
        int s,e,v;
        cin>>s>>e>>v;
        graph[s][e]=v;
    }

    minDist[1]=0;
    int cur = 1;
    visited[1]=true;
    for(int j=1;j<=n;j++){
        for(int i=1;i<=n;i++){
            if(!visited[i] && graph[cur][i]!=0 && minDist[i]>minDist[cur]+graph[cur][i]) {
                minDist[i]=minDist[cur]+graph[cur][i];
            }
        }

        int minNum = INT_MAX;
        for(int i=1;i<=n;i++){
            if(!visited[i] && minDist[i]<minNum){
                cur = i;
                minNum = minDist[i];
            }
        }
        visited[cur]=true;
    }
    if(minDist[n]==INT_MAX) cout<<-1<<endl;
    else cout<<minDist[n]<<endl;
    return 0;
}
