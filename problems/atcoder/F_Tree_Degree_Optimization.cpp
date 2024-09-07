#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

struct Node {
    ll w, w0;  
    bool operator<(Node const & o) const {
        return w > o.w;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n);
    priority_queue<Node> q;
    ll ans = 0;
    for(int i=0; i<n; ++i) {
        cin>>a[i];
        ans += a[i];
        q.push({a[i]*3ll, a[i]});
    }

    for(int i=0; i<n-2; ++i) {
        auto [w, w0] = q.top();
        q.pop();
        ans += w;
        q.push({w+w0*2, w0});
    }
    cout<<ans;
    return 0;
}
/*

https://atcoder.jp/contests/abc359/tasks/abc359_f
树的度
若干个有序数组选数，总和最小
优先队列

*/