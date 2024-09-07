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
#include<random>
#include<fstream>
#ifdef YJL
#include<debug.h>
#else
#define debug(args...)0
#define debug_n(a,n)0
#endif
using namespace std;
typedef long long ll;

constexpr int N = 2e5 + 10;

int mex(const vector<int>& a) {
    vector<int> vis(a.size()+1);
    for(int x:a)
        if(x<(int)a.size())
            vis[x]=1;
    int p=0;
    while(vis[p]) p++;
    return p;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin>>n;
    vector<int> a;
    for(int i=1; i<=n; ++i)  {
        int l,r;
        cin>>l>>r;
        if(l==r) a.push_back(l);
    }
    int ans=mex(a);
    cout<<ans<<endl;
    return 0;
}
/*




*/