/*
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> nums(1,0);
    while(n--){
        int num;
        cin>>num;
        nums.push_back(num);
    }
    nums.push_back(0);

    stack<int> sta;
    int result = 0;
    for(int i=0;i<nums.size();i++){
        while(!sta.empty() && nums[i] < nums[sta.top()]){
            int height = nums[sta.top()];
            sta.pop();
            int length = i-sta.top()-1;
            result = max(result,height*length);
        }
        sta.push(i);
    } 

    cout<<result;
    return 0;
}