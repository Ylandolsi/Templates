struct implicitLazySegTree {
 
	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		ll sum;
		ll lazyAdd;
		Node(){
			lch = 0  ,rch = 0 ; 
			sum = 0 , lazyadd=  0 ; 
		}
	};
 
	int sz;
	vector<Node> tree;
    	// sz  = max element (abs( X )) ( abs X <= sz )
	implicitLazySegTree(int _sz) : sz(_sz) {
		tree.push_back({0, 0, 0, 0}); //acts as null
		tree.push_back({0, 0, 0, 0}); //root node
	}

	void push(int v, int tl, int tr) {
		assert(v != 0);
		if (tl != tr && tree[v].lCh == 0) {
            // add new childrens !! 
			tree.push_back(tree[0]);
			tree[v].lCh = tree.size() - 1;
			tree.push_back(tree[0]);
			tree[v].rCh = tree.size() - 1;
		}
		if (tree[v].lazyAdd) {
			tree[v].sum += (tr-tl+1)*tree[v].lazyAdd;
			if (tl != tr) {
				assert(tree[v].lCh != 0);//need to push lazy to childs, else incorrect
				assert(tree[v].rCh != 0);
				tree[tree[v].lCh].lazyAdd += tree[v].lazyAdd;
				tree[tree[v].rCh].lazyAdd += tree[v].lazyAdd;
			}
			tree[v].lazyAdd = 0;
		}
	}
 
	//add diff to each value in range [l,r]
	void update(int l, int r, ll diff) {
		update(1, -sz   , sz , l, r, diff);
	}
	void update(int v, int tl, int tr, int l, int r, ll diff) {
		if (tr < l || r < tl)
			return;
		push(v, tl, tr);
		int tm = (tl + tr) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (l <= tl && tr <= r) {
			tree[v].sum += (tr-tl+1)*diff;
			if (tl != tr) {
				assert(lCh != 0);
				assert(rCh != 0);
				tree[lCh].lazyAdd += diff;
				tree[rCh].lazyAdd += diff;
			}
			return;
		}
		update(lCh, tl, tm, l, r, diff);
		update(rCh, tm + 1, tr, l, r, diff);
		tree[v].sum = tree[lCh].sum + tree[rCh].sum;
	}
 
	//sum on range [l,r]
	ll query(int l, int r) {
		return query(1, -(sz-1), sz - 1, l, r);
	}
	ll query(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (tr < l || r < tl)
			return 0;
		if (l <= tl && tr <= r)
			return tree[v].sum;
		int tm = (tl + tr) / 2;
		return query(tree[v].lCh, tl, tm, l, r) +
		           query(tree[v].rCh, tm + 1, tr, l, r);
	}
};
void solve(){
    implicitLazySegTree sg (11); 
    sg.update(-10 , -8 ,5 );
    print ( sg.query(-10 ,-8 )) ;     
}
