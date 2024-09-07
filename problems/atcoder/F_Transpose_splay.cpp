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

struct Splay {
    struct Node {
        int key, siz;
        int rev;
        int fa, ch[2];
    };
    int n, id, root;
    vector<Node> t;
    Splay(int n) : n(n), id(0), root(0), t(n+10) {// [1,n]建树
        root = build(0, n+1);
    }
    void pushup(int u) {
        t[u].siz = 1 + t[t[u].ch[0]].siz + t[t[u].ch[1]].siz;
    }
    void pushdown(int u) {
        if (t[u].rev) {
            swap(t[u].ch[0], t[u].ch[1]);
            t[t[u].ch[0]].rev^=1, t[t[u].ch[1]].rev ^= 1;
            t[u].rev = 0;
        }
    }
    int build(int l, int r) {
        int u = ++id;
        int mid = (l+r)/2;
        t[id].key = mid;
        t[id].siz = 1;
        if (l<mid) t[u].ch[0] = build(l, mid-1);
        if (mid<r) t[u].ch[1] = build(mid+1, r);
        t[t[u].ch[0]].fa = t[t[u].ch[1]].fa = u;
        pushup(u);
        return u;
    }
    void reverse(int l, int r) {// 翻转[l,r]
        l = get_kth(l), r = get_kth(r+2);
        splay(l), splay(r, l);
        t[t[r].ch[0]].rev ^= 1;
    }
    void rotate(int u) {
        int fa = t[u].fa, gfa = t[fa].fa;
        t[gfa].ch[t[gfa].ch[1] == fa] = u, t[u].fa = gfa;
        int k = (t[fa].ch[1] == u);
        t[fa].ch[k] = t[u].ch[k^1], t[t[u].ch[k^1]].fa = fa;
        t[u].ch[k^1] = fa, t[fa].fa = u;
        pushup(fa), pushup(u);
    }
    void splay(int u, int s=0) {
        while (t[u].fa != s) {
            int fa = t[u].fa, gfa = t[fa].fa;
            if (gfa != s) {
                if ((t[fa].ch[1] == u) ^ (t[gfa].ch[1] == fa)) rotate(u);
                else rotate(fa);
            }
            rotate(u);
        }
        if (!s) root = u;
    }
    int get_kth(int Rank) {
        int u = root;
        while (u) {
            pushdown(u);
            if (t[t[u].ch[0]].siz >= Rank) u = t[u].ch[0];
            else if (t[t[u].ch[0]].siz+1 >= Rank) return u;
            else Rank -= t[t[u].ch[0]].siz+1, u = t[u].ch[1];
        }
        return 0;
    }
    void midOrder(int u,vector<int>& a) {// 遍历[1,n]
        if (!u) return;
        pushdown(u);
        midOrder(t[u].ch[0], a);
        if (t[u].key >= 1 and t[u].key <= n) a.push_back(t[u].key);
        midOrder(t[u].ch[1],a);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin>>s;
    int sz = count_if(s.begin(),s.end(),[](char c){return c!='(' and c!=')';});
    Splay tr(sz);

    string t;
    stack<int> st;
    for(int i=0, p=0; i<s.size(); ++i) {
        if(s[i]=='(')
            st.push(t.size());
        else if(s[i]==')') {
            int l = st.top();
            st.pop();
            int r = t.size();
            if(l<r) tr.reverse(l+1, r);
        }else {
            t += char(s[i]^((st.size()&1) ? ('a'^'A') : 0));
        }
    }
    vector<int> a;
    tr.midOrder(tr.root, a);
    for(int x:a) {
        cout<<t[x-1];
    }
    return 0;
}
/*

https://atcoder.jp/contests/abc350/tasks/abc350_f
splay 解法

*/