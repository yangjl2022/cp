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
// #include<bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Tree;

template<class T>
auto lsh(vector<T>& A) {// return lsh's function
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    return [&](const T& x) {
        return lower_bound(A.begin(), A.end(), x)-A.begin();
    };
}

constexpr int N = 1e5 + 10, SQ = 400;
constexpr int prm[10] = {9,31,183,381,861,1771,1953,2217,2319,2493};
const ll P = prm[5]+ll(1e18);
constexpr int X = 131;
ll mul(ll a, ll b) {
    ll c = (ll)a * b - (ll)((long double) a / P * b + 0.5L) * P;
    return c<0 ? c+P : c;
}
ll norm(ll x) {
    return x<0?x+P:x>=P?x-P:x;
}
ll powX[N];

int n,m;
string s[N];
ll h[N];
map<ll, Tree> mp[SQ];

struct Node {
    int op,l,r;
    string s;
};

vector<ll> pref[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    powX[0] = 1;
    for(int i=1; i<N; ++i) {
        powX[i] = mul(powX[i-1], X);
    }

    cin>>n>>m;
    for(int i=0; i<n; ++i) {
        cin>>s[i];
    }

    vector<Node> qry;
    vector<int> pos;
    for(int k=0; k<m; ++k) {
        int op;
        cin>>op;
        if(op == 1) {
            int i,j;
            string c;
            cin>>i>>j>>c;
            qry.push_back({op,i,j,c});
        }else {
            string t;
            int l,r;
            cin>>t>>l>>r;
            qry.push_back({op,l,r,t});
            pos.push_back((int)t.size()-1);
        }
    }
    auto ls = lsh(pos);
    debug(pos);

    for(int i=0; i<n; ++i) {
        ll pre = 0;
        for(int j=0,v=0; j<s[i].size(); ++j) {
            pre = norm(pre + mul(s[i][j], powX[j]));
            while(v < pos.size() and pos[v] < j)
                v++;
            if(v < pos.size() and pos[v] == j) {
                pref[i].push_back(pre);
                mp[v][pre].insert(i);
                debug("insert", v, pre, i);
            }
        }
    }

    int ans = 0;
    for(int k=0; k<m; ++k) {
        if(qry[k].op == 1) {
            auto [op,i,j,tt] = qry[k];
            char c = tt[0];
            --i,--j;
            debug(i,j,c);

            for(int v=0; v<pos.size(); ++v)  {
                int p = pos[v];
                if(p >= s[i].size()) break;
                if(p >= j) {
                    mp[v][pref[i][v]].erase(i);
                    pref[i][v] = norm(pref[i][v] - mul(s[i][j], powX[j]));
                    pref[i][v] = norm(pref[i][v] + mul(c, powX[j]));
                    mp[v][pref[i][v]].insert(i);
                    // debug("reInsert", p, pref[i][v], i);
                }
            }
            s[i][j] = c;
        }else {
            auto [op,l,r,t] = qry[k];

            l = (l^ans)%n+1;
            r = (r^ans)%n+1;
            if(l > r) swap(l, r);

            --l,--r;
            // debug(l,r);

            ans = 0;
            ll pre = 0;
            for(int j=0; j<t.size(); ++j) {
                pre = norm(pre + mul(t[j], powX[j]));
            }
            // debug(pre);
            int w = ls(t.size()-1);
            auto it = mp[w].find(pre);
            if(it != mp[w].end()) {
                auto const& tr = it->second;
                auto itl = tr.lower_bound(l);
                if(itl != tr.end()) {
                    auto itr = --tr.upper_bound(r);
                    // debug(*it, l, r, *tr.upper_bound(r));
                    ans += tr.order_of_key(*itr)-tr.order_of_key(*itl)+1;
                }
            }
            cout<<ans<<"\n";
        }
    }
    return 0;
}
/*
利用 |q| 的总长度不超过 1e5，那么 |q| 的长度只有 sqrt(1e5) 种，维护这些长度的前缀的哈希值，这样每次修改只要修改 sqrt(1e5) 种哈希值



*/