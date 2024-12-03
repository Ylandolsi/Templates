
// https://ideone.com/53bZDT 
// https://www.spoj.com/problems/TTM/
#include <bits/stdc++.h>
using namespace std ; 
#ifndef ONLINE_JUDGE
#include "./debugger.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif
template<typename... T>void read(T&... args) {((cin >> args), ...);}
template<typename... T>void print(T&&... args) {((cout << args ), ...);}
#define int long long
typedef pair<int , int > pi ; typedef vector<int> vi ; 
#define all(x) begin(x), end(x) 
#define f(i , d , fn ) for (int i = d ; i <=  fn  ;i++)
#define ff(i , d , fn ) for (int i = d ; i >=  fn  ;i--)
void Set_IO();
int ansquer ; 




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

    void  merge (Node a , Node  b ){
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



    int getkth(int lnd, int rnd, int k, int l, int r) {
        if (l == r) {
            int locc = st[rnd].occ - st[lnd].occ;
            if ( locc && k > 0  ){
                if ( k &1 ) ansquer ^= l ; 
            } 
            return l;
        }
        push( p , l , r ); 
        int locc = st[pl[rnd]].occ - st[pl[lnd]].occ;
        int md = l + (r - l) / 2;
        if (locc >= k) {
            return getkth(pl[lnd], pl[rnd], k, l, md);
        }
        ansquer ^= st[pl[rnd]].valeur ^ st[pl[lnd]].valeur;
        return getkth(pr[lnd], pr[rnd], k - locc, md + 1, r);
    }


    int getkthInPathTree(int ndu, int ndv, int ndlc , int parlcand  ,   int k, int l, int r) {
        // l , r always fixed ! ( boundaries of our seg tree !!!)
        // ndu : root of u , ndv root of v , ndlc root of lca , parclnd root of par lca :
     
        if (l == r) {
            return l;
        }
 
        int md = l + (r - l) / 2;
        int lsum = st[pl[ndu]].valeur + st[pl[ndv]].valeur - st[pl[ndlc]].valeur  -st[pl[parlcand]].valeur ;

        if (lsum >= k) {
            return getkth(pl[ndu], pl[ndv], pl[ndlc], pl[parlcand] ,  k, l, md);
        }
        return getkth(pr[ndu], pr[ndv], pr[ndlc] ,  pr[parlcand] ,  k - lsum, md + 1, r);
    }





};
PresLazy<Node> sg ;


const int INF = 2e9  ;
void solve(){
    int n, m ; 
    read ( n, m ) ; 
    vi a(n+1);
    sg.init();
    roots[0] = 0 ; // intiilize 
    // roots[0] =sg.addnode(); optional  
    const int left = - INF , right = INF  ; 
    for ( int i = 1 ; i <= n ; i++ ){
        cin >> a[i];
        roots[0] =sg.update(roots[0] , left , right , i  ,a[i] ); 
    
    }
    currentime = 0 ; 

    for  (int i = 1 ; i  <= m ; i++ ){
        char op ; 
        read(op);
        if ( op =='Q'){
            int l , r; 
            read( l , r) ; 
            cout << sg.query(roots[currentime] , left , right , l , r ).valeur << endl; 
        }
        else if ( op =='C'){
            int l , r , d ;
            read( l , r  , d); 
            roots[currentime +1 ]= sg.LazyUpdate(roots[currentime ] , left , right , l ,r  , d );
            currentime++ ; 
        }
        else if (op == 'B'){
            int t ; 
            cin >> t; 
            currentime =t; 
        }
        else if ( op == 'H'){
            int l , r   , t ; 
            read( l , r , t ) ; 
            cout << sg.query(roots[t] , left , right , l , r ).valeur << endl; 

        }
    }

}


signed main() {
    Set_IO();
    int t = 1;
    for ( int TT  = 1 ; TT  <= t ; TT ++ ) { 
        cerr <<"start test_case " << TT << endl ;
        solve (); 
        cerr << "end test \n" ; 
    }    
}

void Set_IO(){
    cin.tie(0)->sync_with_stdio(0) ;  
    #ifndef ONLINE_JUDGE 
    freopen("inp.txt", "r", stdin); freopen("out.txt", "w", stdout); freopen("err.txt", "w", stderr); 
    #endif
    cout << fixed << setprecision(14) ; 

}