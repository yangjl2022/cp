/**
 *    author:  yangjl
 *    created: 2024.08.30 19:51:55
**/
#include <bits/stdc++.h>
#ifdef YJL
#include "debug.h"
#else
#define debug(...)0
#endif
using namespace std;
using ll = long long;

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x : v) {
        is >> x;
    }
    return is;
}

int dfs(string s) {
    if(s.empty()) {
        return 1;
    }
    int ans = 0;
    for(int i = 0; i + 3 < s.size(); ++i) {
        if(s.substr(i, 4) == "0011") {
            ans += dfs(s.substr(0, i) + s.substr(i + 4));
        }
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        cout << dfs(s) << '\n';
    }
    return 0;
}
/*


*/