
// https://cses.fi/problemset/hack/1144/entry/8340563/
typedef struct Node {
    int nl;
    int nr;
    int num;
    Node *lc;
    Node *rc;
    Node(int _nl, int _nr, int _num): nl(_nl), nr(_nr), num(_num), lc(NULL), rc(NULL) {}
}node;
 
int arr[200005];
node *root;
 
void pull(node *now) {
    now->num = (now->lc?now->lc->num:0) + (now->rc?now->rc->num:0);
}
 
void update(node *now, int tar, int val) {
    if (now->nl == now->nr && now->nl == tar) {
        now->num += val;
        return;
    }
    int mid = (now->nl+now->nr)>>1;
    if (tar <= mid) {
        if (!now->lc) now->lc = new node(now->nl, mid, 0);
        update(now->lc, tar, val);
    }else {
        if (!now->rc) now->rc = new node(mid+1, now->nr, 0);
        update(now->rc, tar, val);
    }
    pull(now);
}
 
int query(node *now, int tl, int tr) { // [tl , tr ]
    if (tl <= now->nl && now->nr <= tr) {
        return now->num;
    }
    int mid = (now->nl+now->nr)>>1, ret = 0;
    if (tl <= mid) {
        if (now->lc) ret += query(now->lc, tl, tr);
    }
    if (mid < tr) {
        if (now->rc) ret += query(now->rc, tl, tr);
    }
    return ret;
}
