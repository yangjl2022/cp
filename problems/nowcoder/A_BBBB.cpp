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

constexpr int N = 2e7 + 10;
int a[N], an, b[N];
int pre[N];

void mul(string const& s) {
    for(int i=0; i<an; ++i) {
        pre[i+1] = pre[i]+a[i];
    }
    int l = s.size(), i = l-1;
    // l个s[i]
    int v = s[i]-'0';
    // v*('1'*l)*a
    for(int j=0; j<an; ++j) {
        // len = min(j+1, l)
        b[j] += (pre[j+1]-pre[max(0, j+1-l)])*v;
    }
    for(int j=an; j<an+l-1; ++j) {
        // len = min(an, an+l-2-j+1)
        b[j] += (pre[an]-pre[max(0, -l+1+j)])*v;
    }
    an += l-1;
    memcpy(a, b, sizeof(int)*an);
    memset(b, 0, sizeof(int)*an);

    for(int i=0; i+1<an; ++i) {
        if(a[i]>9) {
            int t = a[i]/10;
            a[i+1] += t;
            a[i] -= t*10;
        }
    }
    while(a[an-1]>9) {
        int t = a[an-1]/10;
        a[an] += t;
        a[an-1] -= t*10;
        an++;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        string s,t;
        cin>>s>>t;
        if(s == "0" or t == "0") {
            cout<<"0\n";
            continue;
        }
        
        an = s.size();
        for(int i=0; i<an; ++i) {
            a[i] = s[an-i-1]-'0';
        }
        mul(t);
        for(int i=an-1; i>=0; --i) {
            cout<<a[i];
        }
        cout<<'\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87255/D
对于一段数位相同的数字的高精度乘法
可以用前缀和做到 O(n)



*/