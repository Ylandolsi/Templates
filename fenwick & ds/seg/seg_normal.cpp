struct Node {
    int ans = 1e18 ;
    void  merge ( int b ){ ans = min ( ans , b ) ; }
    void pull(const Node &a, const Node &b) {
        ans = min ( a.ans  , b.ans ) ;
    }
};
template<typename Node >
struct SegmentTree {
    
    int n; 
    Node neutral ; 
    vector<int> a ;
    vector<Node> st;

    SegmentTree(int _n) : n(_n), a(n), st(4*n) {}
    SegmentTree(vector<int>& aa ) : n((int)aa.size()), a(aa), st(4*(int)aa.size()) {
        build(1, 0, n-1);
    }
    void build(int p, int ns ,  int ne ) {
        if (ns == ne) {
            st[p] =  a[ns]  ;
            return;
        }
        int m = (ns + ne) / 2;
        build(2*p, ns , m );
        build(2*p+1, m+1, ne);
        st[p].pull(st[2*p], st[2*p+1]);
    }

    Node query(int p, int i, int j , int ns,  int ne ) {
        if (i > ne || j < ns) return neutral;
        if (ns >= i && ne <= j)
            return st[p];
        int m = (ns+ ne) / 2;
        Node ret, ls = query(2*p, i, j , ns , m ), rs = query(2*p+1, i, j , m+1, ne );
        ret.pull(ls, rs);
        return ret;
    }
    int query(int i, int j) {
        return query(1, i, j , 0 ,  n -1 ).ans;
    }
    void set(int p, int POS  ,  int val , int ns , int ne ) {
        if ( ns == ne ){
            st[p].ans = val ; 
            return ; 
        }
        int m = (ns + ne) / 2;
        if  (POS <= m ) set(2*p, POS,  val, ns , m );
        else set(2*p+1,POS,  val , m+1 , ne );
        st[p].pull(st[2*p], st[2*p+1]);
    }

    void set(int i, int val) {
        set(1, i,  val , 0 , n- 1 );
    }
    void update(int p, int POS  ,  int val , int ns , int ne ) {
        if ( ns == ne ){
            st[p].ans+= val  ; 
            return ; 
        }
        int m = (ns + ne) / 2;
        if  (POS <= m ) update(2*p, POS,  val, ns , m );
        else update(2*p+1,POS,  val , m+1 , ne );
        st[p].pull(st[2*p], st[2*p+1]);
    }

    void update(int i, int val) {
        update(1, i,  val , 0 , n- 1 );
    }


    // get rem-th element 
    int walk(int id = 1 , int ns = 0 , int ne = n -1  , int rem){
        if (ns == ne) return ns;
        int mid = ns + (ne - ns) / 2;
        int lc = 2 * id;
        int rc = lc + 1;
        if (st[lc].ans >= rem) return walk(lc, ns, mid, rem);
        return walk(rc, mid + 1, ne, rem - st[lc].ans);
    }
  


    int getFirstOnCondition(int qs, int qe, int dir, int id, int ns, int ne, int k) {
        if (qs > ne || qe < ns) return -1;
        if (qs <= ns && qe >= ne) {
            // check condition on interval
        }
        if (ns == ne) {
            return ns;
        }
        int p;
        int l = 2 * id ;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        if (dir == 0)
            p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        else
            p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
        if (p == -1) {
            if (dir == 0)
                p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
            else
                p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        }
        st[id].pull(st[l], st[r]);
        return p;
    }
    int getFirstOnCondition(int qs, int qe, int dir, const int v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1 && dir >= 0 && dir <= 1);
        return getFirstOnCondition(qs, qe, dir, 1, 0, n - 1, v);
    }

    // this is only for last value && condition must be applied for everlement before  :
    // this is when the condition should applied on all the segment from [0 , j ] 
    //  for exp : 
    // find the last position such a[ind] >= K && before that it never exist a[d] < K  
    // then for every element in [ 0, ind ] should also satisfy this !
    // before going to right node ! we check if the left node satisfy the condition or no  
    // this works only when starting checking from the first index 
    // but if we want to ignore some position we put its value to ( +- inf )
    // https://codeforces.com/contest/1611/submission/285542329 ( editorial does the same )
    // BUTTTT !
    // We can change it into getfirst on not satisfying the condition: 
    // same idea : https://codeforces.com/contest/1611/submission/285545444
    int getLastOnCondition(int id = 1 , int ns = 0, int ne = n -1  , int k) {
        // ns = 0 , ne = n-1 always we cant change them ! 
        if (ns == ne ) {
            if (st[id].ans2 - x  >=  -k ) return ns;
            else return -1; 
        }
    
        int p = -1 ;
        int l = 2 * id ;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        if (  (st[l].ans2  - x  >= -k) ) p = getFirstOnCondition(r, md + 1, ne, k);
        if (p == -1) {
            p = getFirstOnCondition(l, ns, md, k);
        }
        st[id].pull(st[l], st[r]);
        return p;
    }

};