#include <bits/stdc++.h>
using namespace std ; 
#define int long long
#define REP(i , d , fn ) for (int i = d ; i <=  fn  ;i++)


void Set_IO();
const int INF = 2e18 ; 
struct Matrix {
        int n, m;
        vector <vector <int>> mat;
        Matrix() {}
        Matrix(int _n, int _m) {
                n = _n, m = _m;
                //INF
                mat = vector <vector <int>> (n, vector <int> (m , INF ));
        }
        Matrix(vector< vector<int> > v) { n = (int)v.size(); m = n ? (int)v[0].size() : 0; mat = v; }
        inline Matrix operator * ( const Matrix & b ){
            int r1= m , c1 = n ; 
            int r2= b.m , c2 = b.n ; 
            Matrix res(c1 , r2 ); 
            for ( int i = 0 ; i < c1 ; i++ ){
                for  (int k = 0 ; k <r2 ; k++ ){
                    for ( int j = 0 ; j < r1 ; j++ ) {
                        // Dif merge 
                        res.mat[i][k]  =  min ( res.mat[i][k] , mat[i][j] +  b.mat[j][k] )  ; 
                    }
                }
            }
            return res ; 
        }

        inline Matrix operator ^ ( int e  ){
                assert( n == m ); 
                Matrix unit ( n ,n );  
                Matrix Rs = mat; 
                for ( int i = 0 ; i < n ; i++ )
                    unit.mat[i][i] = 0 ; 
                
                while ( e ){
                    if ( e& 1 ) unit = unit * Rs   ;  
                    Rs = Rs * Rs   ; 
                    e >>= 1 ;
                }
                return unit ; 
        }
};

void solve(){
    int n , m , k    ; 
    cin >>n >> m >> k   ;    
    // Set to Inf first !
    vector  ok ( n ,  vector<int>( n  , INF  ) )  ;
    REP (  i , 0 , m -1 ){
        int u, v , c ; 
        cin >> u >> v >>c ; 
        u-- , v-- ;  
        ok[u][v] = c ; 
    } 
    Matrix exp = ok ; exp = exp ^ k ; 
    int ans = INF ; 
    REP (i , 0 , n - 1 ) REP ( j , 0 ,  n-1 ) ans = min( ans, exp.mat[i][j]); 
    // fif ( ans != INF ) doesnt work 
    if ( ans > 1e18) cout << "IMPOSSIBLE\n";
    else cout << ans << "\n"; 


}


signed main() {
    Set_IO();
    int t = 1;
    while (t-- ) solve (); 
}

void Set_IO(){
    cin.tie(0)->sync_with_stdio(0) ;
    #ifndef ONLINE_JUDGE 
    freopen("inp.txt", "r", stdin); freopen("out.txt", "w", stdout); freopen("err.txt", "w", stderr); 
    #endif
    cout << fixed << setprecision(14) ; 

}