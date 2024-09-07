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
auto lsh(vector<T>& A) {// return lsh's function
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    return [&](const T& x) {
        return lower_bound(A.begin(), A.end(), x)-A.begin();
    };
}

template<class T>
struct Bit {// index-0
    int n;
    vector<T> sum;
    vector<int> path;
    Bit(int n): n(n), sum(n) {}
    void change(int p, T x) {
        path.push_back(p);
        for(++p; p<=n; p+=p&-p) {
            sum[p-1] = max(sum[p-1], x);
        }
    }
    T query(int p) {
        T res = 0;
        for(++p; p>0; p-=p&-p)
            res = max(res, sum[p-1]);
        return res;
    }
    void clear() {
        for(int p:path) {
            for(++p; p<=n; p+=p&-p) {
                sum[p-1] = 0;
            }
        }
        path.clear();
    }
};

constexpr int N = 5e5 + 10;
Bit<ll> tr(N);
int n;
ll x0[N], x[N], y[N];// !!! xi=xj怎么办? done
ll f[N];
ll g[N];

int tmp[N], id[N];
int cmp(int i, int j) {// main sort
    if(x[i] != x[j])
        return x[i]<x[j];
    return y[i] < y[j];
}
void cdq0(int l, int r) {
    if (l==r) return;
    int mid=(l+r)>>1;
    cdq0(l, mid), cdq0(mid+1, r);
    tr.clear();
    for (int k=l, i=l, j=mid+1; k<=r;) {
        if (j>r || (i<=mid && y[id[i]] < y[id[j]])) {
            tr.change(x[id[i]], y[id[i]]);
            tmp[k++]=id[i++];
        } else {
            // xk < xj
            if(x[id[j]]) f[id[j]] = max(f[id[j]], tr.query(x[id[j]]-1));
            tmp[k++]=id[j++];
        }
    }
    copy(tmp+l, tmp+r+1, id+l);
}
void cdq1(int l, int r) {
    if (l==r) return;
    int mid=(l+r)>>1;
    cdq1(l, mid), cdq1(mid+1, r);
    tr.clear();
    for (int k=l, i=l, j=mid+1; k<=r;) {
        if (j>r || (i<=mid && y[id[i]] < y[id[j]])) {
            tr.change(x[id[i]], f[id[i]]);
            tmp[k++]=id[i++];
        } else {
            // xk < xj
            if(x[id[j]]) g[id[j]] = max(g[id[j]], tr.query(x[id[j]]-1));
            tmp[k++]=id[j++];
        }
    }
    copy(tmp+l, tmp+r+1, id+l);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        cin>>n;
        for(int i=1; i<=n; ++i) {
            cin>>x0[i]>>y[i];
            id[i] = i;
            f[i] = g[i] = 0;
        }
        vector<ll> A(x0+1,x0+1+n);
        auto ls = lsh(A);
        for(int i=1; i<=n; ++i)
            x[i] = ls(x0[i]);

        sort(id+1, id+1+n, cmp);
        cdq0(1,n);

        sort(id+1, id+1+n, cmp);
        cdq1(1,n);

        [&](){

        debug(f+1, n);
        debug(g+1, n);
        for(int i=1; i<=n; ++i) {
            if(g[i] > x0[i]) {
                cout<<"NO\n";
                return;
            }
        }
        cout<<"YES\n";

        }();
    }
    return 0;
}
/*
https://codeforces.com/gym/105104/problem/H

对于这题的思路假了，不过练习了cdq
判断是否存在 xi<xj<xk<yi<yj<yk
fi = max yj 满足 xj<xi , yj<yi
gi = max fj .st. xj<xi , yj<yi
for i in [1,n], judge gi>xi

*/