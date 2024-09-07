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
    int tt;
    cin>>tt;
    while(tt--) {
        int n,c,k;
        cin>>n>>c>>k;
        string s;
        cin>>s;

        const int all = (1<<c)-1;
        vector<int> cnt(c);
        vector<int> dp(1<<c);
        for(int i=0, j=0, cur = 0, w; i+k<=n; ++i) {
            while(j<i+k) {
                if(++cnt[w = s[j]-'A'] == 1) {
                    cur ^= 1<<w;
                }
                j++;
            }
            if(i) {
                if(--cnt[w = s[i-1]-'A'] == 0) {
                    cur ^= 1<<w;
                }
            }
            dp[cur ^ all] = 1;
        }

        int ans = c;
        for(int i=(1<<c)-1; i>=0; --i) {
            for(int j=0; j<c; ++j) {
                dp[i] |= dp[i|1<<j];
            }
            if(!dp[i] and (i>>(s.back()-'A')&1)) {
                ans = min(ans, std::__popcount(i));
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
/*
https://codeforces.com/contest/1995/problem/D
正难则反，考虑什么样的结果无法满足条件：
状态 A 在s串中某个长度为k的子串中一个子也没占 <=> 状态A不合法
枚举 k-子串，对应二进制状态为 A，那么 ~A 及其子串都不合法

*/