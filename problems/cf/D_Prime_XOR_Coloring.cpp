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

vector<bool> nPrime;
vector<int> prm,minp,phi,mo;
void sieve(int n) {// sieve [1,n]
    nPrime.resize(n+1), nPrime[1]=true;
    minp.resize(n+1);
    phi.resize(n+1), phi[1]=1;
    mo.resize(n+1), mo[1]=1;
    for(int i=2; i<=n; ++i) {
        if(!nPrime[i]) {
            prm.push_back(i);
            minp[i]=i;
            phi[i]=i-1;
            mo[i]=-1;
        }
        for(int j=0; prm[j]<=n/i; ++j) {
            int k=i*prm[j];
            nPrime[k]=true;
            minp[k]=prm[j];
            if (i%prm[j]==0) {
                phi[k]=phi[i]*prm[j];
                break;
            }
            phi[k]=phi[i]*(prm[j]-1);
            mo[k]=-mo[i];
        }
    }
}

bool check(vector<int> a) {
    int k = *max_element(ALL(a));
    int n = a.size();
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) {
            if(!nPrime[(i+1) ^ (j+1)]) {
                if(a[i] == a[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    sieve(4e5);
    // int n = 200000;
    // int num = 0;
    // for(int i=1; i<=n; ++i) {
    //     for(int j=i+1; j<=n; ++j) {
    //         if(!nPrime[i^j]) {
    //             num++;
    //             // cerr<<i<<" "<<j<<endl;
    //         }
    //     }
    // }
    // debug(n, num);
    vector<int> base{1, 2, 4, 3};
    int tt=100;
    cin>>tt;
    int tot = 1;
    while(tt--) {
        int n = tot++;
        cin>>n;

        vector<int> ans;

        if(n <= 5) {
            int v = 1, m = 1;
            while(ans.size() < n) {
                int base = v;
                int tmp = v;
                for(int i=0; i<tmp; ++i) {
                    int x = base+i;
                    for(int j=0; j<m; ++j) {
                        ans.push_back(x);
                        if(ans.size() >= n) break;
                    }
                    if(ans.size() >= n) break;
                }
                v += tmp;
                m += 1;
            }
        }else {
            while(ans.size() < n) {
                ans.insert(ans.end(), ALL(base));
            }
            ans.resize(n);
        }

        // assert(check(ans));

        cout<<*max_element(ALL(ans))<<'\n';
        for(int i=0; i<n; ++i) {
            cout<<ans[i]<<" ";
        }
        cout<<'\n';

    }
    return 0;
}
/*
https://codeforces.com/contest/1991/problem/D
打表
输出所有合法情况，偶然发现 n=8 时有循环 1,2,4,3,1,2,4,3 这种涂色方式
于是对于前几个特判，对于后面的采用 1,2,4,3 循环的方式来构造
并用暴力程序检测前 100 个答案的正确性

打表代码如下：
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

vector<bool> nPrime;
vector<int> prm,minp,phi,mo;
void sieve(int n) {// sieve [1,n]
    nPrime.resize(n+1), nPrime[1]=true;
    minp.resize(n+1);
    phi.resize(n+1), phi[1]=1;
    mo.resize(n+1), mo[1]=1;
    for(int i=2; i<=n; ++i) {
        if(!nPrime[i]) {
            prm.push_back(i);
            minp[i]=i;
            phi[i]=i-1;
            mo[i]=-1;
        }
        for(int j=0; prm[j]<=n/i; ++j) {
            int k=i*prm[j];
            nPrime[k]=true;
            minp[k]=prm[j];
            if (i%prm[j]==0) {
                phi[k]=phi[i]*prm[j];
                break;
            }
            phi[k]=phi[i]*(prm[j]-1);
            mo[k]=-mo[i];
        }
    }
}

bool check(vector<int> a) {
    int k = *max_element(ALL(a));
    int n = a.size();
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) {
            if(!nPrime[(i+1) ^ (j+1)]) {
                if(a[i] == a[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

vector<int> ans;
int n, k;
int num;
void dfs() {
    if(ans.size() >= n) {
        // if(num <= 20) {
        if(1) {
            if(check(ans)) {
                ++num;
                debug(ans);
            }
        }
        return;
    }
    for(int i=1; i<=k; ++i) {
        ans.push_back(i);
        dfs();
        ans.pop_back();
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    sieve(4e5);
    for(n=8; n<=8; ++n) {
        for(k=1; k<=n; ++k) {
            num = 0;
            dfs();
            if(num) {
                break;
            }
        }
    }
    return 0;
}
// 1 2 4 3
*/