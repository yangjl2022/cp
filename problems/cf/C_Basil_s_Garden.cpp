#include "bits/stdc++.h"
#ifndef YJL
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
        vector<int> a(n);
        cin>>a;
        int cur = 0, ans = 0;
        for(int i=n-1; i>=0; --i) {
            cur = max(a[i], cur+1);
            ans = max(ans, cur);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
/*
https://codeforces.com/contest/1987/problem/C
依次从后往前考虑，每个h[i]什么时候变成0?
if 后一个花的时间 < h[i]:
    相当于后面的没影响
    ans[i] = h[i]
else:
    h[i] 会在 某个时刻和 h[i+1] 相同
    ans[i] 会比 ans[i+1] 多一步
ans[i] = max(h[i], ans[i+1]+1)
*/