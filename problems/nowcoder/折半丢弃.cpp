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
        int n;
        cin>>n;
        vector<int> vis(n+1);
        int p = 0;
        for(int i=0, x; i<n; ++i) {
            cin>>x;
            while(x != 0 and (x >= n or vis[x])) {
                x /= 2;
            }
            vis[x] = 1;
        }

        for(int i=n-1; i>=0; --i) {
            if(!vis[i]) continue;
            while(vis[p]) p++;
            if(i+1 == p) break;

            vis[i] = 0;
            int x = i/2;
            while(x != 0 and vis[x]) {
                x /= 2;
            }
            vis[x] = 1;
        }
        cout<<p<<'\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/86387/E
mex
从大到小贪心

也可以二分答案再贪心

*/