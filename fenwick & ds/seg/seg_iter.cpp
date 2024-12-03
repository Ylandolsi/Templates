
// https://codeforces.com/contest/1904/submission/236562611

template<class T , typename F = function<int(int, int)>  > struct Seg { // comb(ID,b) = b
	F comb;
	T ID = 0; 
	int n; vector<T> seg;
	Seg(int _n , const F &Unite  , int neutral = 0   ) {
		n = _n , ID = neutral ; 
		comb = Unite ; 
		seg.assign(2*n,ID);
	}
	void add(int i, T val){tree[i+n] = val;}
	void build(){
		for (int i = n-1;i>0;--i) tree[i] = comb(tree[i<<1], tree[i<<1|1]);
	}
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	// set val at position p
	void set(int p, T val) {  p += n , seg[ p ] = val; for (p /= 2; p; p /= 2) pull(p); }
	void upd(int p, T val) {  p += n , seg[ p ] += val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// query on interval [l, r]
        if(l>r) return ID ;
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			// if l is odd means its right cilds of its parent 
			// take left child and move to ( node that adjacent to parent to right )
			// ,not ot parent ( bcz parent dosent include its left child  ! 
			if (l&1) ra = comb(ra,seg[l++]);
			// if not keep mocing up untill u found left child or root = 1 ! 

			// same logic of r
	
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
	void dbgit(){for(int i=0;i<n;i++)cout<<query(i,i)<<" ";cout<<'\n';}
};
inline int f1(int a, int b) { return max(a, b);};
inline int f2(int a, int b) { return min(a, b);};
inline int f3(int a, int b) { return (a +  b);};
 
Seg<int> mn(n + 2,  f2  , (int) 1e9) ; 




