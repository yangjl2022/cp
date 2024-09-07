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

// return the first i of [l,r],such as check(i)=true
// if no such i,return r+1
template<class T, class Func>
T binaryMin(T l, T r, Func check) {
    T ans = r + 1;
    while(l <= r) {
        T mid = l + (r - l) / 2;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return ans;
}
// return the last i of [l,r],such as check(i)=true
// if no such i,return l-1
template<class T, class Func>
T binaryMax(T l, T r, Func check) {
    T ans = l - 1;
    while(l <= r) {
        T mid = l + (r - l) / 2;
        if(check(mid)) {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return ans;
}

vector<bool> nPrime;
vector<int> prm;//, minp, phi, mo;
void sieve(int n) {// sieve [1,n]
    nPrime.resize(n + 1), nPrime[1] = true;
    for(int i = 2; i <= n; ++i) {
        if(!nPrime[i]) {
            prm.push_back(i);
        }
        for(int j = 0; prm[j] <= n / i; ++j) {
            int k = i * prm[j];
            nPrime[k] = true;
            if(i % prm[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    sieve(3e5);
    int tt;
    cin >> tt;
    while(tt--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), pref(n + 1);
        cin >> a;
        partial_sum(ALL(a), pref.begin() + 1);

        constexpr int inf = 1e9;
        int ans = binaryMax(-inf, inf, [&](int mid) {
            int t = 0, lst = 0;
            set<pair<int, int>> st;
            st.emplace(0, 0);
            for(int i = 1; i <= n; ++i) {
                int ok = 0;
                for(auto const& [value, p] : st) {
                    if(value > pref[i] - mid) {
                        break;
                    }
                    if(!nPrime[i - p]) {
                        ok = 1;
                        break;
                    }
                }

                if(ok) {
                    lst = i;
                    if(++t >= k) break;
                    st.clear();
                }
                st.emplace(pref[i], i);
            }
            return t >= k;
        });

        if(ans <= -inf) {
            cout << "impossible\n";
            continue;
        }
        cout << ans << '\n';
    }
    return 0;
}
/*
https://acm.hdu.edu.cn/showproblem.php?pid=7471
最大化最小值，二分答案
提取 k 段长度为质数，且子段和 >= mid
贪心考虑，找到第一段的最小右端点，然后再依次考虑2,3,4..段
1. 子段和 >= mid：通过判断前缀和之差>=mid，即 pref[i] - mid >= pref[j]，可以通过 set 维护
2. 遍历 set 判断长度是否为质数

题解说由于数据随机，期望遍历 set 只有log次（我不理解）
*/