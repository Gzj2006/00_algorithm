/*题目描述：

给定一个由 1（陆地）和 0（水）组成的矩阵，你需要计算岛屿的数量。岛屿由水平方向或垂直方向上相邻的陆地连接而成，并且四周都是水域。你可以假设矩阵外均被水包围。

输入描述：

第一行包含两个整数 N, M，表示矩阵的行数和列数。

后续 N 行，每行包含 M 个数字，数字为 1 或者 0。

输出描述：

输出一个整数，表示岛屿的数量。如果不存在岛屿，则输出 0。*/

//dfs
#include<iostream>
#include<vector>
using namespace std;

int dir[4][2]={1,0,0,1,-1,0,0,-1};//四个方向遍历
void dfs(const vector<vector<int>>& isl,vector<vector<bool>> visited,int x,int y)
{
    for(auto [dx,dy]:dir){
        int nx = x+dx,ny=y+dy;
        if(!visited[nx][ny]&&isl[nx][ny]==1){
            visited[nx][ny]==true;
            dfs(isl,visited,nx,ny);
        }
    }
}

int main(){
    int M,N;
    cin>>M>>N;
    vector<vector<int>> isl(N,vector<int>(M,0));
    vector<vector<bool>>  visited(N,vector<bool>(M,false));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>isl[i][j];
        }
    }

    int result=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isl[i][j]==1&&!visited[i][j]){
                result+=1;
                dfs(isl,visited,i,j);
            }
        }
    }
    cout<<result;
}