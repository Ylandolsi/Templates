// O(log(n))
https://discord.com/channels/753345240529895537/753368833141506212/1288235733051772948
// F type 
// op merge 
// e natural value !

https://cses.fi/paste/1f0b80ee9c8f6291969d12/
https://codeforces.com/contest/1667/submission/282843666
/* 
    how to calcualte memory !
    nlogn * sizeof(node) / 10^6 
*/
ll op(ll a, ll b) { return max(a, b); }
ll e() { return -1e18; }

// R not included !
template <class F, class S, S (*op)(S, S), S (*e)()>
struct sparse_segtree {
    struct node {
        F l, r;
        S x = e();
        int lc = 0, rc = 0, p;
    };
    vector<node> d;
    int k = 0;

    int add_node(F l, F r, int p) {
        d.push_back(node());
        tie(d.back().l, d.back().r, d.back().p) = {l, r, p};
        return d.size() - 1;
    }

    int get_lc(int i) {
        if (!d[i].lc)
            d[i].lc = add_node(d[i].l, (d[i].l + d[i].r) >> 1, i);
        return d[i].lc;
    }

    int get_rc(int i) {
        if (!d[i].rc)
            d[i].rc = add_node((d[i].l + d[i].r) >> 1, d[i].r, i);
        return d[i].rc;
    }

    void update(int i) {
        d[i].x = op(d[d[i].lc].x, d[d[i].rc].x);
    }

    sparse_segtree(F l, F r) {
        add_node((F) -1, (F) -1, -1);
        add_node(l, r, 0);
    }

    S get(F i) {
        int j = 1;
        while (j and (i != d[j].l or d[j].l + 1 != d[j].r))
            j = i < (d[j].l + d[j].r) >> 1 ?
                d[j].lc :
                d[j].rc;
        return d[j].x;
    }
    // tbadl value = 
    void set(F i, S x) {
        int j = 1;
        while (d[j].l != i or d[j].l + 1 != d[j].r)
            j = i < (d[j].l + d[j].r) >> 1 ?
                get_lc(j) :
                get_rc(j);

        d[j].x = x;
        while (d[j].p) {
            j = d[j].p;
            update(j);
        }
    }
    // tzid +
    void apply(F i, S x) {
        int j = 1;
        d[j].x = op(d[j].x, x);
        while (d[j].l != i or d[j].l + 1 != d[j].r) {
            j = i < (d[j].l + d[j].r) >> 1 ?
                get_lc(j) :
                get_rc(j);
            d[j].x = op(d[j].x, x);
        }
    }

    S prod(F l, F r, int j = 1) {
        if (j == 0 or d[j].r <= l or d[j].l >= r)
            return e();
        if (l <= d[j].l and d[j].r <= r)
            return d[j].x;
        return op(
            prod(l, r, d[j].lc),
            prod(l, r, d[j].rc)
        );
    }
};
const int x = 1e9 ;
// limit range [ -x ,x ]
sparse_segtree<ll, ll, op, e> seggy(- (x + 1), x + 1);

this one is good also without pointer !
https://gist.github.com/nicotina04/9adef47dbc346c4581fe2d1d75e2bc21