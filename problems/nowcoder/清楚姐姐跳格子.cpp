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
    assert(1 <= tt and tt <= 100);
    int sn = 0;
    while(tt--) {
        int n;
        cin >> n;
        assert(1 <= n and n <= 5000);
        sn += n;
        assert(1 <= sn and sn <= 5000);

        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            assert(1 <= a[i] and a[i] <= n);
        }

        vector<int> dp(n + 1, n + 2);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            vector<int> vis(n + 1);
            for(int j = i; j < n; ++j) {
                vis[a[j]] = 1;
                if(vis[j + 1 - i]) {
                    dp[j + 1] = min(dp[j + 1], dp[i] + 1);
                }
            }
        }
        cout << (dp[n] > n ? -1 : dp[n]) << "\n";
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87652/D
整个问题可以分解子问题：
- 假设最优解选择的布告大小从左到右依次为 s1,s2,...,sm
- 那么我们去掉最后一个 sm，可以变成 [1, n-sm] 的子问题，最优解为 s1,s2,..,s_{m-1}

考虑DP
dp[i] 表示前i个布告这一子问题的最优解
那么可以转移：dp[i]+1 -> dp[j],if a[i+1],..,a[j] 中存在 j-i 大小的布告

*/