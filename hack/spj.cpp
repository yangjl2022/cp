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
#define massert(condition, msg) if(!(condition)) {cerr<<(msg)<<endl; exit(1);}

std::string wordle_query(std::string query, std::string answer) {
    int n = std::size(query);
    std::string res(n, 'B');

    std::array<int,26> count = {};
    for (char c: answer) count[c-'a']++;

    // place green tiles
    for (int i = 0; i < n; i++) {
        if (query[i] == answer[i]) {
            res[i] = 'G';
            count[query[i]-'a']--;
        } 
    }

    // place yellow tiles
    for (int i = 0; i < n; i++) {
        if (res[i] != 'G' && count[query[i]-'a'] > 0) {
            count[query[i]-'a']--;
            res[i] = 'Y';
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int g,n;
    cin>>g>>n;
    vector<pair<string,string>> a(g-1);
    for(auto& [t,res]:a) cin>>t>>res;

    string s;
    cin>>s;
    for(char c:s) {
        massert(c>='a' and c<='z', "invalid character.");
    }

    for(auto& [t,ans]:a) {
        // string res(n, 'B');
        // for(int j=0; j<n; ++j) {
        //     if(s[j]==t[j]) {
        //         res[j] = 'G';
        //     }
        // }
        // for(int j=0; j<n; ++j) {
        //     if(res[j] != 'G') {
        //         for(int k=0; k<n; ++k) {
        //             if(t[k] == s[j] and res[k] == 'B') {
        //                 res[k] = 'Y';
        //                 break;
        //             }
        //         }
        //     }
        // }
        massert(wordle_query(t,s)==ans, "!!!");
    }
    return 0;
}
/*




*/