#include<string>
using namespace std;

template<class T>
string isPrime(T n) {
    string str=to_string(n);
    for(int i=2; i<=n/i; ++i)
        if(n%i==0) 
            return str+" is not prime: "
                +str+" % "+to_string(i)+" == 0";
    return n>1? str+" is prime": str+" is not prime";
} 
