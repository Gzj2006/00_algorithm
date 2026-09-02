//给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main(){
    int n,hei;
    vector<int> height;
    cin>>n;
    while(n--){
        cin>>hei;
        height.push_back(hei);
    }

    stack<int> sta;
    int result = 0;
    for(int i=0;i<height.size();i++){
        while(!sta.empty() && height[i]>height[sta.top()]){
            int low = sta.top();
            sta.pop();
            if(sta.empty()) break;
            result += (i-sta.top()-1) * (min(height[sta.top()],height[i]) - height[low]);
        }
        sta.push(i);
    }
    cout<<result;
    return 0;
}