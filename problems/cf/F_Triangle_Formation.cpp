#include <bits/stdc++.h>
#ifdef YJL
#include "debug.h"
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    cin>>a;
    while(q--) {
        int l,r;
        cin>>l>>r;
        --l,--r;
        int m = r-l+1;
        if(m >= 200) {
            cout<<"YES\n";
            continue;
        }

        vector<int> v(a.begin()+l, a.begin()+r+1);
        sort(ALL(v));
        
        [&](){
            int head = -1;
            for(int i=0; i+2<m; ++i) {
                if(v[i]+v[i+1]>v[i+2]) {
                    if(head == -1) {
                        head = i+2;
                    }else if(i> head) {
                        cout<<"YES\n";
                        return;
                    }
                }
                if(i+5 < m) {
                    if(v[i+1] + v[i+2] > v[i+3] and v[i] + v[i+4] > v[i+5]
                    or v[i+0] + v[i+2] > v[i+3] and v[i+1] + v[i+4] > v[i+5]
                    or v[i+0] + v[i+3] > v[i+4] and v[i+1] + v[i+2] > v[i+5]
                    ) {
                        cout<<"YES\n";
                        return;
                    }
                }
            }
            cout<<"NO\n";
        }();
    }
    return 0;
}
/*
https://codeforces.com/contest/1991/problem/F
思维
首先对 a[l],..,a[r]排序考虑
假设我们从左到右依次考虑相邻的三个数组成三角形：
- a[i] + a[i+1] > a[i+2]
找到最小的这样的 i，必定有 i<=100，因为如果一直有 a[i] + a[i+1] <= a[i+2]，
那么该数列的元素一定依次 >= fibonacci数列，100次以后肯定超过了 1e18
所以100个元素必定能组成一个三角形，那么200个元素一定能组成两个

现在考虑元素数量 < 200 的情况
对于所选元素 b0,b1,b2,b3,b4,b5 必定满足以下情况之一：
1. b0 + b1 > b2, b3 + b4 > b5
2. b1 + b2 > b3, b1 + b4 > b5
3. b0 + b2 > b3, b1 + b4 > b5
4. b0 + b3 > b4, b1 + b2 > b5

然后贪心的考虑：
对于情况1, b0,b1,b2 要在 a 中连续，b0,b1,b2 要在 a 中连续，最优
对于情况234，b0,b1,b2,b3,b4,b5 在 a 中连续最优

*/