/*在象棋中，马和象的移动规则分别是“马走日”和“象走田”。现给定骑士的起始坐标和目标坐标，要求根据骑士的移动规则，计算从起点到达目标点所需的最短步数。

骑士移动规则如马。

棋盘大小 1000 x 1000（棋盘的 x 和 y 坐标均在 [1, 1000] 区间内，包含边界）

输入描述

第一行包含一个整数 n，表示测试用例的数量。

接下来的 n 行，每行包含四个整数 a1, a2, b1, b2，分别表示骑士的起始位置 (a1, a2) 和目标位置 (b1, b2)。

输出描述

输出共 n 行，每行输出一个整数，表示骑士从起点到目标点的最短路径长度。

输入示例
6
5 2 5 4
1 1 2 2
1 1 8 8
1 1 8 7
2 1 3 3
4 6 4 6
输出示例
2
4
6
5
1
0*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int b1,b2;
struct Knight{
    int x,y;
    int g,h,f;
    bool operator < (const Knight& k) const{
        return k.f < f;
    }
};

int Heuristic(const Knight& k){
    return (k.x-b1)*(k.x-b1)+(k.y-b2)*(k.y-b2);
}


priority_queue<Knight> que;
int dir[8][2]={2,1,2,-1,-2,1,-2,-1,1,2,1,-2,-1,2,-1,-2};
void Astar(const Knight& k,vector<vector<int>>& moves,vector<vector<bool>>& visited){
    Knight cur,next;
    que.push(k);
    visited[k.x][k.y] = true;
    while(!que.empty()){
        cur = que.top();
        que.pop();
        if(cur.x==b1 && cur.y==b2) break;
        for(auto [dx,dy]:dir){
            next.x = dx + cur.x;
            next.y = dy + cur.y;
            if(next.x<1 || next.x>1000 || next.y<1 || next.y>1000) continue;
            if(!visited[next.x][next.y]){
                next.g = cur.g + 5;
                next.h = Heuristic(next);
                next.f = next.h + next.g;
                que.push(next);
                moves[next.x][next.y] = moves[cur.x][cur.y] + 1;
                visited[next.x][next.y] = true;
            }
            
        }
    }
}

int main(){
    int n,a1,a2;
    cin>>n;
    for(int i=0; i<n; i++){
        vector<vector<bool>> visited(1001,vector<bool>(1001,false));
        vector<vector<int>> moves(1001,vector<int>(1001,0));
        cin>>a1>>a2>>b1>>b2;
        Knight start;
        start.x = a1;
        start.y = a2;
        start.g = 0;
        start.h = Heuristic(start);
        Astar(start,moves,visited);
        while(!que.empty()) {que.pop();}
        cout<<moves[b1][b2]<<endl;
        }

    return 0;
}
