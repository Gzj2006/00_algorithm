/*题目描述
字典 strList 中从字符串 beginStr 和 endStr 的转换序列是一个按下述规格形成的序列：
序列中第一个字符串是 beginStr。
序列中最后一个字符串是 endStr。
每次转换只能改变一个位置的字符（例如 ftr 可以转化 fty ，但 ftr 不能转化 frx）。
转换过程中的中间字符串必须是字典 strList 中的字符串。
beginStr 和 endStr 不在 字典 strList 中
字符串中只有小写的26个字母
给你两个字符串 beginStr 和 endStr 和一个字典 strList，找到从 beginStr 到 endStr 的最短转换序列中的字符串数目。
如果不存在这样的转换序列，返回 0。
输入描述
第一行包含一个整数 N，表示字典 strList 中的字符串数量。 第二行包含两个字符串，用空格隔开，分别代表 beginStr 和 endStr。
后续 N 行，每行一个字符串，代表 strList 中的字符串。
输出描述
输出一个整数，代表从 beginStr 转换到 endStr 需要的最短转换序列中的字符串数量。如果不存在这样的转换序列，
则输出 0。
思路结论
判断两个字符串是否相邻，优先用「枚举 + 哈希」：
1. 对当前字符串每个位置，用 26 个字母替换，判断替换后是否在字典 strList 中（unordered_set 查找 O(1)）。
2. BFS 中每个节点处理 O(26*L) 次替换，最多访问 N 个节点，总复杂度 O(N*26*L) ≈ O(N*L)。
相比「两两比较建图」的 O(N^2*L)，当 N 较大时优势明显；且无需预先建图，省内存。
*/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>
using namespace std;

int main(){
    string beStr,enStr,cStr;
    int N;
    unordered_set<string> dict,visited;
    cin>>N;
    cin>>beStr>>enStr;
    if(beStr==enStr){
        cout<<1;
        return 0;
    }
    for(int i=0;i<N;i++){
        cin>>cStr;
        dict.insert(cStr);
    }

    queue<pair<string,int>> que;
    que.push({beStr,1});
    visited.insert(beStr);
    while(!que.empty()){
        auto[cur,step]=que.front();
        que.pop();
        for(size_t i=0;i<cur.size();i++){
            for(char c='a';c <= 'z';c++){
                string nxt=cur;
                nxt[i]=c;
                if(nxt==cur) continue;
                if(nxt==enStr){
                    cout<<step+1;
                    return 0;
                }
                if(dict.count(nxt)&&!visited.count(nxt)){
                    que.push({nxt,step+1});
                    visited.insert(nxt);
                }
            }
        }
    }
    cout<<0;
}