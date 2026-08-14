/*现有一个 N × M 的矩阵，每个单元格包含一个数值，这个数值代表该位置的相对高度。
矩阵的左边界和上边界被认为是第一组边界，而矩阵的右边界和下边界被视为第二组边界。

矩阵模拟了一个地形，当雨水落在上面时，水会根据地形的倾斜向低处流动，
但只能从较高或等高的地点流向较低或等高并且相邻（上下左右方向）的地点。
我们的目标是确定那些单元格，从这些单元格出发的水可以达到第一组边界和第二组边界。

输入描述：
第一行包含两个整数 N 和 M，分别表示矩阵的行数和列数。
后续 N 行，每行包含 M 个整数，表示矩阵中的每个单元格的高度。
输出描述：
输出共有多行，每行输出两个整数，用一个空格隔开，表示可达第一组边界和第二组边界的单元格的坐标，输出顺序任意。*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dir[4][2]={1,0,-1,0,0,1,0,-1};
void dfs(const vector<vector<int>>& isl,vector<vector<bool>>& P_visited,int x,int y,int N,int M){
    P_visited[x][y]=true;
    for(auto [dx,dy]:dir){
        int nx=x+dx;
        int ny=y+dy;
        if(nx<0||nx>=N||ny<0||ny>=M) continue;
        if(isl[nx][ny]>=isl[x][y]&&!P_visited[nx][ny]){
            dfs(isl,P_visited,nx,ny,N,M);
        }
    }
}
void bfs(const vector<vector<int>>& isl,vector<vector<bool>>& A_visited,int x,int y,int N,int M){
    queue<pair<int,int>> que;
    que.push({x,y});
    A_visited[x][y]=true;
    while(!que.empty()){
        auto[cx,cy]=que.front();
        que.pop();
        for(auto [dx,dy]:dir){
            int nx=dx+cx;
            int ny=dy+cy;
            if(nx<0||nx>=N||ny<0||ny>=M) continue;
            if(isl[nx][ny]>=isl[cx][cy]&&!A_visited[nx][ny]){
            que.push({nx,ny});
            A_visited[nx][ny]=true;
            }
        }
    }
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> isl(N,vector<int>(M,0));
    vector<vector<bool>> P_visited(N,vector<bool>(M,false)),A_visited(N,vector<bool>(M,false));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>isl[i][j];
        }
    }

    //逆流检查
    for(int i=0;i<N;i++){
        dfs(isl,P_visited,i,0,N,M);
        bfs(isl,A_visited,i,M-1,N,M);
    }
    for(int j=0;j<M;j++){
        dfs(isl,P_visited,0,j,N,M);
        bfs(isl,A_visited,N-1,j,N,M);
    }

    //输出
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(P_visited[i][j]&&A_visited[i][j]) cout<<i<<' '<<j<<'\n';
        }
    }
}