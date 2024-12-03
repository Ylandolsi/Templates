// https://cses.fi/problemset/result/11134612/

// https://usaco.guide/plat/hld short hld 
struct Node {
    int ans = 0  ;
    void leaf(int val) {
        ans = val;
    }
    void pull(const Node &a, const Node &b) {
        ans = max( a.ans , b.ans ) ;
    }
};
template <typename Node >
struct SegTree {
    int n, size, log;
    vector<Node> d;
    Node neutral ;
 
    SegTree(int _n) : SegTree(vector<int>(_n)) {}
 
    SegTree(const vector<int>& a) {
        n = (int) a.size();
        size = n <= 1 ? 1 : 1 << (1 + __lg(n - 1));
        log = __builtin_ctz(size);
        d.resize(size << 1);
        for (int i = 0; i < n; i++) d[size + i].leaf (a[i]);
        for (int i = size - 1; i >= 1; i--) Pull(i);
    }
 
    void Pull(int k) {
        d[k].pull(d[k << 1], d[(k << 1) + 1]);
    }
    
    Node get(int p) { // get value at position P of array ! 
        return d[p + size ];
    }
 
    Node query(int l, int r) { // [ l , r]
        r++ ; 
        if (l == r ) return neutral ;
        l += size, r += size  ;
 
        Node sml , smr ;
        while (l < r) {
            if (l & 1) sml.pull(sml, d[l++]);
            if (r & 1) smr.pull(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
 
        sml.pull(sml, smr);
        return sml ; 
    }
 
    Node all_prod() { return d[1]; }
 
    void set(int p, int x) {
        p += size;
        d[p].ans = x;
        for (int i = 1; i <= log; i++) Pull(p >> i);
    }
    void update(int p, int f) {
        p += size;
        d[p].ans++ ; 
        for (int i = 1; i <= log; i++) Pull(p >> i);
    }
};

// O(Q logN ^2)
template <typename T = int, const int VAL_ON_EDGE = 0>
struct HLD {
    // VAL_ON_EDGE = 0 if value on nodes
    // VAL_ON_EDGE = 1 if value on edges
    const vector<vector<T>> &adj;
    vector<T> dep, par, root, pos, SubtreeSz, child, tin;
    int nxtPos;
    SegTree<Node> seg;
 
    HLD(int n, const vector<vector<T>>& G, int treeRoot = 1) : adj(G), seg(n + 3) {
        nxtPos = 1;
        dep = par = root = pos = SubtreeSz = child = vector<T>(n + 5);
        init(treeRoot);
        build(treeRoot);
    }
 
 
    void init(int u, int p = -1, int d = 0) {
        dep[u] = d, par[u] = p, SubtreeSz[u] = 1;
        for (auto v : adj[u]) {
            if (v == p) continue;
            init(v, u, d + 1);
            SubtreeSz[u] += SubtreeSz[v];
            if (SubtreeSz[v] > SubtreeSz[child[u]])
                child[u] = v;
        }
    }
 
    int get_lca(int u, int v) {
        while (root[u] != root[v]) {
            if (dep[root[u]] < dep[root[v]])
                swap(u, v);
            u = par[root[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
 
    void build(int u, bool newChain = true) {
        root[u] = newChain ? u : root[par[u]];
        pos[u] = nxtPos++;
        if (child[u])
            build(child[u], false);
        for (auto v : adj[u]) {
            if (v == par[u] || v == child[u]) continue;
            build(v, true);
        }
    }
 
  
    void makeULower(int& u, int& v) {
        if (dep[root[u]] < dep[root[v]] || (root[u] == root[v] && dep[u] < dep[v]))
            swap(u, v);
    }
 
    Pair<T> moveUp(int& u) {
        Pair<T> ret = {pos[root[u]], pos[u]};
        u = par[root[u]];
        return ret;
    }
 
    
 
    // used only when update path from u to v 
    vector<Pair<T>> queryPath(int u, int v) {
        // return all ranges in segment tree
        vector<Pair<T>> ret;
        // move u and v to the same chain
        while (root[u] != root[v]) {
            makeULower(u, v);
            ret.push_back(moveUp(u));
        }
        makeULower(u, v);
        if (!VAL_ON_EDGE)
            ret.push_back({pos[v], pos[u]});
        else if (u != v)
            ret.push_back({pos[v] + 1, pos[u]});
        return ret;
    }
 
    int getChild(int u, int v) {
        return (par[u] == v) ? u : v;
    }
 
    void update(int u, T val) {
        seg.set(pos[u], val); // maek sure always set or update or whatever here ! 
    }
 
    // update value of edge u-v
    // update all the values between u v 
    void update(int u, int v, T val) {
        for (auto& [l, r] : queryPath(u, v))
            seg.update(l, r, val); // here also same thing 
    }
 
    Node query(int u, int v) {
        Node L;
        while (root[u] != root[v]) {
            makeULower(u , v ); 
            L.pull(seg.query(pos[root[u]], pos[u]), L) ;
            moveUp(u);
        }
        if ( dep[u] > dep[v]) swap( u , v );
        L.pull(seg.query(pos[u],pos[v]), L) ;
 
        return L;
    }
};


HLD<int> hld(n, adj); // nodes can be from ( 0 - n ) // rooted at 1 by defautl ( one indexed nodes ! ) 
for  (int i = 1 ; i<= n ; i++ ) hld.update(i , a[i-1]) ; 
