#include<vector>
#include<random>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<cassert>
using namespace std;

namespace rd {
    mt19937_64 rng(random_device{}());

    /// @brief 随机产生 [l,r] 的整数
    template<typename T>
    T nextInteger(T l, T r) {
        assert(l <= r);
        return rng() % (r - l + 1) + l;
    }

    /// @brief 随机产生 [l,r] 的浮点数
    double nextDouble(double l, double r) {
        assert(l <= r);
        return (long double)rng() / numeric_limits<uint64_t>::max() * (r - l) + l;
    }

    /// @brief 随机产生 长度为len,值在[l,r]中的字符串
    string nextString(int len, char l = 'a', char r = 'z') {
        string s;
        for(int i = 0; i < len; ++i)
            s += nextInteger<int>(l, r);
        return s;
    }

    /// @brief 在[l,r]范围内抽取n个不重复的数
    template<typename T>
    vector<T> choose_unique(T l, T r, int n) {
        assert(r - l + 1 >= n);
        if(n >= (r - l + 1) / 10) {
            vector<T> alls(r - l + 1);
            iota(alls.begin(), alls.end(), l);
            return vector(alls.begin(), alls.begin() + r - l + 1);
        }
        set<T> st;
        while((int)st.size() < n)
            st.insert(rd::nextInteger(l, r));
        vector<T> result;
        for(T x : st)
            result.push_back(x);
        return result;
    }
} // namespace rd


/// @brief Edges 无权边集(u,v)
using Edges = vector<pair<int, int>>;
/// @brief WeightEdges 有权边集合(u,v,w)
using WeightEdges = vector<tuple<int, int, int>>;

/// @brief 图的节点标号从0开始
namespace ug {
    /// @brief 不改变图的结构，对图的节点编号打乱
    void shuffle_number(int n, Edges& e) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        shuffle(p.begin(), p.end(), rd::rng);
        for(auto& [x, y] : e) {
            x = p[x];
            y = p[y];
        }
        shuffle(e.begin(), e.end(), rd::rng);
    }

    /// @brief 返回一颗基环树的所有边，环大小至少为3
    Edges base_ring_tree(int n) {
        assert(n >= 3);
        vector<int> not_adj_0;
        Edges e;
        for(int i = 1; i < n; ++i) {// 先造一颗树
            int v = rd::nextInteger(0, i - 1);
            e.emplace_back(v, i);
            if(v) not_adj_0.push_back(i);
        }

        if(not_adj_0.size()) {
            int v = not_adj_0[rd::nextInteger(0, (int)not_adj_0.size() - 1)];
            e.emplace_back(0, v);
        } else {// 星型图
            int v = rd::nextInteger(2, n - 1);
            e.emplace_back(1, v);
        }
        shuffle_number(n, e);
        return e;
    }

    /// @brief 返回一个基环森林
    Edges base_ring_forest(int n) {
        Edges e;
        for(int i = 0; i < n; ++i) {
            e.emplace_back(i, rd::nextInteger(0, n - 1));
        }
        shuffle_number(n, e);
        return e;
    }
} // namespace ug

namespace dg {
    /// @brief 不改变图的结构，对图的节点编号打乱
    void shuffle_number(int n, WeightEdges& e) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        shuffle(p.begin(), p.end(), rd::rng);
        for(auto& [x, y, w] : e) {
            x = p[x];
            y = p[y];
        }
        shuffle(e.begin(), e.end(), rd::rng);
    }

    /// @brief 返回一个有向图的所有边
    /// @param w_range 边权范围 [first, second]
    WeightEdges new_directed_graph(int n, int m, pair<int, int> w_range = {1, 100}) {
        WeightEdges e(m);
        for(auto& [u, v, w] : e) {
            u = rd::nextInteger(0, n - 1);
            v = rd::nextInteger(0, n - 1);
            w = rd::nextInteger(w_range.first, w_range.second);
        }
        shuffle_number(n, e);
        return e;
    }

    /// @brief 返回一个无自环无重边的有向图的所有边
    /// @param w_range 边权范围 [first, second]
    WeightEdges new_simple_directed_graph(int n, int m, pair<int, int> w_range = make_pair(1, 100)) {
        assert(m <= 1ll * n * (n - 1));
        WeightEdges e(m);
        if(m <= 1ll * n * (n - 1) / 2) {
            set<pair<int, int>> st;
            for(auto& [u, v, w] : e) {
                while(true) {
                    u = rd::nextInteger(0, n - 1);
                    v = rd::nextInteger(0, n - 1);
                    if(u != v && !st.count({u,v}))
                        break;
                }
                w = rd::nextInteger(w_range.first, w_range.second);
                st.emplace(u, v);
            }
        } else {
            int del_num = 1ll * n * (n - 1) - m;
            set<pair<int, int>> st;
            while((int)st.size() < del_num) {
                int u, v;
                while(true) {
                    u = rd::nextInteger(0, n - 1);
                    v = rd::nextInteger(0, n - 1);
                    if(u != v && !st.count({u,v}))
                        break;
                }
                st.emplace(u, v);
            }
            for(int u = 0, i = 0; u < n; ++u) {
                for(int v = 0; v < n; ++v) {
                    if(u == v || st.count({u, v})) continue;
                    int w = rd::nextInteger(w_range.first, w_range.second);
                    e[i++] = {u, v, w};
                }
            }
        }
        shuffle_number(n, e);
        return e;
    }

}// namespace dg