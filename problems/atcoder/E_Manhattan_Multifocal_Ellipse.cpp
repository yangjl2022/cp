/**
 *    author:  yangjl
 *    created: 2024.10.08 20:04:18
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
    int n, D;
    cin >> n >> D;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    sort(ALL(x));
    sort(ALL(y));
    vector<ll> prefx(n + 1), prefy(n + 1);
    for(int i = 0; i < n; ++i) {
        prefx[i + 1] = prefx[i] + x[i];
        prefy[i + 1] = prefy[i] + y[i];
    }

    auto cal = [&](vector<int>& xs, vector<ll>& pref, int p) {
        int i = lower_bound(ALL(xs), p) - xs.begin();
        // (p-xj) for j<i
        // (xj-p) for j>=i
        return 1ll * i * p - pref[i] - 1ll * (n - i) * p + pref.back() - pref[i];
    };

    vector<int> cntx(D + 1), cnty(D + 1);
    constexpr int bound = 3e6;
    for(int i = -bound; i <= bound; ++i) {
        ll t = cal(x, prefx, i);
        if(t >= 0 and t <= D) {
            cntx[t]++;
        }
        t = cal(y, prefy, i);
        if(t >= 0 and t <= D) {
            cnty[t]++;
        }
    }

    partial_sum(ALL(cnty), cnty.begin());
    ll ans = 0;
    for(int i = 0; i <= D; ++i) {
        ans += 1ll * cntx[i] * cnty[D - i];
    }
    cout << ans;
    return 0;
}
/*
https://atcoder.jp/contests/abc366/tasks/abc366_e
思维，前缀和，枚举

sum(|x-x_i|) + sum(|y0-y_i|) <= D
注意到 x,y 两维度的计算互不影响，可以先分别考虑
D,x,y 都是 1e6级别
所以选择的 x,y 范围也是 1e6 级别
可以枚举所有 x 的可能取值，判断 sum(|x-x_i|) 是否 \in [0,D]，如果是，那么它可能对应了一个 y
对于合法的 x 按 sum(|x-x_i|) 分类，统计 count
对于合法的 y 同理
最后对满足 u+v<=D 的 cntx[u] 和 cnty[v] 进行组合即可。
*/