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

---

# 转义字符（Escape Characters）知识点

## 一、常见转义符

转义字符用 `\` 开头，写在字符或字符串字面量里，表示特殊含义。

### 最常用

| 转义符 | 含义 | 说明 |
|--------|------|------|
| `\n` | 换行（LF） | 最常用，输出换行 |
| `\t` | 水平制表符 | 对齐输出用 |
| `\\` | 反斜杠 `\` | 想输出 `\` 本身时 |
| `\'` | 单引号 `'` | 字符字面量里用 |
| `\"` | 双引号 `"` | 字符串里想输出引号时 |
| `\0` | 空字符（NUL） | C 风格字符串结尾标志 |

### 偶尔用到

| 转义符 | 含义 |
|--------|------|
| `\r` | 回车（CR，回到行首） |
| `\b` | 退格 |
| `\a` | 响铃（终端发声） |
| `\f` | 换页（打印用） |
| `\v` | 垂直制表符 |

### 八进制 / 十六进制

| 转义符 | 含义 |
|--------|------|
| `\ddd` | 八进制 ASCII，如 `\101` = `'A'` |
| `\xhh` | 十六进制 ASCII，如 `\x41` = `'A'` |

### 示例

```cpp
cout << "Hello\nWorld\t!\n";      // 换行 + 制表符
cout << "他说：\"你好\"\n";       // 输出引号
cout << "路径：C:\\Users\\a\n";   // 输出反斜杠
cout << '\'' << '\n';             // 字符里用 \'
```

> 提示：算法输出里最常用的是 `\n`（换行）和 `\t`（制表符对齐）。只换行时优先用 `'\n'`，比 `endl` 快（`endl` 会额外刷新缓冲区）。

## 二、`\n`（换行）与 `\r`（回车）的区别

来自老式打字机/电传机：打完一行需要两个动作——纸往上**换一行**，打印头**推回最左**。

### 核心区别

| 转义符 | 名称 | 动作 | 效果 |
|--------|------|------|------|
| `\n` | 换行（LF, Line Feed） | 纸往上走一行 | **光标下移一行**（列不变） |
| `\r` | 回车（CR, Carriage Return） | 打印头回到最左 | **光标回到本行行首**（行不变） |

### 平台行尾差异

- **Windows**：`\r\n`（先回车再换行）
- **Linux / macOS**：`\n`
- 老版 Mac：`\r`

> Windows 的 C++ 文本模式下写文件，`\n` 会被自动补成 `\r\n`；二进制模式则原样输出。网络协议（HTTP、SMTP 等）规定必须用 `\r\n`。

### 实际使用

1. **一般换行 —— 用 `\n` 就够**：
   ```cpp
   cout << "第一行\n第二行\n";
   ```
   终端/编辑器会自动把光标放到下一行行首。

2. **`\r` 的独特用途：原地刷新（进度条）**：
   ```cpp
   for (int i = 0; i <= 100; i += 10){
       cout << "\r加载中... " << i << "%";
       // 不换行，每次回到行首覆盖，实现动态刷新
   }
   ```
   用 `\n` 会一行行往下刷；用 `\r` 始终在同一行更新。

### 一句话总结

- `\n` = **向下换行**（日常输出用它）；
- `\r` = **回到行首**（原地覆盖/刷新同一行，或配合 `\n` 组成 Windows 的 `\r\n`）。

---

# set 与 map 知识点（关联容器）

> 两者底层都是**红黑树**：元素/键**唯一**且**自动升序排列**。

## 一、set（集合）

`std::set` 存**不重复的元素**，插入重复值会被忽略。头文件：`#include <set>`。

| 操作 | 写法 | 说明 |
|------|------|------|
| 声明 | `set<int> s;` | |
| 插入 | `s.insert(x);` | 重复插入被**忽略** |
| 删除 | `s.erase(x);` | 按键删 |
| 判断存在 | `s.count(x)` | 返回 0 或 1 |
| 查找 | `s.find(x)` | 返回迭代器，`!= s.end()` 即找到 |
| 大小/空 | `s.size()` / `s.empty()` | |
| 遍历 | `for (auto x : s)` | 自动**升序** |

```cpp
set<int> st;
st.insert(5); st.insert(3); st.insert(5);   // st = {3, 5}
if (st.count(3)) cout << "有 3";
```

### 核心用途：**去重**

把多个可能重复的元素丢进 set，自动只剩一份：
```cpp
set<int> st;
for (auto [dx,dy] : dir){                       // 最大人工岛：收集四邻岛编号
    if (是陆地) st.insert(islandId[nx][ny]);   // 同一岛多个邻居 → 只保留一个编号
}
```

## 二、map（键值对）

`std::map` 存**键值对**，**键唯一**、按键升序。头文件：`#include <map>`。

| 操作 | 写法 | 说明 |
|------|------|------|
| 声明 | `map<K,V> m;` | K=键，V=值 |
| 插入/修改 | `m[k] = v;` | 不存在→插入；存在→**覆盖** |
| 只插入不覆盖 | `m.insert({k,v});` | 键已存在则**忽略** |
| 取值 | `m[k]` | ⚠️ 键不存在会**自动插入默认值** |
| 安全取值 | `m.at(k)` | 键不存在抛异常 |
| 判断存在 | `m.count(k)` | 返回 0 或 1 |
| 查找 | `m.find(k)` | `!= m.end()` 即找到 |
| 删除 | `m.erase(k);` | |
| 遍历 | `for (auto& [k,v] : m)` | 结构绑定，按键升序 |

```cpp
map<string,int> score;
score["Tom"] = 90;        // 插入
score["Tom"] = 95;        // 覆盖
score.insert({"Amy",88}); // 插入
score.insert({"Tom",60}); // Tom 已存在 → 忽略

if (score.count("Amy")) cout << score["Amy"];   // 判断存在用 count/find

for (auto& [name, s] : score)                   // 按键升序：Amy, Tom
    cout << name << ": " << s << '\n';
```

### ⚠️ 最常踩的坑：`m[k]` 会自动插入

```cpp
if (m[key])        // 危险！key 不存在时 m[key] 先插入一个默认值条目
```
判断"键是否存在"**必须用 `find` 或 `count`**，不要用 `m[key]`。

## 三、什么时候用哪个

| 场景 | 推荐 |
|------|------|
| 键是**连续整数**（如岛编号 1,2,3...） | **`vector`**（按下标 O(1)，最快） |
| 键**稀疏/非连续**，或需要按键**排序**遍历 | `map`（O(log n)） |
| 只查不改、不要求排序、追求速度 | `unordered_map`（哈希，平均 O(1)） |

> 口诀：**set 管去重，map 管键值；编号连续用 vector，键散有序才上 map。判断存在别用 `[]`，find/count 最稳。**

---

# unordered_set / unordered_map 知识点（哈希容器）

> 底层是**哈希表**：元素/键**唯一**且**无序**，查找/插入/删除**平均 O(1)**。
> 不需要"有序遍历"时优先用它们，比红黑树（set/map）快。

## 一、unordered_set（无序集合，只存键）

头文件：`#include <unordered_set>`。

| 操作 | 写法 | 说明 |
|------|------|------|
| 声明 | `unordered_set<string> s;` | |
| 插入 | `s.insert(x);` | 重复插入被**忽略** |
| 删除 | `s.erase(x);` | |
| 判断存在 | `s.count(x)` | 返回 0 或 1（最常用） |
| 查找 | `s.find(x)` | `!= s.end()` 即找到 |
| 大小/空 | `s.size()` / `s.empty()` | |
| 遍历 | `for (auto x : s)` | **无序**，顺序不定 |
| 清空 | `s.clear();` | |

### 用容器初始化（单词接龙常用）

```cpp
vector<string> strList = {"hot", "dot", "dog", "lot", "log", "cog"};
unordered_set<string> wordSet(strList.begin(), strList.end());  // 一行建好"字典"
if (wordSet.count("dot")) cout << "在字典里\n";                 // 判存在 O(1)
```

### 核心用途：**判存在**（元素唯一、哈希查找快）

```cpp
unordered_set<string> visited;      // 判重：哪些词已入过队
visited.insert(beginStr);
if (!visited.count(nxt)) visited.insert(nxt);
```

## 二、unordered_map 与 map 的区别

| 维度 | `map` | `unordered_map` |
|------|-------|-----------------|
| 底层结构 | 红黑树 | 哈希表 |
| 是否有序 | **有序**（按键升序） | **无序** |
| 查找/插入/删除 | O(log n) | 平均 O(1)，最坏 O(n)（哈希冲突多时） |
| 内存 | 较小 | 较大（桶数组 + 节点） |
| 迭代器 | 插入/删除不失效 | 扩容/rehash 时可能失效 |
| 可用键类型 | 支持 `<` 比较即可 | 需有 `hash<Key>`（自定义类型需自己写） |

> 类比：`map` 像按字母排好序的字典（慢但有序）；`unordered_map` 像按下标直接翻页（快但无序）。
> ⚠️ 竞赛担心被卡哈希时，可用 `map`（O(log n) 稳定）替代。

## 三、怎么选"字典"数据类型

| 需求 | 推荐 |
|------|------|
| 只判断"某词/某键**在不在**"（只要键不要值） | `unordered_set` |
| 需要"键 → 值"（如 词 → 步数）且不要求排序 | `unordered_map` |
| 需要按键**排序**遍历 | `map` / `set` |
| 键是连续整数 | `vector`（最快） |

> 口诀：**判存在用 unordered_set，键值对应上 unordered_map；不排序追求速度就上哈希，要排序才用红黑树。**

---

# 单词接龙（Word Ladder）——不必建邻接矩阵

## 题目要点

- 从 `beginStr` 到 `endStr` 的转换序列，每次只能改**一个字符**
- 中间词必须都在字典 `strList` 中；`beginStr`/`endStr` 不在字典里
- 输出**最短转换序列中的字符串数量**，不存在输出 0
- 求最短 → 用 **BFS**

## 一、为什么不必建邻接矩阵

- **建图思路**：两两比较字典中的词，是否只差一个字符 → 建 $N\times N$ 邻接矩阵，再 BFS
  - 建图复杂度 $O(N^2 \cdot L)$，空间 $O(N^2)$ —— N 大时内存、时间都爆炸
- **推荐思路（枚举 + 哈希）**：BFS 出队时**现场判断**相邻，不提前建图
  - 对当前词的每个位置，替换成 26 个字母，判断替换结果是否在 `unordered_set` 字典里
  - 每个节点 $O(26\cdot L)$，共 $O(N \cdot 26 \cdot L) \approx O(N\cdot L)$，且省内存

```cpp
unordered_set<string> wordSet(strList.begin(), strList.end());
queue<string> q;  q.push(beginStr);
unordered_set<string> visited;  visited.insert(beginStr);

// 扩展一个节点：
for (int i = 0; i < cur.size(); ++i)
    for (char c = 'a'; c <= 'z'; ++c) {
        string nxt = cur;  nxt[i] = c;
        if (wordSet.count(nxt) && !visited.count(nxt)) {
            visited.insert(nxt);
            q.push(nxt);
        }
    }
```

> 更优：**通配符分组**（把每词挖掉一位作 key，如 `*ot`、`h*t`、`ho*`）可建邻接表，$O(N\cdot L)$，便于双向 BFS。

## 二、BFS 如何标记"当前第几步"

### 方法 1：队列里直接存步数（最直观）

```cpp
queue<pair<string,int>> q;
q.push({beginStr, 1});                       // 起始为 1（序列含起点）
while (!q.empty()) {
    auto [cur, step] = q.front(); q.pop();
    if (cur == endStr) { cout << step; return 0; }
    // ...扩展 nxt...
    q.push({nxt, step + 1});
}
```

### 方法 2：unordered_map 记录距离（vis 兼当 dist）

```cpp
unordered_map<string,int> dist;
dist[beginStr] = 1;
// ...
if (wordSet.count(nxt) && !dist.count(nxt)) {
    dist[nxt] = dist[cur] + 1;
    q.push(nxt);
}
// 输出 dist[endStr]（不存在为 0）
```

### 方法 3：分层 BFS（同层共享一个步数）

```cpp
int step = 1;
while (!q.empty()) {
    int sz = q.size();
    while (sz--) { if (front == endStr) { cout << step; return 0; } /* 扩展 */ }
    ++step;
}
```

| 方法 | 特点 |
|------|------|
| 队列存 step | 直观，但每节点多存一个 int |
| dist map | 距离与判重合一，方便输出 |
| 分层 BFS | 适合统计"走了几层" |

> ⚠️ 输出的是**序列中字符串数量**，所以起点步数从 **1** 开始（不是 0）。

> 口诀：**求最短用 BFS；相邻判断枚举+哈希不建图；步数要么入队要么记 dist、要么按层数。**
