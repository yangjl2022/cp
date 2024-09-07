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

constexpr int N = 2e5 + 10;

#include <ext/rope>
template<typename T>
struct ReversableArray {
    int n;
    __gnu_cxx::rope<T> ro, iro;// [0,n-1]
    // a = [0, 1, ..., num-1]
    ReversableArray(int num) : n(num) {
        for(int i=0; i<n; ++i) ro.push_back(i), iro.push_front(i);
    }
    ReversableArray(vector<T> const& a) : n(a.size()) {
        for(int i=0; i<n; ++i) ro.push_back(a[i]), iro.push_front(a[i]);
    }
    void reverse(int l, int r) {// [l,r]
        if(l>r) return;
        auto as = ro.substr(l, r-l+1);
        auto bs = iro.substr(n-1-r, r-l+1);
        ro.erase(l, r-l+1);
        iro.erase(n-1-r, r-l+1);
        ro.insert(l, bs.begin(), bs.end());
        iro.insert(n-r-1, as.begin(), as.end());
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin>>s;
    int sz = count_if(s.begin(),s.end(),[](char c){return c!='(' and c!=')';});
    ReversableArray<int> ra(sz);

    string t;
    stack<int> st;
    for(int i=0, p=0; i<s.size(); ++i) {
        if(s[i]=='(')
            st.push(t.size());
        else if(s[i]==')') {
            int l = st.top();
            st.pop();
            int r = t.size();
            if(l<r) ra.reverse(l, r-1);
        }else {
            t += char(s[i]^((st.size()&1) ? ('a'^'A') : 0));
        }
    }
    for(int x:ra.ro) {
        cout<<t[x];
    }
    return 0;
}
/*

https://atcoder.jp/contests/abc350/tasks/abc350_f
使用 rope 代替 splay 进行区间翻转

*/