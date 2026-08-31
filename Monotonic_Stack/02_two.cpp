/*给你两个 没有重复元素 的数组 nums1 和 nums2 ，其中nums1 是 nums2 的子集。
请你找出 nums1 中每个元素在 nums2 中的下一个比其大的值。
nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置的右边的第一个比 x 大的元素。如果不存在，对应位置输出 -1 。
示例 1:
输入: nums1 = [4,1,2], nums2 = [1,3,4,2].
输出: [-1,3,-1]
解释:
对于 num1 中的数字 4 ，你无法在第二个数组中找到下一个更大的数字，因此输出 -1 。
对于 num1 中的数字 1 ，第二个数组中数字1右边的下一个较大数字是 3 。
对于 num1 中的数字 2 ，第二个数组中没有下一个更大的数字，因此输出 -1 */

#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
using namespace std;

vector<int> nextGreaterNum(const vector<int>& num1,const vector<int>& num2){
    vector<int> result(num1.size(),-1);
    unordered_map<int,int> umap;
    stack<int> sta;
    for(int i=0;i<num1.size();i++){
        umap[num1[i]] = i;
    }

    if(num1.size()==0) return result;
    sta.push(0);
    for(int i=1;i<num2.size();i++){
        while(!sta.empty() && num2[i]>num2[sta.top()]){
            if(umap.count(num2[sta.top()])){
                int index = umap[num2[sta.top()]];
                result[index] = num2[i];
            }
            sta.pop();
        }
        sta.push(i);
    }

    return result;
}

int main(){
    vector<int> num1,num2;
    int num,n;
    cin>>n;
    while(n--){
        cin>>num;
        num1.push_back(num);
    }
    cin>>n;
    while(n--){
        cin>>num;
        num2.push_back(num);
    }
    vector result = nextGreaterNum(num1,num2);
    for(int v : result){
        cout<<v<<' ';
    }

    return 0;
}