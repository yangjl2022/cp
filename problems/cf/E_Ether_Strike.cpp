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
struct Bit {// index-0
    int n;
    vector<T> sum;
    Bit(int n): n(n), sum(n) {}
    void change(int p, T x) {
        for(++p; p<=n; p+=p&-p) sum[p-1]+=x;
    }
    T query(int p) {
        T res=0;
        for(++p; p>0; p-=p&-p) res+=sum[p-1];
        return res;
    }
    T query(int l, int r) {
        return query(r)-query(l-1);
    }
};

constexpr int N = 2e5 + 10;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; ++i) {
        cin>>a[i];
    }
    int m;
    cin>>m;
    vector<pair<int,int>> b(m);
    for(auto& [p,c]:b) {
        cin>>p>>c;
        --p;
    }

    vector<int> l(n,0), r(n,m-1), ans(n, m);
    vector<pair<int,int>> alls;// (mid, index)
    for(int i=0; i<n; ++i) 
        alls.emplace_back((l[i]+r[i])/2, i);

    while(alls.size()) {
        sort(ALL(alls),[&](const auto& x,const auto& y){
            return x.first < y.first;
        });

        Bit<ll> t0(n), t1(n);
        auto add = [&](int s, ll a, ll d) {
            t0.change(s, a);
            t1.change(s, a*(s-1));
            t0.change(s+1, d-a);
            t1.change(s+1, (d-a)*s);
        };

        vector<pair<int,int>> re;
        for(int i=0,j=0; i<m; ++i) {
            auto& [p, c] = b[i];
            {
                int l = max(0, p-c+1), r = min(n-1, p+c-1);
                add(l, c-(p-l), 1);
                add(p+1, -c-1, -1);
                if(p < r) {
                    add(p+1, c-1, -1);
                    add(r+1, -(c-(r-p)-1), 1);
                }
            }

            for(; j<alls.size() and alls[j].first == i; ++j) {
                auto const& [mid, p] = alls[j];
                ll val = a[p] - (p*t0.query(p) - t1.query(p));
                if(val <= 0) {
                    ans[p] = mid;
                    r[p] = mid-1;
                }else {
                    l[p] = mid + 1;
                }
                if(l[p] <= r[p]) re.emplace_back((l[p]+r[p])/2, p);
            }
        }
        alls = move(re);
    }

    vector<int> sum(m+1);
    for(int i=0; i<n; ++i) {
        sum[ans[i]]++;
    }

    for(int i=0; i<m; ++i) {
        if(i) sum[i] += sum[i-1];
        cout<<sum[i]<<" ";
    }
    return 0;
}
/*

整体二分
树状数组维护区间加等差数列

init    :x,x+d,x+2d,...
one diff:x,d,d,d,....
two diff:x,d-x,0,0,...

a[i] = sum_{j<=i} sum_{k<=j} p[k]
     = sum_{k<=i} p[k] * (i-k+1)
     = i* sum p[k] - sum p[k]*(k-1)

https://codeforces.com/gym/518619/problem/E

*/