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

template <typename T>
vector<int> manacher(const T &s) {
  int n = s.size();
  if(!n) return {};
  vector<int> res(2*n-1, 0);
  int l = -1, r = -1;
  for(int z=0; z < 2*n-1; ++z) {
    int i = (z+1)/2, j = z/2;
    int p = (i >= r ? 0 : min(r-i, res[2*(l+r)-z]));
    while(j+p+1 < n and i-p-1 >= 0 and s[j+p+1] == s[i-p-1]) p++;
    if(j+p > r) l = i-p, r = j+p;
    res[z] = p;
  }
  return res;
  // res[2 * i] = odd radius in position i
  // res[2 * i + 1] = even radius between positions i and i + 1
  // s = "abaa" -> res = {0, 0, 1, 0, 0, 1, 0}
  // in other words, for every z from 0 to 2 * n - 2:
  // calculate i = (z + 1) >> 1 and j = z >> 1
  // now there is a palindrome from i - res[z] to j + res[z]
  // (watch out for i > j and res[z] = 0)
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    string ss;
    cin>>ss;
    map<char,int> w;
    for(int i=0; i<m; ++i) {
        char c;
        int v;
        cin>>c>>v;
        w[c] = v;
    }

    string s;
    vector<ll> score{0};
    for(int i=0,lst=-1; i<ss.size(); ++i) {
        if(i+1==ss.size() || ss[i]!=ss[i+1]) {
            int l = i-lst;// [lst+1 ,i]
            // l个ss[i]
            s += ss[i];
            score.push_back(score.back() + l*w[ss[i]]);
            lst = i;
        }
    }

    debug(s);
    debug(score);

    ll ans = 0;
    auto r = manacher(s);
    debug(s);
    debug(r);
    for(int i=0; i<r.size(); i+=2) {
        int j = i/2;
        debug(j-r[i], j+r[i]);
        // [j-r[i], j+r[i]]
        ans = max(ans, score[j+r[i]+1] - score[j-r[i]] + w[s[j]]);
    }
    cout<<ans<<'\n';
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/82758?from=acm_calendar

马拉车算法



*/