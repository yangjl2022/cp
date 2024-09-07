#ifdef __cplusplus
#include<bitset>
#include<list>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<iostream>
#include<queue>
#include<stack>
#include<deque>
#include<array>
#include<type_traits>
using namespace std;

// powershell : Copy-Item -Path "include\debug.h" -Destination "C:\\mingw64\\x86_64-w64-mingw32\\include"
// 本地编译器 -include debug.h

#define debug(args...)											\
    cerr<<"... ",__varname=#args,__idx=0, __print(args)
#define debug_n(a,n)											\
    cerr<<"... "<<""#a"[0->"<<n-1<<"] = ", __print_n(a,n)

namespace {
template<class T1,class T2> ostream &operator<<(ostream &out,pair<T1,T2> a);
template <class... Args> ostream& operator<<(ostream& out, const std::tuple<Args...> &t);
template<class T> ostream& operator<<(ostream& out,const vector<T>& v);
template<typename T> enable_if_t<!is_same_v<T, char>, ostream&> 
                    operator<<(ostream &out, const basic_string<T> &v);
template<class T> ostream& operator<<(ostream& out,const list<T>& v);
template<class T, class U> ostream& operator<<(ostream& out,const set<T, U>& v);
template<class T> ostream& operator<<(ostream& out,const multiset<T>& v);
template<class T> ostream& operator<<(ostream& out,const unordered_set<T>& v);
template<class T> ostream& operator<<(ostream& out,const deque<T>& v);
template<class T,size_t SIZ> ostream& operator<<(ostream& out,const array<T,SIZ>& v);
template<class T1,class T2> ostream& operator<<(ostream& out,const map<T1,T2>& v);
template<class T1,class T2> ostream& operator<<(ostream& out,const multimap<T1,T2>& v);
template<class T1,class T2> ostream& operator<<(ostream& out,const unordered_map<T1,T2>& v);
template<class T> ostream &operator<<(ostream &out,queue<T> q);
template<class T> ostream &operator<<(ostream &out,priority_queue<T> q);
template<class T, class Cmp> ostream &operator<<(ostream &out, priority_queue<T, vector<T>, Cmp> q);
template<class T> ostream &operator<<(ostream &out,stack<T> v);
ostream& operator<<(ostream& out,__int128_t a);

    // pair
    template<class T1,class T2> 
    ostream &operator<<(ostream &out,pair<T1,T2> a) {
        return out<<'('<<a.first<<','<<a.second<<')';
    }
    // tuple
    template <class Tuple, std::size_t N>
    struct TuplePrinter {
        static void print(ostream& out,const Tuple &t) {
            TuplePrinter<Tuple, N - 1>::print(out, t); ///< 递归
            out << "," << std::get<N - 1>(t); ///< 第 N-1 个元素
        }
    };
    template <class Tuple>
    struct TuplePrinter<Tuple, 1> {///< 递归终止， N == 1
        static void print(ostream& out,const Tuple &t) {
            out << std::get<0>(t); ///< 第 0 个元素
        }
    };
    /// @note 可变参模板函数
    template <class... Args>
    ostream& operator<<(ostream& out, const std::tuple<Args...> &t) {
        out << "(";
        /// @note tuple 类型、参数个数
        TuplePrinter<decltype(t), sizeof...(Args)>::print(out,t);
        return out << ")";
    }

    // sequnce
    #define _sequnce(Type)										\
    template<class T>											\
    ostream& operator<<(ostream& out,const Type<T>& v) {		\
        out<<'{';												\
        int f=0;												\
        for (T x:v) {											\
            if(f++) out<<","; 									\
            out<<x;												\
        }														\
        return out<<'}';										\
    }
    _sequnce(vector)
    _sequnce(list)
    _sequnce(multiset)
    _sequnce(unordered_set)
    _sequnce(deque)
    #undef _sequnce

    template<class T, class U>
    ostream& operator<<(ostream& out,const set<T, U>& v) {
        out<<'{';
        int f=0;
        for (T x:v) {
            if(f++) out<<",";
            out<<x;
        }
        return out<<'}';
    }

    template<typename T>
    enable_if_t<!is_same_v<T, char>, ostream&>
    operator<<(ostream &out, const basic_string<T> &v) {
        out<<'{';
        int f=0;
        for (auto x:v) {
            if(f++) out<<",";
            out<<x;
        }
        return out<<'}';
    }

    // array
    template<class T,size_t SIZ> 
    ostream& operator<<(ostream& out,const array<T,SIZ>& v) {
        out<<'{';
        int f=0;
        for (T x:v) {
            if (f++) out<<",";
            out<<x;
        }
        return out<<'}';
    }

    // map
    #define _map(Type)											\
    template<class T1,class T2>									\
    ostream& operator<<(ostream& out,const Type<T1,T2>& v) {	\
        out<<'{';												\
        int f=0;												\
        for (pair<T1,T2> x:v) {									\
            if(f++) out<<",";									\
            out<<x;												\
        }														\
        return out<<'}';										\
    }
    _map(map)
    _map(multimap)
    _map(unordered_map)
    #undef _map

    // queue
    template<class T>
    ostream &operator<<(ostream &out,queue<T> q) {
        out<<'{';
        for (int f=0; q.size(); q.pop()) {
            if (f++) out<<",";
            out<<q.front();
        }
        return out<<'}';
    }
    // priority_queue
    template<class T> 
    ostream &operator<<(ostream &out,priority_queue<T> q) {
        out<<'{';
        for (int f=0; q.size(); q.pop()) {
            if (f++) out<<",";
            out<<q.top();
        }
        return out<<'}';
    }
    template<class T, class Cmp> 
    ostream &operator<<(ostream &out, priority_queue<T, vector<T>, Cmp> q) {
        out<<'{';
        for (int f=0; q.size(); q.pop()) {
            if (f++) out<<",";
            out<<q.top();
        }
        return out<<'}';
    }
    // stack
    template<class T> 
    ostream &operator<<(ostream &out,stack<T> v) {
        stack<T> st;
        for (; v.size(); v.pop()) st.push(v.top());
        out<<'{';
        for (int f=0; st.size(); st.pop()) {
            if (f++) out<<",";
            out<<st.top();
        }
        return out<<'}';
    }
    // int128
    ostream& operator<<(ostream& out,__int128_t a) {
        if(!a) return out<<0;
        if(a<0) {
            out<<'-';
            a=-a;
        }
        static int b[40], bn;
        for(bn=0; a; a/=10)
            b[++bn]=a%10;
        for(int i=bn; i>0; --i)
            out<<b[i];
        return out;
    }
    // struct
    struct Any { template<typename T> operator T(); };
    template<std::size_t N> struct Tag : Tag<N - 1> {};
    template<> struct Tag<0> {};
    template<typename T> constexpr auto size_(Tag<0>) -> decltype(0u) { return 0; }
    template<typename T> constexpr auto size_(Tag<1>) -> decltype(T{ Any{} }, 0) { return 1; }
    template<typename T> constexpr auto size_(Tag<2>) -> decltype(T{ Any{}, Any{} }, 0) { return 2; }
    template<typename T> constexpr auto size_(Tag<3>) -> decltype(T{ Any{}, Any{}, Any{} }, 0) { return 3; }
    template<typename T> constexpr auto size_(Tag<4>) -> decltype(T{ Any{}, Any{}, Any{}, Any{} }, 0) { return 4; }
    template<typename T> constexpr auto size_(Tag<5>) -> decltype(T{ Any{}, Any{}, Any{}, Any{}, Any{} }, 0) { return 5; }
    template<typename T> constexpr auto size_(Tag<6>) -> decltype(T{ Any{}, Any{}, Any{}, Any{}, Any{}, Any{} }, 0) { return 6; }
    template<typename T> constexpr auto size() { return size_<T>(Tag<6>{}); }
    template<class T>
    ostream& out_struct(ostream& out,T arg) {
        out << '{';
        constexpr auto cnt = size<T>();
        if constexpr (cnt == 1) {
            const auto &[m1] = arg;
            out<<m1;
        } else if constexpr (cnt == 2) {
            const auto &[m1, m2] = arg;
            out<<m1<<",";
            out<<m2;
        } else if constexpr (cnt == 3) {
            const auto &[m1, m2, m3] = arg;
            out<<m1<<",";
            out<<m2<<",";
            out<<m3;
        } else if constexpr (cnt == 4) {
            const auto &[m1, m2, m3, m4] = arg;
            out<<m1<<",";
            out<<m2<<",";
            out<<m3<<",";
            out<<m4;
        } else if constexpr (cnt == 5) {
            const auto &[m1, m2, m3, m4, m5] = arg;
            out<<m1<<",";
            out<<m2<<",";
            out<<m3<<",";
            out<<m4<<",";
            out<<m5;
        } else if constexpr (cnt == 6) {
            const auto &[m1, m2, m3, m4, m5, m6] = arg;
            out<<m1<<",";
            out<<m2<<",";
            out<<m3<<",";
            out<<m4<<",";
            out<<m5<<",";
            out<<m6;
        }else {
            out<<"UnkownType";
        }
        return out << '}';
    }
}



// -------------------------__print----------------------
string __varname;
int __idx;
void __print() {
    cerr<<"debug"<<endl;
}
template<class T>
void __print(T x) {
    while(__idx<(int)__varname.size() && __varname[__idx]!=',')
        cerr<<__varname[__idx++];
    __idx++;
    cerr<<" = ";
    if constexpr ((std::is_aggregate_v<T>)) {
        out_struct(cerr, x);
    }else {
        cerr<<x;
    }
    cerr<<'\n';
}
template<class T,class...Ts> 
void __print(T x,Ts...sub) {
    while(__idx<(int)__varname.size() && __varname[__idx]!=',')
        cerr<<__varname[__idx++];
    __idx++;
    cerr<<" = ";
    if constexpr ((std::is_aggregate_v<T>)) {
        out_struct(cerr, x);
    }else {
        cerr<<x;
    }
    cerr<<" | ";
    __print(sub...);
}


template<class T>
void __print_n(T* a,int n) {
    cerr<<"{";
    for (int i=0; i<n; ++i) {
        if(i) cerr<<",";
        cerr<<a[i];
    }
    cerr<<"}"<<'\n';
}
template<class T>
void __print_n(const T& a,int n) {
    cerr<<"{";
    for (int i=0; i<n; ++i) {
        if(i) cerr<<",";
        cerr<<a[i];
    }
    cerr<<"}"<<'\n';
}

#endif

#if 0
    vector<pair<int,int>> a{{1,2},{3,4}};
    array<array<int,3>,2> b{1,2,3,4,5};
    bitset<10> c(127);
    map<int,int> d{{1,2},{3,4}};
    queue<int> e({1,2,3});
    stack<int> f({45,12});
    deque<int> deq({1,2});
    tuple<int64_t,int> x{1,2};
    
    debug(a,b,c,d,e,f,deq,x);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> q;
    q.emplace(1,2);
    q.emplace(3,4);

    __int128_t i1 = 128;
    
    struct Node {
        int x;
        string s;
        int64_t a;
        char c='z';
    };
    Node n;
    
    debug(q, i1, n);
#endif
