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
#define REP(i , d , fn ) for (int i = d ; i <=  fn  ;i++)
#define PER(i , d , fn ) for (int i = d ; i >=  fn  ;i--)
#define getunique(vt)  vt.erase(unique(all(vt)), vt.end()) // greater_equal -> multiset dec , greater set dec

void Set_IO();


void solve(){
    cout << "hello"; 
}


signed main() {
    Set_IO();
    int t = 1;
    cin >> t ; 
    while (t-- ) solve (); 
}

void Set_IO(){
    cin.tie(0)->sync_with_stdio(0) ;
    #ifndef ONLINE_JUDGE 
    freopen("inp.txt", "r", stdin); 
    freopen("out.txt", "w", stdout); freopen("err.txt", "w", stderr); 
    #endif
    cout << fixed << setprecision(14) ; 

}

/*
    - define upperbound for the ans 
    - SUFFICIENT & NECESSARY CONDITIONS !!! 

    - if the question about maximize try to minimize  !!!!!!!!!!!!!!!!
    
    - suppose ur ans only in [ 0 , i ] ( if u can move forward and backward !!!! )
    
    - If question looks unsolvable from front, try going from back.
        solve for (n) and do the same for solve(n-1) ....

    - Maybe the solution is based on a pattern ? 
    
    - Try to write it as a DP formula ( especialy if its a Math equation or something similar ) 
    
    - Presistent seg if u are working on queries that Depends on a condition on the  Values 
    
    - Consider sqrt tricks ! 

    - All Problems Are easy To Solve : 
        if U are balancing between multiples moves => u are doing something wrong ! 
        make it as simple as possible  
    ** Everything is solvable by binary search

    ** The ones which are not, is solvable by dp

    ** Store Indicies of Each Element , then loop over them , maybe it becomes easier ! 
    
*/