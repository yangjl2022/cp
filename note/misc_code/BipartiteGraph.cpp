#include<bits/stdc++.h>
using namespace std;
// copy from https://judge.yosupo.jp/submission/97319


// https://judge.yosupo.jp/submission/59969 (max matching) and https://judge.yosupo.jp/submission/55732 (edge coloring)
// Max matching in O(E root(V)) --> considerably fast, runs under 100ms for E, V <= 2e5 on library checker
// Edge coloring in O(E root(V) log(D)) where D is max degree
struct BipartiteGraph{
    private:
        const int n;
        const int Lpart, Rpart;
        int matching_num;
        vector<array<int, 2>> raw_edges;// edges from left to right 
        vector<int> num_starts, final_edges;

    public:
        std::vector<int> match;

        BipartiteGraph(int a, int b, int p = 0): Lpart(a), Rpart(b), n(a + b), matching_num(-1), num_starts(a + b + 1, 0), match(n, -1) {
            raw_edges.reserve(p);
        }
        BipartiteGraph(int a, int b, const vector<array<int, 2>>& Edges): Lpart(a), Rpart(b), n(a + b), matching_num(-1), raw_edges(Edges), num_starts(a + b + 1, 0), match(n, -1) {}
        BipartiteGraph(int a, int b, const vector<pair<int, int>>& Edges): Lpart(a), Rpart(b), n(a + b), matching_num(-1), num_starts(a + b + 1, 0), match(n, -1), raw_edges(Edges.size()) {
            const int p = Edges.size(); 
            for(int i = 0; i < p; ++i)
                raw_edges[i] = {Edges[i].first, Edges[i].second};
        }

        inline void addEdge(int u, int v){ raw_edges.push_back({u, v});}

        inline void clear() {
            raw_edges.clear(); final_edges.clear();
            matching_num = -1; 
            fill(num_starts.begin(), num_starts.end(), 0);
            fill(match.begin(), match.end(), -1);

        }
    private:
        struct UnionFind {
            vector<int> UF; UnionFind(int N) : UF(N, -1) {}
            inline int find(int v) { return UF[v] < 0 ? v : UF[v] = find(UF[v]); }
            inline void join(int v, int w) {
            if ((v = find(v)) == (w = find(w))) return;
            if (UF[v] > UF[w]) swap(v, w);
            UF[v] += UF[w]; UF[w] = v; return;}
        };

          struct Pair {
            int s, v; Pair(int s, int v) : s(s), v(v) {}
            bool operator < (const Pair &o) const { return s > o.s; }
          };
        static inline void build(vector<int>& num_starts, vector<int>& final_edges, const int& n, const int& Lpart, const vector<array<int, 2>>& raw_edges) {
            for(const auto& [u, v]: raw_edges) {
                ++num_starts[u + 1];
                ++num_starts[v + Lpart + 1];
            }
            for(int i = 1; i <= n; ++i) num_starts[i] += num_starts[i - 1];
            final_edges.resize(num_starts[n]);
            vector<int> start(num_starts.begin(), num_starts.begin() + n);

            for(const auto& [u, v]: raw_edges){
                final_edges[start[u]++] = v + Lpart;
                final_edges[start[v + Lpart]++] = u;
            }

        }
        static inline int __maxMatching(vector<int>& match, vector<int>& num_starts, vector<int>& final_edges, const int& n, const int& Lpart, const vector<array<int, 2>>& raw_edges){
            if (final_edges.size() != raw_edges.size()) build(num_starts, final_edges, n, Lpart, raw_edges);

            int res = 0; bool update = true;
            std::vector<int> pre(Lpart, -1), root(Lpart, -1);
            while(update){
                update = false; std::queue<int> que;
                for(int i = 0; i < Lpart; i++){
                    if(!~match[i]){
                        root[i] = i; que.push(i);
                    }
                }
                while(que.size()){
                    int v = que.front(); que.pop();
                    if(~match[root[v]]) continue;
                    for(int cur = num_starts[v]; cur < num_starts[v + 1]; ++cur){
                        int nv = final_edges[cur];
                        if(!~match[nv]){
                            while(~nv){
                                match[nv] = v; std::swap(match[v], nv); v = pre[v];
                            }
                            update = true; ++res;
                            break;
                        }
                        nv = match[nv];
                        if(~pre[nv]) continue;
                        pre[nv] = v, root[nv] = root[v];
                        que.push(nv);
                    }
                }
                if(update){
                    std::fill(pre.begin(), pre.end(), -1);
                    std::fill(root.begin(), root.end(), -1);
                }
            }
            return res;
        }

        static inline int makeDRegular(int &V, vector<pair<int, int>> &edges, int &L) { // O(V log V + E), adds atmost E + D new edges
            vector<int> deg(V, 0); 
            for (auto &&e : edges) {
              deg[e.first]++; deg[e.second]++;
            }
            int D = *max_element(deg.begin(), deg.end()); UnionFind uf(V);
            vector<int> cnt(2, 0);
            int R = V - L;
            for (int s = 0; s < 2; s++) {
                std::priority_queue<Pair> PQ;
                  for(int v = s * L; v < L + s * R; ++v) {
                      PQ.push({deg[v], v});
                  }
                cnt[s] = PQ.size();
                while (int(PQ.size()) >= 2) {
                    Pair a = PQ.top(); PQ.pop(); Pair b = PQ.top(); PQ.pop();
                    if (a.s + b.s <= D) { uf.join(a.v, b.v); PQ.emplace(a.s + b.s, a.v); --cnt[s];}
                    else break;
                }
            }
            vector<int> id(V, -1); 
            if (cnt[0] >= cnt[1]) {
                int curId = 0;
                for(int v = 0;  v < V; ++v)
                    if (uf.find(v) == v)
                        id[v] = curId++;
            }
            else{
                int curId = 0;
                for(int v = V - 1;  v >= 0; --v)
                    if (uf.find(v) == v)
                        id[v] = curId++;
                for(auto &&e: edges){
                    swap(e.first, e.second);
                }
                swap(cnt[0], cnt[1]);
            }
            assert (cnt[0] >= cnt[1]);
            deg.assign(V = cnt[0] * 2, 0); edges.reserve(V * D / 2);

            for (auto &&e : edges) {
              deg[e.first = id[uf.find(e.first)]]++;
              deg[e.second = id[uf.find(e.second)]]++;
              assert (e.first < e.second);
            }

            for(int v = 0, w = cnt[0]; v < cnt[0]; ++v) {
                while (deg[v] < D){
                    while (w < V && deg[w] == D) ++w;
                    int x = min(D - deg[w], D - deg[v]);
                    for(int k = 0; k < x; ++k){
                        edges.emplace_back(v, w);
                    }
                    deg[v] += x;
                    deg[w] += x;
                }
            }
            L = cnt[0];
            return D;
          }
          static inline vector<int> eulerianCircuit(int V, const vector<pair<int, int>> &edges, const vector<int> &inds) {
            vector<vector<std::pair<int, int>>> G(V); vector<int> circuit;
            for (int i = 0; i < int(inds.size()); i++) {
                  int v, w; tie(v, w) = edges[inds[i]];
                  G[v].emplace_back(w, i); G[w].emplace_back(v, i);
            }
            vector<bool> vis1(V, false), vis2(inds.size(), false);
            vector<std::pair<int, int>> stk; for (int s = 0; s < V; s++) if (!vis1[s]) {
                  stk.clear(); stk.emplace_back(s, -1); while (!stk.empty()) {
                int v, w, e; tie(v, e) = stk.back(); vis1[v] = true;
                if (G[v].empty()) { circuit.emplace_back(e); stk.pop_back(); }
                else {
                  tie(w, e) = G[v].back(); G[v].pop_back();
                  if (!vis2[e]) { vis2[e] = true; stk.emplace_back(w, e); }
                }
              }
              circuit.pop_back();
            }
            for (auto &&e : circuit) e = inds[e];
            return circuit;
          }
    public:
        int maxMatching() {
            return matching_num = __maxMatching(match, num_starts, final_edges, n, Lpart, raw_edges);
        }

        std::vector<int> edgeColoring() { // Same ordering as add edges (raw_edges)
            int L = Lpart, R = Rpart;
            int V = L + R;
            const int E = raw_edges.size();
            vector<int> color(E, -1);
            vector<pair<int, int>> edges; edges.reserve(E);
            for (const auto &e : raw_edges) {
                assert(e[0] < L && e[1] < R);
                edges.push_back({e[0], e[1] + L});
            }

            int D = makeDRegular(V, edges, L), curCol = 0;

            for(auto &&e: edges){
                assert (e.first < L && e.second >= L);
            }
            R = L;

            BipartiteGraph mm(L, L);

            function<void(int, const vector<int> &)> rec = [&] ( 
                int d, const vector<int> &inds) {
              if (d == 0) return;
              else if (d == 1) {
                for (int e : inds) if (e < int(color.size())) color[e] = curCol;
                curCol++;
              } else if (d % 2 == 0) {
                vector<int> circuit = eulerianCircuit(V, edges, inds), half1, half2;
                half1.reserve(circuit.size() / 2); half2.reserve(circuit.size() / 2);
                for (int i = 0; i < int(circuit.size()); i += 2) {
                  half1.push_back(circuit[i]); half2.push_back(circuit[i + 1]);
                }
                rec(d / 2, half1); rec(d / 2, half2);
              } else {
                  mm.clear();
                for (int e : inds) {
                  int v, w; tie(v, w) = edges[e]; 
                  mm.addEdge(v, w - L);
                }
                mm.maxMatching();
                vector<int> unmatched;
                for (int e : inds) {
                  int v, w; tie(v, w) = edges[e]; 
                  if (mm.match[v] == w) {
                    mm.match[v] = -1; 
                    mm.match[w] = -1;
                    if (e < int(color.size())) color[e] = curCol;
                  } else unmatched.push_back(e);
                }
                curCol++; rec(d - 1, unmatched);
              }
            };
            vector<int> inds(edges.size()); iota(inds.begin(), inds.end(), 0);
            rec(D, inds);	
            return color;
        }

        std::vector<std::array<int, 2>> maxMatchingEdges() {
            if (matching_num == -1)
                maxMatching();
            std::vector<std::array<int, 2>> ans; ans.reserve(matching_num);

            for(int i = 0; i < Lpart; ++i){
                if (match[i] != -1)
                    ans.push_back({i, match[i] - Lpart});
            }
            return ans;
        }


        inline int matchedPair(int u) const {return match[u];}

        std::vector<std::array<int, 2>> minimumEdgeCover(){ // Minimum edges to cover each vertex atleast once.
            if (matching_num == -1)
                maxMatching();
            int idx = 0;
            std::vector<std::array<int, 2>> res(n - matching_num);
            for(int i = 0; i < Lpart; i++){
                if(match[i] != -1) res[idx++] = {i, match[i]};
                else res[idx++] = {i, final_edges[num_starts[i + 1] - 1]};
            }
            assert(n - matching_num == idx);
            return res;
        }

        std::pair<std::vector<int>, std::vector<int>> minimumVertexCover(){
            if (matching_num == -1)
                maxMatching();
            std::vector<bool> reachable(n);
            for(int i = 0; i < Lpart; i++){
                if(match[i] != -1) continue;
                std::queue<int> que;
                que.push(i);
                while(que.size()){
                    int v = que.front(); que.pop();
                    reachable[v] = true;
                    for(int cur = num_starts[v]; cur < num_starts[v + 1]; ++cur){
                        const int nv = final_edges[cur];
                        if(reachable[nv]) continue;
                        if(v >= Lpart && match[v] == nv){
                            reachable[nv] = true;
                            que.push(nv);
                        }
                        if(v < Lpart && match[v] != nv){
                            reachable[nv] = true;
                            que.push(nv);
                        }
                    }
                }
            } 
            std::vector<int> left, right;
            for(int i = 0; i < n; i++){
                if(i < Lpart && !reachable[i]) left.emplace_back(i);
                if(i >= Lpart && reachable[i]) right.emplace_back(i);
            }  
            return std::make_pair(left, right);
        }   

        std::pair<std::vector<int>, std::vector<int>> maxIndependentSet(){
            if (matching_num == -1)
                maxMatching();

            std::vector<int> left, right;
            auto p = minimumVertexCover();
            std::vector<bool> complement(n, false);
            for(const int &v : p.first) complement[v] = true;
            for(const int &v : p.second) complement[v] = true;
            for(int i = 0; i < n; i++){
                if(complement[i]) continue;
                if(i < Lpart) right.emplace_back(i);
                else left.emplace_back(i);
            }
            return std::make_pair(left, right);
        }
};