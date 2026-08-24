# 优先队列（std::priority_queue）知识点

## 一、什么是优先队列

优先队列是一种**特殊队列**：出队的不是最早入队的元素，而是**优先级最高**的元素。
底层实现是**堆（heap）**。

- C++ 默认是**大顶堆**：队首（`top()`）是**最大**的元素
- 入队 `push`、出队 `pop` 都是 **O(log n)**，取队首 `top()` 是 **O(1)**

```
push(3) push(1) push(5)  →  堆顶是 5（大顶堆） →  pop() 依次弹出 5、3、1
```

对应头文件：`#include <queue>`

## 二、std::priority_queue 常用成员函数

| 函数 | 作用 | 返回值 | 示例 |
|------|------|--------|------|
| `push(x)` | 元素入堆 | 无 | `pq.push({0, 1})` |
| `top()` | 查看堆顶元素（**不删除**） | 元素引用 | `auto [d,u] = pq.top();` |
| `pop()` | 移除堆顶元素 | **无返回值** | `pq.pop();` |
| `empty()` | 判断是否为空 | `bool` | `while(!pq.empty())` |
| `size()` | 返回元素个数 | `size_t` | `pq.size()` |

### ⚠️ 易错点

1. **`pop()` 不返回被删除的元素**。取堆顶必须两步：
   ```cpp
   pair<int,int> cur = pq.top();  // ① 先取堆顶
   pq.pop();                      // ② 再删除
   ```
2. 没有 `front()` / `back()`，只有 `top()`。

## 三、大顶堆 / 小顶堆

`priority_queue` 有**三个模板参数**：

```cpp
priority_queue<元素类型, 底层容器, 比较器> pq;
```

- 默认 `priority_queue<int, vector<int>, less<int>>` —— **大顶堆**（堆顶最大）
- 传 `greater<int>` —— **小顶堆**（堆顶最小）

```cpp
priority_queue<int> pq;                          // 大顶堆
priority_queue<int, vector<int>, greater<int>> pq;  // 小顶堆
```

> ⚠️ 只要写了第三个参数，第二个参数 `vector<T>` 就必须写全，否则编译报错。

## 四、Dijkstra 为什么要用优先队列

朴素版 Dijkstra 每次要 **O(n) 遍历找"距离最小的未访问节点"**，总复杂度 **O(n²)**。

堆优化版用优先队列（小顶堆）：
- 每次 **O(log n)** 取当前距离最小的节点
- 总复杂度 **O((n+m)log n)**，适合稀疏图（边数少）

| 版本 | 取最小 | 总复杂度 | 适用 |
|------|--------|---------|------|
| 朴素（邻接矩阵） | O(n) | O(n²) | 稠密图、n 小 |
| 堆优化（邻接表 + pq） | O(log n) | O((n+m)log n) | 稀疏图、n 大 |

## 五、堆里存什么：`pair<距离, 节点>`

堆要同时保存"距离"和"节点号"，所以存 `pair<int,int>`：

```cpp
// 小顶堆：距离小的排在前面（pair 先比 first 距离，再比 second 节点号）
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
pq.push({0, 1});   // 起点距离 0
```

## 六、核心流程 + 惰性删除（lazy deletion）

同一个节点可能**入队多次**（每次发现更短距离就 `push` 一次）。
出队时要检查是不是**过期的旧距离**，是则直接丢弃 —— 这叫**惰性删除**：

```cpp
while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > minDist[u]) continue;   // 惰性删除：旧距离直接丢弃

    for (auto [v, w] : graph[u]) {  // 遍历 u 的邻边
        if (minDist[u] + w < minDist[v]) {
            minDist[v] = minDist[u] + w;
            pq.push({minDist[v], v});   // 新距离入队
        }
    }
}
```

> 💡 有了惰性删除，**就不需要 `visited` 数组了**（这是与朴素版最大的区别）。

## 七、完整模板（堆优化 Dijkstra，邻接表）

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> graph(n + 1);   // graph[u] = {(v, w), ...}
    for (int i = 0; i < m; i++) {
        int s, e, v;
        cin >> s >> e >> v;
        graph[s].push_back({e, v});   // 重边也无妨，松弛时会自动取更小值
    }

    vector<int> minDist(n + 1, INT_MAX);
    minDist[1] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > minDist[u]) continue;   // 惰性删除

        for (auto [v, w] : graph[u]) {
            if (minDist[u] + w < minDist[v]) {
                minDist[v] = minDist[u] + w;
                pq.push({minDist[v], v});
            }
        }
    }

    if (minDist[n] == INT_MAX) cout << -1 << endl;   // 不可达
    else cout << minDist[n] << endl;
    return 0;
}
```

> ⚠️ `auto [d, u]` 是 **C++17 结构化绑定**。C++14 及以下改用 `.first` / `.second`：
> ```cpp
> int d = pq.top().first, u = pq.top().second;
> ```

## 八、自定义比较器（不用 greater 时）

原理：`priority_queue` 里比较器语义是 **`comp(a, b) == true` 表示 a 的优先级低于 b**（a 排在后面）。
所以想小顶堆，比较器里要返回 `a > b`：

```cpp
struct cmp {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
        return a.first > b.first;   // 距离大的优先级低 → 小顶堆
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
```

## 九、常见坑汇总

| 坑 | 后果 |
|----|------|
| 忘了写 `greater` | 变成大顶堆，先取**最大**距离，结果错误 |
| 写了比较器但漏掉 `vector<T>` 参数 | 编译错误 |
| 忘了惰性删除 `if(d > minDist[u]) continue` | 旧条目反复处理，慢（结果通常仍对，但低效） |
| C++14 以下用了结构化绑定 | 编译错误 |
| 边权可能为 0 | 邻接表不受影响（比邻接矩阵 + 0 判无边更稳） |
