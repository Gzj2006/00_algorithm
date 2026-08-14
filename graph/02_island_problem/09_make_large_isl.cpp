/*给定一个由 1（陆地）和 0（水）组成的矩阵，你最多可以将矩阵中的一格水变为一块陆地，在执行了此操作之后，矩阵中最大的岛屿面积是多少。

岛屿面积的计算方式为组成岛屿的陆地的总数。岛屿是被水包围，并且通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设矩阵外均被水包围。

输入描述：

第一行包含两个整数 N, M，表示矩阵的行数和列数。之后 N 行，每行包含 M 个数字，数字为 1 或者 0，表示岛屿的单元格。

输出描述：

输出一个整数，表示最大的岛屿面积。*/
#include<iostream>
#include<vector>
#include<set>
#include<queue>
using namespace std;

int dir[4][2]={1,0,-1,0,0,1,0,-1};
void bfs(vector<vector<int>>& isl,int N,int M,int x,int y,int id,vector<int>& val){
    int count=1;
    queue<pair<int,int>> que;
    que.push({x,y});
    isl[x][y]=id;
    while(!que.empty()){
        auto[cx,cy]=que.front();
        que.pop();
        for(auto [dx,dy]:dir){
            int nx=cx+dx;
            int ny=cy+dy;
            if(nx<0||nx>=N||ny<0||ny>=M) continue;
            if(isl[nx][ny]==1){
                que.push({nx,ny});
                isl[nx][ny]=id;
                count+=1;
            }
        }
    }
    val[id]=count;
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> isl(N,vector<int>(M,0));
    vector<int> val(N*M+2,0);
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>isl[i][j];
        }
    }

    //标号岛屿
    int id=2;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isl[i][j]==1) {
                bfs(isl,N,M,i,j,id,val);
                id+=1;
            }
        }
    }

    //计算最大人工岛
    int result=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(isl[i][j]==0) {
                set<int> ips;
                int num=1;
                for(auto [dx,dy]:dir){
                    if(i+dx<0||i+dx>=N||j+dy<0||j+dy>=M) continue;
                    ips.insert(isl[i+dx][j+dy]);
                }
                for(auto cid:ips){
                    num+=val[cid];
                }
                result=max(result,num);
            }
        }
    }
    cout<<result;
}