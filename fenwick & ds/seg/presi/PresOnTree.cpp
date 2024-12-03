
// https://www.spoj.com/problems/COT/
#include <bits/stdc++.h>
using namespace std ; 
#pragma GCC optimize("O3,unroll-loops","inline","-ffast-math")
#pragma GCC target("sse", "sse2", "sse3", "ssse3", "sse4")
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#define int long long 
typedef vector<int> vi ; 
void Set_IO();
#define ll long long 

const int N = 2e5 + 10  , MAX =N * 40 , LOG = 20 ; 
ll n , q ,  a[N]  ,  parents[N] , depth[N],  node2ind[N] ,   spt[N][LOG] ,  lg[N];
vector<int>adj[N] , ind2node ; 

//(o1) lca 
struct processLca{
    void process(){
        dfs2(1); 
        buildspt();
    }
    void dfs2(int u, int dpth=0, int p=0){
        parents[u] = p ; 
        node2ind[u] = (int) ind2node.size();
        depth[u]=dpth;
        ind2node.push_back(u);
        for(int v:adj[u]){
            if(v==p)
                continue;
            dfs2(v, dpth+1, u);
            ind2node.push_back(u);
        }
    }

    void buildspt(){
        lg[0]=-1;
        for(int i=0;i<ind2node.size();i++){
            spt[i][0]=i;
            lg[i+1]= lg[i]+ !(i&i+1);
        }
        for(int j=1;(1<<j)<=ind2node.size();j++){
            for(int i=0;i+(1<<j)<=ind2node.size();i++){
                int a = spt[i][j-1];
                int b = spt[i+(1<<(j-1))][j-1];
                spt[i][j] = (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
            }
        }
    }

    int SPTMQ(int a , int b){
        int sz = b-a+1;
        int l = lg[sz];
        a = spt[a][l];
        b = spt[b-(1<<l)+1][l];
        return (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
    }

    int getLCA(int u , int v){
        int a = node2ind[u];
        int b = node2ind[v];
        if(a>b)
            swap(a,b);
        return ind2node[SPTMQ(a,b)];
    }
};



struct Node {
    int  valeur  ;
    Node ( int o = 0 ,int  val = 0 ){
        valeur = val;  
    }

    void  merge (Node  & a , Node  &  b ){
        valeur = a.valeur  + b.valeur ;
    }

    void Add ( Node & previous , int newVal ){
        valeur = previous.valeur + newVal ; 
    }

    void Set ( int newval ){
        valeur = newval ; 
    }


};
Node st[MAX] ;   // n * log * 4
int  pl[MAX], pr[MAX]; // N * log * 4 
int roots[N]; // generalyu N *4 is sufficent  

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
    NODE query(int p, int l, int r, int i, int j) {
        if (i > r || j < l)
            return NODE();
        if (i <= l && r <= j)
            return st[p];
        int m = (l + r) / 2;
        Node ret ; 
        ret.merge( query (pl[p], l, m, i, j) , query(pr[p], m+1, r, i, j) ) ;
        return ret ; 
    }

    int update(int p, int l, int r, int idx, int val) {
        if (l == r)
            return newLeaf(p, val ); 
        int m = (l + r) / 2;
        if (idx <= m)
            return newParent(update(pl[p], l, m, idx, val), pr[p]);
        return newParent(pl[p], update(pr[p], m+1, r, idx, val));
    }

    int getkthInPathTree(ll ndu, ll ndv, ll ndlc , ll parlcand  ,   int k, int l, int r) {
        // l , r always fixed ! ( boundaries of our seg tree !!!)
        // ndu : root of u , ndv root of v , ndlc root of lca , parclnd root of par lca :
        if (l == r) 
            return l;
        ll md = l + (r - l) / 2;
        ll lsum = st[pl[ndu]].valeur + st[pl[ndv]].valeur - st[pl[ndlc]].valeur  -st[pl[parlcand]].valeur ;

        if (lsum >= k) {
            return getkthInPathTree(pl[ndu], pl[ndv], pl[ndlc], pl[parlcand] ,  k, l, md);
        }
        return getkthInPathTree(pr[ndu], pr[ndv], pr[ndlc] ,  pr[parlcand] ,  k - lsum, md + 1, r);
    }




};
PresLazy<Node> sg ;


void solve(){
    cin >> n >> q;  
    for ( int i =  1 ; i <= n ; i++ ) cin >>a[i]; 
    for ( int i = 2 ; i <= n  ; i++ ) {
        int u , v ; 
        cin >> u >> v;  
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    processLca LCA ; 
    LCA.process();

    sg.init();
    const   long long   left = INT_MIN  , right = INT_MAX ; 

    roots[0] =sg.addnode();
    auto dfs = [&]( auto &&dfs ,int u , int p )-> void {
        roots[u] = sg.update(roots[p] , left , right , a[u] , 1  ) ; 
        for ( auto &d : adj[u] ){
            if ( d != p) dfs ( dfs , d , u ); 
        }
    };

    dfs ( dfs , 1 , 0 ) ;
    while ( q-- )
    {
        int  u , v , k ; 
        cin >> u >>v >> k; 
        int lc = LCA.getLCA( u ,v ); 
        int Parentof_LCA = parents[lc] ;
        cout <<sg.getkthInPathTree(roots[u] , roots[v] , roots[lc] , roots[Parentof_LCA] , k  , left, right )  + 1  << endl ; 
    }
}


signed main() {
    cin.tie(0)->sync_with_stdio(0) ;  
    int t = 1;
    for ( int TT  = 1 ; TT  <= t ; TT ++ ) solve (); 
   
}
