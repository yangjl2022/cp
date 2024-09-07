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
template<class T>
void chMin(T &a, T b) {
    a=min(a,b);
}
template<class T>
void chMax(T &a, T b) {
    a=max(a,b);
}


constexpr int inf = numeric_limits<int>::max();
int solve(vector<int> a) {
    int n = a.size()/2;
    int lbound = a[0]+a[1];
    auto ok = [&](int x) {
        return x>=lbound;
    };
    debug(lbound, a);

    vector<array<int,2>> f(n, array<int,2>{inf, inf});
    f[1] = {lbound, inf};
    for(int i=2; i<n; ++i) {
        for(int j=0; j<2; ++j) {
            if(j == 1) swap(a[i-1], a[i-1 + n]);

            for(int k=0; k<2; ++k) {
                if(k == 1) swap(a[i], a[i+n]);

                if(i%2 == 0) {
                    if(ok(a[i-1+n]+a[i+n]))
                        f[i][k] = min(f[i][k], max(f[i-1][j], a[i-1+n]+a[i+n]));
                }else {
                    if(ok(a[i-1]+a[i]))
                        f[i][k] = min(f[i][k], max(f[i-1][j], a[i-1]+a[i]));
                }

                if(k == 1) swap(a[i], a[i+n]);
            }

            if(j == 1) swap(a[i-1], a[i-1 + n]);
        }
    }
    debug(f);

    int ans = inf;
    if(ok(a[n-1] + a[n]))
        chMin(ans, max(f[n-1][0], a[n-1] + a[n]));
    if(ok(a[n-1 + n] + a[n]))
        chMin(ans, max(f[n-1][1], a[n-1 + n] + a[n]));
        
    debug(ans, lbound);
    
    if(ans >= inf) return inf;// fixed bug0
    return ans - lbound;// !!! bug0
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        cin>>n;
        vector<int> a(n*2);
        cin>>a;
        if(n == 1) {
            cout<<"0\n";
            continue;
        }

        if(n%2 == 0) {
            int mn = numeric_limits<int>::max();
            int mx = numeric_limits<int>::min();
            for(int i=0; i<n; i+=2) {
                ll s = 0ll + a[i] + a[i+1] + a[i+n] + a[i+n+1];
                int v0[2]{a[i]+a[i+1], a[i+n]+a[i+n+1]};
                int v1[2]{a[i]+a[i+n+1], a[i+n]+a[i+1]};
                sort(v0,v0+2);
                sort(v1,v1+2);
                int t = max(v0[0], v1[0]);
                int t2 = s - t;
                chMin(mn, t);
                chMax(mx, t2);
            }
            cout<<mx-mn<<'\n';
        }else {
            // cout<<"-1\n";
            int ans = 2e9;
            for(int i=0; i<n; ++i) {
                for(int j0=0; j0<2; ++j0) {
                    for(int j1=0; j1<2; ++j1) {
                        ans = min(ans, solve(a));
                        swap(a[1], a[n+1]);
                    }
                    swap(a[0], a[n]);
                }
                rotate(a.begin(), a.begin()+2, a.end());
            }
            cout<<ans<<'\n';
        }
    }
    return 0;
}
/*
https://codeforces.com/contest/1995/problem/E1
思维，DP
偶数情况易解
奇数情况，拆开环，枚举最小值所处位置，其他的数对都要大于这个值
环变成了链，可以DP记录这一路来满足所有数对大于起点，且最大值最小是多少

*/