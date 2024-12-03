// the other tempalte is faster  a little bit !




const int N = 4e5 ; 
const int MAX =N * 40 ;


struct Node {
    int occ , valeur  ;
    int lazy ;
    bool islazy ;  
    Node ( int o = 0 ,int  val = 0 , int lz = 0 , bool islz= 0 ){
        occ = o , valeur = val;  
        islazy = islz , lazy = lz ;

    }

    void  merge (Node & a , Node &   b ){
        valeur = a.valeur  + b.valeur ;
        // occ = a.occ + b.occ ; 
    }

    void Add ( Node & previous , int newVal ){
        valeur = previous.valeur + newVal ; 
        // occ = previous.occ + 1 ; 
    }

    void Set ( int newval ){
        valeur = newval ; 
    }

    void applyLazy ( int Laz , int  l , int r ){
        valeur = valeur + Laz * (r-l +1 ); 
    }
    void CombineLazy ( int val ){
        islazy |= 1 ;
        lazy += val; 
    }

};
Node st[MAX] ;   // n * log * 4
int  pl[MAX], pr[MAX]; // N * log * 4 
int roots[N]; // generalyu N *4 is sufficent  
int currentime ; 


template <typename NODE>
struct  PresLazy
{
    int id; 
    void init(){
        id = 1  ; 
    }    
    int addnode(){
        int p = id++;
        pl[p] = pr[p] = 0; // 0 means dosent exist ! 
        return p;
    }
    int newLeaf(int pos  , int vl ) {
        int newid = addnode();
        st[newid].Add( st[pos] , vl );  // UPDATE NOT SET ( MAKE SURE !! )
        return newid; 
    }

    int newParent(int a, int b) {
        int p = id++;
        pl[p] = a;
        pr[p] = b;
        st[p].merge(st[a], st[b]) ;
        return p;
    }

    int Propagate (int old, int val, int l, int r) {
        int p = id++;
        pl[p] = pl[old];
        pr[p] = pr[old];
        st[p] = st[old] ;
        st[p].applyLazy (val , l, r ) ;
        st[p].CombineLazy(val); 
        return p;
    }


    void push(int p, int l, int r) {
        if (st[p].islazy) {
            if (l != r) {
                int m = (l + r) / 2;
                pl[p] = Propagate (pl[p], st[p].lazy, l, m);
                pr[p] = Propagate (pr[p], st[p].lazy, m+1, r);
            }
            st[p].islazy = 0;
            st[p].lazy = 0 ; 
        }
    }

    /*int build(vi &a , int l, int r) {
        if (l == r)
            return newLeaf(a[l]);
        int m = (l + r) / 2;
        return newParent(build(a, l, m), build(a, m+1, r));
    }*/
    

    // l ,r always fixed !! 
    NODE query(int p, int l, int r, int i, int j) {
        if (i > r || j < l)
            return NODE();
        if (i <= l && r <= j)
            return st[p];
        push(p, l, r);
        int m = (l + r) / 2;
        Node ret ; 
        ret.merge( query (pl[p], l, m, i, j) , query(pr[p], m+1, r, i, j) ) ;
        return ret ; 
    }

    // l ,r always fixed !! 
    int LazyUpdate(int p, int l, int r, int i, int j, int val) {
        if (i > r || j < l)
            return p;
        if (i <= l && r <= j)
            return Propagate (p, val, l, r);
        push(p, l, r);
        int m = (l + r) / 2;
        return newParent(LazyUpdate(pl[p], l, m, i, j, val), LazyUpdate(pr[p], m+1, r, i, j, val));
    }

    // l ,r always fixed !! 
    int update(int p, int l, int r, int idx, int val) {
        if (l == r)
            return newLeaf(p, val );  // UPDATE NOT SET ( MAKE SURE !! )
        push(p , l ,r ) ; 
        int m = (l + r) / 2;
        if (idx <= m)
            return newParent(update(pl[p], l, m, idx, val), pr[p]);
        return newParent(pl[p], update(pr[p], m+1, r, idx, val));
    }
    int copy( int p , int l,  int r ){
        return newParent(pl[p],pr[p]);
    } 



    NODE getKth(int Ndleft, int NdRight, int k, int l, int r) { // 
   
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int lsum = st[pl[NdRight]].valeur - st[pl[Ndleft]].valeur ; 
        if (lsum >= k) 
            return getKth(pl[Ndleft], pl[NdRight]  , k, l, md);
        return getKth(pr[Ndleft],  pr[NdRight],   k - lsum, md + 1,r);
    }


    NODE getkthInPathTree(int ndu, int ndv, int ndlc, int vallc, int k, int l, int r) { // 
                    // ndu : root of u , ndv root of v , ndlc root of lca
                    // vallc value of lca ( used in check )
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int lsum = st[pl[ndu]].valeur + st[pl[ndv]].valeur -2 * st[pl[ndlc]].valeur + (vallc <= md);

        if (lsum >= k) 
            return getkthInPathTree(pl[ndu], pl[ndv]  , pl[ndlc] ,  vallc, k, l, md);
        
        return getkthInPathTree(pr[ndu],  pr[ndv],  pr[ndlc] , vallc, k - lsum, md + 1,r);
    }





};

// dont u ever use left < 0 , if u need negative values shift all of them to positve !



// PresLazy<Node> sg ;
// sg.init();
// roots[0] = 0 ; // intiilize 
// // roots[0] =sg.addnode(); optional  
// const int left = - INF , right = INF  ; 
// roots[0] =sg.update(roots[0] , left , right , i  ,a[i] ); 



/*
    we can represent roots[i] 
    as : ( after sorting the array )
        // roots[i] is the root for seg tree containing all 
        // elements that are a[j] <= a[i] and  j <= i
    


    we will update at pos i ++  , whenever it visited ! 

    and when we asked query
        We will Query ( roots[n]  , L , R ) - Query ( Roots[e] , L , R )   

    meaning
        give me the count of indexes such are between [L, R ] 
            and Are found in seg tree of roots[n] 
            

    exp : 
    https://ideone.com/m2exeG , https://www.spoj.com/problems/KQUERYO/

*/ 

/*

    we have a number X and loop over it divisors : 

        we can represent root[i] 
        storing all divisors of X that are <= i 

        we query root[R] - root[L-1] if we want to [L , R ] of range multples 

        https://ideone.com/SKzhPv
        https://codeforces.com/group/HcnH7vLzrr/contest/562768/problem/C2
*/ 
