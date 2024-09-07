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
    for(auto& x : v) is >> x;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin >> tt;
    while(tt--) {
        int n, m, t;
        cin >> n >> m >> t;
        assert(1 <= m and m < n and n <= int(2e5));
        assert(1 <= t and t <= int(2e5));

        if(t < n) {
            cout << "0\n";
            continue;
        }

        vector<int> a(m);
        cin >> a;
        sort(ALL(a));
        assert(unique(ALL(a)) == a.end());
        for(int x : a) {
            assert(1 <= x and x < n);
        }

        vector<int> d;
        for(int i = 1; i < m; ++i) {
            d.push_back(a[i] - a[i - 1]);
        }
        sort(ALL(d));
        d.erase(unique(ALL(d)), d.end());

        int extra = t - n;
        vector<int> dp(extra + 1);
        dp[0] = 1;
        for(int x : d) {
            x *= 2;
            if(x > extra) continue;
            for(int i = x; i <= extra; ++i) {
                dp[i] |= dp[i - x];
            }
        }
        for(int i = extra; i >= 0; --i) {
            if(dp[i]) {
                cout << n + i << "\n";
                break;
            }
        }
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/88455/F
思维，结论，完全背包DP

n的距离是固定的，所以题目就是要尽量多消耗 t-n 这一余量距离。
考虑到在非相邻的两面墙壁间徘徊，等价于分成若干段来徘徊
所以只考虑相邻两面墙的间距，设为d，那么可操作的空间就是若干个 2d（徘徊一次）
注意到 sum(d) <= n，所以 d 的种类树只有根号种
去重后通过完全背包可以 O(nsqrt(n)) 的解决此问题

也可以 分治NTT和多项式求逆 O(nlognlogn)
*/