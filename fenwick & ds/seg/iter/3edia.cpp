// https://cses.fi/problemset/result/11132115/
struct Node {
    int ans = 0  ;
    void leaf(int val) {
        ans = val;
    }
    void pull(const Node &a, const Node &b) {
        ans = a.ans + b.ans;
    }
};
// O(n), O(log(n))
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
 
    Node query(int l, int r) { // [ l , r ]
        r++ ; 
        if (l == r) return neutral ;
        l += size, r += size;
 
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
        d[p].ans+= f ; 
        for (int i = 1; i <= log; i++) Pull(p >> i);
    }
};