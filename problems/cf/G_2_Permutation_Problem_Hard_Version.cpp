#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        cin>>n;
        vector fac(n+1, vector<int>());
        for(int i=n; i>=1; --i) {
            for(int j=i; j<=n; j+=i) {
                fac[j].push_back(i);
            }
        }

        ll n1 = 0;
        vector fz(n+1, vector<int>());
        vector fm(n+1, vector<int>());
        for(int i=0,a; i<n; ++i) {
            cin>>a;
            // a[i] = i+1;
            int b = i+1;
            int g = gcd(a, b);
            a /= g;
            b /= g;
            n1 += b == 1;
            fz[b].push_back(a);
            fm[a].push_back(b);
        }

        ll ans = 0;
        vector<int> cnt(n+1);
        for(int i=1; i<=n; ++i) {
            for(int j=i; j<=n; j+=i) {
                for(int b2:fm[j]) {
                    cnt[b2]++;
                }
            }
            for(int a:fz[i]) {
                for(int b2:fac[a]) {
                    ans += cnt[b2];
                }
            }
            for(int j=i; j<=n; j+=i) {
                for(int b2:fm[j]) {
                    cnt[b2]--;
                }
            }
        }
        cout<< (ans-n1)/2<<'\n';
    }
    return 0;
}
/*
https://codeforces.com/contest/1986/problem/G2
a1/b1 * a2/b2 是整数
两边除掉gcd之后满足：b1|a2, b2|a1
枚举 b1 的倍数 a2，统计 b2 的情况，然后枚举 a1 的因子统计答案
注意到所有 a 被枚举作为倍数的总次数等于 sum(a的因子数) <= sum_{i=1~n}(i的因子数) = nlogn
“枚举 a1 的因子” 复杂度同理
*/