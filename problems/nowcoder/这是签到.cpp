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


int n,m;
ll a[6][6], b[6][6];
// 求行列式对非质数取模 或者 不取模
ll det(ll a[][6], int n) {
    ll ans = 1;
    for (int i=1; i<=n; ++i)
        for (int j=i+1; j<=n; ++j) {
            while (a[i][i]) {
                int div = a[j][i] / a[i][i];
                for (int k=i; k<=n; ++k) {
                    a[j][k]=(a[j][k]-a[i][k]*div);
                }
                swap(a[i], a[j]);
                ans=-ans;
            }
            swap(a[i], a[j]);
            ans=-ans;
        }
    for (int i=1; i<=n; ++i) ans*=a[i][i];
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m; ++j) {
            cin>>a[i][j];
        }
    }
    n = max(n, m);
    ll ans = 4e18;
    for(int i=1; i<=n; ++i) {
        memcpy(b, a, sizeof a);
        ans = min(ans, det(b, i));
    }
    cout<<ans;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87255/J
行列式板子

*/