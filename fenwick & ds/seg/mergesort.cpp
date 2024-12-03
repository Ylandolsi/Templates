// find first on condition mg tree ! https://codeforces.com/contest/1997/submission/274135703



// code inspired by this 
// https://codeforces.com/contest/1997/submission/273771441
struct SegTree {
    vector<vector<int>> tree;
    int p, k;
    int n , neutral = 0;;
    void build(const vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].push_back( arr[tl]) ;
            return ; 
        } 
        int tm = (tl + tr) / 2;
        int L = v*2+1 , R = v*2+2 ; 
        build(arr, L, tl, tm);
        build(arr, R , tm+1, tr);
        int i = 0 , j = 0 ; 
        tree[v].resize(tree[L].size() + tree[R].size());
        merge(  begin(tree[L]) , end(tree[L])  ,  begin(tree[R]) , end(tree[R]) , tree[v].begin());
    }

    // find how many elements <= val in  range [qs , qe ]
    int query(int qs, int qe, int id, int ns, int ne , int val ) {
        if (qs > ne || qe < ns) return neutral;
        if (qs <= ns && ne <= qe ) {
            int lo = upper_bound(tree[id].begin(), tree[id].end(),val) -tree[id].begin();
            return lo;
        }
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        int res;

        if ( qs >  md ) return query(qs, qe, r, md + 1, ne,val);
        if ( qe <= md ) return query(qs, qe, l, ns, md,val) ;  
        
        int rl = query(qs, qe, l, ns, md,val);
        int rr = query(qs, qe, r, md + 1, ne,val);
        res = (rl+ rr);
            
        
        return res;
    }

    // we are sarching For the-cnt element in Range [ qs , qe ] thats <= val
    int __query_k_th(int qs, int qe, int id, int ns, int ne , int val ,  int cnt )  {
        if (ns == ne) return ne; // return index 
    
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        int res;
    
        if (qs > md) return __query_k_th(qs, qe, r, md +1 , ne , val , cnt);
        if (qe <= md) return __query_k_th(qs, qe, l, ns , md , val , cnt);
    
        int ql = query( qs  , qe  , l , ns , md  , val);
        if (ql >= cnt) return __query_k_th(qs, qe, l, ns , md , val , cnt);
        return __query_k_th(qs, qe, r, md +1 , ne , val , cnt - ql );
    }
    SegTree(int _n) {
        n = _n;
        tree.resize(4 * n);
    }
    void build(const vector<int> &arr) {
        build(arr, 0, 0, n - 1);
    }

    
    int query(int qs, int qe , int val ) {
        return query(qs, qe, 0, 0, n - 1 , val );
    }
    //  approximatly (2.2 seconds pass for n= 2e5 ) 
    // get kth element <= Val between L, R  
    int find_kth ( int l , int r ,    int val , int k ){
        return __query_k_th(l , r , 0 , 0 , n-1 , val , k ) ; 
    }

    int find_kth_sorted ( int l , int r ,  int k ){
        // given [ l , r] return k-th element  (sorted) ( k = 1 indexed ! )
        // 1 2 3 4 5 6 7  k = 3 return 3
        // https://www.youtube.com/watch?v=0F3C2L5v_YA
        // https://ideone.com/ORR0Jq
        int low = -1e9 -1 , high= 1e9 + 1 ; 
        while ( low +1  < high ){
            int md = low + (high- low )/2 ;
            int ch = query(l , r  , md  ) ;
            if ( ch < k  ) low = md ;
            else high = md ;  
        }
        return low + 1  ; 
    }

    void update(int   id ,int  qs , int qe, int index ,int  oldvalue ,int  newvalue )
    {
        // vector<multiset<>> or vector of pdbds 
        if(index<qs or qe<index)  return;
        if(qe==index and qe==index)
        {
            mst[id].erase(mst[id].find({oldvalue,index}));
            mst[id].insert({newvalue,index});
            return;
        }
        int  mid=(qs+qe)/2;
        int l = 2 * id + 1;
        int r = l + 1;
        update( l  , qe , mid , index , oldvalue , newvalue );
        update( r , mid+1 , qs , index , oldvalue , newvalue );
        mst[id].erase(mst[id].find({oldvalue,index}));
        mst[id].insert({newvalue,index});
    }
};



    pi getFirstOnCondition(int qs, int qe, int dir, int id, int ns, int ne,int order,  int k  ) {
        if (qs > ne || qe < ns   ) return {-1,0};
        int vrif = 0; 
        auto bs = [&] (  int ID ) {
                int howmany = lower_bound(all(tree[ID]),k) - tree[ID].begin();
                return tree[ID].size() - howmany ; 
        }; 
        if (qs <= ns && qe >= ne) {
            int verified = bs(id);
            if  ( verified < order ) return {-1,verified} ; 
        }
        if (ns == ne) { return {ns,0}; }
        pi p;
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        
        p = getFirstOnCondition(qs, qe, dir, l, ns, md, order  , k  );
        if (p.first < 0) {
            pi ppp =   getFirstOnCondition(qs, qe, dir, r, md + 1, ne, order - p.second ,  k); 
            ppp.second += p.second ; 
            p = ppp; 
        }
        
        return p;
    }
template <typename M>
    pi getFirstOnCondition(int qs, int qe, int dir, int order ,  const M &v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1 && dir >= 0 && dir <= 1);
        return getFirstOnCondition(qs, qe, dir, 0, 0, n - 1, order ,  v ); 
    }