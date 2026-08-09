//求最大岛屿，bfs
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dir[4][2]={1,0,0,1,-1,0,0,-1};//四个方向遍历
void bfs(const vector<vector<int>>& isl,vector<vector<bool>>& visited,int x,int y,int N,int M,int& count)
{
    queue<pair<int,int>> que;
    que.push({x,y});count+=1;
    visited[x][y]=true;
    while(!que.empty()){
        auto[curx,cury] = que.front();
        que.pop();
        for(auto [dx,dy]:dir){
           int nx = curx + dx;
           int ny = cury + dy; 
            if(nx<0||nx>=N||ny<0||ny>=M) continue;//越界检查
            if(isl[nx][ny]==1&&visited[nx][ny]==false){
                que.push({nx,ny});
                count+=1;
                visited[nx][ny] = true;
            }
        }
    }   
}

int main(){
    int M,N;
    cin>>N>>M;
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
                int count = 0;
                bfs(isl,visited,i,j,N,M,count);
                if(count>result) result = count;
            }
        }
    }
    cout<<result;
}