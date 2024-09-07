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
    for(auto& x : v) is >> x;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> itvs(n);
    vector<int> lst(n, -1), ts{0};
    for(int i = 0, t, p; i < m; ++i) {
        cin >> t >> p;
        --p;
        ts.push_back(t);
        if(lst[p] != -1) {
            itvs[p].emplace_back(lst[p], t);
            lst[p] = -1;
        } else {
            lst[p] = t;
        }
    }

    auto ls = [&](int x) {
        return lower_bound(ALL(ts), x) - ts.begin();
    };

    for(int i = 0; i < n; ++i) {
        for(auto& [l, r] : itvs[i]) {
            l = ls(l);
            r = ls(r);
        }
    }

    int q;
    cin >> q;
    vector<int> ans(q);
    vector<vector<pair<int, int>>> qry(n);
    for(int i = 0; i < q; ++i) {
        int p0, p1;
        cin >> p0 >> p1;
        --p0, --p1;
        if(itvs[p0].size() < itvs[p1].size()) {
            swap(p0, p1);
        }
        if(itvs[p0].size() <= 500) {
            const auto& v0 = itvs[p0];
            const auto& v1 = itvs[p1];
            int i0 = 0, i1 = 0;
            while(i0 < v0.size() and i1 < v1.size()) {
                if(v0[i0].second <= v1[i1].first) {
                    i0++;
                    continue;
                }
                if(v0[i0].first >= v1[i1].second) {
                    i1++;
                    continue;
                }
                int L = max(v0[i0].first, v1[i1].first);
                int R = min(v0[i0].second, v1[i1].second);
                ans[i] += ts[R] - ts[L];
                if(R == v0[i0].second) {
                    i0++;
                } else {
                    i1++;
                }
            }
            continue;
        }
        qry[p0].emplace_back(p1, i);
    }


    vector<int> pref(ts.size());
    vector<int> d(pref.size() + 1);
    for(int i = 0; i < n; ++i) {
        if(qry[i].empty()) {
            continue;
        }

        fill(ALL(d), 0);
        for(auto [l, r] : itvs[i]) {
            d[l + 1] += 1;
            d[r + 1] -= 1;
        }
        for(int i = 1; i < pref.size(); ++i) {
            d[i] += d[i - 1];
            pref[i] = pref[i - 1];
            if(d[i]) {
                pref[i] += ts[i] - ts[i - 1];
            }
        }

        sort(ALL(qry[i]));
        for(int k = 0; k < qry[i].size(); ++k) {
            auto [e, index] = qry[i][k];
            if(k and e == qry[i][k - 1].first) {
                ans[index] = ans[qry[i][k - 1].second];
                continue;
            }
            for(auto [l, r] : itvs[e]) {
                ans[index] += pref[r] - pref[l];
            }
        }
    }

    for(int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
}
/*
https://atcoder.jp/contests/abc365/tasks/abc365_g
题意可以转化为 n 个人，每个人持有若干段区间
多次询问 ui,vi 的区间交集
其中总区间数量为 n 级别

根号分治 O((n+q) sqrt(n))
对于询问：
1. 对于两人拥有区间数同时小于 sqrt(n)，直接归并求区间交集，O(sqrt(n))
2. 否则把询问离线到区间数大于 sqrt(n)的位置上，后面统一处理
这样的位置最多 sqrt(n) 个，而同一个位置上的询问去重后最多包含 1~n，也就是 n 段区间
所以这里可以 O(n) 预处理，然后依次对每个询问 O(1) 求得

*/