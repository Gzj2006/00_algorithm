/*题目描述
给定一个由 1（陆地）和 0（水）组成的矩阵，岛屿是被水包围，并且通过水平方向或垂直方向上相邻的陆地连接而成的。
你可以假设矩阵外均被水包围。在矩阵中恰好拥有一个岛屿，假设组成岛屿的陆地边长都为 1，
请计算岛屿的周长。岛屿内部没有水域。
输入描述
第一行包含两个整数 N, M，表示矩阵的行数和列数。之后 N 行，每行包含 M 个数字，数字为 1 或者 0，
表示岛屿的单元格。
输出描述
输出一个整数，表示岛屿的周长。*/

#include<iostream>
#include<vector>
using namespace std;

int main(){
    int dir[4][2]={1,0,-1,0,0,1,0,-1};
    int N,M;
    cin>>N>>M;
    vector<vector<int>> isl(N,vector<int>(M,0));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>isl[i][j];
        }
    }

    int result=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isl[i][j]==1){
                for(auto [dx,dy]:dir){
                    int nx=i+dx;
                    int ny=j+dy;
                    if(nx<0||nx>=N||ny<0||ny>=M) {result+=1; continue;}
                    if(isl[nx][ny]==0) result+=1;
                }
            }
        }
    }
    cout<<result;
}