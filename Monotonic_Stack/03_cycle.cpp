/*给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。

示例 1:

输入: [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；数字 2 找不到下一个更大的数；第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
提示:

1 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
*/

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> nums(n,0);
    vector<int> nextG(n,-1);
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        nums[i] = num;
    }

    stack<int> sta;
    for(int i=0;i<2*nums.size();i++){
        int cur = i%nums.size();
        while(!sta.empty() && nums[cur]>nums[sta.top()]){
            nextG[sta.top()] = nums[cur];
            sta.pop();
        }
        if(i<n) sta.push(cur);
    }

    for(int i :nextG){
        cout<<i<<' ';
    }
}
