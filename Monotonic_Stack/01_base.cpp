/* 请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。

例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。*/

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

void UpStack(const vector<int>& temp,vector<int>& result){
    stack<int> sta;
    sta.push(0);
    for(int i=1;i<temp.size();i++){
        while(!sta.empty() && temp[i]>temp[sta.top()])
        {
            result[sta.top()] = i-sta.top();
            sta.pop();
        }
        sta.push(i);
    }
}

int main(){
    vector<int> temp;
    int tem;
    while(cin>>tem){
        temp.push_back(tem);
    }
    vector<int> result(temp.size(),0);
    UpStack(temp,result);
    for(auto i: result){
        cout<<i<<' ';
    }
    return 0;
}