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

vector<bool> nPrime;
vector<int> prm, minp, phi, mo;
void sieve(int n) {// sieve [1,n]
    nPrime.resize(n + 1), nPrime[1] = true;
    minp.resize(n + 1);
    phi.resize(n + 1), phi[1] = 1;
    mo.resize(n + 1), mo[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!nPrime[i]) {
            prm.push_back(i);
            minp[i] = i;
            phi[i] = i - 1;
            mo[i] = -1;
        }
        for(int j = 0; prm[j] <= n / i; ++j) {
            int k = i * prm[j];
            nPrime[k] = true;
            minp[k] = prm[j];
            if(i % prm[j] == 0) {
                phi[k] = phi[i] * prm[j];
                break;
            }
            phi[k] = phi[i] * (prm[j] - 1);
            mo[k] = -mo[i];
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    sieve(3e6);
    assert(prm.size() > int(2e5));
    int tt;
    cin >> tt;
    assert(1 <= tt and tt <= int(5e4));
    int sn = 0;
    while(tt--) {
        int n;
        cin >> n;
        sn += n;
        assert(1 <= n and n <= int(2e5));
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            assert(2 <= a[i] and a[i] <= int(1e9));
        }
        sort(ALL(a), greater());
        for(int x : prm) {
            while(a.size() and a.back() < x)
                a.pop_back();
            if(a.size() and a.back() == x) {
                continue;
            }
            cout << x << '\n';
            break;
        }
    }
    assert(1 <= sn and sn <= int(2e5));
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/88455/D
质数筛，排序，贪心，思维

注意到如果x时刻不能拍照，那么 2x,3x,.. 所有x的倍数都不能拍照
=> 如果x时刻能拍照，那么x的所有>=2的因子时都能拍照

因此答案肯定是质数时刻（反证：如果答案不为质数，那么他的一个因子时刻也可以拍照，且答案更小）

更进一步，答案就是a中未出现过的最小质数 p，证明：
1. 小于 p 的质数都在 a 中出现了，不能拍照
2. 小于 p 的非质数必定有因子是质数且 < p，所以也不能拍照
3. p 由于是质数，不会是 a 中某个数的倍数，所以能拍照
于是 p 就是最小的能拍照的时刻

做法：
1. 晒出超过2e5个质数
2. 对于给定的a排好序
3. 用归并的方式，从小到大依次考虑每一个质数有没有在 a 中出现

*/