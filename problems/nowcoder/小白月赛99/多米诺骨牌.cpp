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
    int tt;
    cin >> tt;
    assert(1 <= tt and tt <= int(5e4));
    int sn = 0;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        sn += n;
        assert(1 <= m and m <= n and n <= int(2e5));

        vector<int> h(n);
        cin >> h;
        vector<pair<int, int>> a;
        set<int> st;
        for(int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            assert(1 <= h[i] and h[i] <= int(1e9));
            assert(1 <= x and x <= int(1e9));
            assert(st.insert(x).second);
            a.emplace_back(x, x + h[i]);
        }
        sort(ALL(a));

        vector<int> v;
        int mR = -1, cnt = 0;
        for(auto [l, r] : a) {
            if(mR < l) {
                v.push_back(cnt);
                mR = r;
                cnt = 1;
            } else {
                mR = max(mR, r);
                cnt++;
            }
        }
        v.push_back(cnt);

        sort(ALL(v), greater());
        v.resize(m);
        cout << accumulate(ALL(v), 0) << '\n';
    }
    assert(1 <= sn and sn <= int(2e5));
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/88455/E
贪心
如果左边的i能影响右边的j，那么肯定推i而不是去推j最优
所以依次从左往右推倒，多米诺骨牌被分成若干段，选择m段价值最大的段的起点即可

*/