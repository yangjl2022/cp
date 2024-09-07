/**
 *    author:  yangjl
 *    created: 2024.18.08 19:07:30
**/
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
    for(auto& x : v) {
        is >> x;
    }
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        sort(ALL(a));

        ll ans = -1;
        for(int i = 1; i + 1 < n; ++i) {
            int s = a[i] + a[i - 1];
            int j = --lower_bound(ALL(a), s) - a.begin();
            if(j > i) {
                ans = max(ans, 0ll + a[i] + a[i - 1] + a[j]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/88392/D
贪心，三角形构造

不妨先排序，那么选择 i<j<k 构成三角形 <=> a[i]+a[j]>a[k]
假设 i,j 不相邻，可以选择 i+1，这样得到的答案 a[i+1]+a[j]+a[k] >= a[i]+a[j]+a[k]，并且三角形条件依然满足
于是 j=i+1，考虑枚举 i, 剩下的 k 贪心找 小于 a[i]+a[j] 的最大值即可

*/