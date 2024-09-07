#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<bool FIND_MAX = true, typename I, class F>
I ternarySearch(I l, I r, F f) {
    assert(l<=r);
    while(l < r) {
        I lmid = l + (r - l) / 2;
        I rmid = lmid + 1;
        if constexpr (FIND_MAX) {
            if(f(lmid) < f(rmid)) l = rmid;
            else r = lmid;
        }else {
            if(f(lmid) < f(rmid)) r = lmid;
            else l = rmid;
        }
    }
    return l;
}

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x:v) is>>x;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        cin>>n;

        ll sum = 0;
        vector<ll> C,P;
        for(int i=0; i<n; ++i) {
            char t;
            int x;
            cin>>t>>x;
            if(t == 'C') C.push_back(x*2);
            else P.push_back(x*2);
            sum += x*2;
        }
        
        sort(ALL(C));
        sort(ALL(P));
        vector<ll> prefC(C.size()+1);
        for(int i=0; i<C.size(); ++i) {
            prefC[i+1] = prefC[i] + C[i];
        }
        vector<ll> prefP(P.size()+1);
        for(int i=0; i<P.size(); ++i) {
            prefP[i+1] = prefP[i] + P[i];
        }

        ll ans = sum;
        // ll ans = 0;
        for(int i=0; i<=P.size(); ++i) {
            // i个 | sz-i个
            auto cal = [&](int j) -> ll {
                // debug(i, j);
                assert(0<=j and j<=C.size());
                int cn = min(i*2, (int)C.size()-j);
                int pn = min(j, (int)P.size()-i);
                return sum + (prefC.back() - prefC[C.size()-cn])/2
                            + prefP.back() - prefP[P.size()-pn];
            };
            int j = ternarySearch(0, (int)C.size(), cal);
            // debug(i, j, cal(j));
            ans = max(ans, cal(j));
        }

        cout<<ans/2;
        if(ans&1) {
            cout<<".5";
        }else {
            cout<<".0";
        }
        cout<<"\n";
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85333/J
经典分配为两组的协调问题，第一组分少了不优秀，第一组分多了也不优秀
三分解决

*/