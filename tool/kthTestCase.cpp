#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
using ll = long long;

#define interrupt {                                         \
    cerr << "The " << T << "-th test case missed." <<endl;  \
    break;                                                  \
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tt;
    cin>>tt;
    for(int T=1; T<=tt; ++T) {
        int n;
        if(!(cin>>n))
            interrupt
        vector<int> a(n);
        for(int i=0; i<n; ++i) {
            if(!(cin>>a[i]))
                interrupt
        }

        if(T == 11) {
            cout<<n<<endl;
            for(int i=0; i<n; ++i) {
                cout<<a[i]<<" \n"[i+1==n];
            }
            break;
        }
    }
    cerr<< "Finished." <<endl;
    return 0;
}
/*




*/