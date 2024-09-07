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

constexpr int N = 2e5 + 10;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    
    vector<ll> d(n+10);
    auto add0 = [&](int l, int v, int dx) {
        d[l] += v;
        d[l+1] += dx-v;
    };
    auto add = [&](int l, int r, int v, int dx) {
        // a[l] += v
        // a[l+1] += v+dx
        // a[r] += v+dx*(r-l)

        // one diff: v,dx,dx,.., -v-dx*(r-l)
        // two diff: v, dx-v, 0,0,...
        add0(l, v, dx);
        add0(r+1, -v-dx*(r+1-l), -dx);
    };

    while(m--) {
        int op,p,c;
        cin>>op>>p>>c;
        int l = max(1, p-c+1);
        int r = min(n, p+c-1);
        if(l < p) add(l, p-1, (c-(p-l))*op, op);
        add(p, r, c*op, -op);
    }

    for(int i=1; i<=n; ++i) d[i]+=d[i-1];
    for(int i=1; i<=n; ++i) d[i]+=d[i-1],cout<<d[i]<<" ";
    
    return 0;
}
/*

https://ac.nowcoder.com/acm/contest/82758?from=acm_calendar

静态区间加等差数列
两次差分解决


*/