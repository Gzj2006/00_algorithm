//prim法求最小生成树
/*在世界的某个区域，有一些分散的神秘岛屿，每个岛屿上都有一种珍稀的资源或者宝藏。
不同岛屿之间，路途距离不同，国王希望你可以规划建公路的方案，如何可以以最短的总公路距离将所有岛屿联通起来。
给定一张地图，其中包括了所有的岛屿，以及它们之间的距离。以最小化公路建设长度，确保可以链接到所有岛屿。
输入描述：
第一行包含两个整数V和E，V代表顶点数，E代表边数。顶点编号是从1到V。例如：V=2，一个有两个顶点，分别是1和2。
接下来共有E行，每行三个整数v1，v2和val，v1和v2为边的起点和终点，val代表边的权值。
*/
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

int main(){
    int v,e;
    cin>>v>>e;
    vector<vector<int>> graph(v+1,vector<int>(v+1,0));
    vector<bool> inTree(v+1,false);
    vector<int> minDist(v+1,INT_MAX);
    vector<int> parents(v+1,-1);

    for(int i=0;i<e;i++){
        int s,t,val;
        cin>>s>>t>>val;
        graph[s][t]=val;
        graph[t][s]=val;
    }

    int result=0;
    minDist[1]=0;
    for(int i=1;i<=v;i++){
        int cur=-1,minVal=INT_MAX;
        //求出当前最小距离点
        for(int j=1;j<=v;j++){
            if(!inTree[j] && minDist[j]<minVal){
                minVal = minDist[j];
                cur = j;
            }
        }
        //加入树
        if (cur == -1) break;
        inTree[cur]=true;
        result+=minDist[cur];

        //更新最短距离
        for(int j=1;j<=v;j++){
            if(!inTree[j] && graph[cur][j]!=0 && minDist[j]>graph[cur][j]) {
                minDist[j] =graph[cur][j];
                parents[j] = cur;
            }
        }
    }

    cout<<result<<endl;
    for(int i=1;i<=v;i++){
        cout<<i<<"->"<<parents[i]<<endl;
    }
    return 0;
}
