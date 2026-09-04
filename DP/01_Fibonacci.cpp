//斐波那契数列

#include<iostream>
using namespace std;

int main(){
    int n;
    int num[2];
    cin>>n;
    num[0] = 1;
    num[1] = 1;
    if(n==1) cout<<1;
    if(n==2) cout<<2;
    int sum = 0;
    for(int i=3;i<=n;i++){
        sum = num[0] + num[1];
        num[0] = num[1];
        num[1] = sum;
    }
    cout<<sum;
    return 0;
}