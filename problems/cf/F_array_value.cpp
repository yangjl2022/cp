#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30))*0xbf58476d1ce4e5b9;
        x=(x^(x>>27))*0x94d049bb133111eb;
        return x^(x>>31);
    }
    uint64_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM=
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FIXED_RANDOM);
    }
};// unordered_map<int,int,custom_hash> cnt;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        ll k;
        cin>>n>>k;
        vector<int> a(n);
        cin>>a;

        vector<int> l(n, -1);
        int ans = 0;
        for(int i=30; i>=0; --i) {
            // 在第i位之上 = ans+2^d, 在第i位 < ans+2^d
            unordered_map<int,int,custom_hash> lst;
            vector<int> nl(l);
            ll cnt = 0;
            for(int j=0; j<n; ++j) {
                auto it = lst.find(a[j]>>i);
                if(it != lst.end()) {
                    nl[j] = max(nl[j], it->second);
                }
                lst[(a[j]^ans)>>i] = j;
                if(j) nl[j] = max(nl[j], nl[j-1]);
                cnt += nl[j]+1;
            }
            if(cnt <= k-1) {
                ans += 1<<i;
                l = move(nl);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
/*
https://codeforces.com/contest/1983/problem/F
方法一：二分答案+字典树+树上尺取
方法二：对小于关系按位考虑
*/