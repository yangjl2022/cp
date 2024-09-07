#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

#include "./lib.cpp"
auto rdi = rd::nextInteger<long long>;
template<typename T>
void print(int n, ll l, ll r) {
    for(int i = 0; i < n; ++i) {
        if(i) cout << " ";
        cout << (T)rdi(l, r);
    }
}

int main() {
    int t = 4;
    t = rdi(1, 100);
    cout << t << "\n";
    auto value = [&]() {
        return rdi(0, 3);
    };

    for(int tt = 0; tt < t; ++tt) {
        int n = rdi(1, 5);
        cout << n << "\n";
        cout << rd::nextString(n * 4, '0', '1') << endl;
    }

    return 0;
}
/*




*/
