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
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        cin>>n;
        vector<int> a(n+1, -1);
        for(int i=1; i<=n; ++i) {
            cin>>a[i];
        }

        ll ans = 1;
        for(int i=1,lst=0,ban=0; i<=n; ++i) {
            if(a[i] < a[i-1]) ans = 0;
            if(a[i]!=a[i-1]) {
                if(a[i] == 0) continue;
                ban++;
                for(int j=lst; j<a[i]-1; ++j) {
                    // debug(j, i, ban);
                    if(i-ban < 0) ans = 0;
                    ans = ans * (i-ban)%998244353;
                    ban++;
                }
                lst = a[i];
            }
        }
        if(a[n]!=n) ans = 0;
        cout<<ans<<"\n";
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/82758?from=acm_calendar

mex相关，方案数



*/