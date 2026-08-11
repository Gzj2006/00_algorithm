/*题目描述
给定一个由 1（陆地）和 0（水）组成的矩阵，岛屿指的是由水平或垂直方向上相邻的陆地单元格组成的区域，且完全被水域单元格包围。孤岛是那些位于矩阵内部、所有单元格都不接触边缘的岛屿。
现在你需要计算所有孤岛的总面积，岛屿面积的计算方式为组成岛屿的陆地的总数。
输入描述
第一行包含两个整数 N, M，表示矩阵的行数和列数。之后 N 行，每行包含 M 个数字，数字为 1 或者 0。
输出描述
输出一个整数，表示所有孤岛的总面积，如果不存在孤岛，则输出 0*/

//dfs
#include<iostream>
#include<vector>
using namespace std;

int dir[4][2]={1,0,-1,0,0,1,0,-1};
void dfs(const vector<vector<int>>& isl,vector<vector<bool>>& visited,const int N,const int M,int x,int y,int& count,bool& a){
    for(auto [dx,dy]:dir){
        int nx=x+dx;
        int ny=y+dy;
        if(nx<0||nx>=N||ny<0||ny>=M) { a=false;continue;}
        if(isl[nx][ny]==1&&visited[nx][ny]==false){
            count+=1;
            visited[nx][ny]=true;
            dfs(isl,visited,N,M,nx,ny,count,a);
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

    int result=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isl[i][j]==1&&visited[i][j]==false){
                int count=1;
                bool a_isl=true;
                visited[i][j]=true;
                dfs(isl,visited,N,M,i,j,count,a_isl);
                if(a_isl){result+=count;}
            }
        }
    }
    cout<<result;
}