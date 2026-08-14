#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dir[4][2]={0,1,0,-1,1,0,-1,0};
void bfs(vector<vector<int>>& isl,int N,int M,int x,int y){
    queue<pair<int,int>> que;
    que.push({x,y});
    isl[x][y]=0;
    while(!que.empty()){//淹没靠岸岛屿
        auto [cx,cy]=que.front();
        que.pop();
        for(auto [dx,dy]:dir){
            int nx=cx+dx;
            int ny=cy+dy;
            if(nx<0||nx>=N||ny<0||ny>=M) continue;
            if(isl[nx][ny]==1){
            que.push({nx,ny});
            isl[nx][ny]=0;
            }
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> isl(N,vector<int>(M,0));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>isl[i][j];
        }
    }
    //两侧逼近
    for(int i=0;i<N;i++){
        if(isl[i][0]==1) bfs(isl,N,M,i,0);
        if(isl[i][M-1]==1) bfs(isl,N,M,i,M-1);
    }
    for(int j=0;j<M;j++){
        if(isl[0][j]==1) bfs(isl,N,M,0,j);
        if(isl[N-1][j]==1) bfs(isl,N,M,N-1,j);
    }

    //统计孤岛
    int result=0;
    for(int i=1;i<N;i++){
        for(int j=1;j<M;j++){
            if(isl[i][j]==1) result+=1;
        }
    }
    cout<<result;
}