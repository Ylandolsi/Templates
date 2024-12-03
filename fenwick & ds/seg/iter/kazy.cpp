// https://cses.fi/problemset/hack/1651/entry/11132021/
// https://cses.fi/problemset/result/11132199/
struct Node {
    int ans = 0, lazy = 0  ;
    bool islazy = 0 ; 
    void leaf(int val) {
        ans = val;
    }
    void pull(const Node &a, const Node &b) {
        ans = a.ans + b.ans;
    }
    void push(int val) {
        lazy += val;
        islazy = 1 ; 
    }
    void clean(){
        lazy = 0;
        islazy = 0 ; 
    }
    void apply( int vl ,  int sz ) {
        ans += vl * sz ;  
        // lazy of current node store the lazy of next childs ! 
    }
};
// O(n), O(log(n))
template <typename Node >
struct lazy_segtree {
    int n, size, log;
    vector<Node> d;
    Node neutral ;
 
    lazy_segtree(int _n) : lazy_segtree(vector<int>(_n)) {}
 
    lazy_segtree(const vector<int>& a) {
        n = a.size();
        size = n <= 1 ? 1 : 1 << (1 + __lg(n - 1));
        log = __builtin_ctz(size);
        d.resize(size << 1);
        for (int i = 0; i < n; i++) d[size + i].leaf (a[i]);
        for (int i = size - 1; i >= 1; i--) Pull(i);
    }
 
    void Pull(int k) {
        d[k].pull(d[k << 1], d[(k << 1) + 1]);
    }
 

    void all_apply(int k , int f ) {
        d[k].apply( f , 1 << (log - __lg(k)));
        // 1 << ( log - _lg(k) ) number of childs !
        if ( k < size ) d[k].push(f);
    }
 
    void push(int k) {
        if ( !d[k].islazy ) return ;
        // lazy of node K applied only on its children and not applied to 
        // current node ! 
        all_apply( k <<1 , d[k].lazy )  ; 
        all_apply( (k <<1)  + 1 , d[k].lazy )  ;
        d[k].clean();
    
    }
 
    void set(int p, int x) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p].ans = x;
        for (int i = 1; i <= log; i++) Pull(p >> i);
    }
 
    Node get(int p) { // point query P ! 
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
 
    Node query(int l, int r) { // [ l , r ]
        r++ ; 
        if (l == r) return neutral ;
        l += size, r += size;
 
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
 
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
 
    void update(int p, int f) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p].apply(f , 1 ); 
        for (int i = 1; i <= log; i++) Pull(p >> i);
    }
 
    void update(int l, int r, int f) { // [ l , r ]
        r++ ; 
        if (l == r) return;
        l += size, r += size;
 
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
 
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) {
                    all_apply(l++ , f );
                }
                if (r & 1) {
                    --r ; 
                    all_apply(r , f );
                }
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
 
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) Pull(l >> i);
            if (((r >> i) << i) != r) Pull((r - 1) >> i);
        }
    }
};