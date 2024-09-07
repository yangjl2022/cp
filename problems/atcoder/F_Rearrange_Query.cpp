/**
 *    author:  yangjl
 *    created: 2024.17.08 20:01:21
**/
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
    for(auto& x : v) {
        is >> x;
    }
    return is;
}

#include<random>
mt19937_64 rng(random_device{}());
ll rdi(ll l, ll r) {
    return rng() % (r - l + 1) + l;
}

using ull = unsigned long long;
map<int, ll> mp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<ull> a(n), b(n);
    cin >> a >> b;
    for(auto& x : a) {
        if(!mp.count(x)) {
            mp[x] = rng();
        }
        x = mp[x];
    }
    for(auto& x : b) {
        if(!mp.count(x)) {
            mp[x] = rng();
        }
        x = mp[x];
    }
    a.insert(a.begin(), 0); partial_sum(a.begin(), a.end(), a.begin());
    b.insert(b.begin(), 0); partial_sum(b.begin(), b.end(), b.begin());
    while(q--) {
        int l, r, L, R;
        cin >> l >> r >> L >> R;
        // if(r - l != R - L) {
        //     cout << "No\n";
        //     continue;
        // }
        if(a[r] - a[l - 1] == b[R] - b[L - 1]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
/*
https://atcoder.jp/contests/abc367/tasks/abc367_f
多重集的哈希，随机数

*/