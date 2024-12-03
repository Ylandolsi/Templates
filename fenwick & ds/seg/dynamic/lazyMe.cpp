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
// #define int long long
typedef pair<int , int > pi ; typedef vector<int> vi ; 
#define all(x) begin(x), end(x) 
#define REP(i , d , fn ) for (int i = d ; i <=  fn  ;i++)
#define PER(i , d , fn ) for (int i = d ; i >=  fn  ;i--)
void Set_IO();



const int N = 2e5 + 50   ; 
const int MAX =N * 50 ;


struct Node {
    int occ , valeur  ;
    int lazy ;
    bool islazy ;  
    Node ( int o = 0 ,int  val = 0 , int lz = 0 , bool islz= 0 ){
        occ = o , valeur = val;  
        islazy = islz , lazy = lz ;

    }
    void  merge (Node  a , Node  b ){
        valeur = a.valeur  + b.valeur ;
        // occ = a.occ + b.occ ; 
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
int currentime ; 


template <typename NODE>
struct  DynamicSeg
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


    void Propagate (int p, int val, int l, int r) {
        st[p].applyLazy (val , l, r ) ;
        st[p].CombineLazy(val); 
        
    }


    void push(int p, int l, int r) {
        if (st[p].islazy) {
            if (l != r) {
                int m = (l + r) / 2;
                Propagate (pl[p], st[p].lazy, l, m);
                Propagate (pr[p], st[p].lazy, m+1, r);
            }
            st[p].islazy = 0;
            st[p].lazy = 0 ; 
        }
    }


    // l ,r always fixed !! 


    NODE query(int p, int l, int r, int i, int j) {

        if (i > r || j < l || i > j )
            return NODE();
        if (i <= l && r <= j)
            return st[p];
        push(p, l, r);
        int m = (l + r) / 2;
        Node ret ; 
        ret.merge( query (pl[p], l, m, i, j) , query(pr[p], m+1, r, i, j) ) ;
/*
    Faster !
        Node ret ; 
        if ( m >= i)  ret.valeur += query (pl[p], l, m, i, j).valeur ; 
        if ( m < j )  ret.valeur += query(pr[p], m+1, r, i, j).valeur ; 

*/
        return ret ; 
    }

    // l ,r always fixed !! 
    void LazyUpdate(int p, int l, int r, int i, int j, int val) {
        if (i > r || j < l)
            return ; 
        if (i <= l && r <= j){
            Propagate (p, val, l, r);
            return ; 
        }

        if ( pl[p] ==  0) pl[p] = addnode();
        if ( pr[p] ==  0) pr[p] = addnode();

        push(p, l, r);
        int m = (l + r) / 2;

        LazyUpdate(pl[p], l, m, i, j, val ); 
        LazyUpdate(pr[p], m+1, r, i, j, val);

        st[p].merge( st[pl[p]], st[pr[p]] ) ;
    }


    void update(int p, int l, int r, int idx, int val) {
        if (l == r){
            st[p].valeur +=  val ;   // UPDATE NOT SET ( MAKE SURE !! )
            return ; 
        }
        push(p , l ,r ) ; 
        int m = (l + r) / 2;

        if ( pl[p] ==  0) pl[p] = addnode();
        if ( pr[p] ==  0) pr[p] = addnode();

        if (idx <= m)  update( pl[p] , l , m , idx , val ); 
        else  update( pr[p] , m+1 , r , idx , val ); 
            
        st[p].merge( st[pl[p]], st[pr[p]] )  ; 
    }








};


DynamicSeg<Node> sg ;

void solve(){
    const int left = 0 , right = 1e9 + 7   ; 
    // dont u ever use left < 0 , if u need negative values shift all of them to positve !

    sg.init(); 
    int n ; 
    cin >> n; 
    int q; cin >> q; 
    vector<int>a(n + 1);
    int root = sg.addnode(); 
    for (int i = 1; i <= n; i++) {
        int  x; cin >> x; a[i] = x;
        sg.update(root , left , right, x, 1);
    }
    for (int i = 1; i <= q; i++) {
        char c; cin >> c;
        if (c == '!') {
            int x, y; cin >> x >> y;
            sg.update(root , left ,  right, a[x], -1);
            a[x] = y;
            sg.update(root , left ,  right, a[x], +1);

        }
        else {
            int l, r; cin >> l >> r;
            cout << sg.query(root, left, right, 1 , r).valeur -  sg.query(root, left, right, 1 , l-1).valeur << endl;
        }
    }

}


signed main() {
    Set_IO();
    int t = 1;
    while (t-- ) solve (); 
}

void Set_IO(){
    cin.tie(0)->sync_with_stdio(0) ;
    #ifndef ONLINE_JUDGE 
    freopen("inp.txt", "r", stdin); 
    // freopen("out.txt", "w", stdout); freopen("err.txt", "w", stderr); 
    #endif
    cout << fixed << setprecision(14) ; 

}