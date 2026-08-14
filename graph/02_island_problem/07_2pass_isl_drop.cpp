/*题目描述：

给定一个由 1（陆地）和 0（水）组成的矩阵，岛屿指的是由水平或垂直方向上相邻的陆地单元格组成的区域，且完全被水域单元格包围。孤岛是那些位于矩阵内部、所有单元格都不接触边缘的岛屿。

现在你需要将所有孤岛“沉没”，即将孤岛中的所有陆地单元格（1）转变为水域单元格（0）。

输入描述：

第一行包含两个整数 N, M，表示矩阵的行数和列数。

之后 N 行，每行包含 M 个数字，数字为 1 或者 0，表示岛屿的单元格。

输出描述

输出将孤岛“沉没”之后的岛屿矩阵。*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dir[4][2]={0,1,0,-1,1,0,-1,0};
void bfs(const vector<vector<int>>& isl,int N,int M,int x,int y,vector<vector<bool>>& visited){
    queue<pair<int,int>> que;
    que.push({x,y});
    visited[x][y]=true;
    while(!que.empty()){//标记靠岸岛屿
        auto [cx,cy]=que.front();
        que.pop();
        for(auto [dx,dy]:dir){
            int nx=cx+dx;
            int ny=cy+dy;
            if(nx<0||nx>=N||ny<0||ny>=M) continue;
            if(isl[nx][ny]==1&&!visited[nx][ny]){
            que.push({nx,ny});
            visited[nx][ny]=true;
            }
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> isl(N,vector<int>(M,0));
    vector<vector<bool>> visited(N,vector<bool>(M,false));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>isl[i][j];
        }
    }
    //两侧逼近
    for(int i=0;i<N;i++){
        if(isl[i][0]==1&&!visited[i][0]) bfs(isl,N,M,i,0,visited);
        if(isl[i][M-1]==1&&!visited[i][M-1]) bfs(isl,N,M,i,M-1,visited);
    }
    for(int j=0;j<M;j++){
        if(isl[0][j]==1&&!visited[0][j]) bfs(isl,N,M,0,j,visited);
        if(isl[N-1][j]==1&&!visited[N-1][j]) bfs(isl,N,M,N-1,j,visited);
    }

    //淹没孤岛并输出
    cout<<"---------------------\n";
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isl[i][j]==1&&visited[i][j]==false) isl[i][j]=0;
            cout<<isl[i][j]<<' ';
        }
        cout<<'\n';
    }
}