#include <bits/stdc++.h>
#ifdef YJL
#include "debug.h"
#else
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

constexpr int N = 9, M = 12;
map<string,array<array<pair<int,int>,4>, 5> > mp;
const vector<string> ops = {
    "R1", "R2", "U1", "U2", "F1", "F2",
};
void init() {
    mp["U2"] = array<array<pair<int,int>,4>, 5>{
        array<pair<int,int>,4>{pair(3,4),pair(4,7),pair(7,6),pair(6,3)},
        array<pair<int,int>,4>{pair(3,5),pair(5,7),pair(7,5),pair(5,3)},
        array<pair<int,int>,4>{pair(3,6),pair(6,7),pair(7,4),pair(4,3)},
        array<pair<int,int>,4>{pair(4,4),pair(4,6),pair(6,6),pair(6,4)},
        array<pair<int,int>,4>{pair(4,5),pair(5,6),pair(6,5),pair(5,4)},
    };
    mp["R2"] = array<array<pair<int,int>,4>, 5>{
        array<pair<int,int>,4>{pair(3,6),pair(4,10),pair(9,6),pair(6,6)},
        array<pair<int,int>,4>{pair(2,6),pair(5,10),pair(8,6),pair(5,6)},
        array<pair<int,int>,4>{pair(1,6),pair(6,10),pair(7,6),pair(4,6)},
        array<pair<int,int>,4>{pair(4,7),pair(4,9),pair(6,9),pair(6,7)},
        array<pair<int,int>,4>{pair(4,8),pair(5,9),pair(6,8),pair(5,7)},
    };
    mp["F2"] = array<array<pair<int,int>,4>, 5>{
        array<pair<int,int>,4>{pair(6, 4),pair(6,7),pair(6,10),pair(6, 1)},
        array<pair<int,int>,4>{pair(6, 5),pair(6, 8),pair(6, 11),pair(6, 2)},
        array<pair<int,int>,4>{pair(6, 6),pair(6,9),pair(6,12),pair(6,3)},
        array<pair<int,int>,4>{pair(7,4),pair(7,6),pair(9,6),pair(9,4)},
        array<pair<int,int>,4>{pair(7,5),pair(8,6),pair(9,5),pair(8,4)},
    };
    for(auto [s0, s1] : vector<pair<string,string>>{
        {"U1","U2"},
        {"R1","R2"},
        {"F1","F2"},
    }) {
        auto v = mp[s1];
        for(int i=0; i<v.size(); ++i) {
            reverse(v[i].begin()+1, v[i].end());
        }
        mp[s0] = v;
        // debug(mp[s0]);
        // debug(mp[s1]);
    }
}

const vector<string> a0 = {
 "   OOO      ",
 "   OOO      ",
 "   OOO      ",
 "BBBYYYGGGWWW",
 "BBBYYYGGGWWW",
 "BBBYYYGGGWWW",
 "   RRR      ",
 "   RRR      ",
 "   RRR      ",
};

void print(vector<string> a) {
    for(auto x:a) {
        cerr<<x<<'\n';
    }
    return;
}

vector<string> opt(vector<string> a, string const& op) {
    auto get = [&](pair<int,int> const& p) -> char& {
        return a[p.first-1][p.second-1];
    };
    auto const& v = mp[op];
    for(int i=0; i<v.size(); ++i) {
        char c = get(v[i][0]);
        for(int j=0; j+1<v[i].size(); ++j) {
            get(v[i][j]) = get(v[i][j+1]);
        }
        get(v[i][v[i].size()-1]) = c;
    }
    return a;
}

vector<string> op;
void dfs(vector<string> a) {
    if(a == a0) {
        cout<<op.size()<<'\n';
        for(auto& x : op) {
            cout<<x<<'\n';
        }
        exit(0);
    }
    if(op.size() >= 8) {
        return;
    }
    for(auto& x:ops) {
        op.push_back(x);
        dfs(opt(a, x));
        op.pop_back();
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<string> a(9);
    for(int i=0; i<9; ++i) {
        if(i<3 or i>=6) {
            a[i].resize(3);
            for(int j=0; j<a[i].size(); ++j) {
                cin>>a[i][j];
            }
            a[i] = string(3,' ') + a[i] + string(6, ' ');
        }else {
            a[i].resize(12);
            for(int j=0; j<a[i].size(); ++j) {
                cin>>a[i][j];
            }
        }
    }
    
    init();

    // debug();
    // print(a);
    
    // debug();
    // a = opt(a, "U1");
    // print(a);
    
    // debug();
    // a = opt(a, "U1");
    // print(a);
    
    // debug();
    // a = opt(a, "R2");
    // print(a);
    // exit(0);
    
    dfs(a);
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87255/K
大模拟
题目保证8步之内有解, 8! = 4e4
直接模拟魔方的旋转
bfs会被卡内存，还得用dfs
*/