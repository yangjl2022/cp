#include<iostream>
#include<cmath>
#include<cstring>
#include<cassert>
#include<string>
#include<queue>
#include<deque>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<vector>
#include<set>
#include<unordered_set>
#include<bitset>
#include<climits>
#include<numeric>
#include<functional>
#include<iomanip>
#ifdef YJL
#include<debug.h>
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<class T>
void chMin(T &a, T b) {
    a=min(a,b);
}
template<class T>
void chMax(T &a, T b) {
    a=max(a,b);
}

constexpr int N = 5e3 + 10;
int n;
vector<vector<ll>> solve(vector<int> a) {
    vector<vector<ll>> f(n, vector<ll>(n*2+1));
    for(int i=0; i<n; ++i) {
        ll s=0;
        for(int j=i; j<n; ++j) {
            s+=a[j];
            chMax(f[i][j-i], s);
        }
    }
    for(int i=0;i<n;++i) {
        for(int j=1; j<=n*2; ++j) {
            if(i) chMax(f[i][j], f[i-1][j-1]);
            chMax(f[i][j], f[i][j-1]);
        }
    }
    return f;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;++i) cin >> a[i];
    auto f=solve(a);
    reverse(a.begin(), a.end());
    auto g=solve(a);
    ll ans=0;
    for(int i=0; i<n; ++i) {
        ll s=0;
        for(int j=1; j<=2*n; ++j) {
            ll t=max(f[i][j], g[n-1-i][j]);
            debug(i,j,t);
            s^=t*j;
        }
        s+=i+1;
        ans^=s;
    }
    cout << ans << "\n";
    return 0;
}
/*
ICPC 武汉邀请赛
https://codeforces.com/gym/105143/problem/D

利用前缀和更新答案

*/