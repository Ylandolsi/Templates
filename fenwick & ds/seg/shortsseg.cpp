vi st ;
void init( int n  ){
    st = vi(2*n);
} 
void update(int idx, int val) {
	st[idx += n] = val;
	for (idx /= 2; idx; idx /= 2) st[idx] = max(st[2 * idx], st[2 * idx + 1]);
}

int query(int lo, int hi) {
	int ra = 0, rb = 0;
	for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
		if (lo & 1) ra = max(ra, st[lo++]);
		if (hi & 1) rb = max(rb, st[--hi]);
	}
	return max(ra, rb);
}
////////////

int Tree[4 * N], a[N];
int lazy[4 * N], n;
int upd[4 * N];

int merge(int a, int b) { return max(a, b); }

void unlazy(int id) {
    if (upd[id] == 0) return;
    int l = 2 * id + 1, r = 2 * id + 2;
    Tree[id] += lazy[id]; // apply update ; 
        // propagate 
        lazy[l] += lazy[id] , upd[l] = 1; 
        lazy[r] += lazy[id] , upd[r] = 1;

    upd[id] = lazy[id] = 0;
}

void build(int ns = 1, int ne = n, int id = 0) {
    if (ns == ne) {
        Tree[id] = a[ns];
        return;
    }
    int l = 2 * id + 1, r = 2 * id + 2, md = ns + (ne - ns) / 2;
    build(ns, md, l);
    build(md + 1, ne, r);
    Tree[id] = merge(Tree[l], Tree[r]);
}

void update(int qs, int qe, int val, int ns = 1, int ne = n, int id = 0) {
    unlazy(id);
    if (qs > ne || qe < ns) return;
    if (qs <= ns && ne <= qe) {
        lazy[id] += val, upd[id] = 1;
        unlazy(id);
        return;
    }
    int l = 2 * id + 1, r = 2 * id + 2, md = ns + (ne - ns) / 2;
    update(qs, qe, val, ns, md, l);
    update(qs, qe, val, md + 1, ne, r);
    Tree[id] = merge(Tree[l], Tree[r]);
}

int query(int qs, int qe, int ns = 1, int ne = n, int id = 0) {
    unlazy(id);
    if (qs > ne || qe < ns) return 0;
    if (qs <= ns && ne <= qe) return Tree[id];
    int l = 2 * id + 1, r = 2 * id + 2, md = ns + (ne - ns) / 2;
    return merge(query(qs, qe, ns, md, l), query(qs, qe, md + 1, ne, r));
}
