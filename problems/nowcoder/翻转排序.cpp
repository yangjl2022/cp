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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n), id(n);
    for(int i=0; i<n; ++i) {
        cin>>a[i];
        --a[i];
        id[a[i]] = i;
    }

    vector<pair<int,int>> ans;
    for(int i=0; i<n; ++i) {
        int j = id[i];
        if(i == j) continue;
        ans.emplace_back(i, j);
        swap(id[i], id[a[i]]);
        swap(a[i], a[j]);
        if(j-i > 2) {
            ans.emplace_back(i+1, j-1);
        }
        // debug(id);
    }
    cout<<ans.size()<<"\n";
    for(auto [l,r]:ans) {
        cout<<l+1<<" "<<r+1<<'\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85333/K
需要脑子灵活一点，翻转后又把中间的翻回来，
转化为了swap()排序问题

*/