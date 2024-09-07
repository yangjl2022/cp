/**
 *    author:  yangjl
 *    created: 2024.10.08 22:51:31
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

struct Data {
    ll sum, minh;
    void init(int i, vector<int> const& a) {
        sum = minh = a[i];
    }
    friend Data operator+(const Data& lhs, const Data& rhs) {
        Data re;
        re.sum = lhs.sum + rhs.sum;
        re.minh = max(lhs.minh, rhs.minh - lhs.sum);
        return re;
    }
};

constexpr int LOG = 18;

void print(vector<ll> ans) {
    for(int i = 0; i + 1 < ans.size(); ++i) {
        if(i) {
            ans[i] += ans[i - 1];
        }
        cerr << ans[i] << ' ';
    }
    cerr << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin >> tt;
    while(tt--) {
        int n, _;
        cin >> n >> _;
        vector<int> a(n);
        vector<array<Data, LOG + 1>> toB(n), toF(n);
        vector<Data> pref(n + 1);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            toB[i][0] = {a[i], a[i]};
            toF[i][0] = {a[i], a[i]};
            pref[i + 1] = toF[i][0] + pref[i];
        }

        for(int j = 1; j <= LOG; ++j) {
            for(int i = n - 1; i >= 0; --i) {
                if(i + (1 << j) - 1 >= n) {
                    continue;
                }
                toB[i][j] = toB[i][j - 1] + toB[i + (1 << j - 1)][j - 1];
            }
            for(int i = 0; i < n; ++i) {
                if(i - (1 << j) + 1 < 0) {
                    continue;
                }
                toF[i][j] = toF[i][j - 1] + toF[i - (1 << j - 1)][j - 1];
            }
        }

        vector<ll> ans(n + 1);
        for(int i = 0; i < n; ++i) {
            auto check = [&]() -> bool {
                int l = i, r = i;
                ll h = a[i];
                if(h >= pref[i].minh) {
                    ans[i]++;
                    ans[i + 1]--;
                }
                while(l > 0 or r + 1 < n) {
                    debug(i, l, r);
                    if(l > 0 and h >= a[l - 1]) {
                        for(int k = LOG; k >= 0; --k) {
                            if(l - (1 << k) < 0) {
                                continue;
                            }
                            if(h >= toF[l - 1][k].minh) {
                                h += toF[l - 1][k].sum;
                                l -= 1 << k;
                            }
                        }
                        continue;
                    }
                    if(r + 1 < n and h >= a[r + 1]) {
                        ll h0 = h;
                        int r0 = r;
                        for(int k = LOG; k >= 0; --k) {
                            if(r + (1 << k) >= n) {
                                continue;
                            }
                            if(h >= toB[r + 1][k].minh) {
                                h += toB[r + 1][k].sum;
                                r += 1 << k;
                            }
                        }
                        debug(i, h0, r0);

                        ll t = pref[l].minh;
                        if(h >= t) {
                            ll hh = h0;
                            int rr = r0;
                            for(int k = LOG; k >= 0; --k) {
                                if(rr + (1 << k) >= n) {
                                    continue;
                                }
                                if(hh + toB[rr + 1][k].sum < t) {
                                    hh += toB[rr + 1][k].sum;
                                    rr += 1 << k;
                                }
                            }
                            rr++;
                            assert(rr <= r);
                            ans[rr]++;
                            ans[r + 1]--;
                        }
                        continue;
                    }
                    return false;
                }
                return true;
            };
            check();
            // print(ans);
        }

        for(int i = 0; i < n; ++i) {
            if(i) {
                ans[i] += ans[i - 1];
            }
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
/*
https://codeforces.com/contest/1998/problem/E2
思维，倍增，二分

前置知识：
大鱼吃小鱼并合并，从从左吃到右能否通关，这个问题可以设计支持加法的数据结构做到区间询问

1）
首先考虑 S = {1,2,3,4,..,n} 的情况
对于 u 最终能留在 S 中，贪心的想，肯定是 u 依次去合并邻居最优
- 考虑贪心合并邻居：左边可以合并就往左合并，右边同理，如果最终能全合并完，f(n) 候选人就多了一个
- 对于连续往同一个方向合并，可以使用倍增+二分来优化，单次 logn 复杂度
- 此时复杂度多大呢？其实是 nlognlogn
因为连续往一个方向合并后，此时生命值为 h，下一个目标必定 ai > h
此时往反方向合并增大 h 之后再来合并 ai，如果满足 new h > ai，那么 new h + ai > ai+ai > 2h
所以一来一回之后，h 会翻倍，于是来回次数一定是 logn 级别的。

2）
考虑 S = {1,2,3,...,m} 的贡献来自哪些 u
即考虑 u 对于哪些 f(m) 有贡献
注意 u 通关 [1,m] 肯定是某次吃完 [y, m] 使得 h 足够大，再吃完 [1,x]，最终通关，
如果最终是先吃完左边再吃完右边，也可以看作在左边补一个 0，仍然归属于上述情况

于是我们对于 1) 中对 u 进行大鱼吃小鱼的过程，关注什么时候能吃完前缀 [1,u]:
- 如果在一开始，或者在吃完右边一段 [p,r] 之后，能把 [1,x] 全吃了，此时更新 f()
- 我们找到最小的 rr 使得 h 加上 a[p]~a[rr] 之后就足够把 [1,x] 全吃了
- 那么 u 对于 [1,rr],[1,rr+1],...,[1,r] 这些区间里都能通关，更新 f[rr]~f[r] 加1，使用差分优化

怎么找最小的 rr呢？同样是倍增+加二分可以做到
得解

*/