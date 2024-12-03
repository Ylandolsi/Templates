/**

 * Verification: https://www.spoj.com/submit/HORRIBLE/id=33427567
 

    u can make it morea generic ! 
    https://atcoder.jp/contests/abc371/submissions/57779636


    walk on seg tree =:
        u can find ab3ad / a9rab element such a[i] > propriety or somehting 
        in interval [ l ,r  ]

    segment tree of diffirence array ?
    - answer for a[i] =  query (  0 , i ) 
    - add x to all element in range [l , r ]
    update (l ,+1 )
    update(r+1 , -1 ) ;
    
*/
struct Node {

    // ans is neutral !!! 

    int ans = 0, lazy = 0  ;
    bool islazy = 0 ; 

    // void leaf(int val) {
    //     ans += val;
    // }
    Node(int va = 0 ){ans = va  , lazy = 0 , islazy  = 0; }

    void pull(const Node &a, const Node &b) {
        ans = a.ans + b.ans;
    }

    void push(int val) {
        lazy += val;
        islazy = 1 ; 
    }

    void apply( int l , int r ) {
        ans += (r - l + 1) * lazy; 
        lazy = 0;
        islazy = 0 ; 
    }
};
    
template<typename Node  >
struct SegmentTree {


    int n; 
    Node neutral ; 
    vector<int> a ;
    vector<Node> st;
     

    SegmentTree(int _n) : n(_n), a(n), st(4*n) {
        build(1, 0, n-1);
    }

    SegmentTree(const vector<int> &_a) : n((int) _a.size()), a(_a), st(4*n) {
        build(1, 0, n-1);
    }

    void build(int p, int ns ,  int ne ) {
        if (ns == ne) {
            // st[p].leaf(a[ns]);
            st[p] = Node(a[ns]);
            return;
        }
        int m = (ns + ne) / 2;
        build(2*p, ns , m );
        build(2*p+1, m+1, ne);
        st[p].pull(st[2*p], st[2*p+1]);
    }

    void push(int p , int l , int r ) {
        if (st[p].islazy) {
            if ( l != r) {
                st[2*p].push(st[p].lazy);
                st[2*p+1].push(st[p].lazy);
            }
            st[p].apply( l, r );
        }
    }

    Node query(int p, int i, int j , int ns,  int ne ) {
        push(p ,ns, ne );

        if (i > ne || j < ns) {
            // return neutral;
            return Node();
        }
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

    void update(int p, int i, int j, int val , int ns , int ne ) {
        push(p,ns,ne);
        if (i > ne || j < ns) return ;

        if (ns >= i && ne <= j){
            st[p].push(val);
            push(p,ns,ne);
            return;
        }

        int m = (ns + ne) / 2;
        update(2*p, i, j, val, ns , m );
        update(2*p+1,i, j, val , m+1 , ne );
        st[p].pull(st[2*p], st[2*p+1]);
    }

    void update(int i, int j, int val) {
        update(1, i, j, val , 0 , n- 1 );
    }

    // get rem-th element 
    // or get max / min or whatever element
    //  
    int walk(int id = 1 , int ns = 0 , int ne = n -1  , int rem){
        push(id, ns, ne);
        if (ns == ne) return ns;
        int mid = ns + (ne - ns) / 2;
        int lc = 2 * id;
        int rc = lc + 1;
        if (st[lc].ans >= rem) return walk(lc, ns, mid, rem);
        return walk(rc, mid + 1, ne, rem - st[lc].ans);
    }
  


    int getFirstOnCondition(int qs, int qe, int dir, int id, int ns, int ne, int k) {
        push(id, ns, ne);
        if (qs > ne || qe < ns) return -1;
        if (qs <= ns && qe >= ne) {
            // check condition on interval
        }
        if (ns == ne) {
            return ns;
        }
        // push(id, ns, ne);
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
        push(id, ns, ne);

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










