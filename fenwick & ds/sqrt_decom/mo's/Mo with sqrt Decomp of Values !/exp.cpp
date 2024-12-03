
// https://codeforces.com/group/YTYmnVxV00/contest/568776/problem/F
#include <bits/stdc++.h>
using namespace std ; 
#ifndef ONLINE_JUDGE
#include "./debugger.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif
#define all(x) begin(x), end(x) 
#define REP(i , d , fn ) for (int i = d ; i <=  fn  ;i++)
#define PER(i , d , fn ) for (int i = d ; i >=  fn  ;i--)
void Set_IO();

/*
    Idea : 
            For the values in current Mo interval 
            we need the xor of the first K elements 
            we cant loop over all K ! 

            so we Dvided K into SQRT PARTS !

            the Part remaining we will loop over them 


            OccofVal[i] means occurence of val i in [L , R ] of current mo's 

            xorOFvals[s] means Xorofval ( val in this range [s*sqrt , (s+1) * sqrt ]) 
                    in [L , R ] of current Mo's 

*/

const int N = 1e5 + 5 ;
const int sqr = 350;

int OccofVal[N]; 

int XorofvalsinthsBLock[sqr] ;
int OccsOfallValuesinThisBlock[sqr]; 

struct Compressor {
    vector<int> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(int x) { values.push_back(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(int x) { return lower_bound(all(values), x) - values.begin(); }
    int decompress(int p) { return values[p]; }
} compressor;



struct Query {
    int l, r, k , sidx;
    Query( int l_  = 0 , int r_ = 0 , int k_ = 0 ,  int  sidx_ = 0 ){ 
        l = l_ , r = r_ , k = k_ , sidx = sidx_ ; 
    }
    bool operator <(Query b) const{
        if(l / sqr != b.l / sqr)
            return l / sqr < b.l / sqr;
        return l / sqr % 2 ? r < b.r : r > b.r;
    }
};
int ans[N] ; 
int a[N], aComp[N] ; 

void solve(){
    int n , q ; 
    cin >> n >> q ;
    REP ( i, 1 , n ) cin >>a[i] , compressor.add(a[i]);
    compressor.run();
    REP(  i , 1 , n ) aComp[i]= compressor.compress(a[i]); 
    int currentk ; 

    auto getIdBlockSq = [&]( int e ){return e / sqr  ; }; 
    auto add = [&](int x) {
        x = aComp[x]; 
        int id = getIdBlockSq(x);
        XorofvalsinthsBLock[id] ^= compressor.decompress(x) ; 
        OccsOfallValuesinThisBlock[id]++ ; 

        OccofVal[x]++ ; 
    };
    auto del = [&](int x) {
        x = aComp[x]; 
        int id = getIdBlockSq(x);
        XorofvalsinthsBLock[id] ^= compressor.decompress(x) ; 
        OccsOfallValuesinThisBlock[id]-- ; 
        
        OccofVal[x]-- ;
    };

    auto getans =[&](){
        int ans = 0 ; 
        // loop over the sqrts till  sqrt *x <= K
        int id = 0 ;
        int already = 0 ;  
        while ( id < sqr && already + OccsOfallValuesinThisBlock[id] <= currentk ){
            already += OccsOfallValuesinThisBlock[id]; 
            ans ^= XorofvalsinthsBLock[id]; 
            id++ ; 
        }   

        id = id * sqr ; 
        while  (id < N && already <= currentk ){

            assert(already <= currentk) ; 
            if ( already == currentk ) break ; 
            int occofthis = OccofVal[id] ; 
            int ican = min (occofthis , currentk - already ); 
            if ( ican & 1 ) ans ^= compressor.decompress(id);
            already += ican ; 
            id++ ;
        }

        return ans ; 

    };

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r, k ;
        cin >> l >> r >> k ; 
        // --l; --r;
        queries[i] = {l, r, k, i};
    }


    sort(queries.begin(), queries.end());
    int cur_l = 1, cur_r = 0;


    for (Query &qr : queries) {
        currentk = qr.k ; 
        while (cur_l > qr.l) add(--cur_l);
        while (cur_r < qr.r) add(++cur_r);
        while (cur_l < qr.l) del(cur_l ) ,cur_l++ ; 
        while (cur_r > qr.r) del(cur_r ) ,cur_r-- ; 

        ans[qr.sidx] =getans();
    }

    REP ( i , 0 ,  q -1  ) cout << ans[i] <<"\n" ; 
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