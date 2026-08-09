# 队列（std::queue）知识点

## 一、什么是队列

队列是一种 **先进先出（FIFO，First In First Out）** 的线性数据结构。
先进入的元素先出来，就像排队买票——先来的人先被服务。

```
入队(队尾) ──▶ [ a | b | c ] ──▶ 出队(队首)
```

- 只能在**队尾**添加元素（`push`）
- 只能从**队首**移除元素（`pop` / `front`）

对应头文件：`#include <queue>`

## 二、std::queue 常用成员函数

| 函数 | 作用 | 返回值 | 示例 |
|------|------|--------|------|
| `push(x)` | 元素入队（加到队尾） | 无 | `que.push({0,0})` |
| `front()` | 查看队首元素 | 队首元素引用（**不删除**） | `auto cur = que.front();` |
| `back()` | 查看队尾元素 | 队尾元素引用（不删除） | `que.back()` |
| `pop()` | 移除队首元素 | **无返回值** | `que.pop();` |
| `empty()` | 判断队列是否为空 | `bool` | `while(!que.empty())` |
| `size()` | 返回元素个数 | `size_t` | `que.size()` |

### ⚠️ 易错点

1. **`pop()` 不返回被删除的元素**。取元素必须两步：
   ```cpp
   pair<int,int> cur = que.front();  // ① 先取出队首
   que.pop();                        // ② 再删除队首
   ```
2. **`front()` 之前要先判断非空**，否则空队列取队首是未定义行为。
3. **入队即标记 visited**，防止同一元素被重复入队，导致死循环。

## 三、BFS 遍历模板（以岛屿问题为例）

BFS（广度优先搜索）用队列实现"层层扩散"：从起点开始，先访问所有相邻节点，再访问相邻的相邻……直到没有新的可达节点。

```cpp
#include <queue>
using namespace std;

int dir[4][2] = {1,0, 0,1, -1,0, 0,-1};  // 下、右、上、左 四个方向

void bfs(const vector<vector<int>>& isl, vector<vector<bool>>& visited,
         int x, int y, int N, int M)
{
    queue<pair<int,int>> que;
    que.push({x, y});          // ① 起点入队
    visited[x][y] = true;      // ② 入队即标记

    while(!que.empty()){                       // ③ 队列非空就继续扩散
        auto [cx, cy] = que.front();           // ④ 取出队首坐标
        que.pop();

        for(auto [dx, dy] : dir){              // ⑤ 遍历四个方向
            int nx = cx + dx, ny = cy + dy;
            if(nx < 0 || nx >= N || ny < 0 || ny >= M) continue;  // 越界跳过
            if(!visited[nx][ny] && isl[nx][ny] == 1){
                visited[nx][ny] = true;        // ⑥ 入队前先标记
                que.push({nx, ny});
            }
        }
    }
}
```

### 完整调用逻辑

```cpp
int result = 0;
for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
        if(isl[i][j] == 1 && !visited[i][j]){
            result++;                 // 发现一个新岛屿
            bfs(isl, visited, i, j, N, M);  // 把整块岛屿标记完
        }
```

## 四、BFS 与 DFS 对比

| 对比项 | BFS（广度优先） | DFS（深度优先） |
|--------|----------------|----------------|
| 数据结构 | **队列 queue** | 递归 / 栈 stack |
| 扩散方式 | 逐层向外扩散（先近后远） | 一条路走到底再回头 |
| 特点 | 可求**最短路径** | 代码简洁，天然递归 |
| 岛屿问题 | 能解 | 能解 |
| 大矩阵风险 | 无栈溢出问题 | 递归深可能**栈溢出** |

## 五、BFS 典型应用场景

- 图/矩阵的连通块统计（如岛屿数量）
- **最短路径**（无权图，第一次到达即最短）
- 迷宫求最短步数
- 多源扩散问题（多个起点同时入队）

> 记忆口诀：**BFS 用队列，层层扩散；DFS 用递归，一路到底。入队即标记，防重防死循环。**
