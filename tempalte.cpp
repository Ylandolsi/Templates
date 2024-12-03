#include <bits/stdc++.h>
using namespace std ; 
#ifndef ONLINE_JUDGE
#include "debugger.cpp"
#else
#pragma GCC optimize("O3,unroll-loops","inline","-ffast-math")
#pragma GCC target("sse", "sse2", "sse3", "ssse3", "sse4")
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#define debug(...)
#define debugArr(...)
#define show(...)
#endif
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
typedef long long ll ; 
struct chash {
    static unsigned hash32(unsigned x) {
        // https://groups.google.com/g/prng/c/VFjdFmbMgZI
        x += 0x9e3779b9;
        x = (x ^ (x >> 16)) * 0x85ebca6b;
        x = (x ^ (x >> 13)) * 0xc2b2ae35;
        return x ^ (x >> 16);
    }
 
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    template<typename T>
    uint64_t operator()(T x) const {
        static const uint64_t FIXED_RANDOM = splitmix64(chrono::steady_clock::now().time_since_epoch().count() );
        return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM)) : splitmix64(x ^ FIXED_RANDOM);
    }
};
template<typename P, typename Q> using gphash = gp_hash_table<P, Q, chash>;
template<typename P, typename Q> using umap = unordered_map<P, Q, chash>;
template<typename T, typename Cmp = less<T>> // greater
using iset = tree<T, null_type, Cmp, rb_tree_tag,
		  tree_order_statistics_node_update, allocator<T>>;

template<typename... T>void read(T&... args) {((cin >> args), ...);}
template<typename... T>void print(T&&... args) {((cout << args ), ...);}
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

template<typename T> T ceil(T x, T y){return (x >= 0 ? (x + y - 1) / y : x / y);}
template<typename T> T floor(T x, T y){return x / y - ((x ^ y) < 0 and x % y);}

template<class T , class V > bool ckmax(T& a, const V& b){return a < b ? a = b, 1 : 0;}
template<class T , class V > bool ckmin(T& a, const V& b){return a > b ? a = b, 1 : 0;}
#define pb push_back
#define int long long  
typedef array<int, 2> pi ; typedef vector<int> vi ; 
#define len(v) (int)v.size()
#define f(i , d , fn ) for (int i = d ; i <=  fn  ;i++)
#define ff(i , d , fn ) for (int i = d ; i >=  fn  ;i--)

#define all(x) x.begin(), x.end() 
#define getunique(vt)  vt.erase(unique(all(vt)), vt.end()) // greater_equal -> multiset dec , greater set dec
const long double pi_ = atan2(0, -1) , eps = 1e-9; 


void YES(bool x) { if (x) cout << ("Yes\n"); else cout << ("No\n"); }
void input_output();

void solve(){
    

}
    

int32_t main() {
    input_output();
    int t = 1;
    cin >> t;
    for ( int i = 1 ; i <= t ; i++ ){
        show("------- Case " , i, "------- : \n" );
        solve();
        show("\n---------------------- .\n \n "); 
    }     
    double Time_elapsed= 1.0 * clock() / CLOCKS_PER_SEC ; 
    debug(Time_elapsed);
        
}


void input_output() {
    cout.tie(0), cin.tie(0), ios_base::sync_with_stdio(0) ;  
    cout << fixed << setprecision(14) ; 
    cerr << fixed << setprecision(14) ; 
    #ifndef ONLINE_JUDGE 
    freopen("inp.txt", "r", stdin); freopen("out.txt", "w", stdout); freopen("err.txt", "w", stderr); 
    #endif
}



