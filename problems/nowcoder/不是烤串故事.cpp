/**
 *    author:  yangjl
 *    created: 2024.18.08 19:24:09
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

// z[i]表示 s 和 s[i:] 匹配的最大长度
vector<int> zfunc(const string& s) {
    int n = s.size();
    vector<int> z(n);
    for(int i = 1, l = 0, r = 0; i < n; i++) {
        if(i <= r) z[i] = min(z[i - l], r - i + 1);
        while(i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    z[0] = n;
    return z;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        string s, t;
        cin >> n >> s >> t;
        vector<int> f(n + 1);
        for(int i = n - 1; i >= 0; --i) {
            if(s[i] == t[i]) {
                f[i] = f[i + 1] + 1;
            }
        }
        auto z = zfunc(t + string(s.rbegin(), s.rend()));

        int ml = 0, index = 0;
        for(int i = 0; i < n; ++i) {
            // s0-si, s[i+1]-s[n-1]
            // => si-s0, s[i+1]~s[n-1]
            int l = z[2 * n - 1 - i];
            if(l == i + 1) {
                l += f[i + 1];
            }
            if(l > ml) {
                ml = l;
                index = i;
            }
        }

        cout << ml << " " << index + 1 << '\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/88392/F
字符串算法，Z函数，
卡哈希？

按题意，枚举每个位置，计算 lcp 即可，使用 Z 函数，一点构造技巧，可以 O(n) 预处理出 s[i]~s[0] 这个串和 t 的 LCP
剩余部分的匹配，由于匹配起始的下标相同，可以提前从后往前扫描一遍预处理好。
复杂度：O(n)

方法二（WA了部分数据，可能卡哈希，尝试过换模数和底数，依旧没过）
使用哈希+二分计算 LCP，依据题意来即可
复杂度：O(nlogn)
*/