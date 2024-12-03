// https://cses.fi/problemset/result/10903637/
const int MS = 1e5 +10  ;
int n, m;
int tot;
int root;
struct node {
    int l, r;
    int sum;
}t[MS * 4];
void push_up(int rt) {
    t[rt].sum = t[t[rt].l].sum + t[t[rt].r].sum;
}
// u can add any value between [ l ,r  ]
// l ,r should be fixed dont change 
void update(int rt, int l, int r, int pos, int k) {
    if (l == r && l == pos) {
        t[rt].sum += k;
        return;
    }
    int m = l + r >> 1;
    if (m >= pos){
        if ( !t[rt].l) t[rt].l = ++tot ;
        update(t[rt].l, l, m, pos, k);

    } 
    else {
        if ( !t[rt].r) t[rt].r = ++ tot ;
        update(t[rt].r, m + 1, r, pos, k);
    }
    push_up(rt);
}
int query(int rt, int L, int R, int l, int r) { // [ L ,R ]
    if (L <= l && r <= R) {
        return t[rt].sum;
    }
    int m = l + r >> 1;
    int ans = 0;
    if (m >= L) ans += query(t[rt].l, L, R, l, m);
    if (m < R) ans += query(t[rt].r, L, R, m + 1, r);
    return ans;
}
int kth(int rt, int l, int r, int k) {
    if (l == r)return l;
    int mid = l + r >> 1;
    if (k <= t[t[rt].l].sum)return kth(t[rt].l, l, mid, k);
    else return kth(t[rt].r, mid + 1, r, k - t[t[rt].l].sum);
}


const int N = 1e9 ; 
void solve(){
    tot = 1 , root = 1 ;
    // in this case our range [ -N , N ]; 
    update( 1 , -N , N , 1e8 , 1 );  
    update( 1 , -N , N , -1e7 , 1 );
    cout << query(1 , -N ,N ,-N , N );   
}